#include <iostream>
#include <fstream>

#include "Area2Scene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "ChongNhon.h"

using namespace std;

CArea2Scene::CArea2Scene(int id, LPCWSTR filePath, CCamera* camera) : CScene(id, filePath)
{
	this->camera = camera;
	key_handler = new CPlayScenceKeyHandler(this);
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_OBJECTS	1
#define SCENE_SECTION_BRICK		2
#define SCENE_SECTION_CHONG_NHON		3
#define SCENE_SECTION_PORTAL	4

#define OBJECT_TYPE_MARIO	101

#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024

/*
	Parse a line in section [OBJECTS]
*/
void CArea2Scene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CPlayer(x, y);
		player = (CPlayer*)obj;

		DebugOut(L"[INFO] Player object created!\n");
		break;
	break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

	obj->SetAnimationSet(ani_set);
	objects.push_back(obj);
}

void CArea2Scene::_ParseSecion_BRICK(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 5) return;
	int identity = atoi(tokens[0].c_str());
	float left = atof(tokens[1].c_str());
	float top = atof(tokens[2].c_str());
	float right = atof(tokens[3].c_str());
	float bottom = atof(tokens[4].c_str());
	CBrick* brick = new CBrick(identity, left, top, right, bottom);
	objects.push_back(brick);
}

void CArea2Scene::_ParseSection_CHONG_NHON(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 5) return;
	int identity = atoi(tokens[0].c_str());
	float left = atof(tokens[1].c_str());
	float top = atof(tokens[2].c_str());
	float right = atof(tokens[3].c_str());
	float bottom = atof(tokens[4].c_str());
	ChongNhon* brick = new ChongNhon(identity, left, top, right, bottom);
	objects.push_back(brick);
}

void CArea2Scene::_ParseSection_PORTAL(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 5) return;
	int identity = atoi(tokens[0].c_str());
	float left = atof(tokens[1].c_str());
	float top = atof(tokens[2].c_str());
	float right = atof(tokens[3].c_str());
	float bottom = atof(tokens[4].c_str());
	int scene_id = atoi(tokens[5].c_str());
	CPortal* portal = new CPortal(identity, left, top, right, bottom, scene_id);
	objects.push_back(portal);
}

void CArea2Scene::Load()
{
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

		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line == "[BRICK]")
		{
			section = SCENE_SECTION_BRICK; continue;
		}
		if (line == "[CHONG_NHON]")
		{
			section = SCENE_SECTION_CHONG_NHON; continue;
		}
		if (line == "[PORTAL]")
		{
			section = SCENE_SECTION_PORTAL; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		switch (section)
		{
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		case SCENE_SECTION_BRICK: _ParseSecion_BRICK(line); break;
		case SCENE_SECTION_CHONG_NHON: _ParseSection_CHONG_NHON(line); break;
		case SCENE_SECTION_PORTAL: _ParseSection_PORTAL(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"resources\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CArea2Scene::_CheckCameraAndWorldMap()
{

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);

	camera->UpdateCamera(cx, cy);
}

void CArea2Scene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	_CheckCameraAndWorldMap();

}

void CArea2Scene::Render()
{
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

/*
	Unload current scene
*/
void CArea2Scene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	CPlayer* mario = ((CArea2Scene*)scence)->GetPlayer();
	switch (KeyCode)
	{
	case DIK_X:
		mario->SetState(PLAYER_STATE_JUMP);
		break;
	case DIK_A:
		mario->Reset();
		break;
	}
}

void CPlayScenceKeyHandler::OnKeyUp(int keyCode)
{

}

void CPlayScenceKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	CPlayer* player = ((CArea2Scene*)scence)->GetPlayer();

	player->KeyState(states);
}
