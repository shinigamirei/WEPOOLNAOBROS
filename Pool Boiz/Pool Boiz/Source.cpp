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
#define SIDES 2

Camera camera;

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
vao[3];

static glm::mat4 modelViewMat = glm::mat4(1.0);
static glm::mat4 projMat = glm::mat4(1.0);
static float Xangle = 0.0, Yangle = 0.0, Zangle = 0.0; // Angles to rotate scene.

static int torCounts[4];

//66*33
//72*36
//edge

float Vertexs[] = //on eye level atm
{
	-18.0,0.0,-36.0,
	-16.5,0.0,-33.0,
	18.0,0.0,36.0,
	16.5,0.0,33.0,
	18.0,0.0,36.0,
	16.5,0.0,33.0,
	-18.0,0.0,36.0,
	-16.5,0.0,33.0
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
	-16.5,-1.0,-33.0,
	16.5,-1.0,-33.0,
	-16.5,-1.0,33.0,
	16.5,-1.0,33.0
};

static glm::vec4 playAreaColours = { 0.0,1.0,0.0,1.0 };

float sidesVert[] =
{
	-16.5,0.0,-33.0,
	-16.5,-1.0,-33.0,
	-16.5,0.0,33.0,
	-16.5,-1.0,33.0,
	16.5,0.0,33.0,
	16.5,-1.0,33.0,
	16.5,0.0,-33.0,
	16.5,-1.0,-33.0
};
float sidesColors[] =
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

void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	// Calculate and update modelview matrix.
	//this is where we would translate e.g camera
	//modelViewMat = glm::mat4(1.0);
	//modelViewMat = glm::rotate(modelViewMat, Zangle, glm::vec3(0.0, 0.0, 1.0));
	//modelViewMat = glm::rotate(modelViewMat, Yangle, glm::vec3(0.0, 1.0, 0.0));
	//modelViewMat = glm::rotate(modelViewMat, Xangle, glm::vec3(1.0, 0.0, 0.0));
	//glUniformMatrix4fv(modelViewMatLoc, 1, GL_FALSE, value_ptr(modelViewMat));

	//glUniform1ui(objectLoc, ANUS); // Update object name.
	//glBindVertexArray(vao[ANUS]);
	//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

	//glUniform1ui(objectLoc, PLAYAREA); // Update object name.
	//glBindVertexArray(vao[PLAYAREA]);
	//glMultiDrawElements(GL_TRIANGLE_STRIP, torCounts, GL_UNSIGNED_INT,0,4);

	//glBindVertexArray(vao[SIDES]);
	//glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, 0);
	 


	glm::mat4 projMat = glm::perspective(70.0, 1.0, 0.1, 1000.0);
	glm::mat4 viewMat = glm::lookAt(glm::vec3(0, 1, -4), glm::vec3(0), glm::vec3(0, 1, 0));
	glm::mat4 modelMat = glm::mat4(1);

	glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, value_ptr(projMat));
	glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, value_ptr(viewMat));
	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, value_ptr(modelMat));
	
	glBindVertexArray(vao[ANUS]);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0);



	glFlush();
	glutSwapBuffers();
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
/*	// Create shader program executable.
	char* vertexShader = readTextFile("vertexShader.glsl");
	vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, (const char**)&vertexShader, NULL);
	glCompileShader(vertexShaderId);

	char* fragmentShader = readTextFile("fragmentShader.glsl");
	fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, (const char**)&fragmentShader, NULL);
	glCompileShader(fragmentShaderId);

	programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);
	glUseProgram(programId);
	///////////////////////////////////////
*/
	glGenVertexArrays(3, vao);
	

	{
		GLuint this_vao;
		glGenVertexArrays(1, &this_vao);
		glBindVertexArray(this_vao);


		float verts[]{
			0.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
		};
		float colours[]{
			1,0,0,1,
			0,1,0,1,
			0,0,1,1,
			0,0,0,0
		};

		unsigned int inds[]
		{
			1,0,2,3
		};

		//Vertex vbo
		{
			GLuint vbo;
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(verts) * sizeof(float), &verts[0], GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
			glEnableVertexAttribArray(0);
		}
		//Vertex colours
		{
			GLuint vbo;
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(colours) * sizeof(float), &colours[0], GL_STATIC_DRAW);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
			glEnableVertexAttribArray(1);
		}
		//Index vbo
		{
			GLuint vbo;
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(inds) * sizeof(unsigned int), &inds[0], GL_STATIC_DRAW);
		}


		glBindVertexArray(0);

		vao[ANUS] = this_vao;
	}

	/*
	// BEGIN bind VAO id vao[ANNULUS] to the set of vertex array calls following.
	glBindVertexArray(vao[ANUS]);
	glGenBuffers(2, buffer); // Generate buffer ids.
	glBindBuffer(GL_ARRAY_BUFFER, buffer[VERTICES]);// Bind vertex buffer and reserve space.
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertexs), Vertexs, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[INDICES]);// Bind and fill indices buffer to tell gpu the order of which to draw
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(stripIndices), stripIndices, GL_STATIC_DRAW);	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertexs[0]), 0);// Specify vertex pointers to the start of the respective data.
	glEnableVertexAttribArray(0);
	// END bind VAO id vao[ANNULUS].

	// BEGIN bind VAO id vao[trin] to the set of vertex array calls following
	glBindVertexArray(vao[PLAYAREA]);
	glGenBuffers(2, buffer); // Generate buffer ids
	glBindBuffer(GL_ARRAY_BUFFER, buffer[VERTICES]);// Bind vertex buffer and
	glBufferData(GL_ARRAY_BUFFER, sizeof(playAreaVert) * sizeof(float), playAreaVert, GL_STATIC_DRAW);//reserve space
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[INDICES]);// Bind and fill indices buffer.
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(stripIndices), stripIndices, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(playAreaVert[0]), 0);
	glEnableVertexAttribArray(1);
	// END bind VAO id vao[tRIN].

	// BEGIN bind VAO id vao[sides] to the set of vertex array calls following
	glBindVertexArray(vao[SIDES]);
	glGenBuffers(2, buffer); // Generate buffer ids
	glEnableClientState(GL_VERTEX_ARRAY);// Enable two vertex arrays: co-ordinates and color
	glEnableClientState(GL_COLOR_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[VERTICES]);// Bind vertex buffer and
	glBufferData(GL_ARRAY_BUFFER, sizeof(sidesVert) + sizeof(sidesVert), NULL, GL_STATIC_DRAW);//reserve space
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(sidesVert), sidesVert);// Copy vertex coordinates data into first half of vertex buffer.
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(sidesVert), sizeof(sidesColors), sidesColors);// Copy vertex color data into second half of vertex buffer.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[INDICES]);// Bind and fill indices buffer.
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(stripIndices), stripIndices, GL_STATIC_DRAW);
	glVertexPointer(3, GL_FLOAT, 0, 0);// Specify vertex and color pointers to the start of the respective data.
	glColorPointer(3, GL_FLOAT, 0, (GLvoid*)(sizeof(sidesVert)));
	// END bind VAO id vao[sides].
	*/


	// Obtain color uniform locations and set values.
//	anusColorLoc = glGetUniformLocation(programId, "hemColor");
//	glUniform4fv(hemColorLoc, 1, &hemColors[0]);
	playColorLoc = glGetUniformLocation(programId, "PlayAreaColour");
	glUniform4fv(playColorLoc, 1, &playAreaColours[0]);





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