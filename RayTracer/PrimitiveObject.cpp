#include "pch.h"
#include "PrimitiveObject.h"

#define COLOR 255.0f



PrimitiveObject::PrimitiveObject(glm::vec3 ambientToSet, glm::vec3 PositionToSet)
{
	ambient = ambientToSet* COLOR;
	position = PositionToSet;
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
