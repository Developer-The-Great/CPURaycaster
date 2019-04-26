#pragma once
#include "FreeImage.h"
#include <string>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#define BPP 24



class Image
{


public:
	Image(int width,int height,std::string filename);
	void SetPixel(int w, int h, glm::vec3 rgb);
	void SaveImage();
	~Image();

	FIBITMAP*bitmap = nullptr;

private:

	

	int imageWidth;
	int imageHeight;

	std::string filename;

};

