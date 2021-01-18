#pragma once
#include "ScenceKeyHandler.h"

class EndingSceneKeyHandler : public ScenceKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	EndingSceneKeyHandler(Scene* s) : ScenceKeyHandler(s) {};
};