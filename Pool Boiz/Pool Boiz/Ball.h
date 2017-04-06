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
	int indicesCount;
	float radius;
	std::vector<glm::vec3> vertices;
	std::vector<GLuint> indices;
	glm::vec4 colour;
	Ball();
	~Ball();
	void Update();
	GLuint MakeVao();
	void SideCollision();
	void BallCollision(GameObject a);
};

