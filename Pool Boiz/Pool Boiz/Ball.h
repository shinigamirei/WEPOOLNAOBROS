#pragma once
#include "GameObject.h"
#include <vector>
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
class Ball :
	public GameObject
{
public:
	int lats;
	int longs;
	float radius;
	std::vector<float> vertices;
	std::vector<float> indices;
	int indicesCount;
	std::vector<float> colours;
	Ball();
	~Ball();
	void calc();
	void update();
	GLuint MakeVao();
	void sideCollision();
};

