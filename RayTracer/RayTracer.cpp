// RayTracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;

void rayTrace(int width, int height);

int main()
{
	std::string fileName;

	cout << "Welcome to not real time ray tracing!" << endl;
	cout << "Input file name: ";

	std::getline(std::cin, fileName);

	const int width = 400;
	const int height = 400;

	//rayTrace(width,height);

	








}
void rayTrace(int width,int height)
{
	unsigned int Total = width * height;
	//make a new image

	for (int i = 0; i < height; i++)
	{
		unsigned int CurrentRow = i * width;
		for (int j = 0; j < width; j++)
		{
			//shoot a ray through the pixel

			//check for intersection

			//find the final color
			
			if(j%100 == 0)
			{
				cout << "Completed pixels " << CurrentRow + j << "/" << Total << std::endl;
			}
		}
	}
	cout << "IMAGE_COMPLETED" << endl;
	//return image


}

