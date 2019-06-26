#include "pch.h"
#include "Debug.h"
#include <gtx/string_cast.hpp>

void Debug::Log(std::string log)
{
	std::cout << log << std::endl;
}

void Debug::Log(std::string valueName, float value)
{
	std::cout << valueName << ": " << value << std::endl;
}

void Debug::Log(std::string mat4Name, glm::mat4 mat4Value)
{
	std::cout << mat4Name << ": "<< std::endl;
	std::cout << glm::to_string(mat4Value) << std::endl;
}

void Debug::Log(std::string vec3Name, glm::vec3 vec3Value)
{
	std::cout << vec3Name << ": " << std::endl;
	std::cout << glm::to_string(vec3Value) << std::endl;
}

Debug::Debug()
{
}


Debug::~Debug()
{
}
