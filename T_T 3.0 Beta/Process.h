#pragma once
#include "Globals.h"
class CProcess
{
public:
	string WindowName;
	string ProcessName;

	HWND hWindow;
	DWORD ProcessID;
	HANDLE hProcess;


	HWND GetWindow();
	HWND GetWindow(string WindowName);

	DWORD GetProcessID();
	DWORD GetProcessID(string WindowName);

	HANDLE GetHandle();
	HANDLE GetHandle(string ProcessName);

	DWORD GetModuleBaseAddres(string ModuleName);
	DWORD GetModuleBaseAddres(HANDLE hProcess, string ModuleName);

	template < class TypeValue > TypeValue ReadMemory(DWORD Address);

	string  ReadMemoryString(DWORD Address, int Size);

	CProcess();
	CProcess(string GameWindowName, string GameProcessName);
	~CProcess();
};

template <class TypeValue>
TypeValue CProcess::ReadMemory(DWORD Address)
{
	TypeValue Value;
	ReadProcessMemory(hProcess, (LPCVOID*)Address, &Value, sizeof(TypeValue), 0);
	return Value;
}

extern CProcess* Process;


