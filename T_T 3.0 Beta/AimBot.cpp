#include "AimBot.h"
#include "Process.h"
#include "Entity.h"
#include "MyWindow.h"
CAimBot* AimBot = new CAimBot;
//char *AimBonesNames[4] = { "Head", "Neck", "Chest", "Stomach"};
//_OnceXOR("Head"), _OnceXOR("Neck"), _OnceXOR("Chest"), _OnceXOR("Stomach")
CAimBot::CAimBot()
{
}


CAimBot::~CAimBot()
{
}


int CAimBot::AimBonesTable[4] = { 10, 5, 4, 2 };

int CAimBot::SleepTime = 10;
int CAimBot::HotKey = 0x06;//0x2;
int CAimBot::FOV = 5;//15;
int CAimBot::TargetID = -1;
int CAimBot::LastTarget = -1;
int CAimBot::PredictMovment = 17;
int CAimBot::AimBoneID = 10;
int CAimBot::AimBoneIndex = 0;

Bones CAimBot::AimBone;
float CAimBot::DistanceFromCrosshair = 99999;
float CAimBot::Distance = 99999;
float CAimBot::ClosestDistance = 99999;
float CAimBot::m_Ingamesensitivity = 2.0;
float CAimBot::RadiusX = 0;
float CAimBot::RadiusY = 0;
float CAimBot::Radius = 0;
float CAimBot::m_XMultiplayer = 2.0;
float CAimBot::m_YMultiplayer = 2.0;
float CAimBot::BustSpeed = 1.0;
float CAimBot::Pixels = 0;
float CAimBot::Smooth = 1.0;
float CAimBot::StopAimingAtDistance = 0;

float CAimBot::Imprecise = 0;
float CAimBot::ImpreciseX = 0;
float CAimBot::ImpreciseY = 0;
float CAimBot::LastImpreciseX = 0;
float CAimBot::LastImpreciseY = 0;
clock_t CAimBot::flTargetTime;
clock_t CAimBot::LastRandomMove;
float CAimBot::MaxRandTime = 100;
float CAimBot::AdditionalTime = 20;
float CAimBot::RandomMultiplier = 1.5;
float CAimBot::RandomX = 1.5;
float CAimBot::RandomY = 1.5;
bool CAimBot::bRandomMoves = false;
bool CAimBot::StopRandomMovesWhenShooting = true;

bool CAimBot::Active = false;
bool CAimBot::AimOnClosestToPlayer = false;
bool CAimBot::AimOnClosestToCrosshair = true;
bool CAimBot::LockOnTarget = false;
bool CAimBot::DrawFOV = true;//false;
bool CAimBot::bRage = false;//true;
bool CAimBot::DontLockNext = false;
bool CAimBot::FocusOnlySpotted = false;

Vector3D CAimBot::AimPosition;
Vector3D CAimBot::Diffrnce;

clock_t CAimBot::AimbotStartTime = 0;
int CAimBot::StopAimbotAfterXMS = 0;
//bool CAimBot::StopAimbotAfterXMS;



Color CAimBot::FovColor = Color((float)120 / (float)255, (float)0 / (float)255, (float)125 / (float)255, (float)0 / (float)255);


void CAimBot::DropTarget()
{
	TargetID = -1;
	ClosestDistance = Distance = 99999;
	DistanceFromCrosshair = 99999;
}

void CAimBot::GetBestTarget()
{
	//if (TargetID == -1)
	//{
	AimBoneID = AimBonesTable[AimBoneIndex];
	for (int i = 0; i < GlobalVariables::MaxPlayers; i++)
	{
		if (!Entity[i].Valid)
			continue;

		if (!Entity[i].ValidBones)
			continue;

		if (FocusOnlySpotted)
		{
			if (Entity[i].Spotted == false)
				continue;
		}

		if (Entity[i].Team == LocalPlayer->Team)
			continue;
		if (Entity[i].IsLocalPlayer == true)
			continue;

		if (!Entity[i].Bone[AimBoneID].IsOnScreen)
			continue;

		DistanceFromCrosshair = Get3dDistance(Vector3D{ Entity[i].Bone[AimBoneID].PositionOnScreen.x, Entity[i].Bone[AimBoneID].PositionOnScreen.y, 0 }, Vector3D{ (float)(CMyWindow::Width / 2), (float)(CMyWindow::Height / 2), 0 });
		if (AimOnClosestToCrosshair)
			Distance = DistanceFromCrosshair;
		else
			Distance = Entity[i].Distance;

		if (DistanceFromCrosshair <= Radius)
		{
			if (Distance < ClosestDistance)
			{
				ClosestDistance = Distance;
				TargetID = i;
			}
		}

	}
	//}
}

void CAimBot::CheckFov()
{
	/*
	float fov = 0.0f, mag = 0.0f, dot = 0.0f;
	QAngle ang, aim;
	gUtil.calcAngles(source, dest, ang);
	makeVector(angle, aim);
	makeVector(ang, ang);
	mag = sqrt(aim[0] * aim[0] + aim[1] * aim[1] + aim[2] * aim[2]);
	dot = aim[0] * ang[0] + aim[1] * ang[1] + aim[2] * ang[2];
	fov = acos(dot / (mag * mag)) * 57.2957914;
	return fov;
	*/
}

void CAimBot::Rage()
{
	Vector3D TempAimpos = AimPosition;

	TempAimpos.x /= Pixels*(-1.0);
	TempAimpos.y /= Pixels;

	if (TempAimpos.x > 1 || TempAimpos.x < -1)
		AimPosition.x = TempAimpos.x;
	else
		AimPosition.x /= -0.22;

	if (TempAimpos.y > 1 || TempAimpos.y < -1)
		AimPosition.y = TempAimpos.y;
	else
		AimPosition.y /= 0.22;

	if (AimPosition.x > -120 && AimPosition.x  < 120 && AimPosition.y > -120 && AimPosition.y < 120)
	{
		MouseMove(AimPosition.y, AimPosition.x);
	}
}

void CAimBot::Custom()
{
	DistanceFromCrosshair = Get3dDistance(Vector3D{ Entity[TargetID].Bone[AimBoneID].PositionOnScreen.x, Entity[TargetID].Bone[AimBoneID].PositionOnScreen.y, 0 }, Vector3D{ (float)(CMyWindow::Width / 2), (float)(CMyWindow::Height / 2), 0 });
	if (DistanceFromCrosshair  < StopAimingAtDistance)
		return;

	if (AimPosition.x > Smooth)
		AimPosition.x = 0 + Smooth;
	else if (AimPosition.x < -Smooth)
		AimPosition.x = 0 - Smooth;

	if (AimPosition.y > Smooth)
		AimPosition.y = 0 + Smooth;
	else if (AimPosition.y < -Smooth)
		AimPosition.y = 0 - Smooth;

	if (bRandomMoves)
		RandomMoves();

	AimPosition.x /= Pixels*(-1.0);
	AimPosition.y /= Pixels;

	MouseMove(AimPosition.y, AimPosition.x);
}


float randMToN(float M, float N)
{
	return M + (rand() / (RAND_MAX / (N - M)));
}

void CAimBot::RandomMoves()
{
	if (StopRandomMovesWhenShooting)
	{
		if (Process->ReadMemory<int>(GlobalVariables::ClientAddress + Offsets::AttackAddres) == 5)
			return;
	}

	if (LastRandomMove + randMToN(0, MaxRandTime) + AdditionalTime < clock())
	{
		float Deviation1 = randMToN(-RandomMultiplier, RandomMultiplier);
		float Devation2 = randMToN(-RandomX, RandomX);
		float Devation3 = randMToN(-RandomY, RandomY);
		switch (rand() % 2)
		{
		case 0:
			ImpreciseX = Deviation1 * cos(Devation2);
			ImpreciseY = Deviation1 * sin(Devation3);
			break;
		case 1:
			ImpreciseX = Deviation1 * sin(Devation2);
			ImpreciseY = Deviation1 * cos(Devation3);
			break;

		}
		LastRandomMove = clock();
	}

	AimPosition.x += ImpreciseX;
	AimPosition.y += ImpreciseY;

}

/*

clock_t CAimBot::AimbotStartTime;
clock_t CAimBot::StopAimbotAfter;
bool CAimBot::StopAimbotAfterXMS;
*/
DWORD WINAPI CAimBot::Run()
{
	while (!GlobalVariables::ExitCheat)
	{
		Sleep(SleepTime);

		if (!Active)
			continue;

		Radius = FOV *(CMyWindow::Height / 90);

		if (HotKey != 0)
		{
			if (!GetAsyncKeyState(HotKey))
			{
				DropTarget();
				AimbotStartTime = 0;
				continue;
			}
			else if(AimbotStartTime == 0)
			{
				AimbotStartTime = clock();
			}
		}
		
		if (StopAimbotAfterXMS != 0 && AimbotStartTime != 0)
		{
			if (AimbotStartTime + StopAimbotAfterXMS < clock())
			{
				//AimbotStartTime = 0;
				continue;
			}
		}
		

		if (DontLockNext == false)
			DropTarget();


		GetBestTarget();
		if (TargetID < 0 || TargetID > GlobalVariables::MaxPlayers)
			continue;
		if (!Entity[TargetID].Valid)
			continue;

		if (TargetID != -1)
		{
			Vector3D BonePred = Entity[TargetID].Bone[AimBoneID].PositionInGame;
			BonePred.x += Entity[TargetID].Velocity.x / PredictMovment;
			BonePred.y += Entity[TargetID].Velocity.y / PredictMovment;
			BonePred.z += Entity[TargetID].Velocity.z / PredictMovment;

			BonePred.z += 1.5;

			CalcAngle(LocalPlayer->EyePos, BonePred, AimPosition);

			if (AimPosition.x < -360 || AimPosition.x > 360)
				continue;

			if (AimPosition.y < -360 || AimPosition.y > 360)
				continue;
			
			AimPosition.x -= m_XMultiplayer*LocalPlayer->Punch.x;
			AimPosition.y -= m_YMultiplayer*LocalPlayer->Punch.y;
			AimPosition.x = LocalPlayer->vViewAngle.x - AimPosition.x;
			AimPosition.y = LocalPlayer->vViewAngle.y - AimPosition.y;

			if (AimPosition.y < -180.0f)
				AimPosition.y += 360.0f;
			if (AimPosition.y > 180.0f)
				AimPosition.y -= 360.0f;

			if (AimPosition.x < -90.0f)
				AimPosition.x += 180.0f;
			if (AimPosition.x > 90.0f)
				AimPosition.x -= 180.0f;

			m_Ingamesensitivity = Process->ReadMemory<float>(GlobalVariables::ClientAddress + Offsets::SensivityAddress);
			Pixels = ((0.22 * m_Ingamesensitivity * 1) / BustSpeed);

			if (bRage)
				Rage();
			else
				Custom();


		}
	}
	ExitThread(0);
}