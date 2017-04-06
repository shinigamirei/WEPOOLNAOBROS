#include "GameObject.h"
#include <iostream>
#include<vector>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>

#include "glm\common.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::update()
{

}

void GameObject::render(unsigned int modelMatLoc, unsigned int vao[], int num,int indec)
{
	glm::mat4 modelMat(1);
	modelMat = glm::translate(modelMat, glm::vec3(position));
	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));

	glBindVertexArray(vao[num]);
	glDrawElements(GL_TRIANGLE_STRIP, indec, GL_UNSIGNED_INT, 0);
}
