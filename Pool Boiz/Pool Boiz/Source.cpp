#include <iostream>
#include <cmath>
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib")

#include"GameObject.h"
#include"Ball.h"
#include"World.h"
#include <vector>

#include "glm\common.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define VERTICES 0
#define INDICES 1
#define ANUS 0
#define TRINGLE 1

static unsigned int stripIndices[] = { 0, 1, 2, 3, 4, 5, 6, 7, 0, 1 };

static unsigned int buffer[2];

static unsigned int vao[2];

float Vertexs[] =
{
	20.0,20.0,0.0,
	30.0,70.0,0.0,
	20.0,80.0,0.0,
	70.0,70.0,0.0,
	80.0,80.0,0.0,
	70.0,30.0,0.0,
	80.0,20.0,0.0,
	30.0,30.0,0.0
};

float colors[] =
{
	0.0, 0.0, 0.0,
	1.0, 0.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 0.0, 1.0,
	1.0,1.0,1.0,
	1.0,0.0,1.0,
	0.0,1.0,0.0,
	0.0,1.0,1.0
};

float Tirnglr[] =
{
	40.0,40.0,0.0,
	60.0,40.0,0.0,
	60.0,60.0,0.0
};

float tcolors[] =
{
	0.0, 0.0, 0.0,
	1.0, 0.0, 0.0,
	0.0, 1.0, 0.0,
};

void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(vao[ANUS]);
	glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, 0);

//	glBindVertexArray(vao[TRINGLE]);
//	glDrawElements(GL_TRIANGLE_STRIP, 3, GL_UNSIGNED_INT, 0);

	glFlush();
//	glutSwapBuffers();
}

void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glGenVertexArrays(2, vao);
	
	// BEGIN bind VAO id vao[ANNULUS] to the set of vertex array calls following.
	glBindVertexArray(vao[ANUS]);
	glGenBuffers(2, buffer); // Generate buffer ids.
	glEnableClientState(GL_VERTEX_ARRAY);// Enable two vertex arrays: co-ordinates and color.
	glEnableClientState(GL_COLOR_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[VERTICES]);// Bind vertex buffer and reserve space.
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertexs) + sizeof(colors), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertexs), Vertexs);// Copy vertex coordinates data into first half of vertex buffer.
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(Vertexs), sizeof(colors), colors);// Copy vertex color data into second half of vertex buffer.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[INDICES]);// Bind and fill indices buffer.
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(stripIndices), stripIndices, GL_STATIC_DRAW);	
	glVertexPointer(3, GL_FLOAT, 0, 0);// Specify vertex and color pointers to the start of the respective data.
	glColorPointer(3, GL_FLOAT, 0, (GLvoid*)(sizeof(Vertexs)));
	// END bind VAO id vao[ANNULUS].

}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

void GamLEP()
{

}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 2);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Paoul my love");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutIdleFunc(GamLEP);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}