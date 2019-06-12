#pragma once
#include <vector>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/string_cast.hpp>

#include <iostream>

class Triangle
{
public:
	Triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c);
	~Triangle();
	glm::vec3* GetTriangles() ;

	friend std::ostream& operator<<(std::ostream& os, Triangle& triangle);

private:

	glm::vec3 triangles[3];
};

