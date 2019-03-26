#include "stdafx.h"

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
HWND GetMainWindow();
void MyPostMessage(HWND hWnd);

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
			::MessageBox(hWnd, TEXT("开始注入"), TEXT("提示"), MB_OK);
			MyPostMessage(hWnd);
		}
		else
		{
			::MessageBox(hWnd, TEXT("记事本不存在"), TEXT("提示"), MB_OK);
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

void MyPostMessage(HWND hWnd)
{
	for (int i = 0; i < 25; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'.', 1);
	PostMessageW(hWnd, WM_CHAR, L',', 1);
	PostMessageW(hWnd, WM_CHAR, L']', 1);
	PostMessageW(hWnd, WM_CHAR, L']', 1);
	PostMessageW(hWnd, WM_CHAR, L'.', 1);
	for (int i = 0; i < 33; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L',', 1);
	PostMessageW(hWnd, WM_CHAR, L'/', 1);
	for (int i = 0; i < 7; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\\', 1);
	PostMessageW(hWnd, WM_CHAR, L']', 1);
	PostMessageW(hWnd, WM_CHAR, L']', 1);
	PostMessageW(hWnd, WM_CHAR, L']', 1);
	PostMessageW(hWnd, WM_CHAR, L'.', 1);
	for (int i = 0; i < 17; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 16; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L',', 1);
	PostMessageW(hWnd, WM_CHAR, L'/', 1);
	for (int i = 0; i < 15; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L']', 1);
	PostMessageW(hWnd, WM_CHAR, L'`', 1);
	for (int i = 0; i < 23; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'.', 1);
	PostMessageW(hWnd, WM_CHAR, L']', 1);
	for (int i = 0; i < 19; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L']', 1);
	PostMessageW(hWnd, WM_CHAR, L'.', 1);
	for (int i = 0; i < 13; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 12; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L']', 1);
	PostMessageW(hWnd, WM_CHAR, L'/', 1);
	for (int i = 0; i < 24; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\\', 1);
	PostMessageW(hWnd, WM_CHAR, L'.', 1);
	for (int i = 0; i < 15; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 27; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L']', 1);
	for (int i = 0; i < 10; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 9; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 31; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'`', 1);
	for (int i = 0; i < 11; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 31; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\\', 1);
	for (int i = 0; i < 8; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 7; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 35; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\\', 1);
	for (int i = 0; i < 7; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 35; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\\', 1);
	for (int i = 0; i < 6; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 5; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 39; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\\', 1);
	PostMessageW(hWnd, WM_CHAR, L'.', 1);
	PostMessageW(hWnd, WM_CHAR, L' ', 1);
	PostMessageW(hWnd, WM_CHAR, L' ', 1);
	PostMessageW(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 39; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\\', 1);
	for (int i = 0; i < 4; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 3; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 87; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'.', 1);
	PostMessageW(hWnd, WM_CHAR, L' ', 1);
	PostMessageW(hWnd, WM_CHAR, L' ', 1);
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	PostMessageW(hWnd, WM_CHAR, L' ', 1);
	PostMessageW(hWnd, WM_CHAR, L' ', 1);
	PostMessageW(hWnd, WM_CHAR, L'.', 1);
	for (int i = 0; i < 89; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'.', 1);
	PostMessageW(hWnd, WM_CHAR, L' ', 1);
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	PostMessageW(hWnd, WM_CHAR, L' ', 1);
	PostMessageW(hWnd, WM_CHAR, L' ', 1);
	PostMessageW(hWnd, WM_CHAR, L'/', 1);
	for (int i = 0; i < 90; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L' ', 1);
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	PostMessageW(hWnd, WM_CHAR, L' ', 1);
	PostMessageW(hWnd, WM_CHAR, L'=', 1);
	for (int i = 0; i < 91; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\\', 1);
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	PostMessageW(hWnd, WM_CHAR, L'=', 1);
	for (int i = 0; i < 93; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 94; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	PostMessageW(hWnd, WM_CHAR, L'=', 1);
	for (int i = 0; i < 93; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	PostMessageW(hWnd, WM_CHAR, L'=', 1);
	for (int i = 0; i < 93; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	PostMessageW(hWnd, WM_CHAR, L'=', 1);
	for (int i = 0; i < 93; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	PostMessageW(hWnd, WM_CHAR, L'.', 1);
	for (int i = 0; i < 93; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	PostMessageW(hWnd, WM_CHAR, L' ', 1);
	for (int i = 0; i < 93; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	PostMessageW(hWnd, WM_CHAR, L' ', 1);
	PostMessageW(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 92; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	PostMessageW(hWnd, WM_CHAR, L' ', 1);
	PostMessageW(hWnd, WM_CHAR, L' ', 1);
	PostMessageW(hWnd, WM_CHAR, L'=', 1);
	for (int i = 0; i < 90; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'^', 1);
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 3; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\\', 1);
	for (int i = 0; i < 88; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'/', 1);
	PostMessageW(hWnd, WM_CHAR, L' ', 1);
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 4; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	for (int i = 0; i < 88; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L' ', 1);
	PostMessageW(hWnd, WM_CHAR, L' ', 1);
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 4; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'.', 1);
	for (int i = 0; i < 86; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'.', 1);
	PostMessageW(hWnd, WM_CHAR, L' ', 1);
	PostMessageW(hWnd, WM_CHAR, L' ', 1);
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 5; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 84; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'.', 1);
	for (int i = 0; i < 3; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 7; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\\', 1);
	for (int i = 0; i < 80; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'/', 1);
	for (int i = 0; i < 5; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 8; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 78; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'`', 1);
	for (int i = 0; i < 6; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 9; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 76; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'`', 1);
	for (int i = 0; i < 7; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 11; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\\', 1);
	for (int i = 0; i < 72; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'/', 1);
	for (int i = 0; i < 9; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 12; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'=', 1);
	for (int i = 0; i < 70; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'^', 1);
	for (int i = 0; i < 10; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 13; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'.', 1);
	for (int i = 0; i < 67; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'/', 1);
	PostMessageW(hWnd, WM_CHAR, L'.', 1);
	for (int i = 0; i < 11; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 15; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 64; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'`', 1);
	for (int i = 0; i < 13; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 17; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\\', 1);
	for (int i = 0; i < 60; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'/', 1);
	for (int i = 0; i < 15; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 18; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 58; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'.', 1);
	for (int i = 0; i < 16; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 20; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 54; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'`', 1);
	for (int i = 0; i < 18; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 22; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 50; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'`', 1);
	for (int i = 0; i < 20; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 24; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\\', 1);
	for (int i = 0; i < 46; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'`', 1);
	for (int i = 0; i < 22; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 26; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\\', 1);
	for (int i = 0; i < 42; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'`', 1);
	for (int i = 0; i < 24; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 28; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 37; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'/', 1);
	PostMessageW(hWnd, WM_CHAR, L'.', 1);
	for (int i = 0; i < 26; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 30; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'.', 1);
	PostMessageW(hWnd, WM_CHAR, L'\\', 1);
	for (int i = 0; i < 32; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'[', 1);
	for (int i = 0; i < 29; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 33; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 27; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'/', 1);
	PostMessageW(hWnd, WM_CHAR, L'`', 1);
	for (int i = 0; i < 31; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 36; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 22; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'`', 1);
	for (int i = 0; i < 34; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 39; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 16; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'[', 1);
	for (int i = 0; i < 37; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 42; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\\', 1);
	for (int i = 0; i < 10; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'/', 1);
	PostMessageW(hWnd, WM_CHAR, L'.', 1);
	for (int i = 0; i < 39; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 44; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 6; i++) {
		PostMessageW(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'`', 1);
	for (int i = 0; i < 42; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 46; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'.', 1);
	PostMessageW(hWnd, WM_CHAR, L'\\', 1);
	PostMessageW(hWnd, WM_CHAR, L'O', 1);
	PostMessageW(hWnd, WM_CHAR, L'`', 1);
	for (int i = 0; i < 44; i++) {
		PostMessageW(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessageW(hWnd, WM_CHAR, L'\n', 1);
}