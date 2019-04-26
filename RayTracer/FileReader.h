#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Scene;

class FileReader
{
public:
	FileReader();
	void ReadFile(std::string fileName,Scene* scene);
	~FileReader();
};

