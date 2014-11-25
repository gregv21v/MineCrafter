#version 330 core

struct LightProperties {
	bool isEnabled;
	bool isLocal;
	bool isSpot;
	vec3 ambient;
	vec3 color;
	vec3 position;
	vec3 halfVector;
	vec3 coneDirection;
	float spotCosCutoff;
	float spotExponent;
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
	float shininess;
	float strength;
};

// for shadow mapping
in VS_FS_INTERFACE
{
	vec4 shadow_coord;
	vec3 world_coord;
	vec3 eye_coord;
	vec3 normal;
} fragment;


// the set of lights to apply, per invocation of this shader
const int MaxLights = 2;
uniform LightProperties Lights[MaxLights];

//uniform float Shininess;
//uniform float Strength;
uniform vec3 EyeDirection;

// shadow mapping uniforms
uniform int shadowMappingEnabled;
uniform sampler2DShadow depth_texture;
uniform sampler2D tex;
uniform vec3 light_position;
uniform vec3 material_ambient;
uniform vec3 material_diffuse;
uniform vec3 material_specular;
uniform float material_specular_power;

in vec4 vertColor;
in vec3 vertNormal;
in vec4 vertPosition;

// texturing
in vec2 vertTexCoord;
flat in int vertIsTextured;

out vec4 fragColor;

void main()
{
	// Default Material Properties 
	//vec3 material_ambient = vec3(0.0, 0.0, 0.0);
	//vec3 material_diffuse = vec3(1.0, 1.0, 1.0);
	//vec3 material_specular = vec3(1.0, 1.0, 1.0);

	//------------------------------------------------------------\\
	//             			Shadow Mapping 					      \\
	//------------------------------------------------------------\\
	


	vec3 N = fragment.normal;
	vec3 L = normalize(light_position - fragment.world_coord);
	vec3 R = reflect(-L, N);
	vec3 E = normalize(fragment.eye_coord);
	//float NdotL = dot(N, L);
	//float EdotR = dot(-E, R);
	//float diffuse = max(NdotL, 0.0);
	//float specular = max(pow(EdotR, material_specular_power), 0.0);
	float f = textureProj(depth_texture, fragment.shadow_coord);
	//vec3 shadowColor = vec3(material_ambient + 
			//f * (material_diffuse * diffuse + material_specular * specular));
	//------------------------------------------------------------\\



	vec3 scatteredLight = vec3(0.0); // or, to a global ambient light
	vec3 reflectedLight = vec3(0.0);
	// loop over all the lights
	for (int light = 0; light < MaxLights; ++light) {
		if (! Lights[light].isEnabled) continue;
		vec3 halfVector;
		vec3 lightDirection = Lights[light].position;
		float attenuation = 1.0;
		// if local, compute per-fragment direction, halfVector, attenuation
		if (Lights[light].isLocal) {
			lightDirection = lightDirection - vec3(vertPosition);
			float lightDistance = length(lightDirection);
			lightDirection = lightDirection / lightDistance;
			attenuation = 1.0 / (Lights[light].constantAttenuation
				+ Lights[light].linearAttenuation * lightDistance
				+ Lights[light].quadraticAttenuation * pow(lightDistance, 2) );
			if (Lights[light].isSpot) {
				float spotCos = dot(lightDirection, -Lights[light].coneDirection);
				if (spotCos < Lights[light].spotCosCutoff)
					attenuation = 0.0;
				else
					attenuation *= pow(spotCos, Lights[light].spotExponent);
			}
			halfVector = normalize(lightDirection + EyeDirection);
		} else {
			halfVector = Lights[light].halfVector;
		}

		float diffuse = max(0.0, dot(vertNormal, lightDirection));
		float specular = max(0.0, dot(vertNormal, halfVector));

		if (diffuse == 0.0)
			specular = 0.0;
		else
			specular = pow(specular, Lights[light].shininess) * Lights[light].strength;
		// Accumulate all the lights effects
		scatteredLight += Lights[light].ambient * attenuation +
							Lights[light].color * diffuse * attenuation;
		reflectedLight += Lights[light].color * specular * attenuation;
	}

	vec3 lightingColor;
	float alpha;
	//fragColor = vec4(rgb, vertColor.a);

	

	

	if(shadowMappingEnabled == 1)
	{
	//------------------------------------------------------------------------------------------\\
	//             						Texturing 						      					\\
	//------------------------------------------------------------------------------------------\\
		if(vertIsTextured == 1)
		{
			lightingColor = min(f * texture(tex, vertTexCoord).rgb * scatteredLight + reflectedLight, vec3(1.0));
			alpha = texture(tex, vertTexCoord).a;
		}
		else 
		{
			lightingColor = min(f * vertColor.rgb * scatteredLight + reflectedLight, vec3(1.0));
			alpha = vertColor.a;
		}
		//------------------------------------------------------------------------------------------\\
		fragColor = vec4(lightingColor, alpha);
	} 
	// Just so lighting will always work.
	else 
	{
		if(vertIsTextured == 1)
		{
			lightingColor = min(texture(tex, vertTexCoord).rgb * scatteredLight + reflectedLight, vec3(1.0));
			alpha = texture(tex, vertTexCoord).a;
		}
		else 
		{
			lightingColor = min(vertColor.rgb * scatteredLight + reflectedLight, vec3(1.0));
			alpha = vertColor.a;
		}
		fragColor = vec4(lightingColor, alpha);
	}
	



}