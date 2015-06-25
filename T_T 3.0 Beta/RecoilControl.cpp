#include "RecoilControl.h"
#include "AimBot.h"
#include "Entity.h"
#include "Process.h"
CRecoilControl* RecoilControl = new CRecoilControl;

CRecoilControl::CRecoilControl()
{
}


CRecoilControl::~CRecoilControl()
{
}

bool CRecoilControl::Active = false;
int CRecoilControl::ShootingState = false;
int CRecoilControl::SleepTime = 2;
Vector3D CRecoilControl::vDelta = Vector3D{ 0, 0, 0 };
Vector3D CRecoilControl::vPunch = Vector3D{ 0, 0, 0 };
Vector3D CRecoilControl::vPrevPunch = Vector3D{ 0, 0, 0 };
float CRecoilControl::m_Yaw = 0.022;
float CRecoilControl::m_Ingamesensitivity = 2.0;
float CRecoilControl::m_Windowssensitivity = 1;
float CRecoilControl::m_XMultiplayer = 1.6;
float CRecoilControl::m_YMultiplayer = 1.8;
int CRecoilControl::RecoilDrawType = 0;
float CRecoilControl::RecoilDrawResolution = 4;

int CRecoilControl::HotKey = VK_F4;
clock_t CRecoilControl::LastKeyPress = 0;

DWORD WINAPI CRecoilControl::Run()
{
	while (true)
	{
		Sleep(SleepTime);
		if (CAimBot::Active && (GetAsyncKeyState(CAimBot::HotKey) || CAimBot::HotKey == 0))
			continue;

		if (GetAsyncKeyState(HotKey) && LastKeyPress + 250 < clock())
		{
			Active = !Active;
			LastKeyPress = clock();
		}


		if (Active && LocalPlayer->Address != NULL)
		{
			vPunch = LocalPlayer->ReadPunch();
			ShootingState = Process->ReadMemory<int>(GlobalVariables::ClientAddress + Offsets::AttackAddres);
			if (ShootingState == 4)
			{
				vDelta = Vector3D{ 0, 0, 0 };
				vPrevPunch = vPunch;
			}
			else
			{
				m_Ingamesensitivity = Process->ReadMemory<float>(GlobalVariables::ClientAddress + Offsets::SensivityAddress);
				vDelta.x = ((LocalPlayer->Punch.x - vPrevPunch.x)*m_YMultiplayer) / (m_Yaw * m_Ingamesensitivity * GlobalVariables::MouseMultiplyer)*(-1.0);
				vDelta.y = ((LocalPlayer->Punch.y - vPrevPunch.y)*m_XMultiplayer) / (m_Yaw * m_Ingamesensitivity * GlobalVariables::MouseMultiplyer);
				vPrevPunch = LocalPlayer->Punch;

				MouseMove(vDelta.y, vDelta.x);
			}
		}

	}
	return 0x0;
}