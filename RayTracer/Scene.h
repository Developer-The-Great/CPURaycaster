#pragma once
#include <string>
#include <vector>
#include <iterator>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "PrimitiveObject.h"
#include "Camera.h"


class Scene
{
public:
	int width, height;

	std::vector<PrimitiveObject> primitives;

	std::vector<glm::vec3> vertices;
	
	Scene(std::string fileName);

	glm::vec3 CameraPos;
	glm::vec3 Up;
	glm::vec3 CameraLookAt;
	Camera* GetCam();

	float Fov;


	~Scene();
private:

	void checkSceneValidity();

	Camera *Cam;



};

