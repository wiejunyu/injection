//�������ȡ������
#include <windows.h>;
#include <windowsx.h>;
#include <strsafe.h>;
#define WM_MYMBUTTONDOWN INT_MAX
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HHOOK SetHook();
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);
BOOL DeleteHook(HHOOK hook);

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
	case WM_MYMBUTTONDOWN:
		MessageBox(hwnd, TEXT("����˴�������"), TEXT("��ʾ��"), MB_OK);
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
			hdc = GetDC(hMyHwnd);
			TextOut(hdc, 130, 0, buff, iTarget);
			ReleaseDC(hMyHwnd, hdc);
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
