#pragma once
#include <string>
#include <vector>
#include <iterator>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "PrimitiveObject.h"
#include "Camera.h"
#include "Light.h"


class Scene
{
public:
	int width, height;
	
	std::vector<glm::vec3> vertices;
	
	Scene(std::string fileName);

	vec3 CameraPos;
	vec3 Up;
	vec3 CameraLookAt;
	vec3 emission;

	Camera* GetCam();

	float Fov;

	std::vector<PrimitiveObject*> GetPrimitives();
	std::vector<Light*> GetLights();
	

	void AddPrimitive(PrimitiveObject* obj);
	void AddLight(Light* light);

	

	~Scene();
private:

	void checkSceneValidity();

	std::vector<PrimitiveObject*> primitives;

	std::vector<Light*> lights;

	Camera *Cam;

	

};

