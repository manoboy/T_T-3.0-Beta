#include "Entity.h"
#include "Process.h"
#include "MyWindow.h"
CLocalPlayer* LocalPlayer = new CLocalPlayer;
CEntity* Entity = new CEntity[64];

CEntity::CEntity()
{
}


CEntity::~CEntity()
{
}



CLocalPlayer::CLocalPlayer()
{
}


CLocalPlayer::~CLocalPlayer()
{
}


Vector3D CEntity::GetBone(int iBone)
{
	if (!Valid)
		return Vector3D(0, 0, 0);

	Vector3D TempBone;
	TempBone.x = Process->ReadMemory<float>(BoneAddress + 0x30 * iBone + 0x0C);
	TempBone.y = Process->ReadMemory<float>(BoneAddress + 0x30 * iBone + 0x1C);
	TempBone.z = Process->ReadMemory<float>(BoneAddress + 0x30 * iBone + 0x2C);
	return TempBone;
}

Vector3D CEntity::GetBoneFast(int iBone)
{
	// Bone Matrix must be updated
	if (!Valid)
		return Vector3D(0, 0, 0);
	Vector3D TempBone;
	TempBone.x = BonesMatix[iBone].Matrix[0][3];
	TempBone.y = BonesMatix[iBone].Matrix[1][3];
	TempBone.z = BonesMatix[iBone].Matrix[2][3];
	return TempBone;
}

void CEntity::ReadBone(int iBone)
{
	if (!Valid)
		return;

	Bone[iBone].PositionInGame.x = Process->ReadMemory<float>(BoneAddress + 0x30 * iBone + 0x0C);
	Bone[iBone].PositionInGame.y = Process->ReadMemory<float>(BoneAddress + 0x30 * iBone + 0x1C);
	Bone[iBone].PositionInGame.z = Process->ReadMemory<float>(BoneAddress + 0x30 * iBone + 0x2C);
	Bone[iBone].IsOnScreen = WorldToScreen(Bone[iBone].PositionInGame, Bone[iBone].PositionOnScreen);
}
void CEntity::ReadBoneFromMatrix(int iBone)
{
	if (!Valid)
		return;

	Bone[iBone].PositionInGame.x = BonesMatix[iBone].Matrix[0][3];
	Bone[iBone].PositionInGame.y = BonesMatix[iBone].Matrix[1][3];
	Bone[iBone].PositionInGame.z = BonesMatix[iBone].Matrix[2][3];
	Bone[iBone].IsOnScreen = WorldToScreen(Bone[iBone].PositionInGame, Bone[iBone].PositionOnScreen);
}


BoneMatrix CEntity::GetBoneMatrix(int iBone)
{
	BoneMatrix TempBone;
	if (!Valid)
		return TempBone;

	TempBone = Process->ReadMemory<BoneMatrix>(BoneAddress + 0x30 * iBone);
	return TempBone;
}

void CEntity::ReadBonesMatrix()
{
	if (!Valid)
		return;

	ReadProcessMemory(Process->hProcess, (LPCVOID)(BoneAddress), &BonesMatix, sizeof(BonesMatix), NULL);
}


void CEntity::Read(int Index)
{
	Address = Process->ReadMemory<DWORD>(GlobalVariables::ClientAddress + Offsets::EntityList + (Index * 0x10));
	if (Address == NULL)
	{
		Valid = false;
		return;
	}
	Health = Process->ReadMemory<int>(Address + 0xFC);
	if (Health <= 0)
	{
		Valid = false;
		return;
	}
	LifeState = Process->ReadMemory<BYTE>(Address + 0x25B);
	if (LifeState != 0)
	{
		Valid = false;
		return;
	}
	Team = Process->ReadMemory<int>(Address + 0xF0);


	Valid = true;

	Position = Process->ReadMemory<Vector3D>(Address + 0x134);
	weaponHandle = Process->ReadMemory<DWORD>(Address + 0x12C0);
	weaponIDFirst = weaponHandle & 0xFFF;
	WeaponAddress = Process->ReadMemory<DWORD>(GlobalVariables::ClientAddress + Offsets::EntityList + ((weaponIDFirst - 1) * 0x10));
	WeaponID = Process->ReadMemory<int>(WeaponAddress + 0x0000168c);
	Clip1 = Process->ReadMemory<int>(WeaponAddress + 0x000015c0);
	//Clip2 = Process->ReadMemory<int>(WeaponAddress + 0x000015c4);
	ShotsFired = Process->ReadMemory<int>(Address + 0x00001d60);
	IsLocalPlayer = Process->ReadMemory<bool>(Address + 0x19c0);
	if (IsLocalPlayer)
	{
		Valid = false;
		LocalPlayer->weaponHandle = weaponHandle;
		LocalPlayer->weaponIDFirst = weaponIDFirst;
		LocalPlayer->WeaponAddress = WeaponAddress;
		LocalPlayer->WeaponID = WeaponID;
		LocalPlayer->Clip1 = Clip1;
		LocalPlayer->Clip2 = Clip2;
		LocalPlayer->ShotsFired = ShotsFired;
		return;
	}
	
	IsOnScreen = WorldToScreen(Position, PosOnScreen);
	PseudoHeadPosInGame = Vector3D{ Position.x, Position.y, Position.z + 70.0f };
	PseudoHeadIsOnScreen = WorldToScreen(PseudoHeadPosInGame, PseudoHeadPosOnScreen);
	if (!IsOnScreen && !PseudoHeadIsOnScreen && !IsLocalPlayer)
	{
		return;
	}
	Spotted = Process->ReadMemory<bool>(Address + 0x935);
	BoneAddress = Process->ReadMemory<DWORD>(Address + 0xA78);
	//MoveSpeed = Process->ReadMemory<float>(Address + 0xAD0);
	flags = Process->ReadMemory<int>(Address + 0x100);
	Velocity = Process->ReadMemory<Vector3D>(Address + 0x110);

	BoxHeight = PosOnScreen.y - PseudoHeadPosOnScreen.y;
	BoxWidth = BoxHeight*0.35;

	Box.left = PosOnScreen.x - BoxWidth/2;
	Box.top = PseudoHeadPosOnScreen.y;
	Box.right = PosOnScreen.x + BoxWidth/2;
	Box.bottom = PosOnScreen.y;


	Distance = Get3dDistance(Position, LocalPlayer->Position);

	if (BoneAddress != NULL)
	{
		ValidBones = true;
		ReadBonesMatrix();
		ReadBoneFromMatrix(10);
		ReadBoneFromMatrix(5);
		ReadBoneFromMatrix(4);
		ReadBoneFromMatrix(2);
		if (Get3dDistance(Position, Bone[2].PositionInGame) > 100)
			ValidBones = false;
	}
}

void CLocalPlayer::Read()
{
	Address = Process->ReadMemory<DWORD>(GlobalVariables::ClientAddress + Offsets::LocalPlayer);
	if (Address)
	{
		Team = Process->ReadMemory<int>(Address + 0xF0);
		Health = Process->ReadMemory<int>(Address + 0xFC);
		Falling = Process->ReadMemory<int>(Address + 0x100);
		Punch = Process->ReadMemory<Vector3D>(Address + 0x000013e8);
		ViewAngle = Process->ReadMemory<float>(Address + 0x1590);
		Fov = Process->ReadMemory<int>(Address + 0x159C);
		vViewAngle = Process->ReadMemory<Vector3D>(Address + 0x158C);
		//CrossHairID = Process->ReadMemory<int>(Address + 0x00002400);
		PositionOnScreen = Vector3D(CMyWindow::Width / 2, CMyWindow::Height, 0);
		EyePos = Process->ReadMemory<Vector3D>(Address + 0x104);
		Position = Process->ReadMemory<Vector3D>(Address + 0x134);
		LifeState = Process->ReadMemory<BYTE>(Address + 0x25B);
		EyePos += Position;
	}
	else
	{
		Team = 0;
		Health = 0;
		Falling = 0;
		Punch = Vector3D(0,0,0);
		ViewAngle = 0;
		Fov = 0;
		vViewAngle = Vector3D(0, 0, 0);
		CrossHairID = 0;
		PositionOnScreen = Vector3D(0, 0, 0);
		EyePos = Vector3D(0, 0, 0);
		Position = Vector3D(0, 0, 0);
		LifeState = 0;
		EyePos += Vector3D(0, 0, 0);
	}
}
Vector3D CLocalPlayer::ReadPunch()
{
	if (Address)
	{
		return Process->ReadMemory<Vector3D>(Address + 0x000013e8);
	}

	return Vector3D(0, 0, 0);
}