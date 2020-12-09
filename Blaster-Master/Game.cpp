#include <iostream>
#include <fstream>
#include <string>

#include "Game.h"
#include "Utils.h"

#include "Area2Scene.h"

#include "Textures.h"
#include "Sprites.h"
#include "Animations.h"

CGame* CGame::__instance = NULL;

/*
	Initialize DirectX, create a Direct3D device for rendering within the window, initial Sprite library for
	rendering 2D images
	- hInst: Application instance handle
	- hWnd: Application window handle
*/
void CGame::Init(HWND hWnd)
{
	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);

	this->hWnd = hWnd;

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;

	RECT r;
	GetClientRect(hWnd, &r);	// retrieve Window width & height 

	d3dpp.BackBufferHeight = r.bottom + 1;
	d3dpp.BackBufferWidth = r.right + 1;

	screen_height = r.bottom + 1;
	screen_width = r.right + 1;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv);

	if (d3ddv == NULL)
	{
		OutputDebugString(L"[ERROR] CreateDevice failed\n");
		return;
	}

	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	// Initialize sprite helper from Direct3DX helper library
	D3DXCreateSprite(d3ddv, &spriteHandler);

	OutputDebugString(L"[INFO] InitGame done;\n");
}

/*
	Utility function to wrap LPD3DXSPRITE::Draw
*/
void CGame::Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha, bool flip)
{
	float width = right - left;
	float height = bottom - top;
	int scale = 1;
	D3DXVECTOR2 center = D3DXVECTOR2(flip ? (width / 2) * scale - width * scale : (width / 2) * scale, (height / 2) * scale);
	D3DXVECTOR2 translate = D3DXVECTOR2(flip ? x + width * scale : x, y);
	D3DXVECTOR2 scaling = D3DXVECTOR2((flip) ? -1 : 1, 1);
	float angle = 0;
	SetRenderData(center, translate, scaling);
	RECT r;
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;
	D3DXMATRIX oldMatrix;
	D3DXMATRIX matrix;
	D3DXMatrixTransformation2D(
		&matrix,
		NULL,
		0.0f,
		&scaling,
		&center,
		angle,
		&translate
	);

	spriteHandler->GetTransform(&oldMatrix);
	spriteHandler->SetTransform(&matrix);
	spriteHandler->Draw(texture, &r, NULL, NULL, D3DCOLOR_ARGB(alpha, 255, 255, 255));
	spriteHandler->SetTransform(&oldMatrix);

}

void CGame::SetRenderData(D3DXVECTOR2& center, D3DXVECTOR2& translate, D3DXVECTOR2& scaling)
{
	float cam_x, cam_y;
	((CArea2Scene*)GetCurrentScene())->GetCameraPosition(cam_x, cam_y);
	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);
	mt._22 = -1;
	mt._41 = -cam_x;
	mt._42 = cam_y;
	D3DXVECTOR4 curTranslate;
	D3DXVECTOR4 curCenter;

	D3DXVec2Transform(&curCenter, &D3DXVECTOR2(center.x, center.y), &mt);

	D3DXVec2Transform(&curTranslate, &D3DXVECTOR2(translate.x, translate.y), &mt);

	center.x = curCenter.x;
	center.y = curCenter.y;
	translate.x = curTranslate.x;
	translate.y = curTranslate.y;
}


int CGame::IsKeyDown(int KeyCode)
{
	return (keyStates[KeyCode] & 0x80) > 0;
}

void CGame::InitKeyboard()
{
	HRESULT
		hr = DirectInput8Create
		(
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8, (VOID**)&di, NULL
		);

	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] DirectInput8Create failed!\n");
		return;
	}

	hr = di->CreateDevice(GUID_SysKeyboard, &didv, NULL);

	// TO-DO: put in exception handling
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] CreateDevice failed!\n");
		return;
	}

	// Set the data format to "keyboard format" - a predefined data format 
	//
	// A data format specifies which controls on a device we
	// are interested in, and how they should be reported.
	//
	// This tells DirectInput that we will be passing an array
	// of 256 bytes to IDirectInputDevice::GetDeviceState.

	hr = didv->SetDataFormat(&c_dfDIKeyboard);

	hr = didv->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);


	// IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
	//
	// DirectInput uses unbuffered I/O (buffer size = 0) by default.
	// If you want to read buffered data, you need to set a nonzero
	// buffer size.
	//
	// Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
	//
	// The buffer size is a DWORD property associated with the device.
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

	hr = didv->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

	hr = didv->Acquire();
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] DINPUT8::Acquire failed!\n");
		return;
	}

	DebugOut(L"[INFO] Keyboard has been initialized successfully\n");
}

void CGame::ProcessKeyboard()
{
	HRESULT hr;

	// Collect all key states first
	hr = didv->GetDeviceState(sizeof(keyStates), keyStates);
	if (FAILED(hr))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			HRESULT h = didv->Acquire();
			if (h == DI_OK)
			{
				DebugOut(L"[INFO] Keyboard re-acquired!\n");
			}
			else return;
		}
		else
		{
			//DebugOut(L"[ERROR] DINPUT::GetDeviceState failed. Error: %d\n", hr);
			return;
		}
	}

	keyHandler->KeyState((BYTE*)&keyStates);



	// Collect all buffered events
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	hr = didv->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);
	if (FAILED(hr))
	{
		//DebugOut(L"[ERROR] DINPUT::GetDeviceData failed. Error: %d\n", hr);
		return;
	}

	// Scan through all buffered events, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = keyEvents[i].dwOfs;
		int KeyState = keyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
			keyHandler->OnKeyDown(KeyCode);
		else
			keyHandler->OnKeyUp(KeyCode);
	}
}

CGame::~CGame()
{
	if (spriteHandler != NULL) spriteHandler->Release();
	if (backBuffer != NULL) backBuffer->Release();
	if (d3ddv != NULL) d3ddv->Release();
	if (d3d != NULL) d3d->Release();
}

/*
	Standard sweptAABB implementation
	Source: GameDev.net
*/
void CGame::SweptAABB(
	float ml, float mt, float mr, float mb,
	float dx, float dy,
	float sl, float st, float sr, float sb,
	float& t, float& nx, float& ny)
{

	float dx_entry, dx_exit, tx_entry, tx_exit;
	float dy_entry, dy_exit, ty_entry, ty_exit;

	float t_entry;
	float t_exit;

	t = -1.0f;			// no collision
	nx = ny = 0;

	//
	// Broad-phase test 
	//

	float bl = dx > 0 ? ml : ml + dx;
	float bt = dy > 0 ? mt + dy : mt;
	float br = dx > 0 ? mr + dx : mr;
	float bb = dy > 0 ? mb : mb + dy;

	if (br < sl || bl > sr || bb > st || bt < sb) return;


	if (dx == 0 && dy == 0) return;		// moving object is not moving > obvious no collision

	if (dx > 0)
	{
		dx_entry = sl - mr;
		dx_exit = sr - ml;
	}
	else if (dx < 0)
	{
		dx_entry = sr - ml;
		dx_exit = sl - mr;
	}


	if (dy > 0)
	{
		dy_entry = sb - mt;
		dy_exit = st - mb;
	}
	else if (dy < 0)
	{
		dy_entry = st - mb;
		dy_exit = sb - mt;
	}

	if (dx == 0)
	{
		tx_entry = -999999.0f;
		tx_exit = 999999.0f;
	}
	else
	{
		tx_entry = dx_entry / dx;
		tx_exit = dx_exit / dx;
	}

	if (dy == 0)
	{
		ty_entry = -99999.0f;
		ty_exit = 99999.0f;
	}
	else
	{
		ty_entry = dy_entry / dy;
		ty_exit = dy_exit / dy;
	}


	if ((tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f) return;

	t_entry = max(tx_entry, ty_entry);
	t_exit = min(tx_exit, ty_exit);

	if (t_entry > t_exit) return;

	t = t_entry;

	if (tx_entry > ty_entry)
	{
		ny = 0.0f;
		dx > 0 ? nx = -1.0f : nx = 1.0f; // huong
	}
	else
	{
		nx = 0.0f;
		dy > 0 ? ny = -1.0f : ny = 1.0f; // huong
	}

}

CGame* CGame::GetInstance()
{
	if (__instance == NULL) __instance = new CGame();
	return __instance;
}

#define MAX_GAME_LINE 1024


#define GAME_FILE_SECTION_UNKNOWN -1
#define GAME_FILE_SECTION_SETTINGS 1
#define GAME_FILE_SECTION_SCENES 2
#define GAME_FILE_SECTION_TEXTURES 3
#define GAME_FILE_SECTION_SPRITES 4
#define GAME_FILE_SECTION_ANIMATIONS 5
#define GAME_FILE_SECTION_ANIMATION_SETS 6
#define GAME_FILE_SECTION_TILES 7

void CGame::_ParseSection_SETTINGS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;
	if (tokens[0] == "start")
		current_scene = atoi(tokens[1].c_str());
	else
		DebugOut(L"[ERROR] Unknown game setting %s\n", ToWSTR(tokens[0]).c_str());
}

void CGame::_ParseSection_SCENES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;
	int id = atoi(tokens[0].c_str());
	LPCWSTR path = ToLPCWSTR(tokens[1]);

	LPSCENE scene = new CArea2Scene(id, path);
	scenes[id] = scene;
}

void CGame::_ParseSection_TILES(string line)
{
	vector<string> tokens = split(line);
	string path = tokens[0];
	int total = atoi(tokens[1].c_str());
	for (int num = 0; num < total; num++)
	{
		string fullPath = path + std::to_string(num) + ".png";
		CTextures::GetInstance()->Add(num, ToLPCWSTR(fullPath.c_str()), D3DCOLOR_XRGB(255, 255, 255));
	}
}

void CGame::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 5) return;
	int texId = atoi(tokens[0].c_str());
	LPCWSTR texPath = ToLPCWSTR(tokens[1].c_str());

	int red = atoi(tokens[2].c_str());
	int green = atoi(tokens[3].c_str());
	int blue = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texId, texPath, D3DCOLOR_XRGB(red, green, blue));
}

void CGame::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 6) return;
	int spriteId = atoi(tokens[0].c_str());
	int left = atoi(tokens[1].c_str());
	int top = atoi(tokens[2].c_str());
	int right = atoi(tokens[3].c_str());
	int bottom = atoi(tokens[4].c_str());

	int texId = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texId);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texId);
		return;
	}
	CSprites::GetInstance()->Add(spriteId, left, top, right, bottom, tex);
}

void CGame::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 3) return;
	int aniId = atoi(tokens[0].c_str());
	LPANIMATION ani = new CAnimation();

	for (int i = 1; i < tokens.size(); i += 2)
	{
		int spriteId = atoi(tokens[i].c_str());
		int time = atoi(tokens[i + 1].c_str());
		ani->Add(spriteId, time);
	}

	CAnimations::GetInstance()->Add(aniId, ani);
}

void CGame::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 2) return;
	int ani_setId = atoi(tokens[0].c_str());
	LPANIMATION_SET aniSet = new CAnimationSet();

	for (int i = 1; i < tokens.size(); i++)
	{
		int aniId = atoi(tokens[i].c_str());

		LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);
		aniSet->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_setId, aniSet);
}

/*
	Load game campaign file and load/initiate first scene
*/
void CGame::Load(LPCWSTR gameFile)
{
	DebugOut(L"[INFO] Start loading game file : %s\n", gameFile);

	ifstream f;
	f.open(gameFile);
	char str[MAX_GAME_LINE];

	// current resource section flag
	int section = GAME_FILE_SECTION_UNKNOWN;

	while (f.getline(str, MAX_GAME_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TILES]") { section = GAME_FILE_SECTION_TILES; continue; }
		if (line == "[SETTINGS]") { section = GAME_FILE_SECTION_SETTINGS; continue; }
		if (line == "[SCENES]") { section = GAME_FILE_SECTION_SCENES; continue; }
		if (line == "[TEXTURES]") { section = GAME_FILE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") { section = GAME_FILE_SECTION_SPRITES; continue; }
		if (line == "[ANIMATIONS]") { section = GAME_FILE_SECTION_ANIMATIONS; continue; }
		if (line == "[ANIMATION_SETS]") { section = GAME_FILE_SECTION_ANIMATION_SETS; continue; }
		//
		// data section
		//
		switch (section)
		{
			case GAME_FILE_SECTION_TILES:
				_ParseSection_TILES(line);
				break;
			case GAME_FILE_SECTION_SETTINGS: _ParseSection_SETTINGS(line); break;
			case GAME_FILE_SECTION_SCENES: _ParseSection_SCENES(line); break;
			case GAME_FILE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
			case GAME_FILE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
			case GAME_FILE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
			case GAME_FILE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		}
	}
	f.close();

	DebugOut(L"[INFO] Loading game file : %s has been loaded successfully\n", gameFile);

	SwitchScene(current_scene);
}

void CGame::SwitchScene(int scene_id)
{
	DebugOut(L"[INFO] Switching to scene %d\n", scene_id);

	scenes[current_scene]->Unload();

	//CTextures::GetInstance()->Clear();
	//CSprites::GetInstance()->Clear();
	//CAnimations::GetInstance()->Clear();

	current_scene = scene_id;
	LPSCENE s = scenes[scene_id];
	CGame::GetInstance()->SetKeyHandler(s->GetKeyEventHandler());
	s->Load();
}
