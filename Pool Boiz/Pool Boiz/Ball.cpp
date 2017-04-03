#include "Ball.h"
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#include<vector>
#include<iostream>
#include "glm\common.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Ball::Ball()
{
	lats = 6;
	longs = 6;
	Radius = 3.0;
}


Ball::~Ball()
{
}

void Ball::calc()
{
	float verts[]
	{
		-10.0,0.0,-10.0,
		-10.0,0.0,10.0,
		10.0,0.0,-10.0,
		10.0,0.0,10.0
	};

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(3);


	vertices.push_back(verts[0]);
	vertices.push_back(verts[1]);
	vertices.push_back(verts[2]);
	vertices.push_back(verts[3]);
	vertices.push_back(verts[4]);
	vertices.push_back(verts[5]);
	vertices.push_back(verts[6]);
	vertices.push_back(verts[7]);
	vertices.push_back(verts[8]);
	vertices.push_back(verts[9]);
	vertices.push_back(verts[10]);
	vertices.push_back(verts[11]);

/*
	// Calc The Vertices
	for (int i = 0; i <= lats; ++i)
	{

		float V = i / (float)lats;
		float phi = V * glm::pi <float>();

		// Loop Through Slices
		for (int j = 0; j <= longs; ++j)
		{

			float U = j / (float)longs;
			float theta = U * (glm::pi <float>() * 2);

			// Calc The Vertex Positions
			float x = cosf(theta) * sinf(phi);
			float y = cosf(phi);
			float z = sinf(theta) * sinf(phi);

			// Push Back Vertex Data
			vertices.push_back(x * Radius);
			vertices.push_back(y * Radius);
			vertices.push_back(z * Radius);

			std::cout << i;
		}

	}


	// Calc The Index Positions
	for (int i = 0; i < longs * lats + longs; ++i) {

		indices.push_back(i);
		indices.push_back(i + longs + 1);
		indices.push_back(i + longs);

		indices.push_back(i + longs + 1);
		indices.push_back(i);
		indices.push_back(i + 1);
		indicesCount += 6;
		std::cout << i * 6<<std::endl;
	}*/
}

GLuint Ball::MakeVao()
{
	{
		GLuint this_vao;
		glGenVertexArrays(1, &this_vao);
		glBindVertexArray(this_vao);

		//Vertex vbo
		{
			GLuint vbo;
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() *sizeof(float), &vertices[0], GL_STATIC_DRAW);
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
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
		}
		glBindVertexArray(0);
		return (this_vao);
	}
}