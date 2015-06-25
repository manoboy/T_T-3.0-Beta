#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <TlHelp32.h>
#include <ctime>
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdint>
#include <fstream>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <Wincrypt.h>

#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glu32.lib")
#include <dwmapi.h>
#pragma comment(lib, "Dwmapi.lib")
#pragma warning(disable : 4996)
#include<winuser.h>
#pragma comment(lib, "user32.lib")
#include "Encrypt.h"

using namespace std;


extern char *KeyNames[256];

namespace Offsets
{
	extern DWORD ViewMatrix;
	extern DWORD LocalPlayer;
	extern DWORD EntityList;
	extern DWORD RadarBaseOffset;
	extern DWORD SensivityAddress;
	extern DWORD AttackAddres;
	extern DWORD RadarBaseAddress;
}

namespace GlobalVariables
{
	extern bool ExitCheat;

	extern DWORD ClientAddress;

	extern int MaxPlayers;

	extern float MouseMultiplyer;

}

void MouseMove(float x, float y);
void MouseButton(int Type);
void MouseUP(int Type);