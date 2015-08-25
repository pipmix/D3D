#include "loadOBJ.h"





loadOBJ::loadOBJ(string filename)
{
}

loadOBJ::~loadOBJ()
{
}

void loadOBJ::addVertex(float x, float y, float z){



		vertices.push_back(
			XMFLOAT3(
			(vertices[x], vertices[x + 1], vertices[x + 2]),
			vertices[y], vertices[y + 1], vertices[y + 2],
			vertices[z], vertices[z + 1], vertices[z + 2]
				)
			);







}
