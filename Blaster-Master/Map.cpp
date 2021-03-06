#include "Camera.h"

#include "Map.h"
#include "Game.h"
#include "Textures.h"
#include "Utils.h"
#include "Area2OverworldScene.h"

#include <iostream>
#include <fstream>

#define MAX_MAP_LINE 1024

#define MAP_SECTION_UNKNOWN -1
#define MAP_SECTION_SIZE 1
#define MAP_SECTION_MAP 2

Map* Map::__instance = NULL;

Map* Map::GetInstance()
{
	if (__instance == NULL)
	{
		__instance = new Map();
	}
	return __instance;
}

Map::Map()
{

}

void Map::GenerateANewMap(LPCWSTR filePath)
{
	DebugOut(L"[INFO] Start loading map %s\n", filePath);

	ifstream f;
	f.open(filePath);

	int section = MAP_SECTION_UNKNOWN;

	char str[MAX_MAP_LINE];
	int row = 0;
	while(f.getline(str, MAX_MAP_LINE))
	{
		string line(str);
		vector<string> tokens = split(line, " ");
		bouncingRight = tokens.size() * 16 - 16;
		for (int i = 0; i < tokens.size(); i++)
		{
			map[row][i] = atoi(tokens[i].c_str());
		}
		++row;
	}
	bouncingTop = row * 16 - 16;
	DebugOut(L"[INFO] Load map success!");
	f.close();
}

void Map::Render()
{
	float cam_l, cam_t, cam_r, cam_b;
	Camera::GetInstance()->GetBouncingBox(cam_l, cam_t, cam_r, cam_b);

	for (int row = 0; row < bouncingTop / 16; row++)
	{
		for (int column = 0; column < bouncingRight / 16; ++column)
		{
			float tileLeft = column * 16;
			float tileRight = column * 16 + 16;
			float tileTop = row * 16 + 16;
			float tileBottom = row * 16;

			if (tileBottom >= cam_t || tileLeft >= cam_r || tileTop <= cam_b || tileRight <= cam_l)
			{
				continue;
			}

			int texId = map[bouncingTop/16 - row][column];
			if (dynamic_cast<Area2OverworldScene*>(CGame::GetInstance()->GetCurrentScene()))
			{
				texId += 200;
			}
			LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texId);
			CGame::GetInstance()->Draw(tileLeft, tileTop, tex, 0, 0, 16, 16);
		}
	}
}

void Map::GetBouncing(int& top, int& right)
{
	top = bouncingTop;
	right = bouncingRight;
}

void Map::GetBouncing(long& top, long& right)
{
	top = bouncingTop;
	right = bouncingRight;
}

