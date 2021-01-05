#include "Area2OverworldScene.h"

#include <fstream>

#include "PlayScenceKeyHandler.h"

#include "JasonGoUpState.h"

#include "Camera.h"
#include "Map.h"
#include "Textures.h"
#include "Utils.h"
#include "GridManager.h"

#include "Player.h"


#define SCENE_SECTION_UNKNOWN		-1
#define SCENE_SECTION_MAP			0
#define SCENE_SECTION_OBJECTS		1
#define SCENE_SECTION_BRICK			2
#define SCENE_SECTION_PORTAL		3

#define MAX_SCENE_LINE 1024

Area2OverworldScene::Area2OverworldScene(int id, LPCWSTR filePath) : Scene(id, filePath)
{
	key_handler = new PlayScenceKeyHandler(this);

}

void Area2OverworldScene::_ParseSection_OBJECTS(string line)
{

}

void Area2OverworldScene::_ParseSecion_BRICK(string line, int type)
{

}

void Area2OverworldScene::_ParseSection_PORTAL(string line)
{

}

void Area2OverworldScene::_ParseSection_MAP(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 1) return;
	LPCWSTR filePath = ToLPCWSTR(tokens[0]);

	Map::GetInstance()->GenerateANewMap(filePath);
	GridManager::GetInstance()->Reset();
}

void Area2OverworldScene::Load(float player_x, float player_y)
{
	CPlayer::GetInstance()->SetPosition(50, 50);
	CPlayer::GetInstance()->SwitchToOverworldState();
	Camera::GetInstance()->UpdateCamera();
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[MAP]")
		{
			section = SCENE_SECTION_MAP; continue;
		}

		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line == "[BRICK]")
		{
			section = SCENE_SECTION_BRICK; continue;
		}
		if (line == "[PORTAL]")
		{
			section = SCENE_SECTION_PORTAL; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		switch (section)
		{
			case SCENE_SECTION_MAP: _ParseSection_MAP(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
			case SCENE_SECTION_BRICK: _ParseSecion_BRICK(line); break;
			case SCENE_SECTION_PORTAL: _ParseSection_PORTAL(line); break;
			default: break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void Area2OverworldScene::Update(DWORD dt)
{

}

void Area2OverworldScene::Render()
{
	Map::GetInstance()->Render();
	CPlayer::GetInstance()->Render();
}

/*
	Unload current scene
*/
void Area2OverworldScene::Unload()
{

}
