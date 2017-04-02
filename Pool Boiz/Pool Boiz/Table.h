#pragma once
#include "GameObject.h"
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>

class Table :
	public GameObject
{
public:
	Table();
	~Table();
	GLuint MakeVao();
};

