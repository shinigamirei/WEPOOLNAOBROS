#version 430 core

#define ANUS 0
#define PLAYAREA 1

layout(location=0) in vec4 anusCoords;
layout(location=1) in vec4 playCoords;

uniform mat4 projMat;
uniform mat4 modelViewMat;
uniform uint object;

vec4 coords;

void main(void)
{
   if (object == ANUS) coords = anusCoords;
   if (object == PLAYAREA) coords = playCoords;
   
   gl_Position = projMat * modelViewMat * coords;
}