#include "Radar.h"
#include "MyWindow.h"
#include "Entity.h"

const double PI = 3.14;
CRadar* Radar = new CRadar;

bool CRadar::Active = false;
float CRadar::x = CMyWindow::CenterX;
float CRadar::y = CMyWindow::CenterY;
float CRadar::Width = 100;
float CRadar::Height = 100;
float CRadar::Size = 50;
float CRadar::Range = 30;

float CRadar::BaseX = 0;
float CRadar::BaseY = 0;
float CRadar::Angle = 0;
float CRadar::RealRange = 0;

Color CRadar::FillColor = Color((float)120/(float)255, 0, (float)28/255, 0);
Color CRadar::LinesColor = Color(255, 255, 255, 255);
Color CRadar::AllyColor = Color(255, 0, 0, 255);
Color CRadar::EnemyColor = Color(255, 255, 0, 0);
Color CRadar::MyColor = Color(255, 255, 255, 255);
//SwapLines0
CRadar::CRadar()
{
}

CRadar::~CRadar()
{
}

void CRadar::Update()
{
	if (GetAsyncKeyState(VK_UP))
		y--;
	if (GetAsyncKeyState(VK_DOWN))
		y++;
	if (GetAsyncKeyState(VK_LEFT))
		x--;
	if (GetAsyncKeyState(VK_RIGHT))
		x++;
	Width = Height = Size * 2;
	RealRange = Size / 2 * Range;
}

void CRadar::Draw()
{
	if (!Active)
		return;
	Drawings->FilledBox(x, y, Width, Height, FillColor);
	Drawings->Line(x + Width / 2, y + Height / 2, x, y, 1, LinesColor);
	Drawings->Line(x + Width / 2, y + Height / 2, x + Width, y, 1, LinesColor);

}

void CRadar::DrawEntity(int Index)
{
	if (!Active)
		return;

	BaseX = Entity[Index].Position.x - LocalPlayer->Position.x;
	BaseY = Entity[Index].Position.y - LocalPlayer->Position.y;
	Angle = LocalPlayer->ViewAngle;


	float yaw = (Angle)* (3.14159265358979323846 / 180.0);
	float mainViewAngles_CosYaw = cos(yaw);


	float mainViewAngles_SinYaw = sin(yaw);
	float OnRadarX = BaseY*(-mainViewAngles_CosYaw) + BaseX*mainViewAngles_SinYaw;
	float OnRadarY = BaseX*(-mainViewAngles_CosYaw) - BaseY*mainViewAngles_SinYaw;

	if (fabs(OnRadarX)>RealRange || fabs(OnRadarY) > RealRange)
	{
		if (OnRadarY > OnRadarX)
		{
			if (OnRadarY > -OnRadarX) {
				OnRadarX = RealRange*OnRadarX / OnRadarY;
				OnRadarY = RealRange;
			}
			else  {
				OnRadarY = -RealRange*OnRadarY / OnRadarX;
				OnRadarX = -RealRange;
			}
		}
		else {
			if (OnRadarY > -OnRadarX) {
				OnRadarY = RealRange*OnRadarY / OnRadarX;
				OnRadarX = RealRange;
			}
			else  {
				OnRadarX = -RealRange*OnRadarX / OnRadarY;
				OnRadarY = -RealRange;
			}
		}
	}

	int ScreenX = x + Width / 2 + int(OnRadarX / RealRange*Size);
	int ScreenY = y + Height / 2 + int(OnRadarY / RealRange*Size);

	if (Entity[Index].Team != LocalPlayer->Team)
		Drawings->Line(ScreenX, ScreenY - 1, ScreenX, ScreenY + 1, 2, EnemyColor);
	else
		Drawings->Line(ScreenX, ScreenY - 1, ScreenX, ScreenY + 1, 2, AllyColor);

}

