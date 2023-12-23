#pragma once

#include <vector>
#include <sstream>
#include <map>
#include <functional>

struct Variable
{
	std::string value;
	bool initialized;
};

struct Class
{
	std::string name;
	std::map<std::string, std::function<void(const std::vector<std::string>&)>> methods;
	std::map<std::string, Variable> variables;
};

class Interpreter
{

public:
	virtual ~Interpreter() = default;
	static std::map<std::string, Class> classes;

	Interpreter();

	void execute(const std::vector<std::string>& program);
	void setVariableValue(const std::string className, const std::string& varName, std::string value);
	Variable getVariableValue(const std::string className, const std::string& varName);
	virtual void addToken(const std::string& className, const std::string& methodName,
	                      const std::function<void(const std::vector<std::string>&)>& method);
	std::string bundelTokens(const std::vector<std::string>& tokens);

private:
	std::vector<std::string> tokenize(const std::string& line);
	void runLine(const std::string& line);
	void removeQuotes(std::string& str);
	void stopInterpreter();
};
