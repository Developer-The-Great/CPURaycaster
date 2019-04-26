// RayTracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include "FreeImage.h"
#include "Image.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#define WIDTH 400
#define HEIGHT 400

#define OUT

using std::cout;
using std::endl;

Image* rayTrace(int width, int height, std::string fileName);

int main()
{
	std::string fileName;

	cout << "Welcome to not real time ray tracing!" << endl;
	cout << "Input file name: ";

	std::getline(std::cin, fileName);

	Image* image = rayTrace(WIDTH, HEIGHT, fileName);

	if (image)
	{
		image->SaveImage();
		delete image;
	}
	else
	{
		cout << "ERROR::IMAGE_IS_NULL" << endl;
	}
	

	
	
	return 0;
}
Image* rayTrace(int width,int height, std::string fileName)
{
	unsigned int Total = width * height;
	//make a new image
	Image* image = new Image(width, height, fileName);

	if (!image->bitmap) 
	{ 
		cout << "NULL_BITMAP" << endl; 
		return nullptr;
	}


	for (int i = 0; i < height; i++)
	{
		unsigned int CurrentRow = i * width;
		for (int j = 0; j < width; j++)
		{
			//shoot a ray through the pixel
			
			//check for intersection

			//find the final color
			glm::vec3 color = glm::vec3(0, (double)j / width * 255.0, (double)i / height * 255.0);
	
			image->SetPixel(j, i, color);

			if(j%100 == 0)
			{
				cout << "Completed pixels " << CurrentRow + j << "/" << Total << std::endl;
			}
		}
	}
	cout << "IMAGE_COMPLETED" << endl;

	
	//return image
	return image;

}

