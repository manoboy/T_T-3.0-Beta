#include "Visuals.h"
#include "Entity.h"
#include "RecoilControl.h"
#include "MyWindow.h"
#include "AimBot.h"
#include "Process.h"
#include "Radar.h"
#include"ObjectManager.h"

CVisuals* Visuals = new CVisuals;

Color CVisuals::EnemyBoxColor = Color((float)255 / (float)255, (float)255 / (float)255, (float)0 / (float)255, (float)0 / (float)255);
Color CVisuals::AllyBoxColor = Color(255 / 255, 0 / 255, 0 / 255, 255 / 255);

Color CVisuals::HealthTextColor = Color((float)255 / (float)255, (float)0 / (float)255, (float)255 / (float)255, (float)0 / (float)255);
Color CVisuals::DistanceTextColor = Color(255 / 255, 255 / 255, 255 / 255, 0 / 255);
Color CVisuals::WeaponTextColor = Color(255 / 255, 255 / 255, 255 / 255, 0 / 255);
Color CVisuals::NameTextColor = Color(255 / 255, 255 / 255, 255 / 255, 0 / 255);

Color CVisuals::BombBoxColor = Color(255 / 255, 255 / 255, (float)125 / (float)255, 0 / 255);
Color CVisuals::BombTextColor = Color(255 / 255, 255 / 255, 255 / 255, 255 / 255);

Color CVisuals::WeaponDropedBoxColor = Color(255 / 255, 255 / 255, (float)125 / (float)255, 0 / 255);
Color CVisuals::WeaponDropedTextColor = Color(255 / 255, 255 / 255, 255 / 255, 255 / 255);

Color CVisuals::CrosshairColor = Color(255 / 255, 0 / 255, 255 / 255, 255 / 255);
Color CVisuals::RecoilCircleColor = Color(255 / 255, 255 / 255, 0 / 255, 255 / 255);
float CVisuals::RecoilDrawResolution = 6.0f;
int CVisuals::RecoilDrawType = 0;

CVisuals::CVisuals()
{
	LastTextXPos = DistancePosX = 3;
	LastTextYPos = DistancePosY = CMyWindow::FontSpacing;
	LastTextXPos = WearingWeponPosX = 3;
	LastTextYPos = WearingWeponPosY = LastTextYPos + CMyWindow::FontSpacing;
	HealthPosX = 0;
	HealthPosY = CMyWindow::FontSpacing;

	bDrawCrosshair = false;
	bDrawRecoilCrosshair = false;
	bDrawESP = false;
	bDrawHealth = false;
	bDrawSnapLine = false;
	bDrawHead = false;
	bDrawBones = false;
	bDrawBone = false;
	bDrawDistance = false;
	bDrawWeapon = false;
	bDrawName = false;
	bDrawAlly = false;
	bDrawBomb = false;
	bDrawGranades = false;
	bDrawDropedWeapons = false;
}


CVisuals::~CVisuals()
{
}

void CVisuals::InitPosiitons()
{
	LastTextXPos = DistancePosX = 3;
	LastTextYPos = DistancePosY = CMyWindow::FontSpacing;
	LastTextXPos = WearingWeponPosX = 3;
	LastTextYPos = WearingWeponPosY = LastTextYPos + CMyWindow::FontSpacing;
	HealthPosX = 0;
	HealthPosY = CMyWindow::FontSpacing;
}

void CVisuals::Render()
{
	if (CRadar::Active)
		Radar->Draw();

	for (int i = 0; i < GlobalVariables::MaxPlayers; i++)
	{
		if (!Entity[i].Valid)
			continue;

		Radar->DrawEntity(i);

		if (!Entity[i].IsOnScreen)
			continue;


		if (Entity[i].Team != LocalPlayer->Team)
		{
			if (bDrawESP)
				DrawESP(i, Red);
			if (bDrawHealth)
				DrawHealth(i);
			if (bDrawSnapLine)
				DrawSnapLine(i, Red);
			if (bDrawHead)
				DrawHead(i, White);
			if (bDrawBones)
				DrawBones(i, White);
			if (bDrawDistance)
				DrawDistance(i);
			if (bDrawWeapon)
				DrawWeapon(i);
			if (bDrawName)
				DrawName(i);
		}
		else
		{
			if (!bDrawAlly)
				continue;

			if (bDrawESP)
				DrawESP(i, Blue);
			if (bDrawHealth)
				DrawHealth(i);
			if (bDrawSnapLine)
				DrawSnapLine(i, Blue);
			if (bDrawHead)
				DrawHead(i, White);
			if (bDrawBones)
				DrawBones(i, White);
			if (bDrawDistance)
				DrawDistance(i);
			if (bDrawWeapon)
				DrawWeapon(i);
			if (bDrawName)
				DrawName(i);
		}



	}

	if (bDrawCrosshair)
		DrawCrosshair();

	if (bDrawRecoilCrosshair)
		DrawRecoilCrosshair();

	if (CAimBot::DrawFOV && CAimBot::Active)
		DrawFovAimbot();

	//ObjectManager->ReadObjects();

	if (bDrawBomb)
		DrawBomb();

	if (bDrawDropedWeapons)
		DrawDropedWeapons();
}

void CVisuals::DrawFovAimbot()
{
	Drawings->FilledCircle(CMyWindow::CenterX, CMyWindow::CenterY, CAimBot::Radius, 20, CAimBot::FovColor);
}

void CVisuals::DrawCrosshair()
{
	Drawings->FilledBox(CMyWindow::CenterX + 2, CMyWindow::CenterY - 1, 6, 3, CrosshairColor);
	Drawings->FilledBox(CMyWindow::CenterX - 1, CMyWindow::CenterY + 3, 2, 6, CrosshairColor);

	Drawings->FilledBox(CMyWindow::CenterX - 8, CMyWindow::CenterY - 1, 6, 3, CrosshairColor);
	Drawings->FilledBox(CMyWindow::CenterX - 1, CMyWindow::CenterY - 8, 2, 6, CrosshairColor);
}

void CVisuals::DrawRecoilCrosshair()
{
	Vector3D Punch = LocalPlayer->ReadPunch();
	float Punch2ScreenX = (CMyWindow::Width / 358.f) * (Punch.x * 2);
	float Punch2ScreenY = (CMyWindow::Height / 178.f) * (Punch.y * 2);

	switch (RecoilDrawType)
	{
	case 0:
		Drawings->Circle(CMyWindow::CenterX - Punch2ScreenY, CMyWindow::CenterY + Punch2ScreenX, RecoilDrawResolution, 10, RecoilCircleColor);
		break;
	case 1:
		Drawings->FilledBox(CMyWindow::CenterX - Punch2ScreenY + 2, CMyWindow::CenterY + Punch2ScreenX - 1, 6, 3, RecoilCircleColor);
		Drawings->FilledBox(CMyWindow::CenterX - Punch2ScreenY - 1, CMyWindow::CenterY + Punch2ScreenX + 3, 2, 6, RecoilCircleColor);

		Drawings->FilledBox(CMyWindow::CenterX - Punch2ScreenY - 8, CMyWindow::CenterY + Punch2ScreenX - 1, 6, 3, RecoilCircleColor);
		Drawings->FilledBox(CMyWindow::CenterX - Punch2ScreenY - 1, CMyWindow::CenterY + Punch2ScreenX - 8, 2, 6, RecoilCircleColor);
		break;
	}
	
}

void CVisuals::DrawESP(int PlayerIndex, Color Color)
{
	if (Entity[PlayerIndex].IsOnScreen)
	{
		if (Entity[PlayerIndex].PseudoHeadIsOnScreen)
		{
			Drawings->Box(Entity[PlayerIndex].Box.left, Entity[PlayerIndex].Box.top, Entity[PlayerIndex].BoxWidth, Entity[PlayerIndex].BoxHeight, 2, Color);
		}
	}
}

void CVisuals::DrawHealth(int PlayerIndex)
{
	if (Entity[PlayerIndex].IsOnScreen)
	{
		char Buf[10];
		sprintf(Buf, "%d", Entity[PlayerIndex].Health);
		Drawings->ShadowCenterText(Buf, Entity[PlayerIndex].PosOnScreen.x, Entity[PlayerIndex].PosOnScreen.y + HealthPosY, HealthTextColor);
	}
}

void CVisuals::DrawSnapLine(int PlayerIndex, Color Color)
{
	Drawings->Line(LocalPlayer->PositionOnScreen.x, LocalPlayer->PositionOnScreen.y, Entity[PlayerIndex].PosOnScreen.x, Entity[PlayerIndex].PosOnScreen.y, 1, Color);
}

void CVisuals::DrawHead(int PlayerIndex, Color color)
{
	if (Entity[PlayerIndex].ValidBones == false)
		return;

	Vector3D HeadPosTop;
	Vector3D HeadPosBot;

	Vector3D HeadTop = Entity[PlayerIndex].Bone[10].PositionInGame;
	Vector3D HeadBot = Entity[PlayerIndex].Bone[10].PositionInGame;
	HeadBot.z -= 2;
	HeadTop.z += 7;
	int BoneWidth;
	int BoneHeight;
	if (WorldToScreen(HeadBot, HeadPosBot) && WorldToScreen(HeadTop, HeadPosTop))
	{
		BoneWidth = BoneHeight = HeadPosBot.y - HeadPosTop.y;
		Drawings->Box(HeadPosTop.x - BoneWidth / 2, HeadPosTop.y, BoneWidth, BoneHeight, 2, color);
	}
}

void CVisuals::DrawBones(int PlayerIndex, Color Color)
{
	if (Entity[PlayerIndex].ValidBones == false)
		return;

	Entity[PlayerIndex].ReadBoneFromMatrix(0);
	Entity[PlayerIndex].ReadBoneFromMatrix(7);
	Entity[PlayerIndex].ReadBoneFromMatrix(8);
	Entity[PlayerIndex].ReadBoneFromMatrix(13);
	Entity[PlayerIndex].ReadBoneFromMatrix(14);
	Entity[PlayerIndex].ReadBoneFromMatrix(15);
	Entity[PlayerIndex].ReadBoneFromMatrix(21);
	Entity[PlayerIndex].ReadBoneFromMatrix(24);
	Entity[PlayerIndex].ReadBoneFromMatrix(25);
	Entity[PlayerIndex].ReadBoneFromMatrix(27);
	Entity[PlayerIndex].ReadBoneFromMatrix(28);

	DrawBone(0, 5, PlayerIndex, Color);

	DrawBone(5, 13, PlayerIndex, Color);
	DrawBone(13, 14, PlayerIndex, Color);
	DrawBone(14, 15, PlayerIndex, Color);

	DrawBone(5, 7, PlayerIndex, Color);
	DrawBone(7, 8, PlayerIndex, Color);
	DrawBone(8, 21, PlayerIndex, Color);

	DrawBone(28, 27, PlayerIndex, Color);
	DrawBone(27, 0, PlayerIndex, Color);

	DrawBone(25, 24, PlayerIndex, Color);
	DrawBone(24, 0, PlayerIndex, Color);
}

void CVisuals::DrawBone(int Start, int End, int PlayerIndex, Color Color)
{

	if (!Entity[PlayerIndex].Bone[Start].IsOnScreen)
		return;

	if (!Entity[PlayerIndex].Bone[End].IsOnScreen)
		return;

	Drawings->Line(Entity[PlayerIndex].Bone[Start].PositionOnScreen.x, Entity[PlayerIndex].Bone[Start].PositionOnScreen.y, Entity[PlayerIndex].Bone[End].PositionOnScreen.x, Entity[PlayerIndex].Bone[End].PositionOnScreen.y, 1, Color);
};


void CVisuals::DrawDistance(int Index)
{
	char Buf[32];
	sprintf(Buf, "%.f", Entity[Index].Distance);
	Drawings->ShadowText(Buf, Entity[Index].Box.right + DistancePosX, Entity[Index].Box.top + DistancePosY, DistanceTextColor);

}

void CVisuals::DrawWeapon(int Index)
{
	if (Entity[Index].WeaponID > 0 && Entity[Index].WeaponID<52)
		Drawings->ShadowText(WeaponName[Entity[Index].WeaponID], Entity[Index].Box.right + WearingWeponPosX, Entity[Index].Box.top + WearingWeponPosY, WeaponTextColor);
}

void CVisuals::DrawName(int Index)

{

	ReadProcessMemory(Process->hProcess, (LPCVOID*)(Offsets::RadarBaseAddress + (0x1E0 * Index) + 0x204), &Entity[Index].Name, sizeof(Entity[Index].Name), 0);
	Drawings->ShadowCenterText(Entity[Index].Name, Entity[Index].PosOnScreen.x, Entity[Index].Box.top - 3, NameTextColor);
}



void CVisuals::DrawBomb()
{
	//if (Bomb.Owner != -1)
	//	return;
	
	Vector3D PositionBot;
	Vector3D PositionTop;
	if (WorldToScreen(Bomb.Position, PositionBot))
	{

		Drawings->Box(PositionBot.x - 10, PositionBot.y - 10, 20, 20, 1, BombBoxColor);
		Drawings->ShadowText(_TempXOR("Bomb"), PositionBot.x, PositionBot.y, BombTextColor);
		//DrawString("Bomb", PositionBot.x - 10, PositionBot.y + 10, D3DCOLOR_ARGB(255, 255, 255, 255), m_pFontSmall);
	}
	
}

void CVisuals::DrawDropedWeapons()
{

	for (int i = 0; i < CWeapon::Count; i++)
	{
		Vector3D PositionBot;
		if (WorldToScreen(Weapon[i].Position, PositionBot))
		{

			Drawings->Box(PositionBot.x - 10, PositionBot.y - 10, 20, 20, 1, WeaponDropedBoxColor);
			Drawings->ShadowText(Weapon[i].Name, PositionBot.x, PositionBot.y, WeaponDropedTextColor);
			//DrawString(Buf, PositionBot.x - 10, PositionBot.y + 10, D3DCOLOR_ARGB(255, 255, 255, 255), m_pFontSmall);
		}
	}
	
}

char *RecoilDrawTypes[2] = { _OnceXOR("Circle"), _OnceXOR("Cross") };

char *WeaponName[52] =
{
	_OnceXOR("0"),
	_OnceXOR("Desert Eagle"),
	_OnceXOR("Dual Berettas"),
	_OnceXOR("Five-SeveN"),
	_OnceXOR("Glock"),
	_OnceXOR("5"),
	_OnceXOR("6"),
	_OnceXOR("AK-47"),
	_OnceXOR("AUG"),
	_OnceXOR("AWP"),
	_OnceXOR("FAMAS"),
	_OnceXOR("G3SG1"),
	_OnceXOR("12"),
	_OnceXOR("Galil AR"),
	_OnceXOR("M249"),
	_OnceXOR("15"),
	_OnceXOR("M4A4"),
	_OnceXOR("MAC-10"),
	_OnceXOR("18"),
	_OnceXOR("P90"),
	_OnceXOR("20"),
	_OnceXOR("21"),
	_OnceXOR("22"),
	_OnceXOR("23"),
	_OnceXOR("UMP-45"),
	_OnceXOR("XM1014"),
	_OnceXOR("PP-Bizon"),
	_OnceXOR("MAG-7"),
	_OnceXOR("Negev"),
	_OnceXOR("Sawed-Off"),
	_OnceXOR("30"),
	_OnceXOR("Zeus x27"),
	_OnceXOR("P2000"),
	_OnceXOR("MP7"),
	_OnceXOR("MP9"),
	_OnceXOR("Nova"),
	_OnceXOR("CZ75-Auto"),
	_OnceXOR("37"),
	_OnceXOR("SCAR-20"),
	_OnceXOR("SG 553"),
	_OnceXOR("SSG 08"),
	_OnceXOR("41"),
	_OnceXOR("Knife"),
	_OnceXOR("Flashbang"),
	_OnceXOR("HE Granade"),
	_OnceXOR("Smoke Granade"),
	_OnceXOR("46"),
	_OnceXOR("Decoy Granade"),
	_OnceXOR("48"),
	_OnceXOR("C4"),
	_OnceXOR("50"),
	_OnceXOR("Tec-9"),
};