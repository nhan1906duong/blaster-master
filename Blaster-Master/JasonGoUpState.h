#pragma once
#include "JasonOverworldState.h"

class JasonGoUpState: public JasonOverworldState
{
public:
	JasonGoUpState(PlayerData* data);

	int CurrentAnimationId();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	void OnKeyUp(int keyCode);
	void OnKeyDown(int keyCode);
	void KeyState(BYTE* states);
};

