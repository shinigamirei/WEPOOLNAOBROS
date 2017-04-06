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
	velocity = glm::vec3{0,0,2};

	for (int i = 0; i < lats; i++)
	{

		float V = i / (float)lats;
		float phi = V * PI;// work out the angle of the lat

										  // Loop Through Slices
		for (int j = 0; j <= longs; ++j)
		{

			float U = j / (float)longs;
			float theta = U * (PI * 2);//angle of long

													  // Calc The Vertex Positions
			float x = cosf(theta) * sinf(phi);
			float y = cosf(phi);
			float z = sinf(theta) * sinf(phi);

			// Push Back Vertex Data
			vertices.push_back(x * radius);
			vertices.push_back(y * radius);
			vertices.push_back(z * radius);

			std::cout << y << std::endl;
		}
	}
	// Calc The Index Positions
	for (int i = 0; i < longs * lats; i++) {

		indices.push_back(i);
		indices.push_back(i + longs);
		indices.push_back(i + longs +1);

		indicesCount += 2;
	}
	for (int h = 0; h < longs*lats;h++)
		std::cout << indices[h]<<std::endl;
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
		
//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		std::vector<float> verticies
		{
		};
		
		verticies.push_back(-1.0);
		verticies.push_back(0.0);
		verticies.push_back(-1.0);

		verticies.push_back(-1.0);
		verticies.push_back(0.0);
		verticies.push_back(1.0);

		verticies.push_back(1.0);
		verticies.push_back(0.0);
		verticies.push_back(-1.0);

		verticies.push_back(1.0);
		verticies.push_back(0.0);
		verticies.push_back(1.0);

		verticies.push_back(1.0);
		verticies.push_back(2.0);
		verticies.push_back(1.0);

		verticies.push_back(-1.0);
		verticies.push_back(2.0);
		verticies.push_back(1.0);

		verticies.push_back(-1.0);
		verticies.push_back(2.0);
		verticies.push_back(-1.0);

		verticies.push_back(1.0);
		verticies.push_back(2.0);
		verticies.push_back(-1.0);
		
		for (int g = 0; g < 24;g++)
			std::cout << verticies[g] << std::endl;
		std::vector<unsigned int> in
		{
			0, 1, 2, 3, 4, 1, 5, 0, 6, 7, 5, 4, 2, 7, 6
		};


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
			float size = verticies.size() * sizeof (float);
			GLuint vbo;
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER,size, &verticies[0], GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
			glEnableVertexAttribArray(0);
		}
		//Vertex colours
/*		{
			GLuint vbo;
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(colours) * sizeof(float), &colours[0], GL_STATIC_DRAW);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
			glEnableVertexAttribArray(1);
		}*/
		//Index vbo
		{
			unsigned int indicesSize = indices.size() * sizeof(unsigned int);
			GLuint vbo;
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indec), &indec[0], GL_STATIC_DRAW);
		}
		glBindVertexArray(0);
		return (this_vao);
	}
}

void Ball::sideCollision()
{

}