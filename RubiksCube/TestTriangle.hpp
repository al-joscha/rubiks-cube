#pragma once
#include "GameInterface.hpp"
#include <GL/glew.h>

class TestTriangle : public GameInterface
{	
public:
	void Initialize() override;
	void Update(double deltaTime) override;
	void Render(float aspectRatio) override;
	void ClearResources() override;
	
private:
	GLuint m_shaderProgram;
	GLint m_transformLocation;
	GLuint m_arrayBufferObject;
	GLuint m_vertexBufferObject;
	float m_turningAngle;
	
};

