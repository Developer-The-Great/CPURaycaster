#include "pch.h"
#include "Transform.h"
#include <iostream>

Transform::Transform()
{
}
mat3 Transform::rotate(const float degrees, const vec3& axis)
{
	glm::normalize(axis);

	mat3 I(1.0);

	mat3 UCrossProductMatrix(
		0, axis.z, -axis.y,
		-axis.z, 0, axis.x,
		axis.y, -axis.x, 0);

	//R(axis,0) = I*cos(0) + axis*axis^T(1-cos(0)) + axis sin0
	mat3 Result = I * glm::cos(glm::radians(degrees)) + glm::outerProduct(axis, axis)*(1 - glm::cos(glm::radians(degrees))) + UCrossProductMatrix * glm::sin(glm::radians(degrees));

	return Result;
}

mat4 Transform::translate(const float & tx, const float & ty, const float & tz)
{
	mat4 translate
	(	1.0, 0, 0, tx,
		0, 1.0, 0, ty,
		0, 0, 1.0, tz,
		0, 0, 0,  1.0
	);
	return translate;
}

mat4 Transform::scale(const float & tx, const float & ty, const float & tz)
{
	mat4 scale
	(	tx, 0, 0, 0,
		0, ty, 0, 0,
		0, 0, tz, 0,
		0, 0, 0, 1
	);
	return scale;
}



Transform::~Transform()
{
}
