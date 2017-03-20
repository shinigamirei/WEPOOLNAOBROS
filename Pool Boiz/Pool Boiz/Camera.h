#pragma once
#include <glm\common.hpp>

class Camera
{
public:
	glm::vec3 camPos;
	glm::vec3 camTarget;
	glm::vec3 camDirection;//z direction of camera
	glm::vec3 camRight;//x axis of camera
	glm::vec3 camUp;//y axis of camera
	Camera();
	~Camera();
	void CameraUpdate();
};

