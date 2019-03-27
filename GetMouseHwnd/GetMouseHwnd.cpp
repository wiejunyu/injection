//鼠标点击拖拽出矩形，放开绘画
//鼠标拖动形状
#include <windows.h>;
#include <strsafe.h>;
#define WM_MYMBUTTONDOWN INT_MAX
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK MouseProc(int nCode,WPARAM wParam,LPARAM lParam);
void SetHook();

HHOOK g_hKeyboardHook;
DWORD g_dwThreadID;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
	HWND hwnd;
	MSG msg;
	static TCHAR szAppName[] = TEXT("GetMouseHwnd");//指定窗口类名,面向程序员

	WNDCLASS wndclass;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;//窗口风格
	wndclass.lpfnWndProc = WndProc;//回调函数
	wndclass.cbClsExtra = 0;//预留的额外空间
	wndclass.cbWndExtra = 0;//预留的额外空间
	wndclass.hInstance = hInstance;//该窗口的句柄
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//为所有基于该窗口类的窗口设定一个图标
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);//为所有基于该窗口类的窗口设定一个鼠标指针
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//指定窗口背景色
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;//指定窗口类名,面向程序员
	RegisterClass(&wndclass);
	hwnd = CreateWindow(
		szAppName,
		TEXT("点击鼠标获取窗体句柄"),
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		800,
		600,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message)
	{
	case WM_CREATE:
		g_dwThreadID = GetCurrentThreadId();
		SetHook();
		return 0;
	case WM_MYMBUTTONDOWN:
		MessageBox(hwnd,TEXT("点击了窗体外面"), TEXT("提示框"),MB_OK);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
}

void SetHook()
{
	HMODULE mod = GetModuleHandle(TEXT("KeyboardHookDLL.dll"));   //获取当前DLL模块句柄
	g_hKeyboardHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, mod, 0);
}

LRESULT CALLBACK MouseProc(
	int nCode,
	WPARAM wParam,
	LPARAM lParam
)
{
	POINT pBUTTON;
	HWND hGetWindows;
	if (nCode >= 0)
	{
		if (wParam == WM_LBUTTONDOWN)
		{
			pBUTTON.x = LOWORD(lParam);
			pBUTTON.y = HIWORD(lParam);
			//hGetWindows = WindowFromPoint(pBUTTON);
			PostThreadMessage(g_dwThreadID, WM_MYMBUTTONDOWN, pBUTTON.x, pBUTTON.y);
		}
	}
	return CallNextHookEx(g_hKeyboardHook, nCode, wParam, lParam);
}


void DeleteHook()
{
	UnhookWindowsHookEx(g_hKeyboardHook);
}
