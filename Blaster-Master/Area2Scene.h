#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
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
	vector<LPGAMEOBJECT> staticObjects;

	vector<CollisionExplosion*> collisions;

	void _Init_Player(float player_x, float player_y);
	void _ParseSection_MAP(string map);
	void _ParseSection_OBJECTS(string line);
	void _ParseSecion_BRICK(string line, int type = 0);
	void _ParseSection_CHONG_NHON(string);
	void _ParseSection_PORTAL(string);
	void _CheckCameraAndWorldMap();

	void _DrawBlood();

	void _RefreshObject();
public:
	CArea2Scene(int id, LPCWSTR filePath);

	virtual void Load(float player_x, float player_y);
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	CPlayer* GetPlayer() { return player; }

	void AddCollision(float, float);

	bool CanAddPosition(float y);
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CPlayScenceKeyHandler(CScene* s) :CScenceKeyHandler(s) {};
};

