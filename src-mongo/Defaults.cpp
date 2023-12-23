#include "Defaults.h"

#include <iostream>


Defaults::Defaults()
{
	Interpreter::addToken("Main", "print", [this](const std::vector<std::string>& args)
	{
		std::cout << bundelTokens(args) << std::endl;
	});

	Interpreter::addToken("Main", "close", [this](const std::vector<std::string>& args)
	{
		exit(0);
	});

	Interpreter::addToken("Main", "setVar", [this](const std::vector<std::string>& args)
	{
		if (args.size() == 3)
		{
			setVariableValue(args[0],args[1], args[2]);
		}
		else
		{
			std::cout << "Error: setVar takes 3 arguments" << std::endl;
		}
	});

	Interpreter::addToken("Main", "getVar", [this](const std::vector<std::string>& args)
	{
			if (args.size() == 2)
			{
				std::cout << args[0] << std::endl;
				std::cout << getVariableValue(args[0], args[1]).value << std::endl;
			}
			else
			{
				std::cout << "Error: getVar takes 2 arguments" << std::endl;
			}
	});
}
