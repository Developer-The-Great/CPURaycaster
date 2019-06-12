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
	
	std::vector<glm::vec3>::iterator iterVec;

	/*for (iterVec = vertices.begin(); iterVec != vertices.end(); ++iterVec)
	{
		cout << glm::to_string(*iterVec) << endl;
	}*/

	int triangleCount = indices.size() / 3;

	for (int i = 0; i < triangleCount; i++)
	{
		cout << "indices" << endl;
		cout << indices[i * 3] << endl;
		cout << indices[i * 3 + 1] << endl;
		cout << indices[i * 3 + 2] << endl;

		Triangle triangle(vertices[indices[i*3]], vertices[indices[i*3 + 1]], vertices[indices[i*3 + 2]]);

		triangles.push_back(triangle);
		
	}
	
	
	/*cout << "triangles count " << triangleCount << endl;
	std::vector<Triangle>::iterator iter;

	for (iter = triangles.begin(); iter != triangles.end(); ++iter)
	{
		cout << *iter << endl;
	}*/

}

std::vector<Triangle> TriangularObject::GetTriangles()
{
	return triangles;
}

TriangularObject::~TriangularObject()
{
	
}

std::ostream & operator<<(std::ostream& os, const TriangularObject & triObj)
{
	// TODO: insert return statement here
	os << "--TriangularObject: " << endl;



	for (auto triangle : triObj.triangles)
	{
		os << triangle << endl;
	}

	return os;
}


