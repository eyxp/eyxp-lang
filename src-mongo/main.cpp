#include <iostream>
#include "Interpreter.h"
#include "FileHandler.h"
#include "Defaults.h"


FileHandler fileHandler;
Interpreter interpreter;
Defaults defaults;

#define DEBUG 1

int main()
{
	std::string path;

	std::cout << "[Mongo] Hello User!" << std::endl;
	std::cout << "[Mongo] Insert file path to execute" << std::endl;

	#ifdef _WIN32
		system("cls");
	#elif __linux__ || __APPLE__
		system("clear");
	#endif

	#if DEBUG
		fileHandler.handleFileExecuting("C:/MongoScript", interpreter);
	#else
		std::cin >> path;
		fileHandler.handleFileExecuting(path, interpreter);
	#endif




	return 0;
}
