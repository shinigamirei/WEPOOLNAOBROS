#pragma once
#include "glm\common.hpp"

class GameObject
{
public:
	glm::vec3 Position;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	GameObject();
	~GameObject();
	virtual void update();
	virtual void render();
};

