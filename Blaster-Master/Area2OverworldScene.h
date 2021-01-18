#pragma once
#include <string>

#include "Scene.h"
#include "GameObject.h"

#include "CollisionExplosion.h"


using namespace std;

class Area2OverworldScene: public Scene
{
private:
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> staticObjects;

	vector<CollisionExplosion*> collisions;

	void _ParseSection_MAP(string map);
	void _ParseSection_OBJECTS(string line);
	void _ParseSecion_BRICK(string line, int type = 0);
	void _ParseSection_PORTAL(string);
	void _ParseSection_CHONG_NHON(string);
	void _RefreshObject();
	void RemoveCollisionObject();
	void _DrawBlood();
public:
	Area2OverworldScene(int id, LPCWSTR filePath);
	virtual void Load(float player_x, float player_y);
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	void AddCollision(float, float, int type);

	void OnSpacePress();
};

