#include <iostream>
#include "Interpreter.h"
#include "FileHandler.h"
#include "Defaults.h"


FileHandler fileHandler;
Interpreter interpreter;
Defaults defaults;

int main()
{
	std::string path;

	std::cout << "[Mongo] Hello User!" << std::endl;
	std::cout << "[Mongo] Insert file path to execute" << std::endl;

	std::cin >> path;

	#ifdef _WIN32
		system("cls");
	#elif __linux__ || __APPLE__
		system("clear");
	#endif

	fileHandler.handleFileExecuting(path, interpreter);

	return 0;
}
