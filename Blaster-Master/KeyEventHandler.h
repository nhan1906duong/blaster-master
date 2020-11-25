#pragma once
#include <Windows.h>

/*
	Abstract class to define keyboard event handlers
	Cac ham nay duoc goi moi frame qua ham ProccessKeyboard()
*/
class CKeyEventHandler
{
public:
	// dang nhan hay khong ?? STATE
	// goi 1 lan trong 1 frame
	virtual void KeyState(BYTE* state) = 0;
	// event vua nhan xuong
	// goi tuong ung voi so key duoc nhan trong 1 frame
	virtual void OnKeyDown(int KeyCode) = 0;
	// event vua tha ra
	// goi tuong ung voi so key duoc nhan trong 1 frame
	virtual void OnKeyUp(int KeyCode) = 0;
};
typedef CKeyEventHandler* LPKEYEVENTHANDLER;