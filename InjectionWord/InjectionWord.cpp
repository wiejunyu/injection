//点击鼠标获取窗体句柄
#include "stdafx.h";

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HHOOK SetHook();
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);
BOOL DeleteHook(HHOOK hook);
DWORD dll_inject(HWND hwnd);

//全局句柄
HWND hMyHwnd;
//全局钩子
HHOOK g_hKeyboardHook;
//窗体是否在置顶状态
BOOL bTopping = false;
//是否是获取子窗体状态
BOOL bButtonSon = false;

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
		400,
		400,
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
	PAINTSTRUCT ps;
	HDC hdc;

	//按钮
	static RECT rButton;
	POINT pButton;

	//窗体始终置顶
	HWND hForegdWnd;
	DWORD dwForegdWndThreadID;
	DWORD dwThreadID;

	//安全字符串
	TCHAR buff[128];
	size_t iTarget;

	switch (message)
	{
	case WM_CREATE:
		hMyHwnd = hwnd;
		return 0;
	case WM_LBUTTONDOWN:
		pButton.x = GET_X_LPARAM(lParam);
		pButton.y = GET_Y_LPARAM(lParam);
		if (PtInRect(&rButton, pButton))
		{
			bTopping = true;
			SetHook();
		}
		return 0;
	case WM_KILLFOCUS:

		#pragma region  窗体始终置顶
		if (bTopping) {
			hForegdWnd = GetForegroundWindow();
			dwForegdWndThreadID = GetWindowThreadProcessId(hForegdWnd, NULL);
			dwThreadID = GetCurrentThreadId();
			AttachThreadInput(dwThreadID, dwForegdWndThreadID, TRUE);
			SetForegroundWindow(hwnd);
			SetFocus(hwnd);
			AttachThreadInput(dwThreadID, dwForegdWndThreadID, FALSE);
		}
		#pragma endregion

		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		#pragma region  开始获取按钮
		rButton.left = 0; rButton.top = 0; rButton.right = 100; rButton.bottom = 30;
		RoundRect(hdc, rButton.left, rButton.top, rButton.right, rButton.bottom, 30, 30);
		StringCchPrintf(buff, 128, TEXT("点击开始获取"));
		StringCchLength(buff, 128, &iTarget);
		TextOut(hdc, 5, 5, buff, iTarget);
		#pragma endregion

		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
}

HHOOK SetHook()
{
	HMODULE mod = GetModuleHandle(TEXT("KeyboardHookDLL.dll"));   //获取当前DLL模块句柄
	g_hKeyboardHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, mod, 0);
	return g_hKeyboardHook;
}

LRESULT CALLBACK MouseProc(
	int nCode,
	WPARAM wParam,
	LPARAM lParam
)
{
	POINT pButton;
	HWND hGetWindows;
	HDC hdc;

	//安全字符串
	TCHAR buff[128];
	size_t iTarget;

	//返回结果
	DWORD re;
	LPVOID lpMsgBuf;

	if (nCode >= 0)
	{
		if (wParam == WM_LBUTTONDOWN)
		{
			GetCursorPos(&pButton);
			hGetWindows = WindowFromPoint(pButton);
			if (hGetWindows == NULL)
			{
				StringCchPrintf(buff, 128, TEXT("NULL"));
				StringCchLength(buff, 128, &iTarget);
			}
			else
			{
				StringCchPrintf(buff, 128, TEXT("%x"), hGetWindows);
				StringCchLength(buff, 128, &iTarget);
				bTopping = false;
			}
			re = dll_inject(hGetWindows);
			FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, re, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
			MessageBox(NULL, (LPCTSTR)(re == RE_NOPROCESS ? TEXT("进程不存在") : lpMsgBuf), TEXT("提示"), MB_OK);
			if (!DeleteHook(g_hKeyboardHook))
			{
				MessageBox(NULL, TEXT("卸载失败"), TEXT("失败"), MB_OK);
			}
		}
	}
	return CallNextHookEx(g_hKeyboardHook, nCode, wParam, lParam);
}


BOOL DeleteHook(HHOOK hook)
{
	return UnhookWindowsHookEx(hook);
}

DWORD dll_inject(HWND hwnd) {
	//安全字符串
	TCHAR buff[128];
	size_t iTarget;

	#pragma region 文件EXE路径获得DLL路径
	//TCHAR _szPath[MAX_PATH + 1] = { 0 };
	//GetModuleFileName(NULL, _szPath, MAX_PATH);
	//(_tcsrchr(_szPath, _T('\\')))[1] = 0;//删除文件名，只获得路径 字串

	//const TCHAR *pNameDll = TEXT("LoveDll.dll");

	//int len_szPath = lstrlen(_szPath);
	//int len_pNameDll = lstrlen(pNameDll);
	//TCHAR* szBuff = new TCHAR[len_szPath + len_pNameDll + 1];
	//szBuff[0] = _T('\0');
	//lstrcat(szBuff, _szPath);
	//lstrcat(szBuff, pNameDll);
	//const TCHAR *pLocDll = szBuff;
	#pragma endregion

	#pragma region 手动路径
	/*const TCHAR *pLocDll = TEXT("F:\\工作\\项目\\控制台\\Love\\x64\\Release\\LoveDll.dll");
	const TCHAR *pNameDll = TEXT("LoveDll.dll");*/

	const TCHAR *pLocDll = TEXT("F:\\工作\\项目\\控制台\\Love\\x64\\Release\\injectionDll.dll");
	const TCHAR *pNameDll = TEXT("injectionDll.dll");
	#pragma endregion

	HANDLE hThread = NULL;

	//进程名称
	DWORD ProcessID;
	GetWindowThreadProcessId(hwnd, &ProcessID);

	if (!ProcessID) {
		return RE_NOPROCESS;
	}
	else {
		//获取进程ID
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, ProcessID);
		//在寄主申请内存
		LPVOID strRmt = VirtualAllocEx(hProcess, nullptr, MAX_PATH, MEM_COMMIT, PAGE_READWRITE);
		//获得注入DLL大小
		size_t lenLocDll = 2 * _tcslen(pLocDll);
		//判断寄主申请内存是否成功
		if (strRmt) {
			//把DLL写入寄主内存
			BOOL ret = WriteProcessMemory(hProcess, strRmt, pLocDll, lenLocDll, nullptr);
			//获得LoadLibraryW的函数地址以使用LoadLibrary函数
			LPTHREAD_START_ROUTINE loadlib = LPTHREAD_START_ROUTINE(GetProcAddress(GetModuleHandle(TEXT("Kernel32")), "LoadLibraryW"));
			//注入
			hThread = CreateRemoteThread(hProcess, nullptr, 0, loadlib, LPVOID(strRmt), 0, nullptr);
		}

		if (hThread == NULL)
		{
			return GetLastError();
		}

		WaitForSingleObject(hThread, INFINITE);
		//到这里已经完成dll的加载即注入了，通过dll函数执行我们要完成的任务
		//释放
		VirtualFreeEx(hProcess, strRmt, 0, MEM_RELEASE);
		CloseHandle(hThread);
		CloseHandle(hProcess);
		return RE_SUCCESS;
	}
}