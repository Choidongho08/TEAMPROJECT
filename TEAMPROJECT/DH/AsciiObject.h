#pragma once
#include<vector>
#include<string>

using std::vector;
using std::string;

struct AsciiObjcets
{
	std::vector<string> vecPlane;
	std::vector<string> vecCloud;
};

void ObjectInit(AsciiObjcets& objs);

void ObjectUpdate(AsciiObjcets& objs);
void ObjectRender(const AsciiObjcets& objs);

