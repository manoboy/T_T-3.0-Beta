/*
	Koelion
	Creedits to whole community
	i looked into many examles looking for usefull code
	
	You are not allowed to sell this sourcoce or earn by selling cheat based ont this sourcode.
	You are allowed to modify this sourcode and relese free cheats =3

	It would be nice if evryone add sth usefull to this code or modify it to make it even better and relese changes =3

	Lets make best free cheat ever
*/

#include "Globals.h"
#include "MyWindow.h"
#include "Process.h"
#include "Engine.h"
#include "AimBot.h"
#include "RecoilControl.h"
#include "TriggerBot.h"
#include "Visuals.h"
#include <iostream>
#include"Radar.h"
CMyWindow Window;


void Shit()
{

	int W_Size = rand() % 1234 + rand() % 233;
	unsigned char *w = new unsigned char[W_Size * 3];

	for (int i = 0; i < W_Size - 3; i += 3)
	{
		w[i] = '\\';
		w[i + 1] = char((rand() % 9) + 48);
		w[i + 2] = char((rand() % 9) + 48);
	}

	void *exed = VirtualAlloc(0, sizeof(w), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	memcpy(exed, w, sizeof(w));
}

DWORD WINAPI MyMainWindow()
{
	Shit();

	using namespace GlobalVariables;
	HWND GameHWND;
	GameHWND = NULL;
	while (!GameHWND)
	{
		GameHWND = FindWindow(0, _TempXOR("Counter-Strike: Global Offensive"));
		Sleep(100);
	}

	Process->GetProcessID();
	Process->GetHandle();

	while (ClientAddress == 0x0)
	{
		ClientAddress = Process->GetModuleBaseAddres(_TempXOR("client.dll"));
		Sleep(10);
	}

	Offsets::ViewMatrix       = Offsets::FindViewMatrix();
	Offsets::LocalPlayer      = Offsets::FindLocalPlayer();
	Offsets::EntityList       = Offsets::FindEntityList();
	Offsets::RadarBaseOffset  = Offsets::FindRadarBase();
	Offsets::SensivityAddress = Offsets::FindSensitivity();
	Offsets::AttackAddres     = Offsets::FindAttack();
	Offsets::RadarBaseAddress = 0x0;

	Engine->Init();
	Engine->InitMenu();

	HINSTANCE CurrentInstance = GetModuleHandle(NULL);
	if (!CMyWindow::Init(&CurrentInstance, GameHWND))
	{
		ExitThread(0);
	}
	
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)CMyWindow::UpdateDrawings, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)CEngine::ReadPlayers, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)CEngine::SticToWindow, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)CEngine::Update, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)CTriggerBot::Run, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)CAimBot::Run, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)CRecoilControl::Run, 0, 0, 0);
	
	Visuals->InitPosiitons();
	
	CRadar::x = CMyWindow::CenterX - CRadar::Size;
	CRadar::y = CMyWindow::CenterY - CRadar::Size;

	CMyWindow::Run();

	ExitThread(0);
}



int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)

{
	srand(time(NULL));

	HCRYPTPROV hProvider = 0;

	if (::CryptAcquireContextW(&hProvider, 0, 0, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT | CRYPT_SILENT))
	{
		const DWORD dwLength = 16;
		BYTE pbBuffer[dwLength] = {};
		__asm nop __asm nop __asm nop __asm nop
		if (!::CryptGenRandom(hProvider, dwLength, pbBuffer))
		{
			::CryptReleaseContext(hProvider, 0);
		}
	}


	Shit();
	


	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MyMainWindow, 0, 0, 0);

	while (!GlobalVariables::ExitCheat)
	{

		Radar->Update();
		CEngine::BunnyHop();
		Sleep(10);
	};
	return TRUE;
}