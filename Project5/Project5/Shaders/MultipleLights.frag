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
};

// the set of lights to apply, per invocation of this shader
const int MaxLights = 2;
uniform LightProperties Lights[MaxLights];
uniform float Shininess;
uniform float Strength;
uniform vec3 EyeDirection;
in vec4 vertColor;
in vec3 vertNormal;
in vec4 vertPosition;
out vec4 fragColor;

void main()
{
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
			specular = pow(specular, Shininess) * Strength;
		// Accumulate all the lights effects
		scatteredLight += Lights[light].ambient * attenuation +
							Lights[light].color * diffuse * attenuation;
		reflectedLight += Lights[light].color * specular * attenuation;
	}

	// TODO: implement texture stuff here
	vec3 rgb = min(vertColor.rgb * scatteredLight + reflectedLight, vec3(1.0));
	fragColor = vec4(rgb, vertColor.a);

}