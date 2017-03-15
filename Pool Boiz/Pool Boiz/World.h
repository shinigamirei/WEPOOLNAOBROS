#pragma once
#include <vector>
#include "GameObject.h"
class World
{
public:
	std::vector<GameObject> balls;
	World();
	~World();
};

