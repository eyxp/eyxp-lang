#pragma once
#include <iostream>
#include <vector>
#include <filesystem>
#include "Interpreter.h"

class FileHandler
{
public:
	FileHandler();

	void handleFileExecuting(std::string path, Interpreter interpreter);
	void findMongoFiles(const std::filesystem::path& folderPath, std::vector<std::filesystem::path>& mongoFilePaths);
};
