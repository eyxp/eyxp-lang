#include "Defaults.h"

#include <iostream>


Defaults::Defaults()
{
	Interpreter::addToken("Main", "print", [this](const std::vector<std::string>& args)
	{
		std::cout << bundelTokens(args) << std::endl;
	});
}
