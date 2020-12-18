#pragma once
#include <d3d9.h>
#include <vector>
#include <dinput.h>

#include "PlayerData.h"
#include "GameObject.h"

class PlayerState
{
public:
	PlayerState(PlayerData* data) { this->data = data; };

	virtual int CurrentAnimationId() = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects) {};
	virtual void GetBoundingBox(float&, float&, float&, float&) = 0;
	virtual void KeyState(BYTE* states) {};
	virtual void OnKeyDown(int keyCode) {};
	virtual void OnKeyUp(int keyCode) {};

	int IsKeyDown(BYTE* states, int keyCode)
	{
		return (states[keyCode] & 0x80) > 0;
	}

public:
	PlayerData* data;
};