#include <iostream>
#include <cmath>
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib")

#include"GameObject.h"
#include"Ball.h"
#include"World.h"
#include"Camera.h"
#include <vector>

#include "glm\common.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define VERTICES 0
#define INDICES 1
#define ANUS 0
#define PLAYAREA 1

Camera camera;

static unsigned int stripIndices[] = { 0, 1, 2, 3, 4, 5, 6, 7, 0, 1 };
static unsigned int triIndeices[] = { 0, 1, 2 };

static unsigned int buffer[2];

static unsigned int vao[2];
//66*33
//72*36
//edge
float Vertexs[] =
{
	32.0,14.0,0.0,
	33.5,83.0,0.0,
	32.0,86.0,0.0,
	64.0,83.0,0.0,
	65.5,86.0,0.0,
	64.0,17.0,0.0,
	65.5,14.0,0.0,
	33.5,17.0,0.0
};

float colors[] =
{
	0.0,0.0,0.0,
	1.0,0.0,0.0,
	0.0,1.0,0.0,
	0.0,0.0,1.0,
	1.0,1.0,1.0,
	1.0,0.0,1.0,
	0.0,1.0,0.0,
	0.0,1.0,1.0
};

float playAreaVert[] =
{
	40.0,40.0,0.0,
	60.0,40.0,0.0,
	40.0,60.0,0.0,
	60.0,60.0,0.0
};

float playAreaColour[] =
{
	0.0,1.0,0.0,
	0.0,1.0,0.0,
	0.0,1.0,0.0,
	0.0,1.0,0.0
};

void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(vao[ANUS]);
	glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, 0);

	glBindVertexArray(vao[PLAYAREA]);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0);
	 
	glm::mat4 view;
	view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	 
	GLfloat radius = 10.0f;
	GLfloat camX = sin(glutGet(GLUT_ELAPSED_TIME)) * radius;
	GLfloat camZ = cos(glutGet(GLUT_ELAPSED_TIME)) * radius;
	view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	glFlush();
	glutSwapBuffers();
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

	// BEGIN bind VAO id vao[trin] to the set of vertex array calls following
	glBindVertexArray(vao[PLAYAREA]);
	glGenBuffers(2, buffer); // Generate buffer ids
	glEnableClientState(GL_VERTEX_ARRAY);// Enable two vertex arrays: co-ordinates and color
	glEnableClientState(GL_COLOR_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[VERTICES]);// Bind vertex buffer and
	glBufferData(GL_ARRAY_BUFFER, sizeof(playAreaVert) + sizeof(playAreaVert), NULL, GL_STATIC_DRAW);//reserve space
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(playAreaVert), playAreaVert);// Copy vertex coordinates data into first half of vertex buffer.
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(playAreaVert), sizeof(playAreaColour), playAreaColour);// Copy vertex color data into second half of vertex buffer.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[INDICES]);// Bind and fill indices buffer.
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(stripIndices), stripIndices, GL_STATIC_DRAW);
	glVertexPointer(3, GL_FLOAT, 0, 0);// Specify vertex and color pointers to the start of the respective data.
	glColorPointer(3, GL_FLOAT, 0, (GLvoid*)(sizeof(playAreaVert)));
	// END bind VAO id vao[tRIN].

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
/*	camera.CameraUpdate();
	glm::mat4 view;
	view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	GLfloat radius = 10.0f;
	GLfloat camX = sin(glutGet(GLUT_ELAPSED_TIME)) * radius;
	GLfloat camZ = cos(glutGet(GLUT_ELAPSED_TIME)) * radius;
	view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	*/
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