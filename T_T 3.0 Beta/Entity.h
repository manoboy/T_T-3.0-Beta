#pragma once
#include "Globals.h"
#include "Math.h"
class CEntity
{
public:

	DWORD Address;
	DWORD BoneAddress;
	BYTE LifeState;

	Vector3D Position;
	Vector3D Velocity;

	int flags;
	int Team;
	int Health;

	bool IsLocalPlayer;
	
	bool Valid;
	bool ValidBones;

	bool Skip;
	bool Spotted;

	float MoveSpeed;

	Bones Bone[30];
	BoneMatrix BonesMatix[30];
	bool IsOnScreen;
	Vector3D PosOnScreen;
	bool PseudoHeadIsOnScreen;
	Vector3D PseudoHeadPosInGame;
	Vector3D PseudoHeadPosOnScreen;

	wchar_t Name[32];

	float Distance;

	clock_t LastReadWeapons;
	int ReadEvry;
	DWORD weaponHandle;
	DWORD weaponIDFirst;
	DWORD WeaponAddress;
	int WeaponID;
	int Clip1;
	int Clip2;
	int ShotsFired;

	int BoxWidth;
	int BoxHeight;
	RECT Box;
	RECT NamePos;
	RECT WeaponNamePos;
	RECT HealthPos;
	RECT DistancePos;

	void Read(int Index);

	void ReadBone(int iBone);
	void ReadBoneFromMatrix(int iBone);
	Vector3D GetBone(int iBone);
	Vector3D GetBoneFast(int iBone);

	void ReadBonesMatrix();
	BoneMatrix GetBoneMatrix(int iBone);

	CEntity();
	~CEntity();
};

class CLocalPlayer
{
public:
	DWORD Address;

	BYTE LifeState;

	int Team;
	int Health;
	int Falling;
	int CrossHairID;
	int Fov;
	DWORD SetAnglesAddress;
	float ViewAngle;

	Vector3D Position;
	Vector3D EyePos;
	Vector3D PositionOnScreen;
	Vector3D vViewAngle;
	Vector3D Punch;

	DWORD weaponHandle;
	DWORD weaponIDFirst;
	DWORD WeaponAddress;
	int WeaponID;
	int Clip1;
	int Clip2;
	int ShotsFired;

	CLocalPlayer();
	~CLocalPlayer();

	void Read();

	Vector3D ReadPunch();
};

extern CLocalPlayer* LocalPlayer;
extern CEntity* Entity;


