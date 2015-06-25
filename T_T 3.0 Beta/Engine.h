#pragma once
#include "Globals.h"
#include "MyMenu.h"
class CEngine
{
public:
	CEngine();
	~CEngine();

	static int PANICK_KEY;
	static bool bBunnyHop;
	static bool save;
	static bool load;

	static CMyMenu Menu;
	void InitMenu();

	static DWORD WINAPI SticToWindow();
	static clock_t StickToGameWindowUpdateTime;

	void Render();
	static void Init();
	static void ReadViewMatrix();
	static void BunnyHop();
	static int ReadPlayersSleep;
	static DWORD WINAPI ReadPlayers();
	static DWORD WINAPI Update();
};

extern CEngine* Engine;