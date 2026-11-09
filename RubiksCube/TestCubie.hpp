#pragma once

#include "GameInterface.hpp"

#include "CubieRenderer.hpp"

class TestCubie : public GameInterface
{
public:
    void Initialize() override;
    void Update(double deltaTime) override;
    void Render(float aspectRatio) override;
    void ClearResources() override;

private:
    CubieRenderer m_cubieRenderer;
    float m_turningAngle;
};
