#pragma once
#include <vector>
#include "GameObject.h"
class World
{
public:
	std::vector<GameObject> redBalls;
	std::vector<GameObject> yellowBalls;
	std::vector<glm::vec3> ballLocations;
	World();
	~World();
	void GenerateBalls();
};

