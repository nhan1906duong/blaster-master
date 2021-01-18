#include "IntroSceneKeyHandler.h"

#include "Game.h"

void IntroSceneKeyHandler::OnKeyDown(int KeyCode)
{
	//CPlayer::GetInstance()->OnKeyDown(KeyCode);
	if (KeyCode == DIK_SPACE)
	{
		CGame::GetInstance()->SwitchScene(1, 64, 128);
	}
}

void IntroSceneKeyHandler::OnKeyUp(int keyCode)
{
	//CPlayer::GetInstance()->OnKeyUp(keyCode);
}

void IntroSceneKeyHandler::KeyState(BYTE* states)
{
	//CPlayer::GetInstance()->KeyState(states);
}
