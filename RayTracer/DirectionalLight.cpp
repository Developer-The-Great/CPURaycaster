#include "pch.h"
#include "DirectionalLight.h"



DirectionalLight::DirectionalLight(vec3 directionToSet, vec3 colorToSet):Light(directionToSet,colorToSet)
{
}



vec3 DirectionalLight::GetDirection()
{
	return GetPosition();
}

DirectionalLight::~DirectionalLight()
{
	
}
