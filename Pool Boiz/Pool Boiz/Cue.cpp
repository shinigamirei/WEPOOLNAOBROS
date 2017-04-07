#include "Cue.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>

#include "glm\common.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Cue::Cue()
{
	tipRadius = 0.35;
	endRadius = 1.15;
	length = 58;
	indicesCount = 0;
	position = { 10,0,-20};
	velocity = glm::vec3{ 0,0,0 };
	colour = glm::vec4(1, 1, 1, 1);
}


Cue::~Cue()
{
}

GLuint Cue::MakeVao()
{
	GLuint this_vao;
	glGenVertexArrays(1, &this_vao);
	glBindVertexArray(this_vao);

	float verts[]
	{
		-2,0,0,
		2,0,0,
		3,1,0,
		2,2,0,
		-2,2,0,
		3,1,0,

		-2,0,50,
		2,0,50,
		3,1,50,
		2,2,50,
		-2,2,50,
		3,1,50,

	};

	float colours[]
	{
		0,0.6,0,1,
		0,0.6,0,1,
		0,0.6,0,1,
		0,0.6,0,1,

		0.7,0.3,0.1,1,
		0.7,0.3,0.1,1,
		0.7,0.3,0.1,1,
		0.7,0.3,0.1,1,
	};

	unsigned int sidesInds[]{ 0,6,1,7,2,8,3,9,4,10,5,11,0,6 };

	{
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts) * sizeof(float), &verts[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colours) * sizeof(float), &colours[0], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(1);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sidesInds) * sizeof(unsigned int), &sidesInds[0], GL_STATIC_DRAW);
	}
	glBindVertexArray(0);
	return (this_vao);
}