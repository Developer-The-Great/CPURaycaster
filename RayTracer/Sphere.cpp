#include "pch.h"
#include "Sphere.h"





Sphere::Sphere(glm::vec3 positionToSet,glm::vec3 ambientToSet, float radiusToSet):PrimitiveObject(positionToSet,ambientToSet)
{
	
	radius = radiusToSet;
}

Sphere::~Sphere()
{
}
