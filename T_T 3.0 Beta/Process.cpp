#include "Process.h"
CProcess* Process = new CProcess(_TempXOR("Counter-Strike: Global Offensive"), _TempXOR("csgo.exe"));
CProcess::CProcess()
{
}
CProcess::CProcess(string GameWindowName, string GameProcessName)
{
	WindowName = GameWindowName;
	ProcessName = GameProcessName;
}
CProcess::~CProcess()
{
}
HWND CProcess::GetWindow()
{
	hWindow = FindWindow(0, WindowName.c_str());
	return hWindow;
}
HWND CProcess::GetWindow(string WindowName)
{
	return FindWindow(0, WindowName.c_str());
}
DWORD CProcess::GetProcessID()
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 ProcessEntry;
	ZeroMemory(&ProcessEntry, sizeof(ProcessEntry));
	ProcessEntry.dwSize = sizeof(ProcessEntry);

	if (Process32First(hSnapshot, &ProcessEntry))
	{
		while (Process32Next(hSnapshot, &ProcessEntry) == TRUE)
		{

			if (strcmp(ProcessEntry.szExeFile, ProcessName.c_str()) == 0)
			{
				ProcessID = ProcessEntry.th32ProcessID;
				break;
			}
		}
	}

	CloseHandle(hSnapshot);
	return ProcessID;
}
DWORD CProcess::GetProcessID(string ProcessName)
{
	DWORD PID = 0;

	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 ProcessEntry;
	ZeroMemory(&ProcessEntry, sizeof(ProcessEntry));
	ProcessEntry.dwSize = sizeof(ProcessEntry);

	if (Process32First(hSnapshot, &ProcessEntry))
	{
		while (Process32Next(hSnapshot, &ProcessEntry) == TRUE)
		{

			if (strcmp(ProcessEntry.szExeFile, ProcessName.c_str()) == 0)
			{
				PID = ProcessEntry.th32ProcessID;
				break;
			}
		}
	}

	CloseHandle(hSnapshot);

	return PID;
}

DWORD CProcess::GetModuleBaseAddres(string ModuleName)
{
	DWORD ModuleAddress = 0x0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ProcessID);
	MODULEENTRY32 ModuleEntry;
	ModuleEntry.dwSize = sizeof(MODULEENTRY32);

	if (Module32First(hSnapshot, &ModuleEntry))
	{

		while (Module32Next(hSnapshot, &ModuleEntry))
		{
			if (strcmp(ModuleEntry.szModule, ModuleName.c_str()) == 0)
			{
				ModuleAddress = (DWORD)ModuleEntry.modBaseAddr;
				break;
			}
		}
	}
	CloseHandle(hSnapshot);

	return ModuleAddress;
};


HANDLE CProcess::GetHandle()
{
	hProcess = OpenProcess(PROCESS_VM_READ, FALSE, ProcessID);
	return hProcess;
}


HANDLE CProcess::GetHandle(string ProcessName)
{
	HANDLE h_Process;
	h_Process = OpenProcess(PROCESS_VM_READ, FALSE, GetProcessID(ProcessName));
	return h_Process;
}

string CProcess::ReadMemoryString(DWORD Address, int Size)
{
	char Value[64];
	ReadProcessMemory(hProcess, (LPCVOID*)Address, &Value, sizeof(Value), 0);
	return Value;
}

