#include "JasonOverworldDie.h"

#include "Utils.h"

JasonOverworldDie::JasonOverworldDie(PlayerData* data) : JasonOverworldState(data)
{
	DebugOut(L"JasonOverworldDie\n");
}

int JasonOverworldDie::CurrentAnimationId()
{
	return 36;
}

void JasonOverworldDie::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{

}

void JasonOverworldDie::OnKeyDown(int keyCode)
{

}

void JasonOverworldDie::OnKeyUp(int keyCode)
{

}

void JasonOverworldDie::KeyState(BYTE* states)
{
	
}

