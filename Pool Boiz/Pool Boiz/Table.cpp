#include "Table.h"
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>


Table::Table()
{
}


Table::~Table()
{
}

GLuint Table::MakeVao()
{
	GLuint this_vao;
	glGenVertexArrays(1, &this_vao);
	glBindVertexArray(this_vao);

	float verts[]
	{
		-20,0.0,-40,
		20,0.0,-40,
		-20,0.0,40,
		20,0.0,40,

		-20,3.0,-40,
		20,3.0,-40,
		-20,3.0,40,
		20,3.0,40,

	};

	float colours[]
	{
			0,0.4,0,1,
			0,0.4,0,1,
			0,0.4,0,1,
			0,0.4,0,1,
			0,0.6,0,1,
			0,0.6,0,1,
			0,0.6,0,1,
			0,0.6,0,1,
			
	};

	unsigned int playAreaInds[]{ 0,1,2,3,7,1,5,0,4,2,6,7};

	//Vertex vbo
	{
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts) * sizeof(float), &verts[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);
	}
	//Vertex colours		
	{
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colours) * sizeof(float), &colours[0], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(1);
	}
	//Index vbo
	{
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(playAreaInds) * sizeof(unsigned int), &playAreaInds[0], GL_STATIC_DRAW);
	}
	glBindVertexArray(0);
	return (this_vao);
}

GLuint Table::MakeSidesVao()
{
	GLuint this_vao;
	glGenVertexArrays(1, &this_vao);
	glBindVertexArray(this_vao);

	float verts[]
	{
		-20,3.0,-40,
		20,3.0,-40,
		-20,3.0,40,
		20,3.0,40,

		-25,3.0,-45,
		25,3.0,-45,
		-25,3.0,45,
		25,3.0,45,
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

	unsigned int sidesInds[]{0,5,1,7,3,6,2,4,0,5 };

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

