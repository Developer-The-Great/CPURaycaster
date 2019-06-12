#include "pch.h"
#include "Sphere.h"
#include <gtx/string_cast.hpp>
#include <iostream>



Sphere::Sphere(glm::vec3 positionToSet,glm::vec3 ambientToSet, float radiusToSet):PrimitiveObject(ambientToSet,positionToSet)
{
	std::cout << "Sphere Created" << std::endl;
	std::cout << "Position " << glm::to_string(positionToSet) << std::endl;
	radius = radiusToSet;
}

float Sphere::GetRadius() const
{
	return radius;
}

glm::vec3 Sphere::GetPosition() const
{
	return position;
}

Sphere::~Sphere()
{
}

std::ostream & operator<<(std::ostream & os, const Sphere & sphere)
{
	// TODO: insert return statement here
	os << "--Sphere" << std::endl;

	os << "Position " << glm::to_string(sphere.position) << std::endl;
	os << "Radius " << sphere.radius << std::endl;

	return os;
	
}
