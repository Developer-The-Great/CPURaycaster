#include "pch.h"
#include "Image.h"
#include <iostream>


Image::Image(int width, int height, std::string _filename)

{
	FreeImage_Initialise();

	bitmap = FreeImage_Allocate(width, height, BPP);
	filename = _filename;
	if (!bitmap)
	{
		std::cout << "BITMAP_NOT_SUCCESSFULLY_MADE" << std::endl;
	}
	else
	{
		std::cout << "BITMAP_SUCCESSFULLY_MADE" << std::endl;
	}
	imageWidth = width;
	imageHeight = height;


}

void Image::SetPixel(int w, int h, glm::vec3 rgb)
{
	
	if (!bitmap)
	{
		std::cout << "ERROR::BITMAP_IS_NULL" << std::endl;
		return;
	}
	RGBQUAD color;

	//std::cout << "rgb.y " << rgb.y << std::endl;
	color.rgbRed = (double)rgb.x;
	color.rgbGreen = (double)rgb.y;
	color.rgbBlue = (double)rgb.z;

	FreeImage_SetPixelColor(bitmap, w,imageHeight- h, &color);
}

void Image::SaveImage()
{
	if (FreeImage_Save(FIF_PNG, bitmap, "image.png", 0))
	{
		std::cout << "IMAGE_SAVED" << std::endl;
	}
}

Image::~Image()
{
	delete bitmap;
	FreeImage_DeInitialise();
}
