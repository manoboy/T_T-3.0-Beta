#include "ObjectManager.h"
#include "Visuals.h"
#include "Entity.h"
CObjectManager* ObjectManager = new CObjectManager;
CBomb Bomb;
CWeapon Weapon[124];
int CWeapon::Count = 0;
CBomb::CBomb()
{

}

CObjectManager::CObjectManager()
{
	RefreshRate = 25;
}


CObjectManager::~CObjectManager()
{

}

char *Granades[3] = 
{
	_OnceXOR("G/F/S"),
	_OnceXOR("Decoy"),
	_OnceXOR("Molotov")
};


void CObjectManager::ReadObjects()
{
	if (!Visuals->bDrawBomb && !Visuals->bDrawDropedWeapons && !Visuals->bDrawGranades)
		return;

	if (LastRefresh + RefreshRate > clock())
		return;
	LastRefresh = clock();

	MaxObjects = Process->ReadMemory<int>(GlobalVariables::ClientAddress + Offsets::EntityList + 0x4);
	CWeapon::Count = 0;
	for (int i = 64; i<MaxObjects; i++)
	{
		DWORD EntityAddress = Process->ReadMemory<DWORD>(GlobalVariables::ClientAddress + Offsets::EntityList + 0x10 * i);
		if (EntityAddress != 0)
		{

			vt = Process->ReadMemory<int>(EntityAddress + 0x8);
			fn = Process->ReadMemory<int>(vt + 2 * 0x4);
			cls = Process->ReadMemory<int>(fn + 0x1);
			clsn = Process->ReadMemory<int>(cls + 8);
			clsid = Process->ReadMemory<int>(cls + 20);
			//ClassName = Process->ReadMemoryString(clsn, 32);

			if (Visuals->bDrawBomb)
			{
				if (clsid == 35)
				{
					DWORD ResourceAddress = EntityAddress;
					// 0x1614 = m_iPlayerC4
					Bomb.IDOwner = Process->ReadMemory<int>(ResourceAddress + 0x1614);
					if (Bomb.IDOwner >0 && Bomb.IDOwner<64)
						Bomb.Position = Entity[Bomb.IDOwner - 1].Position;
				}
				if (clsid == 28)
				{
					Bomb.Owner = Process->ReadMemory<int>(EntityAddress + 0x148);
					if (Bomb.Owner == -1)
					{
						Bomb.Address = EntityAddress;
						Bomb.ID = clsid;
						Bomb.Position = Process->ReadMemory<Vector3D>(EntityAddress + 0x134);
					}
					continue;
				}
				if (clsid == 103)
				{
					Bomb.Owner = -1;
					Bomb.Address = EntityAddress;
					Bomb.ID = clsid;
					Bomb.Position = Process->ReadMemory<Vector3D>(EntityAddress + 0x134);
					continue;
				}
			}

			if (CWeapon::Count > 120)
				continue;
			if (Visuals->bDrawGranades)
			{
				if (clsid == 9)
				{
					Weapon[CWeapon::Count].Name = Granades[0];
					Weapon[CWeapon::Count].Position = Process->ReadMemory<Vector3D>(EntityAddress + 0x134);
					CWeapon::Count++;
				}
				if (clsid == 40)
				{
					Weapon[CWeapon::Count].Name = Granades[1];
					Weapon[CWeapon::Count].Position = Process->ReadMemory<Vector3D>(EntityAddress + 0x134);
					CWeapon::Count++;
				}
				if (clsid == 93)
				{
					Weapon[CWeapon::Count].Name = Granades[2];
					Weapon[CWeapon::Count].Position = Process->ReadMemory<Vector3D>(EntityAddress + 0x134);
					CWeapon::Count++;
				}
			}

			if (Visuals->bDrawDropedWeapons)
			{
				switch (clsid)
				{
				case 1:
					Weapon[CWeapon::Count].Owner = Process->ReadMemory<int>(EntityAddress + 0x148);
					if (Weapon[CWeapon::Count].Owner == -1)
					{
						Weapon[CWeapon::Count].Name = WeaponName[7];
						Weapon[CWeapon::Count].Position = Process->ReadMemory<Vector3D>(EntityAddress + 0x134);
						CWeapon::Count++;
					}
					break;
				case 38:
					Weapon[CWeapon::Count].Owner = Process->ReadMemory<int>(EntityAddress + 0x148);
					if (Weapon[CWeapon::Count].Owner == -1)
					{
						Weapon[CWeapon::Count].Name = WeaponName[1];
						Weapon[CWeapon::Count].Position = Process->ReadMemory<Vector3D>(EntityAddress + 0x134);
						CWeapon::Count++;
					}
					break;
				case 195:
					Weapon[CWeapon::Count].Owner = Process->ReadMemory<int>(EntityAddress + 0x148);
					if (Weapon[CWeapon::Count].Owner == -1)
					{
						Weapon[CWeapon::Count].Name = WeaponName[8];
						Weapon[CWeapon::Count].Position = Process->ReadMemory<Vector3D>(EntityAddress + 0x134);
						CWeapon::Count++;
					}
					break;
				case 196:
					Weapon[CWeapon::Count].Owner = Process->ReadMemory<int>(EntityAddress + 0x148);
					if (Weapon[CWeapon::Count].Owner == -1)
					{
						Weapon[CWeapon::Count].Name = WeaponName[9];
						Weapon[CWeapon::Count].Position = Process->ReadMemory<Vector3D>(EntityAddress + 0x134);
						CWeapon::Count++;
					}
					break;
				case 197:
					Weapon[CWeapon::Count].Owner = Process->ReadMemory<int>(EntityAddress + 0x148);
					if (Weapon[CWeapon::Count].Owner == -1)
					{
						Weapon[CWeapon::Count].Name = WeaponName[26];
						Weapon[CWeapon::Count].Position = Process->ReadMemory<Vector3D>(EntityAddress + 0x134);
						CWeapon::Count++;
					}
					break;

				case 201:
					Weapon[CWeapon::Count].Owner = Process->ReadMemory<int>(EntityAddress + 0x148);
					if (Weapon[CWeapon::Count].Owner == -1)
					{
						Weapon[CWeapon::Count].Name = WeaponName[2];
						Weapon[CWeapon::Count].Position = Process->ReadMemory<Vector3D>(EntityAddress + 0x134);
						CWeapon::Count++;
					}
					break;
				case 202:
					Weapon[CWeapon::Count].Owner = Process->ReadMemory<int>(EntityAddress + 0x148);
					if (Weapon[CWeapon::Count].Owner == -1)
					{
						Weapon[CWeapon::Count].Name = WeaponName[10];
						Weapon[CWeapon::Count].Position = Process->ReadMemory<Vector3D>(EntityAddress + 0x134);
						CWeapon::Count++;
					}
					break;
				case 203:
					Weapon[CWeapon::Count].Owner = Process->ReadMemory<int>(EntityAddress + 0x148);
					if (Weapon[CWeapon::Count].Owner == -1)
					{
						Weapon[CWeapon::Count].Name = WeaponName[3];
						Weapon[CWeapon::Count].Position = Process->ReadMemory<Vector3D>(EntityAddress + 0x134);
						CWeapon::Count++;
					}
					break;
				case 204:
					Weapon[CWeapon::Count].Owner = Process->ReadMemory<int>(EntityAddress + 0x148);
					if (Weapon[CWeapon::Count].Owner == -1)
					{
						Weapon[CWeapon::Count].Name = WeaponName[11];
						Weapon[CWeapon::Count].Position = Process->ReadMemory<Vector3D>(EntityAddress + 0x134);
						CWeapon::Count++;
					}
					break;
				case 206:
					Weapon[CWeapon::Count].Owner = Process->ReadMemory<int>(EntityAddress + 0x148);
					if (Weapon[CWeapon::Count].Owner == -1)
					{
						Weapon[CWeapon::Count].Name = WeaponName[13];
						Weapon[CWeapon::Count].Position = Process->ReadMemory<Vector3D>(EntityAddress + 0x134);
						CWeapon::Count++;
					}
					break;
				case 207:
					Weapon[CWeapon::Count].Owner = Process->ReadMemory<int>(EntityAddress + 0x148);
					if (Weapon[CWeapon::Count].Owner == -1)
					{
						Weapon[CWeapon::Count].Name = WeaponName[4];
						Weapon[CWeapon::Count].Position = Process->ReadMemory<Vector3D>(EntityAddress + 0x134);
						CWeapon::Count++;
					}
					break;
				case 208:
					Weapon[CWeapon::Count].Owner = Process->ReadMemory<int>(EntityAddress + 0x148);
					if (Weapon[CWeapon::Count].Owner == -1)
					{
						Weapon[CWeapon::Count].Name = WeaponName[32];
						Weapon[CWeapon::Count].Position = Process->ReadMemory<Vector3D>(EntityAddress + 0x134);
						CWeapon::Count++;
					}
					break;
				case 209:
					Weapon[CWeapon::Count].Owner = Process->ReadMemory<int>(EntityAddress + 0x148);
					if (Weapon[CWeapon::Count].Owner == -1)
					{
						Weapon[CWeapon::Count].Name = WeaponName[14];
						Weapon[CWeapon::Count].Position = Process->ReadMemory<Vector3D>(EntityAddress + 0x134);
						CWeapon::Count++;
					}
					break;
				case 211:
					Weapon[CWeapon::Count].Owner = Process->ReadMemory<int>(EntityAddress + 0x148);
					if (Weapon[CWeapon::Count].Owner == -1)
					{
						Weapon[CWeapon::Count].Name = WeaponName[16];
						Weapon[CWeapon::Count].Position = Process->ReadMemory<Vector3D>(EntityAddress + 0x134);
						CWeapon::Count++;
					}
					break;
				case 212:
					Weapon[CWeapon::Count].Owner = Process->ReadMemory<int>(EntityAddress + 0x148);
					if (Weapon[CWeapon::Count].Owner == -1)
					{
						Weapon[CWeapon::Count].Name = WeaponName[17];
						Weapon[CWeapon::Count].Position = Process->ReadMemory<Vector3D>(EntityAddress + 0x134);
						CWeapon::Count++;
					}
					break;
				case 213:
					Weapon[CWeapon::Count].Owner = Process->ReadMemory<int>(EntityAddress + 0x148);
					if (Weapon[CWeapon::Count].Owner == -1)
					{
						Weapon[CWeapon::Count].Name = WeaponName[27];
						Weapon[CWeapon::Count].Position = Process->ReadMemory<Vector3D>(EntityAddress + 0x134);
						CWeapon::Count++;
					}
					break;
				case 215:
					Weapon[CWeapon::Count].Owner = Process->ReadMemory<int>(EntityAddress + 0x148);
					if (Weapon[CWeapon::Count].Owner == -1)
					{
						Weapon[CWeapon::Count].Name = WeaponName[33];
						Weapon[CWeapon::Count].Position = Process->ReadMemory<Vector3D>(EntityAddress + 0x134);
						CWeapon::Count++;
					}
					break;
				case 216:
					Weapon[CWeapon::Count].Owner = Process->ReadMemory<int>(EntityAddress + 0x148);
					if (Weapon[CWeapon::Count].Owner == -1)
					{
						Weapon[CWeapon::Count].Name = WeaponName[34];
						Weapon[CWeapon::Count].Position = Process->ReadMemory<Vector3D>(EntityAddress + 0x134);
						CWeapon::Count++;
					}
					break;
				case 217:
					Weapon[CWeapon::Count].Owner = Process->ReadMemory<int>(EntityAddress + 0x148);
					if (Weapon[CWeapon::Count].Owner == -1)
					{
						Weapon[CWeapon::Count].Name = WeaponName[28];
						Weapon[CWeapon::Count].Position = Process->ReadMemory<Vector3D>(EntityAddress + 0x134);
						CWeapon::Count++;
					}
					break;
				case 218:
					Weapon[CWeapon::Count].Owner = Process->ReadMemory<int>(EntityAddress + 0x148);
					if (Weapon[CWeapon::Count].Owner == -1)
					{
						Weapon[CWeapon::Count].Name = WeaponName[35];
						Weapon[CWeapon::Count].Position = Process->ReadMemory<Vector3D>(EntityAddress + 0x134);
						CWeapon::Count++;
					}
					break;
				case 220:
					Weapon[CWeapon::Count].Owner = Process->ReadMemory<int>(EntityAddress + 0x148);
					if (Weapon[CWeapon::Count].Owner == -1)
					{
						Weapon[CWeapon::Count].Name = WeaponName[36];
						Weapon[CWeapon::Count].Position = Process->ReadMemory<Vector3D>(EntityAddress + 0x134);
						CWeapon::Count++;
					}
					break;
				case 221:
					Weapon[CWeapon::Count].Owner = Process->ReadMemory<int>(EntityAddress + 0x148);
					if (Weapon[CWeapon::Count].Owner == -1)
					{
						Weapon[CWeapon::Count].Name = WeaponName[19];
						Weapon[CWeapon::Count].Position = Process->ReadMemory<Vector3D>(EntityAddress + 0x134);
						CWeapon::Count++;
					}
					break;
				case 222:
					Weapon[CWeapon::Count].Owner = Process->ReadMemory<int>(EntityAddress + 0x148);
					if (Weapon[CWeapon::Count].Owner == -1)
					{
						Weapon[CWeapon::Count].Name = WeaponName[29];
						Weapon[CWeapon::Count].Position = Process->ReadMemory<Vector3D>(EntityAddress + 0x134);
						CWeapon::Count++;
					}
					break;
				case 223:
					Weapon[CWeapon::Count].Owner = Process->ReadMemory<int>(EntityAddress + 0x148);
					if (Weapon[CWeapon::Count].Owner == -1)
					{
						Weapon[CWeapon::Count].Name = WeaponName[38];
						Weapon[CWeapon::Count].Position = Process->ReadMemory<Vector3D>(EntityAddress + 0x134);
						CWeapon::Count++;
					}
					break;
				case 227:
					Weapon[CWeapon::Count].Owner = Process->ReadMemory<int>(EntityAddress + 0x148);
					if (Weapon[CWeapon::Count].Owner == -1)
					{
						Weapon[CWeapon::Count].Name = WeaponName[39];
						Weapon[CWeapon::Count].Position = Process->ReadMemory<Vector3D>(EntityAddress + 0x134);
						CWeapon::Count++;
					}
					break;
				case 228:
					Weapon[CWeapon::Count].Owner = Process->ReadMemory<int>(EntityAddress + 0x148);
					if (Weapon[CWeapon::Count].Owner == -1)
					{
						Weapon[CWeapon::Count].Name = WeaponName[40];
						Weapon[CWeapon::Count].Position = Process->ReadMemory<Vector3D>(EntityAddress + 0x134);
						CWeapon::Count++;
					}
					break;
				case 229:
					Weapon[CWeapon::Count].Owner = Process->ReadMemory<int>(EntityAddress + 0x148);
					if (Weapon[CWeapon::Count].Owner == -1)
					{
						Weapon[CWeapon::Count].Name = WeaponName[31];
						Weapon[CWeapon::Count].Position = Process->ReadMemory<Vector3D>(EntityAddress + 0x134);
						CWeapon::Count++;
					}
					break;
				case 230:
					Weapon[CWeapon::Count].Owner = Process->ReadMemory<int>(EntityAddress + 0x148);
					if (Weapon[CWeapon::Count].Owner == -1)
					{
						Weapon[CWeapon::Count].Name = WeaponName[51];
						Weapon[CWeapon::Count].Position = Process->ReadMemory<Vector3D>(EntityAddress + 0x134);
						CWeapon::Count++;
					}
					break;
				case 232:
					Weapon[CWeapon::Count].Owner = Process->ReadMemory<int>(EntityAddress + 0x148);
					if (Weapon[CWeapon::Count].Owner == -1)
					{
						Weapon[CWeapon::Count].Name = WeaponName[24];
						Weapon[CWeapon::Count].Position = Process->ReadMemory<Vector3D>(EntityAddress + 0x134);
						CWeapon::Count++;
					}
					break;
				case 234:
					Weapon[CWeapon::Count].Owner = Process->ReadMemory<int>(EntityAddress + 0x148);
					if (Weapon[CWeapon::Count].Owner == -1)
					{
						Weapon[CWeapon::Count].Name = WeaponName[25];
						Weapon[CWeapon::Count].Position = Process->ReadMemory<Vector3D>(EntityAddress + 0x134);
						CWeapon::Count++;
					}
					break;
				}
			}


		}
	}
}