#include "Drawings.h"
#include "MyWindow.h"
CDrawings* Drawings = new CDrawings;

Color Red = Color(255 / 255, 255 / 255, 0 / 255, 0 / 255);
Color Green = Color(255 / 255, 0 / 255, 255 / 255, 0 / 255);
Color Blue = Color(255 / 255, 0 / 255, 0 / 255, 255 / 255);
Color Black = Color(255 / 255, 0 / 255, 0 / 255, 0 / 255);
Color White = Color(255 / 255, 255 / 255, 255 / 255, 255 / 255);
Color Aqua = Color(255 / 255, 0 / 255, 255 / 255, 255 / 255);
Color Yellow = Color(255 / 255, 255 / 255, 255 / 255, 0 / 255);
Color Pink = Color(255 / 255, 255 / 255, 0 / 255, 255 / 255);

CDrawings::CDrawings()
{
}


CDrawings::~CDrawings()
{
}

void CDrawings::Line(float x1, float y1, float x2, float y2, float Width, Color color)
{
	glColor4f(color.r, color.g, color.b, color.a);
	glLineWidth(Width);
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}

void CDrawings::Box(float x, float y, float width, float height, float Width, Color color)
{
	glColor4f(color.r, color.g, color.b, color.a);
	glLineWidth(Width);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x, y);
	glVertex2f(x, y + height);
	glVertex2f(x + width, y + height);
	glVertex2f(x + width, y);
	glEnd();
}

void CDrawings::Box(RECT Pos, float Width, Color color)
{
	glColor4f(color.r, color.g, color.b, color.a);
	glLineWidth(Width);
	glBegin(GL_LINE_LOOP);
	glVertex2f(Pos.left, Pos.top);
	glVertex2f(Pos.left, Pos.bottom);
	glVertex2f(Pos.right, Pos.bottom);
	glVertex2f(Pos.right, Pos.top);
	glEnd();
}

void CDrawings::BorderdBox(float x, float y, float width, float height, float Width, float BorderWidth, Color color, Color BorderColor)
{
	glColor4f(BorderColor.r, BorderColor.g, BorderColor.b, BorderColor.a);
	glLineWidth(Width + BorderWidth);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x, y);
	glVertex2f(x, y + height);
	glVertex2f(x + width, y + height);
	glVertex2f(x + width, y);
	glEnd();

	glColor4f(color.r, color.g, color.b, color.a);
	glLineWidth(Width);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x, y);
	glVertex2f(x, y + height);
	glVertex2f(x + width, y + height);
	glVertex2f(x + width, y);
	glEnd();
}

void CDrawings::BorderdBox(RECT Pos, float Width, float BorderWidth, Color color, Color BorderColor)
{
	glColor4f(BorderColor.r, BorderColor.g, BorderColor.b, BorderColor.a);
	glLineWidth(Width + BorderWidth);
	glBegin(GL_LINE_LOOP);
	glVertex2f(Pos.left, Pos.top);
	glVertex2f(Pos.left, Pos.bottom);
	glVertex2f(Pos.right, Pos.bottom);
	glVertex2f(Pos.right, Pos.top);
	glEnd();

	glColor4f(color.r, color.g, color.b, color.a);
	glLineWidth(Width);
	glBegin(GL_LINE_LOOP);
	glVertex2f(Pos.left, Pos.top);
	glVertex2f(Pos.left, Pos.bottom);
	glVertex2f(Pos.right, Pos.bottom);
	glVertex2f(Pos.right, Pos.top);
	glEnd();
}

void CDrawings::FilledBox(float x, float y, float width, float height, Color color)
{
	//glLineWidth(1);
	glColor4f(color.r, color.g, color.b, color.a);
	glBegin(GL_QUADS);
	glVertex2f(x , y); 
	glVertex2f(x , y + height); 
	glVertex2f(x + width, y + height); 
	glVertex2f(x + width, y);
	glEnd();
}

void CDrawings::FilledBox(RECT Pos, Color color)
{
	//glLineWidth(1);
	glColor4f(color.r, color.g, color.b, color.a);
	glBegin(GL_QUADS);
	glVertex2f(Pos.left, Pos.top);
	glVertex2f(Pos.left, Pos.bottom);
	glVertex2f(Pos.right, Pos.bottom);
	glVertex2f(Pos.right, Pos.top);
	glEnd();
}

void CDrawings::GuiBox(float x, float y, float width, float height, Color color, Color BorderColor)
{
	glColor4f(BorderColor.r, BorderColor.g, BorderColor.b, BorderColor.a);
	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x, y);
	glVertex2f(x, y + height);
	glVertex2f(x + width, y + height);
	glVertex2f(x + width, y);
	glEnd();

	glColor4f(color.r, color.g, color.b, color.a);
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x, y + height);
	glVertex2f(x + width, y + height);
	glVertex2f(x + width, y);
	glEnd();
}


void CDrawings::GuiBox(RECT Pos, Color color, Color BorderColor)
{
	glColor4f(BorderColor.r, BorderColor.g, BorderColor.b, BorderColor.a);
	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
	glVertex2f(Pos.left, Pos.top);
	glVertex2f(Pos.left, Pos.bottom);
	glVertex2f(Pos.right, Pos.bottom);
	glVertex2f(Pos.right, Pos.top);
	glEnd();

	glColor4f(color.r, color.g, color.b, color.a);
	glBegin(GL_QUADS);
	glVertex2f(Pos.left, Pos.top);
	glVertex2f(Pos.left, Pos.bottom);
	glVertex2f(Pos.right, Pos.bottom);
	glVertex2f(Pos.right, Pos.top);
	glEnd();
}


void CDrawings::Circle(float cx, float cy, float r, int num_segments, Color color)
{
	float theta = 2 * 3.1415926 / float(num_segments);
	float c = cosf(theta);
	float s = sinf(theta);
	float t;

	float x = r;
	float y = 0;

	glColor4f(color.r, color.g, color.b, color.a);
	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < num_segments; ii++)
	{
		glVertex2f(x + cx, y + cy);
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	}
	glEnd();
}

void CDrawings::FilledCircle(float cx, float cy, float r, int num_segments, Color color)
{
	float theta = 2 * 3.1415926 / float(num_segments);
	float c = cosf(theta);
	float s = sinf(theta);
	float t;

	float x = r;
	float y = 0;

	glColor4f(color.r, color.g, color.b, color.a);
	glBegin(GL_TRIANGLE_FAN);
	for (int ii = 0; ii < num_segments; ii++)
	{
		glVertex2f(x + cx, y + cy);
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	}
	glEnd();
}


void CDrawings::Text(const char *text, int x, int y, Color color)
{
	if (text == NULL)
		return;

	//y += CMyWindow::tm.tmHeight/2;
	//x += 3;
	glColor4f(color.r, color.g, color.b, color.a);
	glRasterPos2i(x, y);

	glPushAttrib(GL_LIST_BIT);
	glListBase(CMyWindow::base);
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
	glPopAttrib();
}

void CDrawings::CenterText(const char *text, int x, int y, Color color)
{

	if (text == NULL)
		return;

	int Len = strlen(text);
	
	//y += CMyWindow::tm.tmHeight / 2;

	int stringWidth = 0;
	for (int j = 0; j < Len; ++j)
		stringWidth += CMyWindow::glyphInfo[text[j]].abcA + CMyWindow::glyphInfo[text[j]].abcB + CMyWindow::glyphInfo[text[j]].abcC;

	glColor4f(color.r, color.g, color.b, color.a);
	glRasterPos2i(x - stringWidth/2, y);
	glPushAttrib(GL_LIST_BIT);
	glListBase(CMyWindow::base);
	glCallLists(Len, GL_UNSIGNED_BYTE, text);
	glPopAttrib();
}
void CDrawings::Text(const wchar_t *text, int x, int y, Color color)
{
	if (text == NULL)
		return;

	char Temp[64];
	wcstombs(Temp, text, 64);

	//y += CMyWindow::tm.tmHeight / 2;
	//x += 3;

	glColor4f(color.r, color.g, color.b, color.a);
	glRasterPos2i(x, y);

	glPushAttrib(GL_LIST_BIT);
	glListBase(CMyWindow::base);
	glCallLists(strlen(Temp), GL_UNSIGNED_BYTE, Temp);
	glPopAttrib();
}

void CDrawings::CenterText(const wchar_t *text, int x, int y, Color color)
{

	if (text == NULL)
		return;
	
	char Temp[64];
	wcstombs(Temp, text, 64);

	int Len = strlen(Temp);

	//y += CMyWindow::tm.tmHeight/2;

	int stringWidth = 0;
	for (int j = 0; j < Len; ++j)
		stringWidth += CMyWindow::glyphInfo[Temp[j]].abcA + CMyWindow::glyphInfo[Temp[j]].abcB + CMyWindow::glyphInfo[Temp[j]].abcC;

	glColor4f(color.r, color.g, color.b, color.a);
	glRasterPos2i(x - stringWidth / 2, y);
	glPushAttrib(GL_LIST_BIT);
	glListBase(CMyWindow::base);
	glCallLists(Len, GL_UNSIGNED_BYTE, Temp);
	glPopAttrib();
}

void CDrawings::ShadowText(const char *text, int x, int y, Color color)
{
	if (text == NULL)
		return;

	//y += CMyWindow::tm.tmHeight/2;
	//x += 3;

	glColor4f(0, 0, 0, 255);
	glRasterPos2i(x + 1, y + 1);

	glPushAttrib(GL_LIST_BIT);
	glListBase(CMyWindow::base);
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
	glPopAttrib();

	glColor4f(color.r, color.g, color.b, color.a);
	glRasterPos2i(x, y);

	glPushAttrib(GL_LIST_BIT);
	glListBase(CMyWindow::base);
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
	glPopAttrib();
}

void CDrawings::ShadowCenterText(const char *text, int x, int y, Color color)
{

	if (text == NULL)
		return;

	int Len = strlen(text);

	//y += CMyWindow::tm.tmHeight / 2;

	int stringWidth = 0;
	for (int j = 0; j < Len; ++j)
		stringWidth += CMyWindow::glyphInfo[text[j]].abcA + CMyWindow::glyphInfo[text[j]].abcB + CMyWindow::glyphInfo[text[j]].abcC;

	glColor4f(0, 0, 0, 255);
	glRasterPos2i(x - stringWidth / 2 + 1, y + 1);

	glPushAttrib(GL_LIST_BIT);
	glListBase(CMyWindow::base);
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
	glPopAttrib();

	glColor4f(color.r, color.g, color.b, color.a);
	glRasterPos2i(x - stringWidth / 2, y);
	glPushAttrib(GL_LIST_BIT);
	glListBase(CMyWindow::base);
	glCallLists(Len, GL_UNSIGNED_BYTE, text);
	glPopAttrib();
}
void CDrawings::ShadowText(const wchar_t *text, int x, int y, Color color)
{
	if (text == NULL)
		return;

	char Temp[64];
	wcstombs(Temp, text, 64);

	//y += CMyWindow::tm.tmHeight / 2;
	//x += 3;

	glColor4f(0, 0, 0, 255);
	glRasterPos2i(x + 1, y + 1);

	glPushAttrib(GL_LIST_BIT);
	glListBase(CMyWindow::base);
	glCallLists(strlen(Temp), GL_UNSIGNED_BYTE, Temp);
	glPopAttrib();

	glColor4f(color.r, color.g, color.b, color.a);
	glRasterPos2i(x, y);

	glPushAttrib(GL_LIST_BIT);
	glListBase(CMyWindow::base);
	glCallLists(strlen(Temp), GL_UNSIGNED_BYTE, Temp);
	glPopAttrib();
}

void CDrawings::ShadowCenterText(const wchar_t *text, int x, int y, Color color)
{

	if (text == NULL)
		return;

	char Temp[64];
	wcstombs(Temp, text, 64);

	int Len = strlen(Temp);

	//y += CMyWindow::tm.tmHeight/2;

	int stringWidth = 0;
	for (int j = 0; j < Len; ++j)
		stringWidth += CMyWindow::glyphInfo[Temp[j]].abcA + CMyWindow::glyphInfo[Temp[j]].abcB + CMyWindow::glyphInfo[Temp[j]].abcC;

	glColor4f(0, 0, 0, 255);
	glRasterPos2i(x - stringWidth / 2 + 1, y + 1);

	glPushAttrib(GL_LIST_BIT);
	glListBase(CMyWindow::base);
	glCallLists(strlen(Temp), GL_UNSIGNED_BYTE, Temp);
	glPopAttrib();

	glColor4f(color.r, color.g, color.b, color.a);
	glRasterPos2i(x - stringWidth / 2, y);
	glPushAttrib(GL_LIST_BIT);
	glListBase(CMyWindow::base);
	glCallLists(Len, GL_UNSIGNED_BYTE, Temp);
	glPopAttrib();
}