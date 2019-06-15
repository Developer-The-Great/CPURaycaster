#include "pch.h"
#include "Transform.h"


Transform::Transform()
{
}

mat4 Transform::translate(const float & tx, const float & ty, const float & tz)
{
	mat4 translate
	(	1.0, 0, 0, tx,
		0, 1.0, 0, ty,
		0, 0, 1.0, tz,
		0, 0, 0, 1.0
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

mat4 Transform::rotate(const float & degrees, const vec3 & axis)
{
	return mat4(1.0);
}


Transform::~Transform()
{
}
