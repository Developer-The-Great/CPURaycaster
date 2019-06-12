// RayTracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/string_cast.hpp>
#include "Ray.h"

#include "FreeImage.h"
#include "Scene.h"
#include "Image.h"

#define WIDTH 640
#define HEIGHT 480

using std::cout;
using std::endl;

Image* rayTrace(int width, int height, std::string fileName, Scene*scene);
glm::vec3 FindColor(PrimitiveObject*Obj);

int main()
{
	std::string fileName;

	cout << "Welcome to not real time ray tracing!" << endl;
	cout << "Input file name: ";

	std::getline(std::cin, fileName);

	Scene* scene = new Scene(fileName);

	Image* image = rayTrace(WIDTH, HEIGHT, fileName,scene);

	if (image)
	{
		image->SaveImage();
		delete image;
	}
	else
	{
		cout << "ERROR::IMAGE_IS_NULL" << endl;
	}
	
	delete scene;
	
	return 0;
}
Image* rayTrace(int width,int height, std::string fileName, Scene*scene)
{
	unsigned int Total = width * height;
	//make a new image
	Image* image = new Image(width, height, fileName);

	if (!image->bitmap) 
	{ 
		cout << "NULL_BITMAP" << endl; 
		return nullptr;
	}

	Ray ray(scene->width,scene->height);
	Camera* cam = scene->GetCam();

	cout << "cam w " << glm::to_string(cam->GetWAxis()) << endl;
	cout << "cam u " << glm::to_string(cam->GetUAxis()) << endl;
	cout << "cam v " << glm::to_string(cam->GetVAxis()) << endl;
	for (int i = 0; i < height; ++i)
	{
		unsigned int CurrentRow = i * width;
		for (int j = 0; j < width; ++j)
		{
			//shoot a ray through the pixel
			ray.FindRayDirection(cam, i, j);;
			//check for intersection
			PrimitiveObject* Obj = ray.IntersectionCheck(scene);

			//find the final color
			glm::vec3 color = FindColor(Obj);
	
			image->SetPixel(j, i, color);

			
		}
		if (i % 2 == 0)
		{
			cout << "Completed pixels " << CurrentRow  << "/" << Total << std::endl;
		}
	}
	cout << "IMAGE_COMPLETED" << endl;

	
	//return image
	return image;

}

glm::vec3 FindColor(PrimitiveObject*Obj)
{
	
	if (!Obj)
	{
		glm::vec3 black(0, 0, 0);
		return black;
	}

	return Obj->GetAmbient();
}

