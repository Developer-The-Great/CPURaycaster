#pragma once
#include <vector>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


#define OUT
#define A_VERY_BIG_NUMBER 1000000
#define EPSILON 0.001

typedef glm::vec4 vec4;
typedef glm::vec3 vec3;
typedef glm::mat4 mat4;
typedef glm::mat3 mat3;

class Camera;
class PrimitiveObject;
class Scene;
class Triangle;
class Sphere;

struct RayIntersectInformation
{
	bool isIntersecting;
	PrimitiveObject* obj = nullptr;
	vec3 normal;
	vec4 intersectionPoint;
	float t;

};
class Ray
{

public:

	Ray(float sceneWidth, float sceneHeight);

	~Ray();

	

	glm::vec4 FindNonTransformedIntersectionPosistion(vec4 p0, vec4 p1, float t, mat4 transform);


	vec3 FindRayDirection(Camera*cam, int i, int j);


	RayIntersectInformation IntersectionCheck(vec3 EyePos, vec3 direction, std::vector<PrimitiveObject*> objects, float maxDistance = A_VERY_BIG_NUMBER);

	RayIntersectInformation RayTriangleIntersect(Triangle tri, glm::vec3 EyePos,  glm::vec3 direction, mat4 transforms);

	RayIntersectInformation RaySphereIntersect(const Sphere* sphere, glm::vec3 direction, glm::vec3 eyePos);

	static float GetDefaultMaxT();
	

private:

	float width;
	float height;

	int itest, jtest;

	float QuadraticSolve(float a, float b, float c, bool positive);

	
};

