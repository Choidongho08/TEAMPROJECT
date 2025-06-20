#pragma once
#include<vector>
#include "Console.h"

using std::vector;

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
