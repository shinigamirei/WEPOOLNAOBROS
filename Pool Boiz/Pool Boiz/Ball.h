#pragma once
#include "GameObject.h"
#include <vector>
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
class Ball :
	public GameObject
{
public:

#define PI 3.14159265
#define HEM_RADIUS 2.0 // Hemisphere radius.
#define HEM_LONGS 10 // Number of longitudinal slices.
#define HEM_LATS 5 // Number of latitudinal slices.
#define HEM_COLORS 0.0, 0.0, 1.0, 1.0 // Hemisphere colors.

	void fillHemVertexArray(glm::vec4 hemVertices[(HEM_LONGS + 1) * (HEM_LATS + 1)]);
	void fillHemIndices(unsigned int hemIndices[HEM_LATS][2 * (HEM_LONGS + 1)]);
	void fillHemCounts(int hemCounts[HEM_LATS]);
	void fillHemOffsets(void* hemOffsets[HEM_LATS]);

	void fillHemisphere(glm::vec4 hemVertices[(HEM_LONGS + 1) * (HEM_LATS + 1)],
		unsigned int hemIndices[HEM_LATS][2 * (HEM_LONGS + 1)],
		int hemCounts[HEM_LATS],
		void* hemOffsets[HEM_LATS]);

	int lats;
	int longs;
	float radius;
	std::vector<float> vertices;
	std::vector<float> indices;
	int indicesCount;
	std::vector<float> colours;
	Ball();
	~Ball();
	void calc();
	void update();
	GLuint MakeVao();
};

