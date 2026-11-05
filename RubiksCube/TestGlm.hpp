#pragma once
#include <glm/ext/quaternion_float.hpp>

#include "GameInterface.hpp"

class TestGlm: public GameInterface
{
public:
	void Initialize();
	void Update(double deltatime) override;

	void Render(float aspectRatio);

private:
	glm::quat m_orientationQuaternion;
	

};

