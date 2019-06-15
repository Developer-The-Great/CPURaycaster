#include "pch.h"
#include "PrimitiveObject.h"

#define COLOR 255.0f



PrimitiveObject::PrimitiveObject(glm::vec3 ambientToSet, glm::vec3 PositionToSet)
{
	ambient = ambientToSet* COLOR;
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

PrimitiveObject::~PrimitiveObject()
{

}
