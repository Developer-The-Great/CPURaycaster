#include "pch.h"
#include "Scene.h"
#include "FileReader.h"

#include <gtx/string_cast.hpp>

using std::cout;
using std::endl;

Scene::Scene(std::string fileName)
{
	FileReader Reader;

	Reader.ReadFile(fileName, this);

	cout << "width " << width << endl;
	cout << "height " << height << endl;

	Cam = new Camera(CameraPos, CameraLookAt,Up, Fov);


	checkSceneValidity();

}

Camera * Scene::GetCam()
{
	return Cam;
}


Scene::~Scene()
{
	delete Cam;
}

void Scene::checkSceneValidity()
{
	cout << "CameraPos: " << glm::to_string(CameraPos) << endl;
	cout << "CameraLoc: " << glm::to_string(CameraLookAt) << endl;
	cout << "CameraUp: " << glm::to_string(Up) << endl;
	cout << "Fov " << Fov << std::endl;

	std::vector<PrimitiveObject>::iterator iter;

	/*for (iter = primitives.begin(); iter < primitives.end; iter++)
	{
		cout << iter->
	}*/



}
