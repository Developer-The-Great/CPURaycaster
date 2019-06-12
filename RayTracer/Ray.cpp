#include "pch.h"
#include "Ray.h"
#include "Camera.h"
#include "Scene.h"
#include "PrimitiveObject.h"
#include "TriangularObject.h"
#include "Triangle.h"
#include "Sphere.h"

#include <iostream>
#include <iterator>
#include <vector>
#include <assert.h> 
#define MAX_DISTANCE 1000000
#define EPSILON 0.001


Ray::Ray(float sceneWidth,float sceneHeight)
{
	width = sceneWidth;
	height = sceneHeight;

}

Ray::~Ray()
{
}

glm::vec3 Ray::GetRayDirection()
{
	return glm::vec3();
}

void Ray::FindRayDirection(Camera * cam, int i, int j)
{
	float maxAngleY = glm::tan(glm::radians(cam->GetFov() / 2.0f));
	float maxAngleX = maxAngleY * (width / height);

	float alphaC = (j - (width / 2)) / (width / 2);

	float betaC = ((height / 2) - i) / (height / 2);

	float alpha = maxAngleX * alphaC;
	
	float beta = maxAngleY * betaC;
	
	glm::vec3 direction = (alpha *cam->GetUAxis() + beta * cam->GetVAxis() - cam->GetWAxis());

	

	direction = glm::normalize(direction);

	itest = i;
	jtest = j;


	rayDirection = direction;

}



PrimitiveObject * Ray::IntersectionCheck( Scene*scene)
{
	//intialize minimal distance to a big number
	float minDistance = MAX_DISTANCE;

	std::vector<PrimitiveObject*> objects = scene->GetPrimitives();
	std::vector<PrimitiveObject*>::iterator iter;
	PrimitiveObject * Obj = nullptr;

	glm::vec3 eyePos = scene->GetCam()->GetCamPos();
	//for each object in scene
	for (iter = objects.begin(); iter != objects.end(); ++iter)
	{
		//determine object type
		//TriangularObject obj((TriangularObject)*iter);
		TriangularObject* TriangularObj = dynamic_cast<TriangularObject*>(*iter);
		//if primitive object is a triangle
		if (TriangularObj)
		{
			std::vector<Triangle>::iterator triangleIter;

			std::vector<Triangle> triangles = TriangularObj->GetTriangles();

			for (triangleIter = triangles.begin(); triangleIter != triangles.end(); ++triangleIter)
			{
				RayIntersectInformation intersectionInfo = RayTriangleIntersect(*triangleIter, scene->GetCam()->GetCamPos());
				
				if (!intersectionInfo.isIntersecting) { continue; }

				if (intersectionInfo.t > 0 && intersectionInfo.t < minDistance)
				{
					minDistance = intersectionInfo.t;
					Obj = TriangularObj;

				}
			}
		}
		
		else
		{
			Sphere* sphere = dynamic_cast<Sphere*>(*iter);
			//if primitive object is a sphere
			if (sphere)
			{
				assert(sphere);

				RayIntersectInformation intersectionInfo = RaySphereIntersect(sphere, eyePos);
				
				if (!intersectionInfo.isIntersecting) { continue; }

				if (intersectionInfo.t > 0 && intersectionInfo.t < minDistance)
				{
					minDistance = intersectionInfo.t;
					Obj = sphere;

				}

			}
			
		
		}

	}
		
	
	return Obj;
}

RayIntersectInformation Ray::RayTriangleIntersect(Triangle tri,glm::vec3 EyePos)
{

	RayIntersectInformation result;
	//find normal

	glm::vec3 a = tri.GetTriangles()[0];
	glm::vec3 b = tri.GetTriangles()[1];
	glm::vec3 c = tri.GetTriangles()[2];

	glm::vec3 normal = glm::cross(a - b, c - b);

	//normal = glm::normalize(normal);

	
	float normalDotDirection = glm::dot(normal, rayDirection);

	float normalDotPoint = glm::dot(a, normal);
	float normalDotOrigin = glm::dot(EyePos, normal);
	//find t
	float t = (normalDotPoint - normalDotOrigin) / normalDotDirection;


	if (t < 0)
	{
		result.isIntersecting = false;
		result.t = t;
		return result;
	}
	//find point where ray intersects the plane where the triangle lies
	glm::vec3 P = EyePos + rayDirection * t;


	//---Barycentric Coordinate Solve-----

	glm::vec3 v0 = b - a;
	glm::vec3 v1 = c - a;
	glm::vec3 v2 = P - a;

	float d00 = glm::dot(v0, v0);
	float d10 = glm::dot(v1, v0);
	float d01 = glm::dot(v0, v1);
	float d11 = glm::dot(v1, v1);
	float d20 = glm::dot(v2, v0);
	float d21 = glm::dot(v2, v1);
	//apply cramers rule

	//find denominator
	float denom = d00 * d11 - d01 * d10;


	float v = (d20 * d11 - d21 * d10)/denom;

	//---- P is in triangle if u + v + w = 1 ------

	if (v < 0 || v > 1)
	{
		result.isIntersecting = false;
		result.t = t;
		return result;
	}

	float w = (d00 * d21 - d01 * d20) / denom;

	if (w < 0 || w > 1)
	{
		result.isIntersecting = false;
		result.t = t;
		return result;
	}

	float u = 1 - w - v;

	if (u < 0 || u > 1)
	{
		result.isIntersecting = false;
		result.t = t;
		return result;
	}
	
	result.isIntersecting = true;
	result.t = t;

	return result;
}

RayIntersectInformation Ray::RaySphereIntersect(const Sphere* sphere,glm::vec3 eyePos)
{
	RayIntersectInformation result;

	result.isIntersecting = false;
	result.t = 0;

	glm::vec3 p0 = eyePos;
	glm::vec3 p1 = rayDirection;
	//ax2 + bx + c = 0
	//P0 = eye
	//P1 = direction
	//a = (P1.P1)
	//b = 2P1*(P0-C)
	//c = (P0-C)(P0-C) - r^2

	glm::vec3 p0MinC = p0 - sphere->GetPosition();
	float r = sphere->GetRadius();

	float a = glm::dot(p1, p1);
	float b = 2 * glm::dot(p1, p0MinC);
	float c = glm::dot(p0MinC, p0MinC) - (r*r);
	
	//b^2 - 4ac
	float discriminant = b * b - 4 * a*c;

	//if roots are positive
	if (discriminant > 0)
	{
		float t1 = QuadraticSolve(a, b, c, true);
		float t2 = QuadraticSolve(a, b, c, false);

		//if both are negative 
		bool isT1Negative = t1 < 0;
		bool isT2Negative = t2 < 0;

		//if the meeting point is behind or if ray is inside sphere
		if (isT1Negative || isT2Negative)
		{
			result.isIntersecting = false;
			result.t = 0;
			return result;
		}
		else
		{
			if (t1 > t2)
			{
				result.isIntersecting = true;
				result.t = t2;
				return result;
			}
			else
			{
				result.isIntersecting = true;
				result.t = t1;
				return result;
			
			}
		
		
		}

	}
	//if roots are equal
	else if (glm::abs(discriminant) < EPSILON)
	{
		float t1 = QuadraticSolve(a, b, c, true);
		
		result.isIntersecting = true;
		result.t = t1;
		return result;
	}
	//if roots are negative
	else
	{
		result.isIntersecting = false;
		result.t = 0;
		return result;
	
	}


	return result;
}

float Ray::QuadraticSolve(float a, float b, float c, bool positive)
{
	float discriminant = b * b - 4 * a*c;
	float denom = 2 * a;

	if (positive)
	{
		float numerator = -b + (glm::sqrt(discriminant));
		return numerator / denom;
	}
	else
	{
		float numerator = -b - (glm::sqrt(discriminant));
		return numerator / denom;
	}
	
}






