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
#include "Debug.h"

#include "TriangularObject.h"
#include "FreeImage.h"
#include "Scene.h"
#include "Image.h"
#include "DirectionalLight.h"
#include "PointLight.h"

#define NORMALEPSILON 0.001f

using std::cout;
using std::endl;

Image* rayTrace(int width, int height, std::string fileName, Scene*scene);
vec3 FindColor(RayIntersectInformation intersectInfo, Scene*scene);
vec3 ColorClamp(vec3 color);

int main()
{
	std::string fileName;

	cout << "Welcome to not real time ray tracing!" << endl;
	cout << "Input file name: ";

	std::getline(std::cin, fileName);
	//construct scene 
	Scene* scene = new Scene(fileName);
	//construct image with constructed scene 
	Image* image = rayTrace(scene->width, scene->height, fileName,scene);

	//if succesfull
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


	//for each row of pixels 
	glm::vec3 color(0, 0, 0);
	for (int i = 0; i < height; ++i)
	{
		
		unsigned int currentRow = i * width;

		//for each pixels in that row 
		for (int j = 0; j < width; ++j)
		{
			//shoot a ray through the pixel
			vec3 direction = ray.FindRayDirection(cam, i, j);

			vec3 eyePos = scene->GetCam()->GetCamPos();
			//check for intersection
			RayIntersectInformation intersectInfo = ray.IntersectionCheck(eyePos,direction,scene->GetPrimitives());
			
			//find the final color
			color = FindColor(intersectInfo,scene);
	
			image->SetPixel(j, i, color);

		}
		if (i % 2 == 0)
		{
			cout << "Completed pixels " << currentRow  << "/" << Total << std::endl;
			

		}
	}
	cout << "IMAGE_COMPLETED" << endl;

	//return image
	return image;
}

glm::vec3 FindColor(RayIntersectInformation intersectInfo, Scene*scene)
{
	const float colorC = 255.0f;
	if (!intersectInfo.obj)
	{
		//cout << "BLACK PIXEL " << endl;
		glm::vec3 black(0, 0, 0);
		return black;
	}

	PrimitiveObject* obj = intersectInfo.obj;
	vec3 normal = glm::normalize(intersectInfo.normal);
	vec3 intersectionPoint = vec3(intersectInfo.intersectionPoint);
	//cout << " normal " << glm::to_string(intersectInfo.normal) << endl;

	//check obj type
	TriangularObject* tri = dynamic_cast<TriangularObject*>(obj);

	/*if (tri) { cout << "Object is triangle" << endl; }
	else { cout << "Object is sphere" << endl; }*/

	std::vector<Light*>lights = scene->GetLights();
	glm::vec3 color(0, 0, 0);

	intersectionPoint = intersectionPoint + NORMALEPSILON * normal;

	//for each light 
	for (Light* light : lights)
	{

		vec3 direction;
		vec3 intersectToPoint;

		DirectionalLight* dirLight = dynamic_cast<DirectionalLight*>(light);

		Ray ray(scene->width, scene->height);
		float maxT = Ray::GetDefaultMaxT();
		float attenuation = 1.0f;

		//if its a direction light
		if (dirLight)
		{
			direction = glm::normalize(dirLight->GetDirection());

		}
		else
		{
			PointLight* pointLight = dynamic_cast<PointLight*>(light);
			//if its a point light
			if (pointLight)
			{

				//get direction with (IntersectionPoint - LightPos)
				direction = glm::normalize(pointLight->GetPosition() - intersectionPoint);

				//normalize direction
				maxT = (pointLight->GetPosition().x - intersectionPoint.x) / direction.x;

				//attenuation = 1.0f/(r);

			}

		}

		RayIntersectInformation intersectToLight = ray.IntersectionCheck(intersectionPoint, direction, scene->GetPrimitives(), maxT);

		if (intersectToLight.obj)
		{
			cout << "Light Blocked " << std::endl;

			continue;
		}

		float nDotL = glm::dot(normal, direction);

		vec3 finalLightOutput = attenuation * (obj->GetDiffuse() / colorC)* (light->GetColor() / colorC) * glm::max(nDotL, 0.0f);

		color+= finalLightOutput;


	}
	//glm::clamp()
	glm::vec3 Result = intersectInfo.obj->GetAmbient() + scene->emission + color * colorC;
	Result = ColorClamp(Result);
	return Result;
	}

	vec3 ColorClamp(vec3 color)
	{
		return glm::clamp(color, 0.0f, 255.0f);

	}


