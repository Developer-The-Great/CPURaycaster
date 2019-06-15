#pragma once
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

typedef glm::mat4 mat4;
typedef glm::vec3 vec3;

class Transform
{
public:
	Transform();
	static mat4 translate(const float &tx, const float &ty, const float &tz);
	static mat4 scale(const float &tx, const float &ty, const float &tz);
	static mat4 rotate(const float& degrees, const vec3& axis);

	
	~Transform();
};

