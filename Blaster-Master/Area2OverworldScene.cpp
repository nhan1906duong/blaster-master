#include "Area2OverworldScene.h"

#include <fstream>

#include "PlayScenceKeyHandler.h"

#include "JasonGoUpState.h"

#include "Camera.h"
#include "Map.h"
#include "Textures.h"
#include "Utils.h"
#include "GridManager.h"

#include "Brick.h"

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
	staticObjects.clear();
	objects.clear();
}

void Area2OverworldScene::_ParseSection_OBJECTS(string line)
{

}

void Area2OverworldScene::_ParseSecion_BRICK(string line, int type)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 5) return;
	int identity = atoi(tokens[0].c_str());
	float left = atof(tokens[1].c_str());
	float top = atof(tokens[2].c_str());
	float right = atof(tokens[3].c_str());
	float bottom = atof(tokens[4].c_str());
	CBrick*	brick = new CBrick(identity, left, top, right, bottom);
	staticObjects.push_back(brick);
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

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"resources\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void Area2OverworldScene::Update(DWORD dt)
{
	_RefreshObject();
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (dynamic_cast<Static*>(objects[i])) continue;
		objects[i]->Update(dt, &objects);
	}
	Camera::GetInstance()->UpdateCamera();
}

void Area2OverworldScene::Render()
{
	Map::GetInstance()->Render();
	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Render();
	}
}

/*
	Unload current scene
*/
void Area2OverworldScene::Unload()
{

}


void Area2OverworldScene::_RefreshObject()
{
	objects.clear();
	objects = GridManager::GetInstance()->GetObjectsToUpdate();
	objects.push_back(CPlayer::GetInstance());
	for (int i = 0; i < staticObjects.size(); ++i)
	{
		objects.push_back(staticObjects[i]);
	}
}
