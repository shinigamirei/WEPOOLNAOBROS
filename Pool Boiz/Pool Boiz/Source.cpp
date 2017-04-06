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
#include"CueBall.h"

#include "glm\common.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm\gtx\rotate_vector.hpp>

#define VERTICES 0
#define INDICES 1
#define ANUS 0
#define PLAYAREA 1
#define SIDES 2

Camera camera;
Table table;
Ball PLZ;
CueBall player;

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
vao[4];


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
	
	vao[4] = player.MakeVao();

	vao[PLAYAREA] = PLZ.MakeVao();
	
	vao[ANUS] = table.MakeVao();
	vao[SIDES] = table.MakeSidesVao();


}

void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glm::mat4 projMat = glm::perspective(70.0, 1.0, 0.1, 1000.0);
	glm::mat4 viewMat = glm::lookAt(glm::vec3(0, 10, 1), glm::vec3(0), glm::vec3(0, 1, 0));
	glm::mat4 modelMat = glm::mat4(1);

	glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, value_ptr(projMat));
	glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, value_ptr(viewMat));
	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, value_ptr(modelMat));

	table.render(modelMatLoc, vao, ANUS, 12);
	player.render(modelMatLoc, vao, 4, 24);

	PLZ.render(modelMatLoc, vao, PLAYAREA, 12);
	table.render(modelMatLoc, vao, SIDES, 10);

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
	case 'q':
		player.hit();
		break;
	case 'a':
		player.heading = glm::rotateY(player.heading, glm::radians(5.0f));
		break;
	case 'd':
		player.heading = glm::rotateY(player.heading, glm::radians(-5.0f));
		break;
	case 'w':
		player.force += 0.1;
		if (player.force > 1) player.force = 1;
		break;
	case's':
		player.force -= 0.1;
		if (player.force < 0) player.force = 0;
		break;
	default:
		break;
	}
}

void GamLEP()
{
	PLZ.update();
	player.update();
	glutPostRedisplay();
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