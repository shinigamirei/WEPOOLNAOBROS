#include "CueBall.h"



CueBall::CueBall()
{
	position = { 0,0,20 };
	force = 0.5;
	heading = glm::vec3{0,0,-1};
}


CueBall::~CueBall()
{
}

void CueBall::hit()
{
	velocity += (glm::vec3{1,1,1} * force * heading);
}