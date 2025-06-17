#pragma once
#include<vector>
#include<string>
#include "Console.h"

using std::vector;
using std::string;

class AsciiObject
{
public:
	AsciiObject(vector<string> obj)
	{
		this->obj = obj;
	}
private:
	vector<string> obj;
public:
	void ObjectInit();
	void ObjectUpdate();
	void ObjectRender(COLOR txtColor, COLOR bgColor);
private:
};
