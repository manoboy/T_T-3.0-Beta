#pragma once
#include "Globals.h"

class CMyWindow
{
public:

	static HWND hWindow;
	static RECT WindowRect;

	static HWND hTargetWindow;
	static RECT TargetWindowRect;
	static RECT TargetClientRect;

	static HINSTANCE *WindowInstance;

	static char* WindowName;
	static int RefreshRate;

	static float Width;
	static float Height;
	static float CenterX;
	static float CenterY;


	static bool SetInstance(HINSTANCE *Instance);
	static void Resize(RECT WindowRect, RECT ClientRect);
	static bool InitWindow();
	static bool Init(HINSTANCE *Instance, HWND _hTargetWindow);
	
	static void Resize();
	static bool SetupGL();

	static void Run();
	static DWORD WINAPI UpdateDrawings();

	static MSG Msg;

	CMyWindow();
	~CMyWindow();
	static HDC MainHDC;
	static HGLRC MainHGLRC;
	static HPALETTE MainPalette;


	static GLuint	base;
	static ABC glyphInfo[256];
	static TEXTMETRIC tm;  
	static HFONT oldfont;
	static float FontHeight;
	static float FontSpacing;
	static GLvoid BuildFont(GLvoid);
	static GLvoid KillFont(GLvoid);
	static GLvoid glPrint(const char *fmt, ...);



	static POINT MousePos;

};


