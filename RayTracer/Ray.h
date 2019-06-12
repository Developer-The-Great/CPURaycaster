#pragma once
#include <vector>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


#define OUT
class Camera;
class PrimitiveObject;
class Scene;
class Triangle;
class Sphere;

struct RayIntersectInformation
{
	bool isIntersecting;
	float t;

};
class Ray
{

public:

	Ray(float sceneWidth, float sceneHeight);

	~Ray();

	glm::vec3 GetRayDirection();

	void FindRayDirection(Camera*cam, int i, int j);

	PrimitiveObject * IntersectionCheck(Scene*scene);

	RayIntersectInformation RayTriangleIntersect(Triangle tri, glm::vec3 EyePos);

	RayIntersectInformation RaySphereIntersect(const Sphere* sphere, glm::vec3 eyePos);

	
	

private:

	float width;
	float height;

	int itest, jtest;

	glm::vec3 rayDirection;

	float QuadraticSolve(float a, float b, float c, bool positive);
};

