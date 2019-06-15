#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm.hpp>
#include <stack>
#include <gtc/matrix_transform.hpp>

#define OUT


typedef glm::vec3 vec3;
typedef glm::mat4 mat4;

class Scene;

class FileReader
{
public:
	FileReader();

	void ReadFile(std::string fileName, OUT Scene* scene);
	bool GetValues(std::stringstream &s, const int numValues, float* values);
	void RightMultiply(const glm::mat4 M, std::stack<glm::mat4>& stack);
	~FileReader();
};

