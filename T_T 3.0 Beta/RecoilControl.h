#pragma once
#include "Globals.h"
#include "Math.h"

class CRecoilControl
{
public:
	static clock_t RefreshRate;
	static clock_t LastRefersh;

	static int SleepTime;
	static int ShootingState;

	static bool Active;

	static Vector3D vDelta;
	static Vector3D vPunch;
	static Vector3D vPrevPunch;
	static float m_Yaw;
	static float m_Ingamesensitivity;
	static float m_Windowssensitivity;
	static float m_XMultiplayer;
	static float m_YMultiplayer;

	static int RecoilDrawType;
	static float RecoilDrawResolution;

	static DWORD WINAPI Run();

	static int HotKey;
	static clock_t LastKeyPress;

	CRecoilControl();
	~CRecoilControl();
	//SwapLines0
};

extern CRecoilControl* RecoilControl;