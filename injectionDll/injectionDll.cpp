#include "stdafx.h"

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
HWND GetMainWindow();

extern "C" BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	HWND hWnd;
	HWND hParWnd, hButWnd;
	int d, d1;
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:

		hWnd = GetMainWindow();
		if (hWnd)
			hWnd = ::FindWindowEx(hWnd, 0, TEXT("EDIT"), NULL);
		if (hWnd)
		{
			MessageBox(hWnd, TEXT("开始注入"), TEXT("提示"), MB_OK);
		}
		else
		{
			MessageBox(hWnd, TEXT("记事本不存在"), TEXT("提示"), MB_OK);
		}
		break;
	case DLL_PROCESS_DETACH:
		// detach from process
		break;

	case DLL_THREAD_ATTACH:
		// attach to thread
		break;

	case DLL_THREAD_DETACH:
		// detach from thread
		break;
	}
	return TRUE; // succesful
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	DWORD dwCurProcessId = *((DWORD*)lParam);
	DWORD dwProcessId = 0;

	GetWindowThreadProcessId(hwnd, &dwProcessId);
	if (dwProcessId == dwCurProcessId && GetParent(hwnd) == NULL)
	{
		*((HWND *)lParam) = hwnd;
		return FALSE;
	}
	return TRUE;
}


HWND GetMainWindow()
{
	DWORD dwCurrentProcessId = GetCurrentProcessId();
	if (!EnumWindows(EnumWindowsProc, (LPARAM)&dwCurrentProcessId))
	{
		return (HWND)dwCurrentProcessId;
	}
	return NULL;
}