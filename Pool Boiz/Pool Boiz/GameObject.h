#pragma once
#include "glm\common.hpp"

class GameObject
{
public:
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	glm::vec3 heading;
	glm::vec4 colour;
	GameObject();
	~GameObject();

	virtual void Update();
	virtual void render(unsigned int, unsigned int[], int ,int);
};

