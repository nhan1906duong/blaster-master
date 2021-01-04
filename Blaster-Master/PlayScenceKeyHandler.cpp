#include "PlayScenceKeyHandler.h"

#include "Player.h"

void PlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	CPlayer::GetInstance()->OnKeyDown(KeyCode);
}

void PlayScenceKeyHandler::OnKeyUp(int keyCode)
{
	CPlayer::GetInstance()->OnKeyUp(keyCode);
}

void PlayScenceKeyHandler::KeyState(BYTE* states)
{
	CPlayer::GetInstance()->KeyState(states);
}
