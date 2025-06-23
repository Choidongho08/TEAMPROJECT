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
	void Log(int in);
	void Log(float in);
	void Pos(std::string file, int line);

private:

};

