#pragma once
#include "GameInterface.h"
#include <GL/glew.h>

class TestTexture : public GameInterface
{
public:
	void Initialize() override;
	void Render(float aspectRatio) override;
	void ClearResources() override;

private:
	GLuint m_shaderProgram;
	GLuint m_vertexBufferObject;
	GLuint m_arrayBufferObject;
	GLint m_transformationLocation;
	GLuint m_texture;
};
