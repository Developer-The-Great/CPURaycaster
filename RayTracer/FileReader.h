#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#define OUT
class Scene;

class FileReader
{
public:
	FileReader();
	void ReadFile(std::string fileName, OUT Scene* scene);
	bool GetValues(std::stringstream &s, const int numValues, float* values);
	~FileReader();
};

