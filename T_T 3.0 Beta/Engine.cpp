#include "Engine.h"
#include "Math.h"
#include "Entity.h"
#include "Process.h"
#include "MyWindow.h"
#include "Drawings.h"
#include "Visuals.h"
#include "ObjectManager.h"
#include "MyButtons.h"
CEngine* Engine = new CEngine;

int CEngine::PANICK_KEY = VK_END;
int CEngine::ReadPlayersSleep = 2;
bool CEngine::bBunnyHop;
bool CEngine::save = false;
bool CEngine::load = false;
clock_t CEngine::StickToGameWindowUpdateTime = 1000;
CMyMenu CEngine::Menu;

CEngine::CEngine()
{
}


CEngine::~CEngine()
{
}

void CEngine::InitMenu()
{
	Menu.Init();
}

void CEngine::Render()
{
	Visuals->Render();
	if (Menu.MenuActive)
	{
		Menu.Draw();
	}
}

void CEngine::ReadViewMatrix()
{

}


void CEngine::BunnyHop()
{
	if (bBunnyHop)
	{
		if (Process->hWindow != GetForegroundWindow())
			return;
		if (GetAsyncKeyState(VK_SPACE))
		{
			if (LocalPlayer->Falling == 257)
			{

				mouse_event(MOUSEEVENTF_MIDDLEDOWN, 0, 0, NULL, NULL);
				Sleep(1);
				mouse_event(MOUSEEVENTF_MIDDLEUP, NULL, NULL, NULL, NULL);
			}
		}
	}
}


DWORD WINAPI CEngine::ReadPlayers()
{
	while (!GlobalVariables::ExitCheat)
	{
		vMatrix = Process->ReadMemory<ViewMatrix>(GlobalVariables::ClientAddress + Offsets::ViewMatrix);
		LocalPlayer->Read();
		Offsets::RadarBaseAddress = Process->ReadMemory<DWORD>(GlobalVariables::ClientAddress + Offsets::RadarBaseOffset);
		Offsets::RadarBaseAddress = Process->ReadMemory<DWORD>(Offsets::RadarBaseAddress + 0x50);
		for (int i = 0; i < GlobalVariables::MaxPlayers; i++)
			Entity[i].Read(i);
		
		ObjectManager->ReadObjects();
		
		Sleep(ReadPlayersSleep);
	}
	ExitThread(0);
}

void CEngine::Init()
{
	int MouseSpeed;
	SystemParametersInfo(SPI_GETMOUSESPEED, 0, &MouseSpeed, 0);

	if (MouseSpeed>3)
		MouseSpeed = MouseSpeed / 2 + 1;

	switch (MouseSpeed)
	{
	case 1:
		GlobalVariables::MouseMultiplyer = 0.0625;
		break;
	case 2:
		GlobalVariables::MouseMultiplyer = 0.0125;
		break;
	case 3:
		GlobalVariables::MouseMultiplyer = 0.25;
		break;
	case 4:
		GlobalVariables::MouseMultiplyer = 0.50;
		break;
	case 5:
		GlobalVariables::MouseMultiplyer = 0.75;
		break;
	case 6:
		GlobalVariables::MouseMultiplyer = 1.0;
		break;
	case 7:
		GlobalVariables::MouseMultiplyer = 1.5;
		break;
	case 8:
		GlobalVariables::MouseMultiplyer = 2.0;
		break;
	case 9:
		GlobalVariables::MouseMultiplyer = 2.5;
		break;
	case 10:
		GlobalVariables::MouseMultiplyer = 3.0;
		break;
	case 11:
		GlobalVariables::MouseMultiplyer = 3.5;
		break;
	}
}

DWORD WINAPI CEngine::Update()
{
	while (!GlobalVariables::ExitCheat)
	{
		if (GetAsyncKeyState(PANICK_KEY))
		{
			GlobalVariables::ExitCheat = true;
		}
		if ((GetAsyncKeyState(VK_DELETE) || GetAsyncKeyState(VK_F6)) && Menu.MenuActiveStateChangeTime + 200 < clock())
		{
			Menu.MenuActive = !Menu.MenuActive;
			Menu.MenuActiveStateChangeTime = clock();
		}
		if (Menu.MenuActive)
		{
			Menu.UpdateSubMenus();
			Menu.ActiveSubMenu->MenuUpdate();
		}

		if (load)
		{
			Menu.MenuLoad();
			load = false;
		}
		if (save)
		{
			Menu.MenuSave();
			save = false;
		}
		
		Sleep(10);
	}
	ExitThread(0);
}

DWORD WINAPI CEngine::SticToWindow()
{
	RECT rGameWindow;
	//return 0;
	while (!GlobalVariables::ExitCheat)
	{

		Process->GetWindow();
		if (Process->hWindow != NULL)
		{

			DWORD dwStyle = GetWindowLong(Process->hWindow, GWL_STYLE);
			if (dwStyle & WS_BORDER)
			{
				GetWindowRect(Process->hWindow, &rGameWindow);
				CMyWindow::WindowRect = rGameWindow;
				CMyWindow::WindowRect.top += 3;
				CMyWindow::WindowRect.bottom -= 3;
				CMyWindow::WindowRect.left += 3;
				int Width = CMyWindow::WindowRect.right - CMyWindow::WindowRect.left;
				int Height = CMyWindow::WindowRect.bottom - CMyWindow::WindowRect.top;
				MoveWindow(CMyWindow::hWindow, CMyWindow::WindowRect.left, CMyWindow::WindowRect.top, Width, Height, true);
			}
		}
		else
		{
			GlobalVariables::ExitCheat = true;
		}
		Sleep(StickToGameWindowUpdateTime);
	}
	ExitThread(0);
}
