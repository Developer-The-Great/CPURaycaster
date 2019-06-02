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

#define WIDTH 400
#define HEIGHT 400


using std::cout;
using std::endl;

Image* rayTrace(int width, int height, std::string fileName, Scene*scene);

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

	Ray ray(WIDTH, HEIGHT);
	Camera* cam = scene->GetCam();

	cout << "cam w " << glm::to_string(-cam->GetWAxis()) << endl;
	for (int i = 0; i < height; ++i)
	{
		unsigned int CurrentRow = i * width;
		for (int j = 0; j < width; ++j)
		{
			//shoot a ray through the pixel
			glm::vec3 direction = ray.FindRayDirection(cam, i, j);
			//check for intersection
			if (i == 200 && j == 200)
			{
				cout << "for height " << i << ",width " << j << " direction: " << glm::to_string(direction) << endl;
			}
			
			//find the final color
			glm::vec3 color = glm::vec3(0, (double)j / width * 255.0, (double)i / height * 255.0);
	
			image->SetPixel(j, i, color);

			if(j%100 == 0)
			{
				//cout << "Completed pixels " << CurrentRow + j << "/" << Total << std::endl;
			}
		}
	}
	cout << "IMAGE_COMPLETED" << endl;

	
	//return image
	return image;

}

