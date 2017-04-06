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
	velocity = glm::vec3{ 0,0,0 };
	colour = glm::vec4(1, 1, 1, 1);

	for (int i = 0; i < 2; i++)
	{
		float V = i / (float)2;
		float phi = V * glm::pi<float>();// work out the angle of the lat

		//calc tip vertices
		{
			glm::vec3 vec;//angle of long
			vec.x = cosf(0) * sinf(phi);
			vec.y = 0;
			vec.z = sinf(0) * sinf(phi);
			vertices.push_back(vec * tipRadius);
		}
		//calc rear vertices
		{
			glm::vec3 vec;
			float U = 1 / (float)longs;
			float theta = U * (glm::pi<float>() * 2);//angle of long

			vec.x = cosf(theta) * sinf(phi);
			vec.y = length;
			vec.z = sinf(theta) * sinf(phi);

			vertices.push_back(vec * endRadius);
		}
	}
	// Calc The Index Positions
	for (GLuint i = 0; i < longs * 2; i++) {

		indices.push_back(i);
		indices.push_back(i + 1);
		indices.push_back(i + longs);
		indices.push_back(i + longs + 1);
		indicesCount += 4;
	}
}


Cue::~Cue()
{
}

GLuint Cue::MakeVao()
{



	GLuint this_vao;
	glGenVertexArrays(1, &this_vao);
	glBindVertexArray(this_vao);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Vertex vbo
	{
		float size = vertices.size() * sizeof(glm::vec3);
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);

	}
	//Vertex colours
	{
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4), &colour, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(1);
	}
	//Index vbo
	{
		unsigned int size = indices.size() * sizeof(unsigned int);
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices.data(), GL_STATIC_DRAW);
	}
	//glBindVertexArray(0);
	return (this_vao);
}