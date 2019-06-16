#include "pch.h"
#include "FileReader.h"
#include "Scene.h"
#include "TriangularObject.h"
#include "Transform.h"
#include "Sphere.h"
#include <stack>

#define VEC3VALS 3

FileReader::FileReader()
{
	


}

void FileReader::ReadFile(std::string fileName, OUT Scene * scene)
{
	int TriCount = 0;
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
	vec3 ambient; 
	vec3 position(0,0,0);

	//intialize matrix stack
	std::stack<mat4> stack;
	//push identity matrix
	stack.push(mat4(1.0f));

	bool validInput;
	int verts = 0;
	std::string oldCmd ="";

	while (std::getline(File, str))
	{
		std::stringstream s(str);
		std::string test;
		s >> test;
		
		std::cout << "oldcmd :" << oldCmd << std::endl;
		std::cout << "cmd :" << test << std::endl;

		//if line in not blank or commented
		if (str.find_first_not_of(" /t/n/r") != std::string::npos && str[0] != '#')
		{
			std::stringstream s(str);
			//std::stringstream s(str);
			float values[10];
			//get command of line
			s >> cmd;
			
			//-----if cmd is the equal to a known command----------
				//-----set values for said command----
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
				std::cout << "size found " << scene->width <<" " << scene->height << std::endl;
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
				
				validInput = GetValues(s, 1, values);
				int MaxVerts = values[0];
			}
			else if (cmd == "vertex")
			{
				
				validInput = GetValues(s, VEC3VALS, values);
				if (validInput )
				{
					scene->vertices.push_back(glm::vec3(values[0], values[1], values[2]));
					std::cout << "vertice: " << values[0] << " " << values[1] << " " << values[2] << std::endl;
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
				validInput = GetValues(s, 4, values);
				std::cout << "sphere found" << std::endl;
				if (validInput)
				{
					std::cout << "values " << values[0] << " " << values[1] << " " << values[2] << " " << std::endl;
					vec3 spherePos(values[0], values[1], values[2]);
					Sphere* sphere = new Sphere(spherePos, ambient, values[3]);

					scene->AddPrimitive(sphere);
					sphere->transform = stack.top();
				}
			}
			else if (cmd == "pushTransform")
			{
				stack.push(stack.top());
			}

			else if (cmd == "popTransform")
			{
				if (stack.size() <= 1)
				{
					std::cout << "ERROR::STACK_HAS_NO_ELEMENTS" << std::endl;
				}
				else
				{
					stack.pop();
				}
			}

			
			else if (cmd == "translate")
			{
				validInput = GetValues(s, 3, values);
				std::cout << "translate " << std::endl;
				if (validInput)
				{
					std::cout << "values " << values[0] << " " << values[1] << " " << values[2] << " " << std::endl;
					RightMultiply(glm::transpose(Transform::translate(values[0], values[1], values[2])), stack);
				}
				
	
			}

			else if (cmd == "scale")
			{
				validInput = GetValues(s, 3, values);
				std::cout << "scale " << std::endl;
				if (validInput)
				{
					std::cout << "values " << values[0] << " " << values[1] << " " << values[2] << " " << std::endl;
					RightMultiply(glm::transpose(Transform::scale(values[0], values[1], values[2])), stack);
				}
			}
			else if (cmd == "rotate")
			{
				validInput = GetValues(s, 4, values);
				std::cout << "rotate " << std::endl;
				if (validInput)
				{
					std::cout << "values " << values[0] << " " << values[1] << " " << values[2] << " " << std::endl;
					mat3 Rot = Transform::rotate(values[3],vec3(values[0], values[1], values[2]));

					
					mat4 rot(Rot);
					RightMultiply(rot, stack);
				}
			}
		}
		
		else
		{
			//cmd string will now store an empty string instead of old commands(this will happen if a comment is found)
			cmd = "";
		}

		//if the previous command is a triangle and the next is not a triangle
		if ((oldCmd == "tri" && test != "tri") || (oldCmd == "tri" && File.eof()))
		{
			//Triangular object has been completed
			if (!tempIndices.empty()) 
			{
				TriangularObject* Obj = new TriangularObject(ambient, position, scene->vertices, tempIndices);
				scene->AddPrimitive(Obj);
				Obj->transform = stack.top();


				std::cout << "--[x]triangular object created" << TriCount << std::endl;
				tempIndices.clear();
				TriCount++;
			}
			
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

void FileReader::RightMultiply(const mat4 M, std::stack<mat4>& stack)
{
	mat4& T = stack.top();

	T = T * M;

}




FileReader::~FileReader()
{
}
