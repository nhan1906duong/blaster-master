#pragma once
#include "Game.h"
#include "Map.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Player.h"


class CArea2Scene : public CScene
{
protected:
	CPlayer* player;					// A play scene has to have player, right? 
	CMap* map;
	CCamera* camera;

	vector<LPGAMEOBJECT> objects;

	void _ParseSection_MAP(string map);
	void _ParseSection_OBJECTS(string line);
	void _ParseSecion_BRICK(string line);
	void _ParseSection_CHONG_NHON(string);
	void _ParseSection_PORTAL(string);
	void _CheckCameraAndWorldMap();

public:
	CArea2Scene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	CPlayer* GetPlayer() { return player; }

	void GetCameraPosition(float& x, float& y);

	//friend class CPlayScenceKeyHandler;
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CPlayScenceKeyHandler(CScene* s) :CScenceKeyHandler(s) {};
};

