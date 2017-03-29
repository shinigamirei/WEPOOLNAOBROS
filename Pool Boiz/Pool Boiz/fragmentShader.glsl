#version 430 core

#define ANUS 0
#define PLAYAREA 1

uniform uint object;
uniform vec4 hemColor, playAreaColour;

out vec4 colourOut;

void main(void)
{
	colourOut = vec4(1,0,0,1); 
}