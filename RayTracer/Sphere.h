#pragma once
#include "PrimitiveObject.h"
#include <iostream>

class Sphere : public PrimitiveObject
{
public:
	Sphere(glm::vec3 positionToSet, glm::vec3 ambientToSet, float radiusToSet);

	float GetRadius() const;
	glm::vec3 GetPosition() const;

	~Sphere();
	friend std::ostream& operator<<(std::ostream& os, const Sphere& sphere);

private:
	
	float radius;
};

