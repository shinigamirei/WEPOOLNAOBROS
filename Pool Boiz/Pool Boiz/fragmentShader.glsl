#version 430 core

#define ANUS 0
#define PLAYAREA 1

uniform uint object;
uniform vec4 hemColor, playAreaColour;

out vec4 colorsOut;

void main(void)
{
   if (object == HEMISPHERE) colorsOut = hemColor; 
   if (object == PLAYAREA) colorsOut = PlayAreaColour;
}