#include <iostream>
#include <cmath>
#include <vector>
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib")

#include"GameObject.h"
#include"Ball.h"
#include"World.h"
#include"Camera.h"
#include"Table.h"
#include"Ball.h"

#include "glm\common.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define VERTICES 0
#define INDICES 1
#define ANUS 0
#define PLAYAREA 1
#define SIDES 2

Camera camera;
Table table;
Ball PLZ;

static unsigned int stripIndices[] = { 0, 1, 2, 3, 4, 5, 6, 7, 0, 1 };
static unsigned int
programId,
modelMatLoc,
projMatLoc,
viewMatLoc,
objectLoc,
anusColorLoc,
playColorLoc,
buffer[2],
budder[2] ,
vao[3];

static glm::mat4 modelViewMat = glm::mat4(1.0);
static glm::mat4 projMat = glm::mat4(1.0);
static float Xangle = 0.0, Yangle = 0.0, Zangle = 0.0; // Angles to rotate scene.


static glm::vec4 playAreaColours = { 0.0,1.0,0.0,1.0 };

// Hemisphere data.
static glm::vec4 hemVertices[(HEM_LONGS + 1) * (HEM_LATS + 1)];
static unsigned int hemIndices[HEM_LATS][2 * (HEM_LONGS + 1)];
static int hemCounts[HEM_LATS];
static void* hemOffsets[HEM_LATS];
static glm::vec4 hemColors = glm::vec4(HEM_COLORS);

// Function to read text file.
char* readTextFile(char* aTextFile)
{
	FILE* filePointer = fopen(aTextFile, "rb");
	char* content = NULL;
	long numVal = 0;

	fseek(filePointer, 0L, SEEK_END);
	numVal = ftell(filePointer);
	fseek(filePointer, 0L, SEEK_SET);
	content = (char*)malloc((numVal + 1) * sizeof(char));
	fread(content, 1, numVal, filePointer);
	content[numVal] = '\0';
	fclose(filePointer);
	return content;
}

GLuint CreateShader(char* vertShadPath,char* fragShadPath ) 
{
	char* vertexShader = readTextFile(vertShadPath);
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, (const char**)&vertexShader, NULL);
	glCompileShader(vertexShaderId);

	char* fragmentShader = readTextFile(fragShadPath);
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, (const char**)&fragmentShader, NULL);
	glCompileShader(fragmentShaderId);

	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);
	return(programId);
}

void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);

	programId = CreateShader("vertexShader.glsl", "fragmentShader.glsl");
	glUseProgram(programId);
	modelMatLoc = glGetUniformLocation(programId, "modelMat");
	projMatLoc = glGetUniformLocation(programId, "projMat");
	viewMatLoc = glGetUniformLocation(programId, "viewMat");
	glGenVertexArrays(4, vao);
	
//	PLZ.calc();
//	vao[PLAYAREA] = PLZ.MakeVao();
	
	vao[ANUS] = table.MakeVao();
	vao[SIDES] = table.MakeSidesVao();
	playColorLoc = glGetUniformLocation(programId, "PlayAreaColour");
	glUniform4fv(playColorLoc, 1, &playAreaColours[0]);

	// ...and associate data with vertex shader.
	glGenBuffers(2, budder);
	glBindVertexArray(vao[3]);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(hemVertices), hemVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(hemIndices), hemIndices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(hemVertices[0]), 0);
	glEnableVertexAttribArray(0);
}

void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glm::mat4 projMat = glm::perspective(70.0, 1.0, 0.1, 1000.0);
	glm::mat4 viewMat = glm::lookAt(glm::vec3(0, 10, -40), glm::vec3(0), glm::vec3(0, 1, 0));
	glm::mat4 modelMat = glm::mat4(1);

	glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, value_ptr(projMat));
	glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, value_ptr(viewMat));
	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, value_ptr(modelMat));

	glBindVertexArray(vao[ANUS]);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(vao[SIDES]);
	glDrawElements(GL_TRIANGLE_STRIP, 19, GL_UNSIGNED_INT, 0);

//	modelMat = glm::translate(modelMat, glm::vec3(PLZ.Position));
//	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));

//	glBindVertexArray(vao[PLAYAREA]);
//	glDrawElements(GL_TRIANGLE_STRIP, 24, GL_UNSIGNED_INT, 0);

// Draw ball as two hemispheres.
	glUniform1ui(objectLoc, 3); // Update object name.
	glBindVertexArray(vao[3]);
	glMultiDrawElements(GL_TRIANGLE_STRIP, hemCounts, GL_UNSIGNED_INT, (const void **)hemOffsets, HEM_LATS);
	modelViewMat = scale(modelViewMat, glm::vec3(1.0, -1.0, 1.0)); // Scale to make inverted hemisphere.
	glMultiDrawElements(GL_TRIANGLE_STRIP, hemCounts, GL_UNSIGNED_INT, (const void **)hemOffsets, HEM_LATS);

	glFlush();
	glutSwapBuffers();
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
}

void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'x':
		Xangle += 5.0;
		if (Xangle > 360.0) Xangle -= 360.0;
		glutPostRedisplay();
		break;
	case 'X':
		Xangle -= 5.0;
		if (Xangle < 0.0) Xangle += 360.0;
		glutPostRedisplay();
		break;
	case 'y':
		Yangle += 5.0;
		if (Yangle > 360.0) Yangle -= 360.0;
		glutPostRedisplay();
		break;
	case 'Y':
		Yangle -= 5.0;
		if (Yangle < 0.0) Yangle += 360.0;
		glutPostRedisplay();
		break;
	case 'z':
		Zangle += 5.0;
		if (Zangle > 360.0) Zangle -= 360.0;
		glutPostRedisplay();
		break;
	case 'Z':
		Zangle -= 5.0;
		if (Zangle < 0.0) Zangle += 360.0;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void GamLEP()
{
//
//	PLZ.Position.z += 1.0;
//	glutPostRedisplay();
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