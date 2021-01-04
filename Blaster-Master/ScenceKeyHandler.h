#pragma once
#include "Scene.h"
#include "KeyEventHandler.h"

class ScenceKeyHandler: public KeyEventHandler
{
protected:
	Scene* scence;

public:
	virtual void KeyState(BYTE* states) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
	ScenceKeyHandler(Scene* s) : KeyEventHandler() { scence = s; }
};

