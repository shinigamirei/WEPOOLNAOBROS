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
#include"Table.h"
#include"Ball.h"
#include"CueBall.h"
#include"Cue.h"

#include "glm\common.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm\gtx\rotate_vector.hpp>

World world;
Table table;
CueBall player;
Ball ball1;
Ball ball2;
Ball ball3;
Ball ball4;
Ball ball5;
Ball ball6;
Ball ball7;
Ball ball8;
Ball ball9;
Ball ball10;
Ball ball11;
Ball ball12;
Ball ball13;
Ball ball14;
Ball ball15;
Cue cue;


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
vao[19];


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

	world.redBalls.push_back(ball1);
	world.redBalls.push_back(ball2);
	world.redBalls.push_back(ball3);
	world.redBalls.push_back(ball4);
	world.redBalls.push_back(ball5);
	world.redBalls.push_back(ball6);
	world.redBalls.push_back(ball7);
	world.yellowBalls.push_back(ball9);
	world.yellowBalls.push_back(ball10);
	world.yellowBalls.push_back(ball11);
	world.yellowBalls.push_back(ball12);
	world.yellowBalls.push_back(ball13);
	world.yellowBalls.push_back(ball14);
	world.yellowBalls.push_back(ball15);
	
	ball1.position = glm::vec3(0, 0, -20);
	ball2.position = glm::vec3(-2, 0, -22.5);
	ball3.position = glm::vec3(4, 0, -25);
	ball4.position = glm::vec3(-6, 0, -27.5);
	ball5.position = glm::vec3(-2, 0, -27.5);
	ball6.position = glm::vec3(8, 0, -30);
	ball7.position = glm::vec3(4, 0, -30);
	ball8.position = glm::vec3(0, 0, -25);
	ball9.position = glm::vec3(2, 0, -22.5);
	ball10.position = glm::vec3(-4, 0, -25);
	ball11.position = glm::vec3(2, 0, -27.5);
	ball12.position = glm::vec3(6, 0, -27.5);
	ball13.position = glm::vec3(-8, 0, -30);
	ball14.position = glm::vec3(-4, 0, -30);
	ball15.position = glm::vec3(0, 0, -30);

	ball1.colour = glm::vec4(1, 0, 0, 1);
	ball2.colour = glm::vec4(1, 0, 0, 1);
	ball3.colour = glm::vec4(1, 0, 0, 1);
	ball4.colour = glm::vec4(1, 0, 0, 1);
	ball5.colour = glm::vec4(1, 0, 0, 1);
	ball6.colour = glm::vec4(1, 0, 0, 1);
	ball7.colour = glm::vec4(1, 0, 0, 1);
	ball9.colour = glm::vec4(1, 1, 0, 1);
	ball10.colour = glm::vec4(1, 1, 0, 1);
	ball11.colour = glm::vec4(1, 1, 0, 1);
	ball12.colour = glm::vec4(1, 1, 0, 1);
	ball13.colour = glm::vec4(1, 1, 0, 1);
	ball14.colour = glm::vec4(1, 1, 0, 1);
	ball15.colour = glm::vec4(1, 1, 0, 1);


	glGenVertexArrays(19, vao);

	vao[2] = player.MakeVao();
	vao[3] = ball1.MakeVao();
	vao[4] = ball2.MakeVao();
	vao[5] = ball3.MakeVao();
	vao[6] = ball4.MakeVao();
	vao[7] = ball5.MakeVao();
	vao[8] = ball6.MakeVao();
	vao[9] = ball7.MakeVao();
	vao[10] = ball8.MakeVao();
	vao[11] = ball9.MakeVao();
	vao[12] = ball10.MakeVao();
	vao[13] = ball11.MakeVao();
	vao[14] = ball12.MakeVao();
	vao[15] = ball13.MakeVao();
	vao[16] = ball14.MakeVao();
	vao[17] = ball15.MakeVao();

	vao[18] = cue.MakeVao();

	vao[0] = table.MakeVao();
	vao[1] = table.MakeSidesVao();


}

void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glm::mat4 projMat = glm::perspective(70.0, 1.0, 0.1, 1000.0);
	glm::mat4 viewMat = glm::lookAt(glm::vec3(0, 100, 1), glm::vec3(0), glm::vec3(0, 1, 0));
	glm::mat4 modelMat = glm::mat4(1);

	glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, value_ptr(projMat));
	glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, value_ptr(viewMat));
	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, value_ptr(modelMat));


	table.render(modelMatLoc, vao, 0, 12);
	player.render(modelMatLoc, vao, 2,player.indicesCount);
	ball1.render(modelMatLoc, vao, 3, player.indicesCount);
	ball2.render(modelMatLoc, vao, 4, player.indicesCount);
	ball3.render(modelMatLoc, vao, 5, player.indicesCount);
	ball4.render(modelMatLoc, vao, 6, player.indicesCount);
	ball5.render(modelMatLoc, vao, 7, player.indicesCount);
	ball6.render(modelMatLoc, vao, 8, player.indicesCount);
	ball7.render(modelMatLoc, vao, 9, player.indicesCount);
	ball8.render(modelMatLoc, vao, 10, player.indicesCount);
	ball9.render(modelMatLoc, vao, 11, player.indicesCount);
	ball10.render(modelMatLoc, vao, 12, player.indicesCount);
	ball11.render(modelMatLoc, vao, 13, player.indicesCount);
	ball12.render(modelMatLoc, vao, 14, player.indicesCount);
	ball13.render(modelMatLoc, vao, 15, player.indicesCount);
	ball14.render(modelMatLoc, vao, 16, player.indicesCount);
	ball15.render(modelMatLoc, vao, 17, player.indicesCount);

	table.render(modelMatLoc, vao, 1, 10);
	
	cue.render(modelMatLoc, vao, 18, cue.indicesCount);
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
		std::cout << player.force;
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
	for each (GameObject i in world.redBalls)
		i.Update();
	for each (GameObject i in world.yellowBalls)
		i.Update();
	player.Update();
	player.BallCollision(ball1);
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