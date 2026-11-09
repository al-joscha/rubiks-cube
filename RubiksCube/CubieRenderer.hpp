#pragma once
#include <vector>
#include <GL/glew.h>
#include <glm/mat4x4.hpp>

class CubieRenderer
{
public:
    float GetCubieExtension() const { return 2.0f * m_offset; }

    void Initialize();
    void Render(const glm::mat4& transformationMatrix);
    void ClearResources();

private:
    void AddSidePosition(int sideType, int direction, std::vector<glm::vec3>& positionArray);
    void AddSideColor(int sideType, int direction, std::vector<glm::vec3>& colorArray);
    void TranscribeToFloatArray(const std::vector<glm::vec3>& vecArray, float* floatArray);

    const float m_offset = 0.5f;

    float m_turningAngle;
    GLuint m_shaderProgram;
    GLuint m_arrayBufferObject;
    GLuint m_vertexBufferObject[2];
    GLint m_transformLocation;
};
