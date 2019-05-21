//�������ȡ������
#include "stdafx.h";

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HHOOK SetHook();
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);
BOOL DeleteHook(HHOOK hook);
DWORD dll_inject(HWND hwnd);

//ȫ�־��
HWND hMyHwnd;
//ȫ�ֹ���
HHOOK g_hKeyboardHook;
//�����Ƿ����ö�״̬
BOOL bTopping = false;
//�Ƿ��ǻ�ȡ�Ӵ���״̬
BOOL bButtonSon = false;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
	HWND hwnd;
	MSG msg;
	static TCHAR szAppName[] = TEXT("GetMouseHwnd");//ָ����������,�������Ա

	WNDCLASS wndclass;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;//���ڷ��
	wndclass.lpfnWndProc = WndProc;//�ص�����
	wndclass.cbClsExtra = 0;//Ԥ���Ķ���ռ�
	wndclass.cbWndExtra = 0;//Ԥ���Ķ���ռ�
	wndclass.hInstance = hInstance;//�ô��ڵľ��
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//Ϊ���л��ڸô�����Ĵ����趨һ��ͼ��
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);//Ϊ���л��ڸô�����Ĵ����趨һ�����ָ��
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//ָ�����ڱ���ɫ
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;//ָ����������,�������Ա
	RegisterClass(&wndclass);
	hwnd = CreateWindow(
		szAppName,
		TEXT("�������ȡ������"),
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

	//��ť
	static RECT rButton;
	POINT pButton;

	//����ʼ���ö�
	HWND hForegdWnd;
	DWORD dwForegdWndThreadID;
	DWORD dwThreadID;

	//��ȫ�ַ���
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

		#pragma region  ����ʼ���ö�
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

		#pragma region  ��ʼ��ȡ��ť
		rButton.left = 0; rButton.top = 0; rButton.right = 100; rButton.bottom = 30;
		RoundRect(hdc, rButton.left, rButton.top, rButton.right, rButton.bottom, 30, 30);
		StringCchPrintf(buff, 128, TEXT("�����ʼ��ȡ"));
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
	HMODULE mod = GetModuleHandle(TEXT("KeyboardHookDLL.dll"));   //��ȡ��ǰDLLģ����
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

	//��ȫ�ַ���
	TCHAR buff[128];
	size_t iTarget;

	//���ؽ��
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
			MessageBox(NULL, (LPCTSTR)(re == RE_NOPROCESS ? TEXT("���̲�����") : lpMsgBuf), TEXT("��ʾ"), MB_OK);
			if (!DeleteHook(g_hKeyboardHook))
			{
				MessageBox(NULL, TEXT("ж��ʧ��"), TEXT("ʧ��"), MB_OK);
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
	//��ȫ�ַ���
	TCHAR buff[128];
	size_t iTarget;

	#pragma region �ļ�EXE·�����DLL·��
	//TCHAR _szPath[MAX_PATH + 1] = { 0 };
	//GetModuleFileName(NULL, _szPath, MAX_PATH);
	//(_tcsrchr(_szPath, _T('\\')))[1] = 0;//ɾ���ļ�����ֻ���·�� �ִ�

	//const TCHAR *pNameDll = TEXT("LoveDll.dll");

	//int len_szPath = lstrlen(_szPath);
	//int len_pNameDll = lstrlen(pNameDll);
	//TCHAR* szBuff = new TCHAR[len_szPath + len_pNameDll + 1];
	//szBuff[0] = _T('\0');
	//lstrcat(szBuff, _szPath);
	//lstrcat(szBuff, pNameDll);
	//const TCHAR *pLocDll = szBuff;
	#pragma endregion

	#pragma region �ֶ�·��
	/*const TCHAR *pLocDll = TEXT("F:\\����\\��Ŀ\\����̨\\Love\\x64\\Release\\LoveDll.dll");
	const TCHAR *pNameDll = TEXT("LoveDll.dll");*/

	const TCHAR *pLocDll = TEXT("F:\\����\\��Ŀ\\����̨\\Love\\x64\\Release\\injectionDll.dll");
	const TCHAR *pNameDll = TEXT("injectionDll.dll");
	#pragma endregion

	HANDLE hThread = NULL;

	//��������
	DWORD ProcessID;
	GetWindowThreadProcessId(hwnd, &ProcessID);

	if (!ProcessID) {
		return RE_NOPROCESS;
	}
	else {
		//��ȡ����ID
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, ProcessID);
		//�ڼ��������ڴ�
		LPVOID strRmt = VirtualAllocEx(hProcess, nullptr, MAX_PATH, MEM_COMMIT, PAGE_READWRITE);
		//���ע��DLL��С
		size_t lenLocDll = 2 * _tcslen(pLocDll);
		//�жϼ��������ڴ��Ƿ�ɹ�
		if (strRmt) {
			//��DLLд������ڴ�
			BOOL ret = WriteProcessMemory(hProcess, strRmt, pLocDll, lenLocDll, nullptr);
			//���LoadLibraryW�ĺ�����ַ��ʹ��LoadLibrary����
			LPTHREAD_START_ROUTINE loadlib = LPTHREAD_START_ROUTINE(GetProcAddress(GetModuleHandle(TEXT("Kernel32")), "LoadLibraryW"));
			//ע��
			hThread = CreateRemoteThread(hProcess, nullptr, 0, loadlib, LPVOID(strRmt), 0, nullptr);
		}

		if (hThread == NULL)
		{
			return GetLastError();
		}

		WaitForSingleObject(hThread, INFINITE);
		//�������Ѿ����dll�ļ��ؼ�ע���ˣ�ͨ��dll����ִ������Ҫ��ɵ�����
		//�ͷ�
		VirtualFreeEx(hProcess, strRmt, 0, MEM_RELEASE);
		CloseHandle(hThread);
		CloseHandle(hProcess);
		return RE_SUCCESS;
	}
}