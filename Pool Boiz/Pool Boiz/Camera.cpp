#include "Camera.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>



Camera::Camera()
{
	camPos = glm::vec3{ 0.0f,0.0f,3.0f };
	camTarget = glm::vec3{ 0.0f,0.0f,0.0f };
	camDirection = glm::normalize(camPos - camTarget);//worked out in a way that means it's actually the negative direction
	camRight = glm::normalize(glm::cross(glm::vec3{ 0.0,1.0,0.0 }, camDirection));
	camUp = glm::normalize(glm::cross(camDirection, camRight));
}


Camera::~Camera()
{
}

void Camera::CameraUpdate()
{
	glm::lookAt(camPos, camTarget, camUp);
}