#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Player.h"
#include "CollisionExplosion.h"

using namespace std;


class CArea2Scene : public CScene
{
private:
	void RemoveCollisionObject();
protected:
	CPlayer* player;

	vector<LPGAMEOBJECT> objects;
	vector<CollisionExplosion*> collisions;

	void _Init_Player(float player_x, float player_y);
	void _ParseSection_MAP(string map);
	void _ParseSection_OBJECTS(string line);
	void _ParseSecion_BRICK(string line);
	void _ParseSection_CHONG_NHON(string);
	void _ParseSection_PORTAL(string);
	void _CheckCameraAndWorldMap();

	void _DrawBlood();
public:
	CArea2Scene(int id, LPCWSTR filePath);

	virtual void Load(float player_x, float player_y);
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	CPlayer* GetPlayer() { return player; }

	void AddObject(LPGAMEOBJECT object);
	void RemoveObject(LPGAMEOBJECT object);
	void AddCollision(float, float);
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CPlayScenceKeyHandler(CScene* s) :CScenceKeyHandler(s) {};
};

