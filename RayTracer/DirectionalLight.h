#pragma once
#include "Light.h"
class DirectionalLight :
	public Light
{
public:
	DirectionalLight(vec3 positionToSet, vec3 colorToSet);

	vec3 GetDirection();
	~DirectionalLight();
};

