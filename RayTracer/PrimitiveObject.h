#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <vector>

typedef glm::mat4 mat4;
typedef glm::vec3 vec3;

class PrimitiveObject
{
public:
	PrimitiveObject(vec3 ambientToSet, vec3 diffuseToSet,vec3 PositionToSet);
	PrimitiveObject();

	mat4 transform;

	virtual glm::vec3 GetAmbient();
	glm::vec3 GetDiffuse();

	int CurrentID;
	
	~PrimitiveObject();

private:
	
protected:
	vec3 ambient;
	vec3 diffuse;
	vec3 position;

	
};

