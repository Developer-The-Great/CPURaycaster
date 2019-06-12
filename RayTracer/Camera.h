#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Camera
{
public:


	Camera(glm::vec3 pos,glm::vec3 lookAtPos, glm::vec3 upDirection,float fovVec);
	~Camera();

	glm::vec3 GetWAxis();
	glm::vec3 GetUAxis();
	glm::vec3 GetVAxis();

	glm::vec3 GetCamPos();
	float GetFov();

private:

	glm::vec3 w,u,v;

	glm::vec3 position;
	glm::vec3 lookAt;
	glm::vec3 Up;
	float fov;

	void createCoordinateFrame(glm::vec3 pos, glm::vec3 lookAtPos, glm::vec3 upDirection);


};

