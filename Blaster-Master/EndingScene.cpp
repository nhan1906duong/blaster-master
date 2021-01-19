#include "EndingScene.h"

#include "EndingSceneKeyHandler.h"
#include "Game.h"
#include "Textures.h"
#include "Camera.h"

EndingScene::EndingScene() : Scene()
{
	key_handler = new EndingSceneKeyHandler(this);

	left = 2;
}

void EndingScene::Load(float  x, float y)
{
}

void EndingScene::Unload()
{

}

void EndingScene::Render()
{
	Camera::GetInstance()->SetPosition(0, CGame::GetInstance()->GetScreenHeight());

	float y = (CGame::GetInstance()->GetScreenHeight() - 226.0f) / 2 + 226.0f;
	CGame::GetInstance()->Draw(0, y, CTextures::GetInstance()->Get(308), left, 2, left + CGame::GetInstance()->GetScreenWidth(), 226);
}

void EndingScene::Update(DWORD dt)
{
	left += dt * 0.03;
	if (left + CGame::GetInstance()->GetScreenWidth() > 513)
	{
		left = 513 - CGame::GetInstance()->GetScreenWidth();
	}
}