#version 330 core
uniform sampler2DShadow depth_texture;
uniform vec3 light_position;
uniform vec3 material_ambient;
uniform vec3 material_diffuse;
uniform vec3 material_specular;
uniform float material_specular_power;

in vec4 vertColor;
in vec3 vertNormal;
in vec4 vertPosition;
out vec4 fragColor;

in VS_FS_INTERFACE
{
	vec4 shadow_coord;
	vec3 world_coord;
	vec3 eye_coord;
	vec3 normal;
} fragment;

void main(void)
{
	vec3 N = fragment.normal;
	vec3 L = normalize(light_position - fragment.world_coord);
	vec3 R = reflect(-L, N);
	vec3 E = normalize(fragment.eye_coord);
	float NdotL = dot(N, L);
	float EdotR = dot(-E, R);
	float diffuse = max(NdotL, 0.0);
	float specular = max(pow(EdotR, material_specular_power),0.0);
	float f = textureProj(depth_texture, fragment.shadow_coord);
	color = vec4(material_ambient + 
			f * (material_diffuse * diffuse + material_specular * specular), 1.0);
}