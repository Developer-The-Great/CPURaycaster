#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Camera;

class Ray
{

public:

	Ray(float sceneWidth, float sceneHeight);
	~Ray();
	glm::vec3 GetRayDirection();
	glm::vec3 FindRayDirection(Camera*cam, int i, int j);
private:
	float width;
	float height;

	

	glm::vec3 rayDirection;


};

