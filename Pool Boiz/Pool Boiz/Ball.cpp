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
	radius = 1.5;
	indicesCount = 0;
	velocity = glm::vec3{0,0,0};
	colour = glm::vec4(1, 1, 1, 1);

	for (int i = 0; i < lats; i++)
	{
		float V = i / (float)lats;
		float phi = V * glm::pi<float>() ;// work out the angle of the lat
									  
		for (int j = 0; j <= longs; ++j)
		{
			glm::vec3 vec;
			float U = j / (float)longs;
			float theta = U * (glm::pi<float>() * 2);//angle of long

			vec.x = cosf(theta) * sinf(phi);
			vec.y = cosf(phi);
			vec.z = sinf(theta) * sinf(phi);

			vertices.push_back(vec * radius);
		}
	}
	// Calc The Index Positions
	for (GLuint i = 0; i < longs * lats ; i++) {

		indices.push_back(i);
		indices.push_back(i + 1);
		indices.push_back(i + longs);
		indices.push_back(i + longs+ 1);
		indicesCount += 4;
	}
}


Ball::~Ball()
{
}

void Ball::Update()
{
	if (velocity.x > 5)
		velocity.x = 5;
	if (velocity.z > 5)
		velocity.z = 5;



	velocity += acceleration*heading;
	position += velocity;
	SideCollision();
}

GLuint Ball::MakeVao()
{
	{
		GLuint this_vao;
		glGenVertexArrays(1, &this_vao);
		glBindVertexArray(this_vao);
		
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		//Vertex vbo
		{
			float size = vertices.size() * sizeof (glm::vec3);
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
			glBufferData(GL_ARRAY_BUFFER,sizeof(glm::vec4),&colour, GL_STATIC_DRAW);
			glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,0,NULL);
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
}

void Ball::SideCollision()
{
	if (position.x > 19)
	{
		position.x = 19;
		heading.x *= -1;
		velocity.x *= -1;
	}
	else if (position.x < -19)
	{
		position.x = -19;
		heading.x *= -1;
		velocity.x *= -1;
	}
	else if (position.z > 39)
	{
		position.z = 39;
		heading.z *= -1;
		velocity.z *= -1;
	}
	else if (position.z < -39)
	{
		position.z = -39;
		heading.z *= -1;
		velocity.z *= -1;
	}
}

void Ball::BallCollision(GameObject a)
{
	int distance = sqrtf(((position.x - a.position.x) * (position.x - a.position.x))+((position.z - a.position.z) * (position.z - a.position.z)));
	if (distance < radius *2)
	{
		float tempVX = velocity.x;
		float tempVZ = velocity.z;
		glm::vec3 tempHead = heading;
		
		std::cout << "collision";
		velocity.x =  a.velocity.x;
		velocity.z = a.velocity.z;
		heading = a.heading;

		a.velocity.x = tempVX;
		a.velocity.z = tempVZ;
		a.heading = tempHead;

		position += velocity;
		a.position += a.velocity;
	}
}