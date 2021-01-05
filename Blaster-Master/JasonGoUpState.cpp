#include "JasonGoUpState.h"

#include "Utils.h"

JasonGoUpState::JasonGoUpState(PlayerData* data) : JasonOverworldState(data)
{
	DebugOut(L"JasonGoUpState\n");
}

int JasonGoUpState::CurrentAnimationId()
{
	return 7;
}

void JasonGoUpState::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{

}

void JasonGoUpState::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	
}

void JasonGoUpState::OnKeyDown(int keyCode)
{
	
}

void JasonGoUpState::OnKeyUp(int keyCode)
{
	
}

void JasonGoUpState::KeyState(BYTE* states)
{

}
