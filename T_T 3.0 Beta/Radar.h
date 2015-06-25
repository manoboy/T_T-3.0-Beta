#pragma once
#include "Globals.h"
#include "Math.h"
#include "Drawings.h"

class CRadar
{
public:
	static bool Active;

	static float x;
	static float y;
	static float Width;
	static float Height;
	static float Size;
	static float Range;

	static Color FillColor;
	static Color LinesColor;
	static Color AllyColor;
	static Color EnemyColor;
	static Color MyColor;

	static float BaseX;
	static float BaseY;
	static float Angle;
	static float RealRange;

	void Update();

	void Draw();
	void DrawEntity(int Index);

	CRadar();
	~CRadar();
};
extern CRadar* Radar;