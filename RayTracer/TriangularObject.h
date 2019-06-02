#pragma once
#include "PrimitiveObject.h"

class Triangle;

class TriangularObject:public PrimitiveObject
{

public:
	TriangularObject(glm::vec3 AmbientToSet, glm::vec3 PositionToSet, std::vector<glm::vec3>vertices, std::vector<int>indices);
	

	~TriangularObject();
private:
	std::vector<Triangle> triangles;

};

