#include "ShadowMap.h"


ShadowMap::ShadowMap()
{
}


ShadowMap::~ShadowMap()
{
}



void ShadowMap::init(glm::mat4 frustum)
{
	setupFramebuffer();
	renderFromLight(frustum);




}


void ShadowMap::setupFramebuffer()
{
	glGenTextures(1, &_textureID);
	glBindTexture(GL_TEXTURE_2D, _textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32,
		DEPTH_TEXTURE_SIZE, DEPTH_TEXTURE_SIZE,
		0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Set up depth comparison mode
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	// Set up wrapping modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0); // unbind the texture

	glGenFramebuffers(1, &_fboID);
	glBindFramebuffer(GL_FRAMEBUFFER, _fboID);

	// Create FBO to render depth into
	glGenFramebuffers(1, &_fboID);
	glBindFramebuffer(GL_FRAMEBUFFER, _fboID);
	// Attach the depth texture to it
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
		_textureID, 0);
	// Disable color rendering as there are no color attachments
	glDrawBuffer(GL_NONE);
}
}


void ShadowMap::renderFromLight(glm::mat4 frustum)
{
	// render scene from point of view of light source
	int t = 0;
	glm::vec3 Y = glm::vec3(0, 0, 0);
	glm::vec3 light_position(
			sinf(t * 6.0f * 3.141592f) * 300.0f,
			200.0f,
			cosf(t * 4.0f * 3.141592f) * 100.0f + 250.0f
	);

	glm::mat4 scene_model_matrix = glm::rotate(glm::mat4(), t * 720.0f, Y);
	glm::mat4 light_view_matrix = glm::lookAt(light_position, glm::vec3(0.0f), Y);
	glm::mat4 light_projection_matrix = frustum;

	Shader shader;

	shader.init("Shaders/GenShadow.vert", "Shaders/GenShadow.frag");

	glUniformMatrix4fv(shader.getUniformLocation("MVPMatrix"),
		1, GL_FALSE,
		glm::value_ptr(light_projection_matrix * light_view_matrix * scene_model_matrix));


	glBindFramebuffer(GL_FRAMEBUFFER, _fboID);
	glViewport(0, 0, DEPTH_TEXTURE_SIZE, DEPTH_TEXTURE_SIZE);

	glClearDepth(1.0f);
	glClear(GL_DEPTH_BUFFER_BIT);


	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(2.0f, 4.0f); // what's this?

	//DrawScene(GL_POLYGON_OFFSET_FILL);
	glEnable(GL_POLYGON_OFFSET_FILL);


}

void ShadowMap::render()
{
	glm::mat4 scene
}