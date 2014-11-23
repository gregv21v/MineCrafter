#include "ShadowMap.h"

// initialize shadow map in the following order:
/*
	init();
	startRenderFromLight();
	world.draw();
	endRenderFromLight();

*/



ShadowMap::ShadowMap()
{
}


ShadowMap::~ShadowMap()
{
}





void ShadowMap::init(glm::mat4 frustum)
{
	// setup matrices and vectors
	_Y = glm::vec3(0, 0, 0); // i don't exactly know what this is
	_lightPosition = glm::vec3(
		sinf(_time * 6.0f * 3.141592f) * 300.0f,
		200.0f,
		cosf(_time * 4.0f * 3.141592f) * 100.0f + 250.0f
	);


	_sceneModelMatrix = glm::rotate(glm::mat4(), _time * 720.0f, _Y);

	_sceneViewMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -300.0f));
	_sceneProjectionMatrix = frustum;

	_scaleBiasMatrix = glm::mat4(
		glm::vec4(0.5f, 0.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.5f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.5f, 0.0f), 
		glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)
	);


	_lightViewMatrix = glm::lookAt(_lightPosition, glm::vec3(1.0), _Y);
	_lightProjectionMatrix = frustum; // this is slightly different in the example code; i am not sure why.

	_shadowMatrix = _scaleBiasMatrix * _lightProjectionMatrix * _lightViewMatrix;


	setupFramebuffer();
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
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}





void ShadowMap::startRenderFromLight()
{
	// render scene from point of view of light source
	_shader.init("Shaders/GenShadow.vert", "Shaders/GenShadow.frag");

	glUniformMatrix4fv(_shader.getUniformLocation("MVPMatrix"),
		1, GL_FALSE,
		glm::value_ptr(_lightProjectionMatrix * _lightViewMatrix * _sceneModelMatrix)
	);

	glBindFramebuffer(GL_FRAMEBUFFER, _fboID);
	glViewport(0, 0, DEPTH_TEXTURE_SIZE, DEPTH_TEXTURE_SIZE);

	glClearDepth(1.0f);
	glClear(GL_DEPTH_BUFFER_BIT);

	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(2.0f, 4.0f); // what's this?
}
void ShadowMap::endRenderFromLight()
{
	glEnable(GL_POLYGON_OFFSET_FILL);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ShadowMap::render(Shader shader)
{
	// shadow matrix
	glUniformMatrix4fv(shader.getUniformLocation("ShadowMatrix"), 1, GL_FALSE, glm::value_ptr(_shadowMatrix));
	// light position
	glUniform3fv(shader.getUniformLocation("light_position"), 1, glm::value_ptr(_lightPosition));
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _textureID);
	glUniform1i(shader.getUniformLocation("depth_texture"), 0);
}