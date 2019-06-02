#pragma once
#include "PrimitiveObject.h"

class Sphere : public PrimitiveObject
{
public:
	Sphere(glm::vec3 positionToSet, glm::vec3 ambientToSet, float radiusToSet);
	~Sphere();
private:
	
	float radius;
};

