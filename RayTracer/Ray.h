#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Ray
{

public:

	Ray();
	~Ray();

private:

	glm::vec3 rayDirection;


};

