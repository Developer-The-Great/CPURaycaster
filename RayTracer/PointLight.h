#pragma once
#include "Light.h"

class PointLight :public Light
{
public:
	PointLight(vec3 positionToSet, vec3 colorToSet);

	~PointLight();
};

