#version 430 core

layout(location=0) in vec3 Coords;

uniform mat4 projMat;
uniform mat4 modelViewMat;
uniform uint object;

void main(void)
{   
   gl_Position = vec4(Coords, 1.0);
}