#pragma once
#include <string>
#include <iostream>
#include <gtc/matrix_transform.hpp>




class Debug
{
public:

	static void Log(std::string log);
	static void Log(std::string valueName,float value);
	static void Log(std::string log, glm::mat4 mat4Value);
	static void Log(std::string log, glm::vec3 mat4Value);

	Debug();
	~Debug();
};

