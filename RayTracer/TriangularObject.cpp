#include "pch.h"
#include "TriangularObject.h"
#include "Triangle.h"
#include <iostream>

using std::cout;
using std::endl;

TriangularObject::TriangularObject(glm::vec3 AmbientToSet,glm::vec3 PositionToSet,std::vector<glm::vec3>vertices,std::vector<int>indices)
	:PrimitiveObject(AmbientToSet, PositionToSet)
{
	

	cout << "creating triangular obj: " << endl;
	cout << "indices length " << indices.size() << endl;

	int triangleCount = indices.size() / 3;

	for (int i = 0; i < triangleCount; i++)
	{

		Triangle triangle(vertices[indices[i*3]], vertices[indices[i*3 + 1]], vertices[indices[i*3 + 2]]);

		triangles.push_back(triangle);
		
	}
	Triangle tri(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	
	cout << "triangles count " << triangleCount << endl;
	std::vector<Triangle>::iterator iter;

	for (iter = triangles.begin(); iter != triangles.end(); ++iter)
	{
		cout << *iter << endl;
	}
}

TriangularObject::~TriangularObject()
{
}
