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
	return rayDirection;
}




vec3 Ray::FindRayDirection(Camera * cam, int i, int j)
{
	float maxAngleY = glm::tan(glm::radians(cam->GetFov() / 2.0f));
	float maxAngleX = maxAngleY * (width / height);

	//add 0.5f to get the center of the pixel
	float jCenter = j + 0.5f;
	float iCenter = i + 0.5f;

	float alphaC = (jCenter - (width / 2)) / (width / 2);

	float betaC = ((height / 2) - iCenter) / (height / 2);

	float alpha = maxAngleX * alphaC;
	
	float beta = maxAngleY * betaC;
	
	glm::vec3 direction = (alpha *cam->GetUAxis() + beta * cam->GetVAxis() - cam->GetWAxis());

	

	direction = glm::normalize(direction);

	itest = i;
	jtest = j;


	rayDirection = direction;

	return rayDirection;
}

RayIntersectInformation Ray::IntersectionCheck(vec3 eyePos, vec3 direction, std::vector<PrimitiveObject*> objects, float maxDistance)
{
	//intialize minimal distance to the max distance of the ray
	float minDistance = maxDistance;

	RayIntersectInformation intersectionInfo;

	std::vector<PrimitiveObject*>::iterator iter;

	//for each object in scene
	for (iter = objects.begin(); iter != objects.end(); ++iter)
	{
		//determine object type
		TriangularObject* TriangularObj = dynamic_cast<TriangularObject*>(*iter);

		//if primitive object is a trianglular object
		if (TriangularObj)
		{
			std::vector<Triangle>::iterator triangleIter;

			std::vector<Triangle> triangles = TriangularObj->GetTriangles();

			for (triangleIter = triangles.begin(); triangleIter != triangles.end(); ++triangleIter)
			{
				RayIntersectInformation currentIntersectionInfo = RayTriangleIntersect(*triangleIter, eyePos, TriangularObj->transform);

				if (!currentIntersectionInfo.isIntersecting) { continue; }

				if (currentIntersectionInfo.t > 0 && currentIntersectionInfo.t < minDistance)
				{
					minDistance = currentIntersectionInfo.t;
					intersectionInfo.obj = TriangularObj;

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

				RayIntersectInformation currentIntersectionInfo = RaySphereIntersect(sphere, eyePos);

				if (!currentIntersectionInfo.isIntersecting) { continue; }

				if (currentIntersectionInfo.t > 0 && currentIntersectionInfo.t < minDistance)
				{
					minDistance = currentIntersectionInfo.t;
					intersectionInfo.obj = sphere;

				}

			}


		}

	}


	return intersectionInfo;
}

RayIntersectInformation Ray::IntersectionCheck( Scene*scene, float maxDistance)
{
	//intialize minimal distance to the max distance of the ray
	float minDistance = maxDistance;

	RayIntersectInformation intersectionInfo;

	std::vector<PrimitiveObject*> objects = scene->GetPrimitives();

	std::vector<PrimitiveObject*>::iterator iter;

	vec3 eyePos = scene->GetCam()->GetCamPos();
	//for each object in scene
	for (iter = objects.begin(); iter != objects.end(); ++iter)
	{
		//determine object type
		TriangularObject* TriangularObj = dynamic_cast<TriangularObject*>(*iter);

		//if primitive object is a trianglular object
		if (TriangularObj)
		{
			std::vector<Triangle>::iterator triangleIter;

			std::vector<Triangle> triangles = TriangularObj->GetTriangles();

			for (triangleIter = triangles.begin(); triangleIter != triangles.end(); ++triangleIter)
			{
				RayIntersectInformation currentIntersectionInfo = RayTriangleIntersect(*triangleIter, eyePos,TriangularObj->transform);
				
				if (!currentIntersectionInfo.isIntersecting) { continue; }

				if (currentIntersectionInfo.t > 0 && currentIntersectionInfo.t < minDistance)
				{
					minDistance = currentIntersectionInfo.t;
					intersectionInfo.obj = TriangularObj;

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

				RayIntersectInformation currentIntersectionInfo = RaySphereIntersect(sphere, eyePos);
				
				if (!currentIntersectionInfo.isIntersecting) { continue; }

				if (currentIntersectionInfo.t > 0 && currentIntersectionInfo.t < minDistance)
				{
					minDistance = currentIntersectionInfo.t;
					intersectionInfo.obj = sphere;

				}

			}
			
		
		}

	}
		
	
	return intersectionInfo;
}



RayIntersectInformation Ray::RayTriangleIntersect(Triangle tri,glm::vec3 EyePos,mat4 transforms)
{
	
	RayIntersectInformation result;

	vec4 rayOrigin(EyePos, 1);
	vec4 rayDir(rayDirection, 0);

	//std::cout << glm::to_string(transforms) << std::endl;

	rayOrigin = glm::inverse(transforms)* rayOrigin;
	rayDir =   glm::inverse(transforms)*rayDir;

	//find normal
	vec3 aVec3 = tri.GetTriangles()[0];
	vec3 bVec3 = tri.GetTriangles()[1];
	vec3 cVec3 = tri.GetTriangles()[2];

	vec4 a(aVec3,1);
	vec4 b(bVec3,1);
	vec4 c(cVec3,1);
	//a-b,c-b
	vec3 normalVec3 = glm::cross(aVec3-bVec3,cVec3-bVec3);
	//set normal
	result.normal = normalVec3;
	vec4 normal(normalVec3,1);

	float normalDotDirection = glm::dot(normal, rayDir);

	float normalDotPoint = glm::dot(a, normal);
	float normalDotOrigin = glm::dot(rayOrigin, normal);
	//find t
	float t = (normalDotPoint - normalDotOrigin) / normalDotDirection;
	
	if (itest == 300 && jtest == 300)
	{
		std::cout << "t " <<  t << std::endl;
	}

	if (t < 0)
	{
		result.isIntersecting = false;
		result.t = t;
		return result;
	}
	//find point where ray intersects the plane where the triangle lies
	vec4 P = rayOrigin + rayDir * t;

	//find non-transformed point
	result.intersectionPoint = transforms * P;
	//---Barycentric Coordinate Solve-----

	vec3 v0 = b - a;
	vec3 v1 = c - a;
	vec3 v2 = P - a;

	float d00 = glm::dot(v0, v0);
	float d10 = glm::dot(v1, v0);
	float d01 = glm::dot(v0, v1);
	float d11 = glm::dot(v1, v1);
	float d20 = glm::dot(v2, v0);
	float d21 = glm::dot(v2, v1);
	

	//find denominator
	float denom = d00 * d11 - d01 * d10;

	//apply cramers rule
	float v = (d20 * d11 - d21 * d10)/denom;

	//---- P is in triangle if u + v + w = 1 ------
	if (itest == 300 && jtest == 300)
	{
		std::cout << "v " << v << std::endl;
	}
	if (v < 0 || v > 1)
	{
		result.isIntersecting = false;
		result.t = t;
		return result;
	}

	float w = (d00 * d21 - d01 * d20) / denom;

	if (itest == 300 && jtest == 300)
	{
		std::cout << "w " << w << std::endl;
	}

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

	glm::vec4 p0(eyePos,1);
	glm::vec4 p1(rayDirection,0);

	p0 = glm::inverse(sphere->transform) * p0;
	p1 = glm::inverse(sphere->transform) * p1;

	

	//ax2 + bx + c = 0
	//P0 = eye
	//P1 = direction
	//a = (P1.P1)
	//b = 2P1*(P0-C)
	//c = (P0-C)(P0-C) - r^2

	glm::vec4 p0MinC = p0 - glm::vec4(sphere->GetPosition(),1);
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
				result.intersectionPoint = FindNonTransformedIntersectionPosistion(p0, p1, t2, sphere->transform);
				result.normal = glm::normalize(vec3(result.intersectionPoint) - sphere->GetPosition());
				//find first intersecting point of ray
				return result;
			}
			else
			{
				result.isIntersecting = true;
				result.t = t1;
				result.intersectionPoint = FindNonTransformedIntersectionPosistion(p0, p1, t1, sphere->transform);
				result.normal = glm::normalize(vec3(result.intersectionPoint) - sphere->GetPosition());
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
float Ray::GetDefaultMaxT()
{
	return A_VERY_BIG_NUMBER;
}
glm::vec4 Ray::FindNonTransformedIntersectionPosistion(vec4 p0, vec4 p1, float t, mat4 transform)
{
	vec4 P = p0 + p1 * t;
	vec4 transformedIntersectPoint = transform * P;

	return transformedIntersectPoint;
}

void Ray::SetRayDirection(vec3 direction)
{
	rayDirection = direction;
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






