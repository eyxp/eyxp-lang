#pragma once

#include <vector>
#include <sstream>
#include <map>
#include <functional>

struct Variable
{
	int value;
	bool initialized;
};

struct Class
{
	std::string name;
	std::map<std::string, std::function<void(const std::vector<std::string>&)>> methods;
};

class Interpreter
{
	std::map<std::string, Variable> variables;

public:
	virtual ~Interpreter() = default;
	static std::map<std::string, Class> classes;

	Interpreter();

	void execute(const std::vector<std::string>& program);
	void setVariableValue(const std::string& varName, int value);
	virtual void addToken(const std::string& className, const std::string& methodName,
	                      const std::function<void(const std::vector<std::string>&)>& method);
	std::string bundelTokens(const std::vector<std::string>& tokens);

private:
	std::vector<std::string> tokenize(const std::string& line);
	void runLine(const std::string& line);
	void removeQuotes(std::string& str);
	void stopInterpreter();
};
