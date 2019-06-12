#include "pch.h"
#include "Scene.h"
#include "FileReader.h"
#include "TriangularObject.h"
#include "Sphere.h"
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


std::vector<PrimitiveObject*> Scene::GetPrimitives()
{
	return primitives;
}

void Scene::AddPrimitive(PrimitiveObject* obj)
{
	primitives.push_back(obj);
}

Scene::~Scene()
{

	for (auto obj : primitives)
	{
		delete obj;
	}
	primitives.clear();
	
	delete Cam;
}

void Scene::checkSceneValidity()
{
	cout << "----------Scene Validity Check-----------" << glm::to_string(CameraPos) << endl;
	cout << "CameraPos: " << glm::to_string(CameraPos) << endl;
	cout << "CameraLookAt: " << glm::to_string(CameraLookAt) << endl;
	cout << "CameraUp: " << glm::to_string(Up) << endl;
	cout << "Fov " << Fov << std::endl;

	std::vector<PrimitiveObject*>::iterator iter;

	for (auto primitive : primitives)
	{
		TriangularObject* triObj = dynamic_cast<TriangularObject*>(primitive);

		if (triObj)
		{
			cout << *triObj << endl;
		}
		else
		{
			Sphere* sphere = dynamic_cast<Sphere*>(primitive);
			if (sphere)
			{
				cout << *sphere << endl;
			}
		}
		
	}

}
