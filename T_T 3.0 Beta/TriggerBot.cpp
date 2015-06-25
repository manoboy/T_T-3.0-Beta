#include "TriggerBot.h"
#include "Process.h"
#include "Entity.h"

CTriggerBot TriggerBot;

CTriggerBot::CTriggerBot()
{
}


CTriggerBot::~CTriggerBot()
{
}
bool CTriggerBot::Active = false;
bool CTriggerBot::OnHotKey = false;
bool CTriggerBot::ShootOnHitBox = false;
bool CTriggerBot::Shoot = false;
bool CTriggerBot::SniperMode = false;

float CTriggerBot::MaxPunch = 2;
int CTriggerBot::HotKey = 2;
int CTriggerBot::SleepTime = 2;
int CTriggerBot::DelayTime = 0;
int CTriggerBot::ShootingTime = 0;;
int CTriggerBot::BreakTime = 0;;

int CTriggerBot::Target = -1;
int CTriggerBot::LastTarget = -69;

int CTriggerBot::ExtraShootingTime = 0;
clock_t CTriggerBot::LastExtraShootingTime = 0;

clock_t CTriggerBot::LastTimeTargetUnderCrosshair = 0;

Bones Bone;
//SwapLines0
void CTriggerBot::ShootOnLoseTarget()
{
	if (Shoot && LastTimeTargetUnderCrosshair + ExtraShootingTime > clock())
	{
		MouseButton(MOUSEEVENTF_LEFTDOWN);
		Sleep(ShootingTime);
		MouseButton(MOUSEEVENTF_LEFTUP);
		Sleep(BreakTime);
	}
	else
	{
		Shoot = false;
	}
};


DWORD WINAPI CTriggerBot::Run()
{
	while (true)
	{
		Sleep(SleepTime);
		if (!Active)
			continue;

		if (OnHotKey)
		{
			if (!GetAsyncKeyState(HotKey))
				continue;
		}
		else
		{
			if (GetAsyncKeyState(0x1))
				continue;
		}

		if (LocalPlayer->Clip1 <= 0)
			continue;

		Target = Process->ReadMemory<int>(LocalPlayer->Address + 0x00002400) - 1;

		if (Target < 0)
		{
			LastTarget = -69;
			ShootOnLoseTarget();
			continue;
		}
		if (Target > GlobalVariables::MaxPlayers)
		{
			LastTarget = -69;
			ShootOnLoseTarget();
			continue;
		}

		if (Entity[Target].Team == LocalPlayer->Team)
		{
			LastTarget = -69;
			continue;
		}

		if (LocalPlayer->Punch.x >= MaxPunch || LocalPlayer->Punch.y >= MaxPunch)
			continue;

		if (LocalPlayer->Punch.x <= -MaxPunch || LocalPlayer->Punch.y <= -MaxPunch)
			continue;

		if (SniperMode)
		{
			if (LocalPlayer->WeaponID == 9 || LocalPlayer->WeaponID == 38 || LocalPlayer->WeaponID == 11 || LocalPlayer->WeaponID == 40)
			{
				if (LocalPlayer->Fov == 90)
					continue;
			}
		}

		if (ShootOnHitBox)
		{
			Vector3D Bone = Entity[Target].GetBoneFast(10);
			Vector3D BottomHitboxHead = Bone;
			BottomHitboxHead.x += -2.771300f;
			BottomHitboxHead.y += -2.878300f;
			BottomHitboxHead.z += -3.103000f;

			Vector3D TopHitboxHead = Bone;
			TopHitboxHead.x += 6.955000f;
			TopHitboxHead.y += 4.020300f;
			TopHitboxHead.z += 5.006700f;

			Vector3D ViewDirection = AngleToDirection(LocalPlayer->vViewAngle);
			if (!RayTrace->Trace(ViewDirection, BottomHitboxHead, TopHitboxHead))
				continue;
		}

		Sleep(DelayTime);

		MouseButton(MOUSEEVENTF_LEFTDOWN);
		Sleep(ShootingTime);
		MouseButton(MOUSEEVENTF_LEFTUP);

		Sleep(BreakTime);

		Shoot = true;

		LastTarget = Target;
		LastTimeTargetUnderCrosshair = clock();

	}
}