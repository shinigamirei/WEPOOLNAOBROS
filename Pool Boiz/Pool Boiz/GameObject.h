#pragma once
#include "glm\common.hpp"

class GameObject
{
public:
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	glm::vec3 heading;
	GameObject();
	~GameObject();
	virtual void update();
	virtual void render(unsigned int, unsigned int[], int ,int);
};

