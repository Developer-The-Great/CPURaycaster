#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <vector>

class PrimitiveObject
{
public:
	PrimitiveObject(glm::vec3 ambientToSet,glm::vec3 PositionToSet);
	PrimitiveObject();

	virtual glm::vec3 GetAmbient();
	~PrimitiveObject();

private:

protected:
	glm::vec3 ambient;
	glm::vec3 position;

	
};

