#pragma once
#include "JasonOverworldState.h"

class JasonGoDownState: public JasonOverworldState
{
public:
	JasonGoDownState(PlayerData* data);

	int CurrentAnimationId();
	void GetBoundingBox(float&, float&, float&, float&);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	void OnKeyUp(int keyCode);
	void OnKeyDown(int keyCode);
	void KeyState(BYTE* states);
};

