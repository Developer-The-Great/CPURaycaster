#include "pch.h"
#include "FileReader.h"
#include "Scene.h"





FileReader::FileReader()
{
	


}

void FileReader::ReadFile(std::string fileName, OUT Scene * scene)
{
	//intialize ifstream
	std::ifstream File;
	//set exceptions
	File.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try 
	{
		//open file
		File.open(fileName);
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::FILE_NOT_SUCESSFULLY_READ" << std::endl;
		return;
	}
	//open file
	std::string str, cmd;

	//get a line
	std::getline(File, str);
	//while streaming
	while (File)
	{
		//if line in not blanked or commented
		if (str.find_first_not_of(" /t/n/r") != std::string::npos && str[0] != '#')
		{
			//put inside string stream
			std::stringstream s(str);
			//put inside cmd(which is a strng)
			s >> cmd;

			//if cmd is the same as a known command
			if (cmd == "Size")
			{
				//get values
				//set values
			}
		}

		}
	}
		

		

	


}



FileReader::~FileReader()
{
}
