#include "pch.h"
#include "Camera.h"





Camera::Camera(glm::vec3 pos, glm::vec3 lookAtPos, glm::vec3 upDirection, float fovVec)
{
	position = pos;

	lookAt = lookAtPos;

	Up = upDirection;

	fov = fovVec;
	createCoordinateFrame(pos, lookAtPos, upDirection, fovVec);

}

Camera::~Camera()
{
}

glm::vec3 Camera::GetWAxis()
{
	return w;
}

glm::vec3 Camera::GetUAxis()
{
	return u;
}

glm::vec3 Camera::GetVAxis()
{
	return v;
}

float Camera::GetFov()
{
	return fov;
}



void Camera::createCoordinateFrame(glm::vec3 pos, glm::vec3 lookAtPos, glm::vec3 upDirection, float fovVec)
{
	//create w
	w = glm::normalize(pos - lookAtPos);
	//create u
	u = glm::normalize(glm::cross(w, upDirection));
	//create v
	v = glm::normalize(glm::cross(w, u));
}
