#pragma once
#include "Game.h"
#include "Map.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Player.h"
//#include "Goomba.h"
//#include "Koopas.h"


class CArea2Scene : public CScene
{
protected:
	CPlayer* player;					// A play scene has to have player, right? 
	//CMap* map;
	CCamera* camera;

	vector<LPGAMEOBJECT> objects;

	void _ParseSection_OBJECTS(string line);
	void _CheckCameraAndWorldMap();

public:
	CArea2Scene(int id, LPCWSTR filePath, CCamera* camera);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	CPlayer* GetPlayer() { return player; }

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

