#pragma once
#include "Math.h"
#include "Globals.h"
#include "Entity.h"
#include "RayTrace.h"

class CTriggerBot
{
public:

	static bool Active;
	static bool OnHotKey;
	static bool ShootOnHitBox;
	static bool Shoot;
	static bool SniperMode;

	static float MaxPunch;

	static int HotKey;

	static int SleepTime;

	static int DelayTime;
	static clock_t LastDelayTime;

	static int ShootingTime;
	static clock_t LastShootingTime;

	static int BreakTime;
	static clock_t LastBreakTime;

	static int ExtraShootingTime;
	static clock_t LastExtraShootingTime;

	static clock_t LastTimeTargetUnderCrosshair;



	static int Target;
	static int LastTarget;

	static Bones Bone;

	static DWORD WINAPI Run();

	static void ShootOnLoseTarget();

	CTriggerBot();
	~CTriggerBot();

};
extern CTriggerBot TriggerBot;
