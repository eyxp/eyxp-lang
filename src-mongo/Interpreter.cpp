#include "Interpreter.h"
#include <iostream>

#include "InterpreterError.h"

std::map<std::string, Class> Interpreter::classes;

Interpreter::Interpreter()
{
}

void Interpreter::execute(const std::vector<std::string>& program)
{
	try
	{
		for (int i = 0; i < program.size(); i++)
		{
			runLine(program[i]);
		}
	}
	catch (const InterpreterError& e)
	{
		std::cerr << "Interpreter Error: " << e.what() << std::endl;
		stopInterpreter();
	}
}


void Interpreter::setVariableValue(const std::string& varName, int value)
{
	variables[varName].value = value;
	variables[varName].initialized = true;
}

void Interpreter::addToken(const std::string& className, const std::string& methodName,
                           const std::function<void(const std::vector<std::string>&)>& method)
{
	classes[className].methods[methodName] = method;
}


void Interpreter::runLine(const std::string& line)
{
	if (line.find(':') != std::string::npos)
	{
		std::string className = line.substr(0, line.find("::"));
		std::string methodeName = line.substr(line.find("::") + 2, line.find('(') - line.find("::") - 2);
		if (classes.contains(className))
		{
			std::string parameter = line.substr(line.find('(') + 1, line.find(')') - line.find('(') - 1);

			std::vector<std::string> tokens = tokenize(parameter);

			classes[className].methods[methodeName](tokens);
		}
		else
		{
			std::cout << classes.size() << std::endl;
			std::cout << className << methodeName << std::endl;
			std::cerr << "Fehler: Klasse oder Methode nicht gefunden." << std::endl;
		}
	}
}

std::vector<std::string> Interpreter::tokenize(const std::string& line)
{
	std::vector<std::string> tokens;
	std::istringstream iss(line);
	std::string token;
	while (iss >> token)
	{
		removeQuotes(token);
		tokens.push_back(token);
	}
	return tokens;
}

void Interpreter::removeQuotes(std::string& token)
{
	if (!token.empty())
	{
		if (token.front() == '"')
		{
			token.erase(0, 1);
		}
		if (token.back() == '"')
		{
			token.pop_back();
		}
	}
}

void Interpreter::stopInterpreter()
{
	std::cout << "Interpreter stopped." << std::endl;
	std::exit(EXIT_FAILURE);
}


std::string Interpreter::bundelTokens(const std::vector<std::string>& tokens)
{
	std::string result;
	for (const auto& token : tokens)
	{
		result += token + " ";
	}

	if (!result.empty())
	{
		result.pop_back();
	}
	return result;
}
