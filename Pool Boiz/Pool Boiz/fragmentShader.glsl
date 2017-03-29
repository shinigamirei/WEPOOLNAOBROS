#version 430 core

in vec4 passColour;

out vec4 colourOut;

void main(void)
{
	colourOut = passColour; 
}