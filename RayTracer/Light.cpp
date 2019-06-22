#include "pch.h"
#include "Light.h"



#define COLOR 255.0f

Light::Light(vec3 positionToSet, vec3 colorToSet)
{
	position = positionToSet;
	color = colorToSet * COLOR;
}



Light::~Light()
{
}

vec3 Light::GetPosition()
{
	return position;
}

vec3 Light::GetColor()
{
	return color;
}
