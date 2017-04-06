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
#define PI 3.14159265
Ball::Ball()
{
	lats = 6;
	longs = 6;
	radius = 3.0;
	indicesCount = 0;

/*	for (int i = 0; i < lats; i++)
	{

		float V = i / (float)lats;
		float phi = V * glm::pi <float>();// work out the angle of the lat

										  // Loop Through Slices
		for (int j = 0; j <= longs; ++j)
		{

			float U = j / (float)longs;
			float theta = U * (glm::pi <float>() * 2);//angle of long

													  // Calc The Vertex Positions
			float x = cosf(theta) * sinf(phi);
			float y = cosf(phi);
			float z = sinf(theta) * sinf(phi);

			// Push Back Vertex Data
			vertices.push_back(x * Radius);
			vertices.push_back(y * Radius);
			vertices.push_back(z * Radius);

			std::cout << i << std::endl << j << std::endl;
		}
	}
	// Calc The Index Positions
	for (int i = 0; i < longs * lats; i++) {

		indices.push_back(i);
		indices.push_back(i + longs);
		std::cout << indices[i]<<std::endl;

		indicesCount += 2;
	}*/
}


Ball::~Ball()
{
}


void Ball::calc()
{
}

void Ball::update()
{
	position += velocity;
}

GLuint Ball::MakeVao()
{
	{
		GLuint this_vao;
		glGenVertexArrays(1, &this_vao);
		glBindVertexArray(this_vao);
		float verts[]
		{
			-2.0,0.0,-2.0,
			-2.0,0.0,2.0,
			2.0,0.0,-2.0,
			2.0,0.0,2.0,
			2.0,2.0,2.0,
			-2.0,2.0,2.0,
			-2.0,2.0,-2.0,
			2.0,2.0,-2.0,

		};
		float colours[]
		{
			0.0,0.0,1.0,
			0.0,0.0,1.0,
			0.0,0.0,1.0,
			0.0,0.0,1.0,
			0.0,0.0,1.0,
			0.0,0.0,1.0,
			0.0,0.0,1.0,
			0.0,0.0,1.0,
		};

		unsigned int indec[]{0,1,2,3,4,1,5,0,6,7,5,4,2,7,6};
		//Vertex vbo
		{
			GLuint vbo;
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER,sizeof(vertices) *sizeof(float), &vertices[0], GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
			glEnableVertexAttribArray(0);
		}
		//Vertex colours
		{
			GLuint vbo;
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(colours) * sizeof(float), &colours[0], GL_STATIC_DRAW);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
			glEnableVertexAttribArray(1);
		}
		//Index vbo
		{
			GLuint vbo;
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertices) * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
		}
		glBindVertexArray(0);
		return (this_vao);
	}
}

// Fill the vertex array with co-ordinates of the sample points.
void Ball::fillHemVertexArray(glm::vec4 hemVertices[(HEM_LONGS + 1) * (HEM_LATS + 1)])
{
	int i, j, k;

	k = 0;
	for (j = 0; j <= lats; j++)
		for (i = 0; i <= longs; i++)
		{
			hemVertices[k].x = radius * cos((float)j / lats * PI / 2.0) * cos(2.0 * (float)i / longs * PI);
			hemVertices[k].y = radius * sin((float)j / lats * PI / 2.0);
			hemVertices[k].z = radius * cos((float)j / lats * PI / 2.0) * sin(2.0 * (float)i / longs * PI);
			hemVertices[k].w = 1.0;
			k++;
		}
}

// Fill the array of index arrays.
void Ball::fillHemIndices(unsigned int hemIndices[HEM_LATS][2 * (HEM_LONGS + 1)])
{
	int i, j;
	for (j = 0; j < HEM_LATS; j++)
	{
		for (i = 0; i <= HEM_LONGS; i++)
		{
			hemIndices[j][2 * i] = (j + 1)*(HEM_LONGS + 1) + i;
			hemIndices[j][2 * i + 1] = j*(HEM_LONGS + 1) + i;
		}
	}
}

// Fill the array of counts.
void Ball::fillHemCounts(int hemCounts[HEM_LATS])
{
	int j;
	for (j = 0; j < HEM_LATS; j++) hemCounts[j] = 2 * (HEM_LONGS + 1);
}

// Fill the array of buffer offsets.
void Ball::fillHemOffsets(void* hemOffsets[HEM_LATS])
{
	int j;
	for (j = 0; j < HEM_LATS; j++) hemOffsets[j] = (GLvoid*)(2 * (HEM_LONGS + 1)*j * sizeof(unsigned int));
}

// Initialize the hemisphere.
void Ball::fillHemisphere(glm::vec4 hemVertices[(HEM_LONGS + 1) * (HEM_LATS + 1)],
	unsigned int hemIndices[HEM_LATS][2 * (HEM_LONGS + 1)],
	int hemCounts[HEM_LATS],
	void* hemOffsets[HEM_LATS])
{
	fillHemVertexArray(hemVertices);
	fillHemIndices(hemIndices);
	fillHemCounts(hemCounts);
	fillHemOffsets(hemOffsets);
}