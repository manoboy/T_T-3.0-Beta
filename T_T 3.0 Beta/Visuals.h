#pragma once
#include "Globals.h"
#include "Drawings.h"

extern char *WeaponName[52];
extern char *RecoilDrawTypes[2];
class CVisuals
{
public:
	CVisuals();
	~CVisuals();

	float WearingWeponPosX;
	float WearingWeponPosY;
	float DistancePosX;
	float DistancePosY;
	float HealthPosX;
	float HealthPosY;
	float LastTextXPos;
	float LastTextYPos;
	void InitPosiitons();

	static float RecoilDrawResolution;
	static int RecoilDrawType;

	void Render();

	void DrawFovAimbot();
	void DrawCrosshair();
	void DrawRecoilCrosshair();

	void DrawESP(int PlayerIndex, Color color);
	void DrawHealth(int PlayerIndex);
	void DrawSnapLine(int PlayerIndex, Color color);
	void DrawHead(int PlayerIndex, Color color);
	void DrawBones(int PlayerIndex, Color color);
	void DrawBone(int Start, int End, int PlayerIndex, Color color);
	void DrawDistance(int Index);
	void DrawWeapon(int Index);
	void DrawName(int Index);


	void DrawBomb();
	void DrawDropedWeapons();

	bool bDrawCrosshair;
	bool bDrawRecoilCrosshair;
	bool bDrawESP;
	bool bDrawHealth;
	bool bDrawSnapLine;
	bool bDrawHead;
	bool bDrawBones;
	bool bDrawBone;
	bool bDrawDistance;
	bool bDrawWeapon;
	bool bDrawName;
	bool bDrawAlly;
	bool bDrawBomb;
	bool bDrawGranades;
	bool bDrawDropedWeapons;

	static Color EnemyBoxColor;
	static Color AllyBoxColor;
	static Color HealthTextColor;
	static Color DistanceTextColor;
	static Color WeaponTextColor;
	static Color NameTextColor;

	static Color CrosshairColor;
	static Color RecoilCircleColor;

	static Color BombBoxColor;
	static Color BombTextColor;

	static Color WeaponDropedBoxColor;
	static Color WeaponDropedTextColor;

	int WeaponsCount;


};
extern CVisuals* Visuals;

