#include "Area2Scene.h"

#include <iostream>
#include <fstream>
#include <algorithm>

#include "Camera.h"
#include "Map.h"
#include "GridManager.h"
#include "PlayScenceKeyHandler.h"

#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Worm.h"
#include "ChongNhon.h"
#include "Floater.h"
#include "Jumper.h"
#include "Insect.h"

#include "DoomieOrb.h"
#include "AttackOrb.h"

#include "Skull.h"
#include "Mine.h"
#include "SophiaBullet.h"

#include "Dome.h"


#include "Brick.h"
#include "SecretWall.h"
#include "FireZone.h"
#include "Stair.h"

using namespace std;

Area2Scene::Area2Scene(int id, LPCWSTR filePath) : Scene(id, filePath)
{
	key_handler = new PlayScenceKeyHandler(this);
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/

#define SCENE_SECTION_UNKNOWN		-1
#define SCENE_SECTION_MAP			0
#define SCENE_SECTION_OBJECTS		1
#define SCENE_SECTION_BRICK			2
#define SCENE_SECTION_CHONG_NHON	3
#define SCENE_SECTION_PORTAL		4
#define SCENE_SECTION_SECRET_WALL	5
#define SCENE_SECTION_FIRE_ZONE		6
#define SCENE_SECTION_STAIR			7

#define OBJECT_TYPE_CON_SAU		10
#define OBJECT_TYPE_DOME		11
#define OBJECT_TYPE_FLOATER		12
#define OBJECT_TYPE_JUMPER		13
#define OBJECT_TYPE_INSECT		14
#define OBJECT_TYPE_ORB			15
#define OBJECT_TYPE_SKULL		16
#define OBJECT_TYPE_MINE		17

#define MAX_SCENE_LINE 1024

void Area2Scene::_Init_Player(float player_x, float player_y)
{
	player = CPlayer::GetInstance();
	player->SetPosition(player_x, player_y);
	objects.push_back(player);
	Camera::GetInstance()->SetSwitchScene();
	Camera::GetInstance()->UpdateCamera();
}

void Area2Scene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	CGameObject* obj = NULL;

	switch (object_type)
	{
		case OBJECT_TYPE_CON_SAU:
			obj = new Worm();
			break;
		case OBJECT_TYPE_DOME:
			{
				int initDirection = atoi(tokens[3].c_str());
				int huong = atoi(tokens[4].c_str());
				obj = new Dome(initDirection, huong);
			}
			break;
		case OBJECT_TYPE_FLOATER:
		{
			int timeDelay = atoi(tokens[3].c_str());
			obj = new Floater(timeDelay);
			break;
		}
		case OBJECT_TYPE_JUMPER:
		{
			int nx = 1;
			if (tokens.size() > 3)
			{
				nx = atoi(tokens[3].c_str());
			}
			obj = new Jumper(nx);
			break;
		}
		case OBJECT_TYPE_INSECT:
		{
			float l = atof(tokens[3].c_str());
			float t = atof(tokens[4].c_str());
			float r = atof(tokens[5].c_str());
			float b = atof(tokens[6].c_str());

			int nx = atoi(tokens[7].c_str());
			int ny = atoi(tokens[8].c_str());

			obj = new Insect(l, t, r, b, nx, ny);
			break;
		}
		case OBJECT_TYPE_ORB:
			obj = new DoomieOrb();
			break;
		case OBJECT_TYPE_SKULL:
		{
			int nx = atoi(tokens[3].c_str());
			obj = new Skull(nx);
			break;
		}
		case OBJECT_TYPE_MINE:
			obj = new Mine();
			break;
		default:
			DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
			return;
	}

	// General object setup
	obj->SetPosition(x, y);
	GridManager::GetInstance()->AddObject(obj);
}

void Area2Scene::_ParseSecion_BRICK(string line, int type)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 5) return;
	int identity = atoi(tokens[0].c_str());
	float left = atof(tokens[1].c_str());
	float top = atof(tokens[2].c_str());
	float right = atof(tokens[3].c_str());
	float bottom = atof(tokens[4].c_str());
	Static* obj;
	if (type == 1)
	{
		obj = new SecretWall(left, top, right, bottom);
	}
	else if (type == 2)
	{
		obj = new FireZone(left, top, right, bottom);
	}
	else if (type == 3)
	{
		int jumpPoint = atof(tokens[5].c_str());
		obj = new Stair(left, top, right, bottom, jumpPoint);
	}
	else
	{
		obj = new CBrick(identity, left, top, right, bottom);
	}
	staticObjects.push_back(obj);
}

void Area2Scene::_ParseSection_CHONG_NHON(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 5) return;
	int identity = atoi(tokens[0].c_str());
	float left = atof(tokens[1].c_str());
	float top = atof(tokens[2].c_str());
	float right = atof(tokens[3].c_str());
	float bottom = atof(tokens[4].c_str());
	ChongNhon* brick = new ChongNhon(identity, left, top, right, bottom);
	staticObjects.push_back(brick);
}

void Area2Scene::_ParseSection_PORTAL(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 8) return;
	int identity = atoi(tokens[0].c_str());
	float left = atof(tokens[1].c_str());
	float top = atof(tokens[2].c_str());
	float right = atof(tokens[3].c_str());
	float bottom = atof(tokens[4].c_str());
	int scene_id = atoi(tokens[5].c_str());
	float cam_x = atoi(tokens[6].c_str());
	float cam_y = atoi(tokens[7].c_str());
	CPortal* portal = new CPortal(identity, left, top, right, bottom, scene_id, cam_x, cam_y);
	staticObjects.push_back(portal);
}

void Area2Scene::_ParseSection_MAP(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 1) return;
	LPCWSTR filePath = ToLPCWSTR(tokens[0]);
	
	Map::GetInstance()->GenerateANewMap(filePath);
	GridManager::GetInstance()->Reset();
}

void Area2Scene::Load(float player_x, float player_y)
{
	_Init_Player(player_x, player_y);

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
		if (line == "[SECRET_WALL]")
		{
			section = SCENE_SECTION_SECRET_WALL; continue;
		}
		if (line == "[CHONG_NHON]")
		{
			section = SCENE_SECTION_CHONG_NHON; continue;
		}
		if (line == "[PORTAL]")
		{
			section = SCENE_SECTION_PORTAL; continue;
		}
		if (line == "[FIRE]")
		{
			section = SCENE_SECTION_FIRE_ZONE; continue;
		}
		if (line == "[STAIR]")
		{
			section = SCENE_SECTION_STAIR; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		switch (section)
		{
		case SCENE_SECTION_MAP: _ParseSection_MAP(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		case SCENE_SECTION_BRICK: _ParseSecion_BRICK(line); break;
		case SCENE_SECTION_SECRET_WALL: _ParseSecion_BRICK(line, 1); break;
		case SCENE_SECTION_FIRE_ZONE: _ParseSecion_BRICK(line, 2); break;
		case SCENE_SECTION_STAIR: _ParseSecion_BRICK(line, 3); break;
		case SCENE_SECTION_CHONG_NHON: _ParseSection_CHONG_NHON(line); break;
		case SCENE_SECTION_PORTAL: _ParseSection_PORTAL(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"resources\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void Area2Scene::Update(DWORD dt)
{
	RemoveCollisionObject();
	_RefreshObject();
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (dynamic_cast<Static*>(objects[i])) continue;
		objects[i]->Update(dt, &objects);
	}
	Camera::GetInstance()->UpdateCamera();

}

void Area2Scene::Render()
{
	Map::GetInstance()->Render();
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
	for (int i = 0; i < collisions.size(); i++)
		collisions[i]->Render();
	_DrawBlood();
}

/*
	Unload current scene
*/
void Area2Scene::Unload()
{
	GridManager::GetInstance()->Clear();
	objects.clear();
	staticObjects.clear();
	collisions.clear();
	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void Area2Scene::RemoveCollisionObject()
{
	collisions.erase(remove_if(collisions.begin(), collisions.end(), [](const CollisionExplosion* obj) {
		return obj->shouldRemove == true;
	}), collisions.end());
}

void Area2Scene::AddCollision(float x1, float y1)
{
	CollisionExplosion* collision = new CollisionExplosion();
	collision->SetPosition(x1, y1);
	collisions.push_back(collision);
}

bool Area2Scene::HasStairNearBy(float& l, float& t, float& r, float& b, float& jumpPoint)
{
	for (int i = 0; i < staticObjects.size(); ++i)
	{
		LPGAMEOBJECT obj = staticObjects[i];
		if (dynamic_cast<Stair*>(obj))
		{
			Stair* stair = dynamic_cast<Stair*>(obj);
			stair->GetBoundingBox(l, t, r, b);
			jumpPoint = stair->GetJumpPoint();
			float midX, midY;
			float l, t, r, b;
			stair->GetBoundingBox(l, t, r, b);
			CPlayer::GetInstance()->GetMidPosition(midX, midY);
			if (midX > stair->GetMidX() - 16 &&
				midX < stair->GetMidX() + 16 &&
				midY >= b && midY <= t)
			{
				return true;
			}
		}
	}
	return false;
}

void Area2Scene::_DrawBlood()
{
	int blood = player->GetBlood();
	int sprite;
	switch (blood)
	{
		case 8:
			sprite = 86;
			break;
		case 7:
			sprite = 87;
			break;
		case 6:
			sprite = 88;
			break;
		case 5:
			sprite = 89;
			break;
		case 4:
			sprite = 90;
			break;
		case 3:
			sprite = 91;
			break;
		case 2:
			sprite = 92;
			break;
		case 1:
			sprite = 93;
			break;
		default:
			sprite = 94;
			break;
	}
	float cam_x, cam_y;
	Camera::GetInstance()->GetPosition(cam_x, cam_y);
	CSprites::GetInstance()->Get(sprite)->Draw(cam_x + 20, cam_y + 100 - CGame::GetInstance()->GetScreenHeight());
}

void Area2Scene::_RefreshObject()
{
	objects.clear();
	objects = GridManager::GetInstance()->GetObjectsToUpdate();
	objects.push_back(player);
	for (int i = 0; i < staticObjects.size(); ++i)
	{
		objects.push_back(staticObjects[i]);
	}
}

bool Area2Scene::CanAddPosition(float y)
{
	float minHeight = 99999.0f;
	for (int i = 0; i < objects.size(); ++i)
	{
		LPGAMEOBJECT obj = objects[i];
		if (dynamic_cast<CBrick*>(obj) || dynamic_cast<CPortal*>(obj))
		{
			float l, t, r, b;
			obj->GetBoundingBox(l, t, r, b);
			float pl, pt, pr, pb;
			CPlayer::GetInstance()->GetBoundingBox(pl, pt, pr, pb);
			if (y > 0)
			{
				if (!(pl > r || pr < l) && b > pt && b - pt < minHeight)
				{
					minHeight = b - pt;
				}
			}
			else
			{
				if (!(pl > r || pr < l) && t < pb && pb - t < minHeight)
				{
					minHeight = pb - t;
				}
			}
		}
	}
	if (minHeight >= 99999.0f) return false;
	if (y < 0)
	{
		return y * -1 < minHeight;
	}
	else
	{
		return y < minHeight;
	}
}