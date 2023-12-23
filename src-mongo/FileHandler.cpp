#include "FileHandler.h"


#include <filesystem>
#include <fstream>

#include "Interpreter.h"

FileHandler::FileHandler()
{
}


void FileHandler::handleFileExecuting(const std::string path, Interpreter interpreter)
{
	if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
	{
		std::vector<std::filesystem::path> mongoFilePaths;

		findMongoFiles(path, mongoFilePaths);


		if (mongoFilePaths.empty())
		{
			std::cout << "No .mongo files found in directory!" << std::endl;
			return;
		}

		Interpreter interpreter;

		for (const auto& mongo_file_path : mongoFilePaths)
		{
			std::ifstream fileStream(mongo_file_path);
			if (fileStream.is_open())
			{
				std::string line;
				std::vector<std::string> lines;
				while (std::getline(fileStream, line))
				{
					lines.push_back(line);
				}
				interpreter.execute(lines);
				fileStream.close();
			}
			else
			{
				std::cerr << "Unable to open file: " << mongo_file_path << std::endl;
			}
		}
	}
	else
	{
		std::cout << "Error while process input file!" << std::endl;
	}
}


void FileHandler::findMongoFiles(const std::filesystem::path& folderPath,
                                 std::vector<std::filesystem::path>& mongoFilePaths)
{
	try
	{
		for (const auto& entry : std::filesystem::directory_iterator(folderPath))
		{
			if (entry.is_regular_file() && entry.path().extension() == ".mongo")
			{
				mongoFilePaths.push_back(entry.path());
			}
			else if (entry.is_directory())
			{
				findMongoFiles(entry.path(), mongoFilePaths);
			}
		}
	}
	catch (const std::filesystem::filesystem_error& e)
	{
		std::cerr << "Filesystem error: " << e.what() << std::endl;
	}
}
