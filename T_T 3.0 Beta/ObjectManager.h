#pragma once
#include "Globals.h"
#include "Process.h"
#include "Math.h"

class CBomb
{
public:

	DWORD Address;
	int ID;
	Vector3D Position;
	DWORD Owner;
	int IDOwner;
	CBomb();
};

class CWeapon
{
public:
	static int Count;
	DWORD Address;
	int ID;
	Vector3D Position;
	DWORD Owner;
	int IDOwner;
	char* Name;
	std::string InGameName;
	CWeapon(){};
};
extern CBomb Bomb;
extern CWeapon Weapon[124];


class CObjectManager
{
public:
	int MaxObjects;
	int vt;
	int fn;
	int cls;
	int clsn;
	int clsid;
	string ClassName;

	int TempCount;

	clock_t LastRefresh;
	clock_t RefreshRate;

	void ReadObjects();
	
	CObjectManager();
	~CObjectManager();
};
extern CObjectManager* ObjectManager;
