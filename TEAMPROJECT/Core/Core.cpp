#include "Core.h"
#include<iostream>
void Core::Run()
{
	std::cout << "けいしぉ" << std::endl;
	// けいしかいしぉ
	while (true)
	{
		Update();
		Render();
		// FrameSync
	}
}

void Core::Update()
{
}

void Core::Render()
{
}
