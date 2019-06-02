#include "pch.h"
#include "FileReader.h"
#include "Scene.h"
#include "TriangularObject.h"

#define VEC3VALS 3




FileReader::FileReader()
{
	


}

void FileReader::ReadFile(std::string fileName, OUT Scene * scene)
{
	std::ifstream File;

	File.open(fileName);
	
	if (!File.is_open())
	{
		std::cout << "FILE_NOT_SUCESSFULLY_READ" << std::endl;
		return;
	}

	std::cout << "FILE_SUCESSFULLY_READ" << std::endl;

	std::string str, cmd;
	//temporary values
	std::vector<int>tempIndices;
	glm::vec3 ambient; 
	glm::vec3 position(0, 0, 0);

	bool validInput;
	int verts = 0;
	std::string oldCmd ="";

	while (std::getline(File, str))
	{
		std::stringstream s(str);
		std::string test;
		s >> test;

		/*std::cout << "oldcmd :" << oldCmd << std::endl;
		std::cout << "cmd :" << test << std::endl;*/

		//if line in not blanked or commented
		if (str.find_first_not_of(" /t/n/r") != std::string::npos && str[0] != '#')
		{
			std::stringstream s(str);
			//std::stringstream s(str);
			float values[10];
			//get command
			s >> cmd;
			
			//if cmd is the same as a known command
			if (cmd == "size")
			{
				validInput = GetValues(s, 2, values);

				if (validInput)
				{
					scene->width = (int)values[0];
					scene->height = (int)values[1];
				}
				////get values
				////set values
				std::cout << "size found" << std::endl;
			}
			else if (cmd == "ambient")
			{
				validInput = GetValues(s, 3, values);
				ambient[0] = values[0];
				ambient[1] = values[1];
				ambient[2] = values[2];
			}
			else if (cmd == "maxverts")
			{
				//set program to store a cube
				validInput = GetValues(s, 1, values);
				int MaxVerts = values[0];
			}
			else if (cmd == "vertex")
			{
				
				validInput = GetValues(s, VEC3VALS, values);
				if (validInput )
				{
					scene->vertices.push_back(glm::vec3(values[0], values[1], values[2]));
					std::cout << "vertice: " << scene->vertices.back().x << " " << scene->vertices.back().y << " " << scene->vertices.back().z << std::endl;
				}
			}
			else if (cmd == "tri")
			{
				validInput = GetValues(s, VEC3VALS, values);
				std::cout << "tri found" << std::endl;
				
				if (validInput)
				{
					tempIndices.push_back(values[0]);
					tempIndices.push_back(values[1]);
					tempIndices.push_back(values[2]);
				}
				////get values
				////set values
				
			}

			else if (cmd == "camera")
			{
				//position,lookAt,Fov
				validInput = GetValues(s, VEC3VALS * 3 + 1, values);
				std::cout << "cam found" << std::endl;
				if (validInput)
				{
					scene->CameraPos[0] = values[0];
					scene->CameraPos[1] = values[1];
					scene->CameraPos[2] = values[2];

					scene->CameraLookAt[0] = values[3];
					scene->CameraLookAt[1] = values[4];
					scene->CameraLookAt[2] = values[5];

					scene->Up[0] = values[6];
					scene->Up[1] = values[7];
					scene->Up[2] = values[8];

					scene->Fov = values[9];
					
				}


			}

			else if (cmd == "sphere")
			{

			}
			
		}
		/*else
		{
			std::cout << "found a comment" << std::endl;
		}*/

		if (oldCmd == "tri" && test != "tri" || oldCmd == "tri" && File.eof())
		{
			//Triangular object complemted
			scene->primitives.push_back(TriangularObject(ambient, position,scene->vertices, tempIndices));

			std::cout << "triangular object created" << std::endl;
			tempIndices.clear();
		}


		oldCmd = cmd;

		
	}
	File.close();
}
bool FileReader::GetValues(std::stringstream &s, const int numValues, float* values)
{

	for (int i = 0; i < numValues; i++)
	{
		s >> values[i];
		if (s.fail())
		{
			std::cout << "value " << i << " cannot be read" << std::endl;
			return false;
		}
		
	}

	return true;
}




FileReader::~FileReader()
{
}
