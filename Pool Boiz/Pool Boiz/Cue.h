#pragma once
#include "GameObject.h"
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#include<vector>
class Cue :
	public GameObject
{
public:
	int longs;
	int indicesCount;
	float length;
	float tipRadius;
	float endRadius;
	std::vector<glm::vec3> vertices;
	std::vector<GLuint> indices;
	glm::vec4 colour;
	GameObject target;
	Cue();
	~Cue();
	GLuint MakeVao();

