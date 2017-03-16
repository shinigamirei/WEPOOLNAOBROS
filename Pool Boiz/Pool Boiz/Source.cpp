#include <iostream>
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
using namespace glm;

#define VERTICES 0
#define INDICES 1
#define ANUS 0
#define TRINGLE 1

static unsigned int anusindec[] = { 0, 1, 2, 3, 4, 5, 6, 7, 0, 1 };

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

void drawScene(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(vao[ANUS]);
	glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, 0);

	glBindVertexArray(vao[TRINGLE]);
	glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, 0);

	glutSwapBuffers();
}

void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glGenBuffers(3, buffer); // Generate buffer ids.

							 // Enable two vertex arrays: co-ordinates and color.
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	// Bind vertex buffer and reserve space.
	glBindBuffer(GL_ARRAY_BUFFER, buffer[VERTICES]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertexs) + sizeof(colors), NULL, GL_STATIC_DRAW);

	// Copy vertex coordinates data into first half of vertex buffer.
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertexs), Vertexs);

	// Copy vertex color data into second half of vertex buffer.
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(Vertexs), sizeof(colors), colors);

	// Bind and fill indices buffer.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[INDICES]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(anusindec), anusindec, GL_STATIC_DRAW);

	// Specify vertex and color pointers to the start of the respective data.
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glColorPointer(3, GL_FLOAT, 0, (GLvoid*)(sizeof(Vertexs)));

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

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
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