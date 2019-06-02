#include "pch.h"
#include "PrimitiveObject.h"





PrimitiveObject::PrimitiveObject(glm::vec3 ambientToSet, glm::vec3 PositionToSet)
{
	ambient = ambientToSet;
	position = PositionToSet;
}

PrimitiveObject::PrimitiveObject()
{
}

PrimitiveObject::~PrimitiveObject()
{

}
