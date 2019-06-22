#pragma once
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

typedef glm::mat3 mat3;
typedef glm::mat4 mat4;
typedef glm::vec3 vec3;

const double pi = 3.14159265;

class Transform
{
public:
	Transform();
	static mat3 rotate(const float degrees, const vec3 & axis);
	static mat4 translate(const float &tx, const float &ty, const float &tz);
	static mat4 scale(const float &tx, const float &ty, const float &tz);


private:
	
	~Transform();
};

