#version 330 core

uniform mat4 VPMatrix;		// view projection matrix
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 ShadowMatrix;


layout(location = 0) in vec4 in_position;
layout(location = 1) in vec2 in_texel;
layout(location = 2) in vec3 in_normal;
layout(location = 3) in int in_textureID;
layout(location = 4) in int	in_isTextured;
layout(location = 5) in int	in_isTransformed;		// if the object is allowed to translate
layout(location = 6) in mat4 ModelMatrix;			// the model translation
layout(location = 10) in vec4 in_color;
layout(location = 11) in mat3 NormalMatrix;

out vec2 vertTexCoord;
out vec4 vertColor;
out vec3 vertNormal;
out vec4 vertPosition;

flat out int vertIsTextured;
flat out int textureID;

// shadow mapping struct
out VS_FS_INTERFACE
{
	vec4 shadow_coord;
	vec3 world_coord;
	vec3 eye_coord;
	vec3 normal;
} vertex;


void main()
{
	
	if(in_isTransformed == 1)
	{
		gl_Position = VPMatrix * ModelMatrix * in_position;
		vertNormal = normalize(NormalMatrix * in_normal);
		vertPosition = ViewMatrix * ModelMatrix * in_position;
	}
	else
	{
		gl_Position = VPMatrix * in_position;
		vertPosition = ViewMatrix * in_position;
		vertNormal = in_normal;

	}

	vertColor = in_color;
	vertTexCoord = in_texel;
	vertIsTextured = in_isTextured;
	
	textureID = in_textureID;

	vec4 world_pos = ModelMatrix * in_position;
	vec4 eye_pos = ViewMatrix * world_pos;
	vec4 clip_pos = ProjectionMatrix * eye_pos;
	vertex.world_coord = world_pos.xyz;
	vertex.eye_coord = eye_pos.xyz;
	vertex.shadow_coord = ShadowMatrix * world_pos;
	vertex.normal = mat3(ViewMatrix * ModelMatrix) * normalize(NormalMatrix * in_normal);
	gl_Position = clip_pos;


}