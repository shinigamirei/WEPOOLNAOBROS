#pragma once
#include <vector>
#include "GameObject.h"
class World
{
public:
	std::vector<GameObject> balls;
	std::vector<glm::vec3> ballLocations;
	World();
	~World();
	void GenerateBalls();
};

