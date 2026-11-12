#include "CubieRenderer.hpp"

#include <cassert>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderUtil.hpp"


void CubieRenderer::Initialize()
{
	std::vector<glm::vec3> positionField;
	std::vector<glm::vec3> colorField;

	for (int sideType = 0; sideType < 3; ++sideType)
	{
		for (int direction : {-1, 1})
		{
			AddSidePosition(sideType, direction, positionField);
			AddSideColor(sideType, direction, colorField);
		}
	}

	m_shaderProgram = ShaderUtil::CreateShaderProgram("VColor.glsl", "FColor.glsl");
	m_transformLocation = glGetUniformLocation(m_shaderProgram, "transformation");

	glGenVertexArrays(1, &m_arrayBufferObject);
	glGenBuffers(2, m_vertexBufferObject);

	glBindVertexArray(m_arrayBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * positionField.size(), positionField.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * colorField.size(), colorField.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CubieRenderer::Render(const glm::mat4& transformationMatrix)
{
	glUseProgram(m_shaderProgram);
	glBindVertexArray(m_arrayBufferObject);

	glUniformMatrix4fv(m_transformLocation, 1, GL_FALSE, glm::value_ptr(transformationMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 6 * 6);

	glBindVertexArray(0);
	glUseProgram(0);
}

void CubieRenderer::ClearResources()
{
	glDeleteVertexArrays(1, &m_arrayBufferObject);
	glDeleteBuffers(2, m_vertexBufferObject);
	glDeleteProgram(m_shaderProgram);
}

void CubieRenderer::AddSidePosition(int sideType, int direction, std::vector<glm::vec3>& positionArray)
{
	assert(sideType >= 0 && sideType <= 2);
	glm::vec3 cornerPoints[2][2];

	const int localXDim = (sideType + 1) % 3;
	const int localYDim = (sideType + 2) % 3;

	for (const int i : {0, 1})
	{
		for (const int j : {0, 1})
		{
			glm::vec3 localPoint(static_cast<float>(direction) * m_offset);
			localPoint[localXDim] = ((2.0f * static_cast<float>(i) - 1.0f) * direction) * m_offset;
			localPoint[localYDim] = (2.0f * static_cast<float>(j) - 1.0f) * m_offset;
			cornerPoints[i][j] = localPoint;
		}
	}

	positionArray.push_back(cornerPoints[0][0]);
	positionArray.push_back(cornerPoints[1][0]);
	positionArray.push_back(cornerPoints[0][1]);

	positionArray.push_back(cornerPoints[1][0]);
	positionArray.push_back(cornerPoints[1][1]);
	positionArray.push_back(cornerPoints[0][1]);
}

void CubieRenderer::AddSideColor(int sideType, int direction, std::vector<glm::vec3>& colorArray)
{
	// constexpr glm::vec3 c[6] = {
	// glm::vec3{0.0f, 1.0f, 0.0f},
	// glm::vec3{1.0f, 0.0f, 0.0f},
	// glm::vec3{1.0f, 1.0f, 1.0f},
	// glm::vec3{1.0f, 0.0f, 1.0f},
	// glm::vec3{1.0f, 1.0f, 0.0f},
	// glm::vec3{0.0f, 0.5f, 0.5f},
	// };
	auto color = glm::vec3(0.0f);
	float baseColor = (direction == -1) ? 0.5f : 1.0f;
	color[sideType] = baseColor;

	// color = c[(sideType + 1) * direction + 3];

	for (auto _ : {1, 2, 3, 4, 5, 6})
		colorArray.push_back(color);
}
