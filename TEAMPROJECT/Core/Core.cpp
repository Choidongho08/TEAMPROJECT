#include "Core.h"
#include<iostream>
void Core::Run()
{
	std::cout << "��������" << std::endl;
	// ��������������
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
