#include "TestCompoundCube.hpp"

#include "TestGlm.hpp"

void TestCompoundCube::Initialize()
{
    m_cubieRenderer.Initialize();
    m_turningAngle = 0.0f;
    for (int i : {0, 1, 2})
    {
        for (int j : {0, 1, 2})
        {
            for (int k : {0, 1, 2})
            {
                glm::mat4 localRot = glm::rotate(glm::mat4(1.0f), i * glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                localRot = glm::rotate(localRot, j * glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                localRot = glm::rotate(localRot, k * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));

                m_cubeState[i][j][k] = localRot;
            }
        }
    }
}

void TestCompoundCube::Update(const double deltaTime)
{
    m_turningAngle += static_cast<float>(deltaTime) * glm::radians(45.0f);
}

void TestCompoundCube::Render(const float aspectRatio)
{
    glm::mat4 object_to_clip = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f)
        * glm::lookAt(glm::vec3(0.0f, 0.0f, -9.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), m_turningAngle, glm::vec3(1.0f));


    auto offset = m_cubieRenderer.GetCubieExtension();
    // auto offset = m_cubieRenderer.GetCubieExtension() * 1.025f;
    for (int i : {0, 1, 2})
    {
        for (int j : {0, 1, 2})
        {
            for (int k : {0, 1, 2})
            {
                glm::mat4 compound = glm::translate(object_to_clip, glm::vec3(i - 1, j - 1, k - 1) * offset);
                compound = compound * m_cubeState[i][j][k];
                m_cubieRenderer.Render(compound);
            }
        }
    }
}

void TestCompoundCube::ClearResources()
{
    m_cubieRenderer.ClearResources();
}
