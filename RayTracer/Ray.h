#pragma once
#include <vector>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


#define OUT

typedef glm::vec4 vec4;
typedef glm::vec3 vec3;
typedef glm::mat4 mat4;

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

	RayIntersectInformation RayTriangleIntersect(Triangle tri, glm::vec3 EyePos, mat4 transforms);

	RayIntersectInformation RaySphereIntersect(const Sphere* sphere, glm::vec3 eyePos);

	
	

private:

	float width;
	float height;

	int itest, jtest;

	glm::vec3 rayDirection;

	float QuadraticSolve(float a, float b, float c, bool positive);
};

