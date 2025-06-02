#pragma once
#include "Enums.h";
#include "AsciiObject.h";
#include <Windows.h>;

void TitleScene(Scene& eCurScene, AsciiObjcets& objs);
void TitleSceneUpdate(Scene& eCurScene);
void TitleSceneRender();

Menu GetCurMenu();
void EnterAnimation();
void FlashAnimation(COORD resolution, int cnt, int delayTime);
void CrossAnimation(COORD resolution, int delayTime);