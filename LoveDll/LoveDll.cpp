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
			//::MessageBox(NULL, TEXT("开始注入"), TEXT("提示"), MB_OK);
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
	HWND fhWnd;
	#pragma region 字体操作，如果字体不一致会导致团变形
	LOGFONT LogFont;
	memset(&LogFont, 0, sizeof(LOGFONT));
	lstrcpy(LogFont.lfFaceName, L"SimSun");
	LogFont.lfWeight = FW_BLACK;//FW_NORMAL;
	LogFont.lfHeight = -24; // 字体大小
	LogFont.lfCharSet = 134;
	LogFont.lfOutPrecision = 3;
	LogFont.lfClipPrecision = 2;
	LogFont.lfOrientation = 45;
	LogFont.lfQuality = 1;
	LogFont.lfPitchAndFamily = 2;
	// 创建字体
	HFONT hFont = CreateFontIndirect(&LogFont);
	// 取得控件句柄
	PostMessage(hWnd, WM_SETFONT, (WPARAM)hFont, TRUE);
	#pragma endregion

	#pragma region 最大化操作，以免显示不完图案
	fhWnd = GetParent(hWnd);
	PostMessage(fhWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0); // 最大化
	#pragma endregion

	#pragma region 图案操作
	for (int i = 0; i < 25; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'.', 1);
	PostMessage(hWnd, WM_CHAR, L',', 1);
	PostMessage(hWnd, WM_CHAR, L']', 1);
	PostMessage(hWnd, WM_CHAR, L']', 1);
	PostMessage(hWnd, WM_CHAR, L'.', 1);
	for (int i = 0; i < 33; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L',', 1);
	PostMessage(hWnd, WM_CHAR, L'/', 1);
	for (int i = 0; i < 7; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\\', 1);
	PostMessage(hWnd, WM_CHAR, L']', 1);
	PostMessage(hWnd, WM_CHAR, L']', 1);
	PostMessage(hWnd, WM_CHAR, L']', 1);
	PostMessage(hWnd, WM_CHAR, L'.', 1);
	for (int i = 0; i < 17; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 16; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L',', 1);
	PostMessage(hWnd, WM_CHAR, L'/', 1);
	for (int i = 0; i < 15; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L']', 1);
	PostMessage(hWnd, WM_CHAR, L'`', 1);
	for (int i = 0; i < 23; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'.', 1);
	PostMessage(hWnd, WM_CHAR, L']', 1);
	for (int i = 0; i < 19; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L']', 1);
	PostMessage(hWnd, WM_CHAR, L'.', 1);
	for (int i = 0; i < 13; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 12; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L']', 1);
	PostMessage(hWnd, WM_CHAR, L'/', 1);
	for (int i = 0; i < 24; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\\', 1);
	PostMessage(hWnd, WM_CHAR, L'.', 1);
	for (int i = 0; i < 15; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 27; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L']', 1);
	for (int i = 0; i < 10; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 9; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 31; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'`', 1);
	for (int i = 0; i < 11; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 31; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\\', 1);
	for (int i = 0; i < 8; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 7; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 35; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\\', 1);
	for (int i = 0; i < 7; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 35; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\\', 1);
	for (int i = 0; i < 6; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 5; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 39; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\\', 1);
	PostMessage(hWnd, WM_CHAR, L'.', 1);
	PostMessage(hWnd, WM_CHAR, L' ', 1);
	PostMessage(hWnd, WM_CHAR, L' ', 1);
	PostMessage(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 39; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\\', 1);
	for (int i = 0; i < 4; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 3; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 87; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'.', 1);
	PostMessage(hWnd, WM_CHAR, L' ', 1);
	PostMessage(hWnd, WM_CHAR, L' ', 1);
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	PostMessage(hWnd, WM_CHAR, L' ', 1);
	PostMessage(hWnd, WM_CHAR, L' ', 1);
	PostMessage(hWnd, WM_CHAR, L'.', 1);
	for (int i = 0; i < 89; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'.', 1);
	PostMessage(hWnd, WM_CHAR, L' ', 1);
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	PostMessage(hWnd, WM_CHAR, L' ', 1);
	PostMessage(hWnd, WM_CHAR, L' ', 1);
	PostMessage(hWnd, WM_CHAR, L'/', 1);
	for (int i = 0; i < 90; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L' ', 1);
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	PostMessage(hWnd, WM_CHAR, L' ', 1);
	PostMessage(hWnd, WM_CHAR, L'=', 1);
	for (int i = 0; i < 91; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\\', 1);
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	PostMessage(hWnd, WM_CHAR, L'=', 1);
	for (int i = 0; i < 93; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 94; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	PostMessage(hWnd, WM_CHAR, L'=', 1);
	for (int i = 0; i < 93; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	PostMessage(hWnd, WM_CHAR, L'=', 1);
	for (int i = 0; i < 93; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	PostMessage(hWnd, WM_CHAR, L'=', 1);
	for (int i = 0; i < 93; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	PostMessage(hWnd, WM_CHAR, L'.', 1);
	for (int i = 0; i < 93; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	PostMessage(hWnd, WM_CHAR, L' ', 1);
	for (int i = 0; i < 93; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	PostMessage(hWnd, WM_CHAR, L' ', 1);
	PostMessage(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 92; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	PostMessage(hWnd, WM_CHAR, L' ', 1);
	PostMessage(hWnd, WM_CHAR, L' ', 1);
	PostMessage(hWnd, WM_CHAR, L'=', 1);
	for (int i = 0; i < 90; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'^', 1);
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 3; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\\', 1);
	for (int i = 0; i < 88; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'/', 1);
	PostMessage(hWnd, WM_CHAR, L' ', 1);
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 4; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	for (int i = 0; i < 88; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L' ', 1);
	PostMessage(hWnd, WM_CHAR, L' ', 1);
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 4; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'.', 1);
	for (int i = 0; i < 86; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'.', 1);
	PostMessage(hWnd, WM_CHAR, L' ', 1);
	PostMessage(hWnd, WM_CHAR, L' ', 1);
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 5; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 84; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'.', 1);
	for (int i = 0; i < 3; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 7; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\\', 1);
	for (int i = 0; i < 80; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'/', 1);
	for (int i = 0; i < 5; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 8; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 78; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'`', 1);
	for (int i = 0; i < 6; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 9; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 76; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'`', 1);
	for (int i = 0; i < 7; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 11; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\\', 1);
	for (int i = 0; i < 72; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'/', 1);
	for (int i = 0; i < 9; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 12; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'=', 1);
	for (int i = 0; i < 70; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'^', 1);
	for (int i = 0; i < 10; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 13; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'.', 1);
	for (int i = 0; i < 67; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'/', 1);
	PostMessage(hWnd, WM_CHAR, L'.', 1);
	for (int i = 0; i < 11; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 15; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 64; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'`', 1);
	for (int i = 0; i < 13; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 17; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\\', 1);
	for (int i = 0; i < 60; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'/', 1);
	for (int i = 0; i < 15; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 18; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 58; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'.', 1);
	for (int i = 0; i < 16; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 20; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 54; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'`', 1);
	for (int i = 0; i < 18; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 22; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 50; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'`', 1);
	for (int i = 0; i < 20; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 24; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\\', 1);
	for (int i = 0; i < 46; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'`', 1);
	for (int i = 0; i < 22; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 26; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\\', 1);
	for (int i = 0; i < 42; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'`', 1);
	for (int i = 0; i < 24; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 28; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 37; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'/', 1);
	PostMessage(hWnd, WM_CHAR, L'.', 1);
	for (int i = 0; i < 26; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 30; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'.', 1);
	PostMessage(hWnd, WM_CHAR, L'\\', 1);
	for (int i = 0; i < 32; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'[', 1);
	for (int i = 0; i < 29; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 33; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 27; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'/', 1);
	PostMessage(hWnd, WM_CHAR, L'`', 1);
	for (int i = 0; i < 31; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 36; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 22; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'`', 1);
	for (int i = 0; i < 34; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 39; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 16; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'[', 1);
	for (int i = 0; i < 37; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 42; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\\', 1);
	for (int i = 0; i < 10; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'/', 1);
	PostMessage(hWnd, WM_CHAR, L'.', 1);
	for (int i = 0; i < 39; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 44; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L',', 1);
	for (int i = 0; i < 6; i++) {
		PostMessage(hWnd, WM_CHAR, L'O', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'`', 1);
	for (int i = 0; i < 42; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	for (int i = 0; i < 46; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'.', 1);
	PostMessage(hWnd, WM_CHAR, L'\\', 1);
	PostMessage(hWnd, WM_CHAR, L'O', 1);
	PostMessage(hWnd, WM_CHAR, L'`', 1);
	for (int i = 0; i < 44; i++) {
		PostMessage(hWnd, WM_CHAR, L' ', 1);
	}
	PostMessage(hWnd, WM_CHAR, L'\n', 1);
	#pragma endregion
}