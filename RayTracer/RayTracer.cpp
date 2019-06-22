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
#include "DirectionalLight.h"
#include "PointLight.h"

#define EPSILON 0.001

using std::cout;
using std::endl;

Image* rayTrace(int width, int height, std::string fileName, Scene*scene);
glm::vec3 FindColor(RayIntersectInformation intersectInfo, Scene*scene);

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

	cout << "cam w " << glm::to_string(cam->GetWAxis()) << endl;
	cout << "cam u " << glm::to_string(cam->GetUAxis()) << endl;
	cout << "cam v " << glm::to_string(cam->GetVAxis()) << endl;
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

			//cout << glm::to_string(ray.GetRayDirection()) << endl;

			//check for intersection
			vec3 eyePos = scene->GetCam()->GetCamPos();
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

glm::vec3 FindColor(RayIntersectInformation intersectInfo,Scene*scene)
{
	
	if (!intersectInfo.obj)
	{
		//cout << "BLACK PIXEL " << endl;
		glm::vec3 black(0, 0, 0);
		return black;
	}
	
	PrimitiveObject* obj = intersectInfo.obj;
	vec3 normal = glm::normalize(intersectInfo.normal);

	std::vector<Light*>lights = scene->GetLights();
	glm::vec3 color(0, 0, 0);

	////for each light 
	//for (Light* light : lights)
	//{
	//	//attenuation
	//	vec3 direction;

	//	DirectionalLight* dirLight = dynamic_cast<DirectionalLight*>(light);

	//	Ray ray(scene->width, scene->height);
	//	float maxT = Ray::GetDefaultMaxT();
	//	float attenuation = 1;


	//	//if its a direction light
	//	if (dirLight)
	//	{
	//		direction = glm::normalize(dirLight->GetDirection());

	//	}
	//	else
	//	{
	//		PointLight* pointLight = dynamic_cast<PointLight*>(light);
	//		//if its a point light
	//		if (pointLight)
	//		{
	//			//get direction with (IntersectionPoint - LightPos)
	//			direction = glm::normalize(vec3(intersectInfo.intersectionPoint) - pointLight->GetPosition());

	//			//normalize direction
	//			maxT = (pointLight->GetPosition().x - intersectInfo.intersectionPoint.x) / direction.x;
	//			float r = glm::distance(vec3(intersectInfo.intersectionPoint), pointLight->GetPosition());
	//			attenuation = 1 / (r*r);

	//		}
	//	
	//	}
	//		
	//	ray.SetRayDirection(direction);
	//	RayIntersectInformation interectToLight =  ray.IntersectionCheck(scene, maxT);

	//	//if there's somthing between intersectPoint and light
	//	if (interectToLight.obj) { continue; }
	//	
	//		//continue

	//	//calculate diffuse shading
	//	//diffuse * max(N.L,0)
	//	//cout << " normal " << glm::to_string(normal) << endl;
	//	color += attenuation * obj->GetDiffuse() * glm::max(glm::dot(normal, direction), 0.0f);

	//
	//}
		
	
	//ambient + emission + foreach light (
	//cout << " diffuse " << glm::to_string(obj->GetDiffuse()) << endl;
	return intersectInfo.obj->GetAmbient() + scene->emission + color;
}

