#pragma once
#include "Math.h"
#include "Drawings.h"
extern char *AimBonesNames[4];
class CAimBot
{
public:

	static int SleepTime;
	static int HotKey;
	static int TargetID;
	static int LastTarget;
	static int FOV;
	static int PredictMovment;

	static int AimBonesTable[4];
	static int AimBoneID;
	static int AimBoneIndex;

	static clock_t AimbotStartTime;
	static int StopAimbotAfterXMS;
	//static bool StopAimbotAfterXMS;

	static float LastImpreciseY;
	static clock_t flTargetTime;
	static clock_t LastRandomMove;
	static float MaxRandTime;

	static Bones AimBone;
	static float Distance;
	static float DistanceFromCrosshair;
	static float ClosestDistance;
	static float m_Ingamesensitivity;
	static float RadiusX;
	static float RadiusY;
	static float Radius;
	static float m_XMultiplayer;
	static float m_YMultiplayer;
	static float BustSpeed;
	static float Pixels;
	static float Smooth;
	static float StopAimingAtDistance;

	static float Imprecise;
	static float ImpreciseX;
	static float ImpreciseY;
	static float LastImpreciseX;
	static float AdditionalTime;
	static float RandomMultiplier;
	static float RandomX;
	static float RandomY;
	static bool bRandomMoves;
	static bool StopRandomMovesWhenShooting;


	static bool Active;
	static bool IsAiming;
	static bool AimOnClosestToPlayer;
	static bool AimOnClosestToCrosshair;
	static bool LockOnTarget;
	static bool DrawFOV;
	static bool bRage;
	static bool DontLockNext;
	static bool FocusOnlySpotted;


	static Vector3D AimPosition;
	static Vector3D Diffrnce;

	static void GetBestTarget();
	static void DropTarget();
	static void Rage();
	static void Custom();
	static void CheckFov();
	static void RandomMoves();
	static DWORD WINAPI Run();

	static Color FovColor;

	CAimBot();
	~CAimBot();
};
extern CAimBot* AimBot;

