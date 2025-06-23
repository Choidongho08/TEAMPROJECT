#pragma once
#include <string>

class Debug
{
public:
	static Debug* Instance;

private:
	int x, y;

public:
	Debug();
	
	void Log(std::string string);

private:

};

