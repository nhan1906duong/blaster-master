#include "Area2OverworldScene.h"

#include <fstream>

#include "PlayScenceKeyHandler.h"

#include "JasonGoUpState.h"

#include "Game.h"
#include "Camera.h"
#include "Map.h"
#include "Textures.h"
#include "Utils.h"
#include "GridManager.h"
#include "Collision.h"

#include "Brick.h"
#include "Portal.h"

#include "Player.h"
#include "EyeBall.h"
#include "Teleporter.h"
#include "Cannon.h"

#include "HPItem.h"
#include "HoverItem.h"
#include "GunItem.h"
#include "ThunderBreakItem.h"
#include "MultiwarheadMissileItem.h"
#include "ChongNhon.h"



#define SCENE_SECTION_UNKNOWN		-1
#define SCENE_SECTION_MAP			0
#define SCENE_SECTION_OBJECTS		1
#define SCENE_SECTION_BRICK			2
#define SCENE_SECTION_PORTAL		3
#define SCENE_SECTION_CHONG_NHON		4

#define MAX_SCENE_LINE 1024

#define	OBJECT_TYPE_HP_ITEM							20
#define	OBJECT_TYPE_THUNDER_BREAK_ITEM				28
#define	OBJECT_TYPE_MULTIWARHEAD_MISSILE_ITEM		29
#define	OBJECT_TYPE_HOVER_ITEM						27
#define OBJECT_TYPE_EYEBALL		23
#define OBJECT_TYPE_TELEPORTER	25
#define OBJECT_TYPE_CANNON		26

Area2OverworldScene::Area2OverworldScene(int id, LPCWSTR filePath) : Scene(id, filePath)
{
	key_handler = new PlayScenceKeyHandler(this);
	staticObjects.clear();
	objects.clear();
}

void Area2OverworldScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = (float) atof(tokens[1].c_str());
	float y = (float) atof(tokens[2].c_str());


	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_EYEBALL:
		obj = new EyeBall();
		break;
	
	case OBJECT_TYPE_TELEPORTER:
		obj = new Teleporter();
		break;
	
	case OBJECT_TYPE_CANNON:
	{
		obj = new Cannon();
		break;
	}
	case OBJECT_TYPE_HP_ITEM:
	{
		obj = new HPItem();
		break;
	}
	case OBJECT_TYPE_HOVER_ITEM:
	{
		obj = new HoverItem();
		break;
	}
	case OBJECT_TYPE_THUNDER_BREAK_ITEM:
	{
		obj = new ThunderBreakItem();
		break;
	}
	case OBJECT_TYPE_MULTIWARHEAD_MISSILE_ITEM:
	{
		obj = new MultiwarheadMissileItem();
		break;
	}
	
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);
	GridManager::GetInstance()->AddObject(obj);
}

void Area2OverworldScene::_ParseSection_CHONG_NHON(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 5) return;
	int identity = atoi(tokens[0].c_str());
	float left = (float)atof(tokens[1].c_str());
	float top = (float)atof(tokens[2].c_str());
	float right = (float)atof(tokens[3].c_str());
	float bottom = (float)atof(tokens[4].c_str());
	ChongNhon* brick = new ChongNhon(identity, left, top, right, bottom);
	staticObjects.push_back(brick);
}

void Area2OverworldScene::_ParseSecion_BRICK(string line, int type)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 5) return;
	int identity = atoi(tokens[0].c_str());
	float left = (float) atof(tokens[1].c_str());
	float top = (float) atof(tokens[2].c_str());
	float right = (float) atof(tokens[3].c_str());
	float bottom = (float) atof(tokens[4].c_str());
	CBrick*	brick = new CBrick(identity, left, top, right, bottom);
	staticObjects.push_back(brick);
}

void Area2OverworldScene::_ParseSection_PORTAL(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 8) return;
	int identity = atoi(tokens[0].c_str());
	float left = (float) atof(tokens[1].c_str());
	float top = (float) atof(tokens[2].c_str());
	float right = (float) atof(tokens[3].c_str());
	float bottom = (float) atof(tokens[4].c_str());
	int scene_id = atoi(tokens[5].c_str());
	float cam_x = (float) atof(tokens[6].c_str());
	float cam_y = (float) atof(tokens[7].c_str());
	CPortal* portal = new CPortal(identity, left, top, right, bottom, scene_id, cam_x, cam_y);
	staticObjects.push_back(portal);
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
	CPlayer::GetInstance()->SetPosition(player_x, player_y);
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
		
		if (line == "[CHONG_NHON]")
		{
			section = SCENE_SECTION_CHONG_NHON; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		switch (section)
		{
			case SCENE_SECTION_MAP: _ParseSection_MAP(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
			case SCENE_SECTION_BRICK: _ParseSecion_BRICK(line); break;
			case SCENE_SECTION_PORTAL: _ParseSection_PORTAL(line); break;
			case SCENE_SECTION_CHONG_NHON: _ParseSection_CHONG_NHON(line); break;
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
	for (size_t i = 0; i < collisions.size(); i++)
		collisions[i]->Render();
}

/*
	Unload current scene
*/
void Area2OverworldScene::Unload()
{
	GridManager::GetInstance()->Clear();
	objects.clear();
	staticObjects.clear();
	collisions.clear();
	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}


void Area2OverworldScene::_RefreshObject()
{
	objects.clear();
	objects = GridManager::GetInstance()->GetObjectsToUpdate();
	objects.push_back(CPlayer::GetInstance());
	for (size_t i = 0; i < staticObjects.size(); ++i)
	{
		objects.push_back(staticObjects[i]);
	}
}

void Area2OverworldScene::RemoveCollisionObject()
{
	collisions.erase(remove_if(collisions.begin(), collisions.end(), [](const CollisionExplosion* obj) {
		return obj->shouldRemove == true;
	}), collisions.end());
}

void Area2OverworldScene::AddCollision(float x1, float y1)
{
	CollisionExplosion* collision = new CollisionExplosion();
	collision->SetPosition(x1, y1);
	collisions.push_back(collision);
}

void Area2OverworldScene::OnSpacePress()
{
	for (size_t i = 0; i < staticObjects.size(); ++i)
	{
		if (dynamic_cast<CPortal*>(staticObjects[i]) && Collision::CheckContain(staticObjects[i], CPlayer::GetInstance()))
		{
			CPortal* portal = dynamic_cast<CPortal*>(staticObjects[i]);
			CGame::GetInstance()->SwitchScene(portal->GetSceneId(), portal->GetCamX(), portal->GetCamY());
			break;
		}
	}
}