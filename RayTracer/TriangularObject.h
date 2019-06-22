#pragma once
#include "PrimitiveObject.h"
#include <iostream>
class Triangle;

class TriangularObject:public PrimitiveObject
{

public:
	TriangularObject(glm::vec3 AmbientToSet, vec3 diffuseToSet,glm::vec3 PositionToSet, std::vector<glm::vec3>vertices, std::vector<int>indices);
	
	std::vector<Triangle> GetTriangles();
	~TriangularObject();

	friend std::ostream & operator<<(std::ostream& os, const TriangularObject & triObj);
	
private:
	std::vector<Triangle> triangles;
	
};

