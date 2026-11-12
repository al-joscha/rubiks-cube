#pragma once
#include "CubieRenderer.hpp"
#include "GameInterface.hpp"

class TestCompoundCube : public GameInterface
{
public:
    void Initialize() override;
    void Update(double deltaTime) override;
    void Render(float aspectRatio) override;
    void ClearResources() override;

private:
    CubieRenderer m_cubieRenderer;
    float m_turningAngle;
    glm::mat4 m_cubeState[3][3][3];
};
