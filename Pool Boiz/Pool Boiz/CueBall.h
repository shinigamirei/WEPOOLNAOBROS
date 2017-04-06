#pragma once
#include "Ball.h"
class CueBall :
	public Ball
{
public:
	float force;
	CueBall();
	~CueBall();
	void hit();
};

