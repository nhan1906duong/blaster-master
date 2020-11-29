#include "Map.h"
#include "Game.h"
#include "Textures.h"
#include "Utils.h"

#include <iostream>
#include <fstream>

#define MAX_MAP_LINE 1024

#define MAP_SECTION_UNKNOWN -1
#define MAP_SECTION_SIZE 1
#define MAP_SECTION_MAP 2

CMap::CMap(LPCWSTR filePath)
{
	DebugOut(L"[INFO] Start loading map %s\n", filePath);

	map = (int**)malloc(128 /*dong*/ * sizeof(int*));
	for (int i = 0; i < 128 /*row*/; i++)
	{
		map[i] = (int*)malloc(128/*cot*/ * sizeof(int));
	}

	ifstream f;
	f.open(filePath);

	int section = MAP_SECTION_UNKNOWN;

	char str[MAX_MAP_LINE];
	int row = 0;
	while(f.getline(str, MAX_MAP_LINE))
	{
		string line(str);
		vector<string> tokens = split(line, " ");
		for (int i = 0; i < 128; i++)
		{
			map[row][i] = atoi(tokens[i].c_str());
		}
		++row;
	}
}

void CMap::Render()
{
	for (int row = 0; row < 128; row++)
	{
		for (int column = 0; column < 128; ++column)
		{
			int texId = map[127 - row][column];
			LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texId);
			CGame::GetInstance()->Draw(column * 16, row * 16 + 16, tex, 0, 0, 16, 16);
		}
	}
}