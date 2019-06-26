#include "pch.h"
#include "PrimitiveObject.h"

#define COLOR 255.0f



PrimitiveObject::PrimitiveObject(vec3 ambientToSet, vec3 diffuseToSet,vec3 PositionToSet)
{

	ambient = ambientToSet * COLOR;
	diffuse = diffuseToSet * COLOR;
	position = PositionToSet;
	transform = mat4(1.0);
}

PrimitiveObject::PrimitiveObject()
{
}

glm::vec3 PrimitiveObject::GetAmbient()
{
	return ambient;
}

glm::vec3 PrimitiveObject::GetDiffuse()
{
	return diffuse;
}

PrimitiveObject::~PrimitiveObject()
{

}
