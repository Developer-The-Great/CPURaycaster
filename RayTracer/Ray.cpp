#include "pch.h"
#include "Ray.h"
#include "Camera.h"


Ray::Ray(float sceneWidth,float sceneHeight)
{
	width = sceneWidth;
	height = sceneHeight;

}

Ray::~Ray()
{
}

glm::vec3 Ray::GetRayDirection()
{
	return glm::vec3();
}

glm::vec3 Ray::FindRayDirection(Camera * cam, int i, int j)
{
	float maxAngle = glm::tan(cam->GetFov() / 2.0f);

	float alphaC = (j - (width / 2)) / (width / 2);

	float betaC = ((height / 2) - i) / (height / 2);

	float alpha = maxAngle * alphaC;

	float beta = maxAngle * betaC;

	glm::vec3 direction = (alpha *cam->GetUAxis() + beta * cam->GetVAxis() - cam->GetWAxis());

	direction = glm::normalize(direction);

	return direction;
}
