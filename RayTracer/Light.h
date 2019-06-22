#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

typedef glm::vec3 vec3;


class Light
{
public:
	Light(vec3 positionToSet,vec3 colorToSet);
	
	virtual ~Light();

	vec3 GetPosition();
	vec3 GetColor();

private:
	vec3 position;
	vec3 color;
};

