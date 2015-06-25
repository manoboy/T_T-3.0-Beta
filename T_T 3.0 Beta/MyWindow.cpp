#include "MyWindow.h"
#include "Engine.h"
HDC CMyWindow::MainHDC = NULL;
HGLRC CMyWindow::MainHGLRC = NULL;
HPALETTE CMyWindow::MainPalette = NULL;
HWND CMyWindow::hWindow = NULL;
RECT CMyWindow::WindowRect = RECT{ 0 };
HWND CMyWindow::hTargetWindow = NULL;
RECT CMyWindow::TargetWindowRect = RECT{ 0 };
RECT CMyWindow::TargetClientRect = RECT{ 0 };
HINSTANCE* CMyWindow::WindowInstance = NULL;
char* CMyWindow::WindowName = NULL;
int CMyWindow::RefreshRate = (1000/200);
float CMyWindow::Width = NULL;
float CMyWindow::Height = NULL;
float CMyWindow::CenterX = NULL;
float CMyWindow::CenterY = NULL;
MSG CMyWindow::Msg;
GLuint	CMyWindow::base = NULL;
HFONT CMyWindow::oldfont;
ABC CMyWindow::glyphInfo[256];

float CMyWindow::FontHeight = 0;
float CMyWindow::FontSpacing = 0;
TEXTMETRIC CMyWindow::tm;

POINT CMyWindow::MousePos;
MARGINS Margin = { -1, -1, -1, -1 };
LRESULT APIENTRY MyWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		CMyWindow::MainHDC = GetDC(hWnd);
		CMyWindow::SetupGL();
		DwmExtendFrameIntoClientArea(CMyWindow::hWindow, &Margin);
		return 0;
	}
	case WM_CLOSE:
	{
		DestroyWindow(hWnd);
	}
	case WM_DESTROY:
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(CMyWindow::MainHGLRC);
		DeleteDC(CMyWindow::MainHDC);
		ReleaseDC(hWnd, CMyWindow::MainHDC);
		PostQuitMessage(0);
		exit(1);
		UnregisterClass(CMyWindow::WindowName, *CMyWindow::WindowInstance);
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);
		glClear(GL_COLOR_BUFFER_BIT);

		/*
		Render
		*/

		Engine->Render();

		SwapBuffers(CMyWindow::MainHDC);
		EndPaint(hWnd, &ps);
		return 0;
	}
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

CMyWindow::~CMyWindow()
{
}

CMyWindow::CMyWindow()
{
	WindowInstance = nullptr;
	MainHDC = NULL;
	MainHGLRC = NULL;
	MainPalette = NULL;
	if (WindowName)
		delete[] WindowName;
	int Length = (rand() % 15) + 5;
	WindowName = new char[Length + 1];
	for (int i = 0; i < Length; i++)
		WindowName[i] = (rand() % 200) + 50;
	WindowName[Length] = 0;

}

void CMyWindow::Run()
{
	while (GetMessage(&Msg, NULL, 0, 0) > 0 && !GlobalVariables::ExitCheat)
	{
		Sleep(1);
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
};

DWORD WINAPI CMyWindow::UpdateDrawings()
{
	while (!GlobalVariables::ExitCheat)
	{
		InvalidateRect(CMyWindow::hWindow, NULL, false);
		Sleep(RefreshRate);
	};
	ExitThread(0);
}

bool CMyWindow::SetInstance(HINSTANCE *Instance)
{
	if (WindowInstance)
		return false;

	if (Instance)
	{
		WindowInstance = Instance;
		return true;
	}

	return false;
}

bool CMyWindow::InitWindow()
{
	WNDCLASSEX WClass;
	WClass.cbSize = sizeof(WNDCLASSEX);
	WClass.style = 0;
	WClass.lpfnWndProc = MyWndProc;
	WClass.cbClsExtra = 0;
	WClass.cbWndExtra = 0;
	WClass.hInstance = *WindowInstance;
	WClass.hIcon = NULL;
	WClass.hCursor = NULL;
	WClass.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	WClass.lpszMenuName = NULL;
	WClass.lpszClassName = WindowName;
	WClass.hIconSm = NULL;

	if (!RegisterClassEx(&WClass))
	{
		return false;
	}
	/*
	hWindow = CreateWindowEx(
		WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_LAYERED,
		WindowName,
		WindowName,
		WS_POPUP | WS_VISIBLE | WS_MAXIMIZE,
		WindowRect.left,
		WindowRect.top - 1,
		Width,
		Height + 1,
		NULL, NULL, *WindowInstance, NULL);
	*/

	hWindow = CreateWindowEx(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED, WindowName, WindowName, WS_POPUP, 1, 1, Width, Height, 0, 0, 0, 0);
	
	if (hWindow == NULL)
	{
		UnregisterClass(WindowName, *WindowInstance);
		return false;
	}

	if (!SetLayeredWindowAttributes(hWindow, RGB(0, 0, 0), 255, LWA_COLORKEY | LWA_ALPHA))
	{
		UnregisterClass(WindowName, *WindowInstance);
		return false;
	}

	BOOL IsEnabled;
	if (DwmIsCompositionEnabled(&IsEnabled) != S_OK)
	{
		UnregisterClass(WindowName, *WindowInstance);
		return false;
	}

	if (!IsEnabled)
	{
		UnregisterClass(WindowName, *WindowInstance);
		return false;
	}

	DWM_BLURBEHIND bb = { DWM_BB_ENABLE | DWM_BB_BLURREGION, true, CreateRectRgn(0, 0, -1, -1), true };
	if (DwmEnableBlurBehindWindow(hWindow, &bb) != S_OK)
	{
		UnregisterClass(WindowName, *WindowInstance);
		return false;
	}

	ShowWindow(hWindow, 1);

	return true;
}

void CMyWindow::Resize()
{
	GetWindowRect(hTargetWindow, &TargetWindowRect);
	GetClientRect(hTargetWindow, &TargetClientRect);
	Width = TargetClientRect.right - TargetClientRect.left;
	Height = TargetClientRect.bottom - TargetClientRect.top;
	CenterX = Width / 2;
	CenterY = Height / 2;
	SetWindowPos(hWindow, 0, TargetWindowRect.left, TargetWindowRect.top, Width, Height, 0);
	glViewport(0, 0, Width, Height);
	glOrtho(TargetClientRect.left, TargetClientRect.right, TargetClientRect.bottom, TargetClientRect.top, 0, 1);

}

void CMyWindow::Resize(RECT WindowRect, RECT ClientRect)
{

	Width = ClientRect.right - ClientRect.left;
	Height = ClientRect.bottom - ClientRect.top;
	SetWindowPos(hWindow, 0, WindowRect.left, WindowRect.top, Width, Height, 0);
	glViewport(WindowRect.left, WindowRect.top, Width, Height);
	glOrtho(ClientRect.left, ClientRect.right, ClientRect.bottom, ClientRect.top, 0, 1);
}

bool CMyWindow::SetupGL()
{
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,                                  // Version Number
		PFD_DRAW_TO_WINDOW |              // Format Must Support Window
		PFD_SUPPORT_OPENGL |              // Format Must Support OpenGL
		//        PFD_SUPPORT_GDI|                  // Format Must Support GDI
		PFD_SUPPORT_COMPOSITION |         // Format Must Support Composition
		PFD_DOUBLEBUFFER,                 // Must Support Double Buffering
		PFD_TYPE_RGBA,                    // Request An RGBA Format
		32,                               // Select Our Color Depth
		0, 0, 0, 0, 0, 0,                 // Color Bits Ignored
		8,                                // An Alpha Buffer
		0,                                // Shift Bit Ignored
		0,                                // No Accumulation Buffer
		0, 0, 0, 0,                       // Accumulation Bits Ignored
		0,                               // No Z-Buffer (Depth Buffer)
		8,                                // Some Stencil Buffer
		0,                                // No Auxiliary Buffer
		PFD_MAIN_PLANE,                   // Main Drawing Layer
		0,                                // Reserved
		0, 0, 0                           // Layer Masks Ignored
	};
	int PixelFormat = ChoosePixelFormat(MainHDC, &pfd);
	if (!PixelFormat)
	{
		return false;
	}
	if (!SetPixelFormat(MainHDC, PixelFormat, &pfd))
	{
		return false;
	}
	if (!DescribePixelFormat(MainHDC, PixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd))
	{
		return false;
	}
	MainHGLRC = wglCreateContext(MainHDC);
	if (!MainHGLRC)
	{
		return false;
	}
	if (!wglMakeCurrent(MainHDC, MainHGLRC))
	{
		return false;
	}

	glEnable(GL_ALPHA_TEST);
	//glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glMatrixMode(GL_PROJECTION);
	Resize();
	glClearColor(0.f, 0.f, 0.f, 0.f);

	return true;
}

bool CMyWindow::Init(HINSTANCE *Instance, HWND _hTargetWindow)
{
	if (!_hTargetWindow)
		return false;
	
	hTargetWindow = _hTargetWindow;

	if (!SetInstance(Instance))
		return false;
	Resize();
	
	if (!InitWindow())
		return false;

	BuildFont();

	return true;
}

GLvoid CMyWindow::BuildFont(GLvoid)
{
	/**/
	HFONT	font;									// Used For Good House Keeping

	base = glGenLists(1000);								// Storage For 96 Characters

	font = CreateFont(14,							// Height Of Font
		0,								// Width Of Font
		0,								// Angle Of Escapement
		0,								// Orientation Angle
		FW_BOLD,						// Font Weight
		FALSE,							// Italic
		FALSE,							// Underline
		FALSE,							// Strikeout
		ANSI_CHARSET,					// Character Set Identifier
		OUT_TT_PRECIS,					// Output Precision
		CLIP_DEFAULT_PRECIS,			// Clipping Precision
		ANTIALIASED_QUALITY,			// Output Quality
		FF_DONTCARE | DEFAULT_PITCH,		// Family And Pitch
		"Comic Sans");
		//"Courier New");					// Font Name

	//oldfont = (HFONT)SelectObject(MainHDC, font);           // Selects The Font We Want
	//wglUseFontBitmaps(MainHDC, 32, 96, base);				// Builds 96 Characters Starting At Character 32								// Delete The Font

	oldfont = (HFONT)SelectObject(MainHDC, font);           // Selects The Font We Want
	wglUseFontBitmaps(MainHDC, 0, 255, base);	
	GetCharABCWidths(MainHDC, 0, 255, &glyphInfo[0]);
	GetTextMetrics(MainHDC, &tm);

	FontHeight = tm.tmHeight/2;
	FontSpacing = FontHeight+3;

	if (oldfont)
		SelectObject(MainHDC, oldfont);							// Selects The Font We Want
	
	DeleteObject(font);
}

GLvoid CMyWindow::KillFont(GLvoid)									
{
	glDeleteLists(base, 255);							
}

GLvoid CMyWindow::glPrint(const char *fmt, ...)					// Custom GL "Print" Routine
{
	char		text[256];								// Holds Our String
	va_list		ap;										// Pointer To List Of Arguments

	if (fmt == NULL)									// If There's No Text
		return;											// Do Nothing

	va_start(ap, fmt);									// Parses The String For Variables
	vsprintf(text, fmt, ap);						// And Converts Symbols To Actual Numbers
	va_end(ap);											// Results Are Stored In Text

	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base - 32);								// Sets The Base Character to 32
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits
}
