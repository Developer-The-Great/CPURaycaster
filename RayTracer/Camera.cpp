#include "pch.h"
#include "Camera.h"
#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/string_cast.hpp>



Camera::Camera(glm::vec3 pos, glm::vec3 lookAtPos, glm::vec3 upDirection, float fovVec)
{
	position = pos;

	lookAt = lookAtPos;

	Up = upDirection;

	fov = fovVec;
	createCoordinateFrame(pos, lookAtPos, upDirection);

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

glm::vec3 Camera::GetCamPos()
{
	
	return position;
}

float Camera::GetFov()
{
	return fov;
}



void Camera::createCoordinateFrame(glm::vec3 pos, glm::vec3 lookAtPos, glm::vec3 upDirection)
{
	//create w
	std::cout << "----------PARAMETER CHECK" << std::endl;
	std::cout << "pos" << glm::to_string(pos) << std::endl;
	std::cout << "lookAtPos" << glm::to_string(lookAtPos) << std::endl;
	std::cout << "upDirection" << glm::to_string(upDirection) << std::endl;

	w = glm::normalize(pos - lookAtPos);
	
	
	//create u
	u = glm::normalize(glm::cross(upDirection,w ));
	//create v
	v = glm::normalize(glm::cross(w, u));
}
