#pragma once
#include "Globals.h"

class Color
{
public:
	Color(){};
	Color(float a, float r, float g, float b) : a(a), r(r), g(g), b(b){};
	float a;
	float r;
	float g;
	float b;
};

extern Color Red;
extern Color Green;
extern Color Blue;
extern Color Black;
extern Color White;
extern Color Aqua;
extern Color Yellow;
extern Color Pink;


class CDrawings
{
public:
	//GLuint	base;
	void Line(float x1, float y1, float x2, float y2, float Width, Color color);
	
	void Box(float x, float y, float width, float height, float Width, Color color);
	void Box(RECT Pos, float Width, Color color);

	void BorderdBox(float x, float y, float width, float height, float Width, float BorderWidth, Color color, Color BorderColor);
	void BorderdBox(RECT Pos, float Width, float BorderWidth, Color color, Color BorderColor);

	void FilledBox(float x, float y, float width, float height, Color color);
	void FilledBox(RECT Pos, Color color);

	void GuiBox(float x, float y, float width, float height, Color color, Color BorderColor);
	void GuiBox(RECT Pos, Color color, Color BorderColor);

	void Circle(float cx, float cy, float r, int num_segments, Color color);
	void FilledCircle(float cx, float cy, float r, int num_segments, Color color);

	void Text(const char *text, int x, int y, Color color);
	void CenterText(const char *text, int x, int y, Color color);

	void Text(const wchar_t *text, int x, int y, Color color);
	void CenterText(const wchar_t *text, int x, int y, Color color);

	void ShadowText(const char *text, int x, int y, Color color);
	void ShadowCenterText(const char *text, int x, int y, Color color);

	void ShadowText(const wchar_t *text, int x, int y, Color color);
	void ShadowCenterText(const wchar_t *text, int x, int y, Color color);

	CDrawings();
	~CDrawings();
};

extern CDrawings* Drawings;