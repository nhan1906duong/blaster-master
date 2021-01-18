#pragma once
#include "ScenceKeyHandler.h"

class IntroSceneKeyHandler : public ScenceKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	IntroSceneKeyHandler(Scene* s) : ScenceKeyHandler(s) {};
};

