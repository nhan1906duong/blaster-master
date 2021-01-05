#include "JasonGoDownState.h"

#include "Utils.h"

JasonGoDownState::JasonGoDownState(PlayerData* data) : JasonOverworldState(data)
{
	DebugOut(L"JasonGoDownState\n");
}

int JasonGoDownState::CurrentAnimationId()
{
	return 32;
}

void JasonGoDownState::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{

}

void JasonGoDownState::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

}

void JasonGoDownState::OnKeyDown(int keyCode)
{

}

void JasonGoDownState::OnKeyUp(int keyCode)
{

}

void JasonGoDownState::KeyState(BYTE* states)
{

}
