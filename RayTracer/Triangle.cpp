#include "pch.h"
#include "Triangle.h"

#define TRIANGLEVERTICES 3
Triangle::Triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
	triangles[0] = a;
	triangles[1] = b;
	triangles[2] = c;
}


Triangle::~Triangle()
{
}

glm::vec3 * Triangle::GetTriangles()
{
	return triangles;
}

std::ostream & operator<<(std::ostream& os, Triangle& triangle)
{
	// TODO: insert return statement here
	os << "Triangle: " << std::endl;

	for (size_t i = 0; i < TRIANGLEVERTICES; i++)
	{
		std::cout << triangle.triangles[i].x << " " << triangle.triangles[i].y << " " << triangle.triangles[i].y << std::endl;
	}
	
	return os;
}
