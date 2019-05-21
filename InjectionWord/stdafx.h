#include <windows.h>;
#include <windowsx.h>;
#include <strsafe.h>;
#include <tlhelp32.h>;
#include <tchar.h>;

#define WM_MYMBUTTONDOWN INT_MAX

//注入返回结果
#define RE_NOPROCESS 1390
#define RE_SUCCESS 0
