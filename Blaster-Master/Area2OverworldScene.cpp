#include "Area2OverworldScene.h"

#include "PlayScenceKeyHandler.h"

#include "Map.h"

Area2OverworldScene::Area2OverworldScene(int id, LPCWSTR filePath) : Scene(id, filePath)
{
	key_handler = new PlayScenceKeyHandler(this);
}


void Area2OverworldScene::Load(float player_x, float player_y)
{

}

void Area2OverworldScene::Update(DWORD dt)
{

}

void Area2OverworldScene::Render()
{
	Map::GetInstance()->Render();
}

/*
	Unload current scene
*/
void Area2OverworldScene::Unload()
{

}
