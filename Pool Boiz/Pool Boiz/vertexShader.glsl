#version 430 core

layout(location=0) in vec3 Coords;
layout(location=1) in vec4 Colours;

uniform mat4 projMat;
uniform mat4 viewMat;
uniform mat4 modelMat;
uniform uint object;

out vec4 passColour;

void main(void)
{   
	passColour = vec4(0.0,1.0,1.0,1.0);
   gl_Position = projMat * viewMat * modelMat * vec4(Coords, 1.0);
}