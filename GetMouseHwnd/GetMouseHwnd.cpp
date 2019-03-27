//�������ק�����Σ��ſ��滭
//����϶���״
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
		MessageBox(hwnd,TEXT("����˴�������"), TEXT("��ʾ��"),MB_OK);
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
	HMODULE mod = GetModuleHandle(TEXT("KeyboardHookDLL.dll"));   //��ȡ��ǰDLLģ����
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
