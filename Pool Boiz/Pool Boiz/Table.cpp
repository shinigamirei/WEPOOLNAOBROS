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
	{
		GLuint this_vao;
		glGenVertexArrays(1, &this_vao);
		glBindVertexArray(this_vao);


		float verts[]{
			0.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
		};
/*	float colours[]{
			1,0,0,1,
			0,1,0,1,
			0,0,1,1,
			0,0,0,0
		};*/

		unsigned int inds[]
		{
			1,0,2,3
		};

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
/*		{
			GLuint vbo;
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(colours) * sizeof(float), &colours[0], GL_STATIC_DRAW);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
			glEnableVertexAttribArray(1);
		}*/
		//Index vbo
		{
			GLuint vbo;
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(inds) * sizeof(unsigned int), &inds[0], GL_STATIC_DRAW);
		}
		glBindVertexArray(0);
		return (this_vao);
	}
}