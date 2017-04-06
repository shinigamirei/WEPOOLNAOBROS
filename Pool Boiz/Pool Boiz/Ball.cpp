#include "Ball.h"
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#include<vector>
#include<iostream>
#include<cmath>
#include "glm\common.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Ball::Ball()
{
	lats = 10;
	longs = 10;
	radius = 3.0;
	indicesCount = 0;
	velocity = glm::vec3{0,0,0};

	for (int i = 0; i < lats; i++)
	{

		float V = i / (float)lats;
		float phi = V * glm::pi<float>() ;// work out the angle of the lat

										  // Loop Through Slices
		for (int j = 0; j <= longs; ++j)
		{
			glm::vec3 vec;
			float U = j / (float)longs;
			float theta = U * (glm::pi<float>() * 2);//angle of long

													  // Calc The Vertex Positions
			vec.x = cosf(theta) * sinf(phi);
			vec.y = cosf(phi);
			vec.z = sinf(theta) * sinf(phi);

			// Push Back Vertex Data
			vertices.push_back(vec * radius);;
		}
	}
	// Calc The Index Positions
	for (int i = 0; i < longs * lats ; i++) {

		indices.push_back(i);
		indices.push_back(i * longs+ 1);
		indices.push_back(i * longs);
		
	

	//	indicesCount += 2;
	}
	for (int h = 0; h < longs*lats;h++);
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
	sideCollision();
}

GLuint Ball::MakeVao()
{
	{
		GLuint this_vao;
		glGenVertexArrays(1, &this_vao);
		glBindVertexArray(this_vao);
		
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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
	
		unsigned int indec[]{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33};
		//Vertex vbo
		{
			float size = vertices.size() * sizeof (glm::vec3);
			GLuint vbo;
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
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
			unsigned int size = indices.size() * sizeof(unsigned int);
			GLuint vbo;
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, &indec[0], GL_STATIC_DRAW);
		}
		//glBindVertexArray(0);
		return (this_vao);
	}
}

void Ball::sideCollision()
{
	if (position.x > 19)
	{
		heading.x *= -1;
		velocity.x *= -1;
	}
	else if (position.x < -19)
	{
		heading.x *= -1;
		velocity.x *= -1;
	}
	else if (position.z > 39)
	{
		heading.z *= -1;
		velocity.z *= -1;
	}
	else if (position.z < -39)
	{
		heading.z *= -1;
		velocity.z *= -1;
	}
}
