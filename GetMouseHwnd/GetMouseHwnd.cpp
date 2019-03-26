// SpyDemo.cpp : �������̨Ӧ�ó������ڵ㡣
#include <Windows.h>
#include <iostream>
using namespace std;
#define MAX_TEXT_LEN 255

BOOL CALLBACK EnumChildProcess(HWND hwnd, LPARAM lParam)
{
	if (hwnd == NULL) {
		return FALSE;
	}
	BOOL ret;
	RECT rect;
	ret = GetWindowRect(hwnd, &rect);
	if (!ret) {
		cout << "GetWindowRect hwnd=" << hwnd << " -> fail(" << GetLastError() << ")" << endl;
	}
	else {
		//printf("GetWindowRect hwnd = %p -> rect=(left=%ld, top=%ld, right=%ld, bottom=%ld)\n", hwnd, rect.left, rect.top, rect.right, rect.bottom);
		ret = PtInRect(&rect, *(POINT *)lParam);
		if (ret) {
			cout << "GetWindowRect hwnd = " << hwnd << " -> rect=(left=" << rect.left << ", top=" << rect.top << ", right=" << rect.right << ", bottom=" << rect.bottom << ")" << endl;
			//printf("PtInRect\n");

			/*
			WINUSERAPI int WINAPI GetWindowText(
			_In_ HWND hWnd,
			_Out_writes_(nMaxCount) LPTSTR lpString,    //�����Ǳ���������file:///��ͷ���ļ�����·��
			_In_ int nMaxCount
			);
			��������ɹ�������ֵ�ǿ������ַ������ַ��������������жϵĿ��ַ�����������ޱ��������ı����������Ϊ�գ��򴰿ڻ���Ƶľ����Ч���򷵻�ֵΪ�㡣�����ø��������Ϣ�������GetLastError������
			*/
			TCHAR windowText[MAX_TEXT_LEN];
			int lenRet = GetWindowText(hwnd, windowText, MAX_TEXT_LEN);
			if (lenRet == 0 && GetLastError() != 0) {
				//GetLastError()��0��-�����ɹ����
				printf("GetWindowText hwnd=%p -> fail(%ld)\n", hwnd, GetLastError());
			}
			else {
				cout << "GetWindowText hwnd="" -> windowText=%s, lenRet=%d\n"), , windowText, lenRet);
			}

			/*
			WINUSERAPI int WINAPI GetClassNameW(
			_In_ HWND hWnd,
			_Out_writes_to_(nMaxCount, return) LPWSTR lpClassName,
			_In_ int nMaxCount
			);

			��������ɹ�������ֵΪ������ָ�����������ַ��������������ʧ�ܣ�����ֵΪ0�������ø��������Ϣ�������GetLastError������
			*/
			TCHAR className[MAX_TEXT_LEN];
			lenRet = GetClassName(hwnd, className, MAX_TEXT_LEN);
			if (lenRet == 0) {
				printf("GetClassName hwnd=%p -> fail(%ld)\n", hwnd, GetLastError());
			}
			else {
				_tprintf(_T("GetClassName hwnd=%p -> className=%s, lenRet=%d\n"), hwnd, className, lenRet);
			}

			/*
			�ҳ�ĳ�����ڵĴ����ߣ��̻߳���̣������ش����ߵı�־��
			�ĸ��̴߳������������,���صľ�������̵߳�id�� ������ֻ��һ���̵߳Ļ�����ô�̱߳�־������̱�־������ָͬһ����־����
			WINUSERAPI DWORD WINAPI GetWindowThreadProcessId(
			_In_ HWND hWnd,
			_Out_opt_ LPDWORD lpdwProcessId //���̺ŵĴ�ŵ�ַ��������ַ��
			);
			�����̺߳�
			*/
			DWORD dwProcessId;
			DWORD dwThreadId = GetWindowThreadProcessId(hwnd, &dwProcessId);
			printf("GetWindowThreadProcessId hwnd=%p -> processId=%ld, threadId=%ld\n", hwnd, dwProcessId, dwThreadId);

			/*
			WINUSERAPI UINT WINAPI GetWindowModuleFileName(
			_In_ HWND hwnd,
			_Out_writes_to_(cchFileNameMax, return) LPTSTR pszFileName, //ģ������·��
			_In_ UINT cchFileNameMax
			);
			����ֵ�Ǹ��Ƶ����������ַ�������
			*/
			TCHAR fileName[MAX_PATH];
			lenRet = GetWindowModuleFileName(hwnd, fileName, MAX_PATH);
			if (lenRet == 0) {
				//�����롼126��-�Ҳ���ָ����ģ�顣
				printf("GetWindowModuleFileName hwnd=%p -> fail(%ld)\n", hwnd, GetLastError());
			}
			else {
				_tprintf(_T("GetWindowModuleFileName hwnd=%p -> fileName=%s\n"), hwnd, fileName);
			}

			/*
			WINUSERAPI BOOL WINAPI GetWindowInfo(
			_In_ HWND hwnd,
			_Inout_ PWINDOWINFO pwi
			);

			typedef struct tagWINDOWINFO
			{
			DWORD cbSize;
			RECT rcWindow;
			RECT rcClient;
			DWORD dwStyle;
			DWORD dwExStyle;
			DWORD dwWindowStatus;
			UINT cxWindowBorders;
			UINT cyWindowBorders;
			ATOM atomWindowType;
			WORD wCreatorVersion;
			} WINDOWINFO, *PWINDOWINFO, *LPWINDOWINFO;
			*/
			WINDOWINFO windowInfo;
			windowInfo.cbSize = sizeof(WINDOWINFO);
			ret = GetWindowInfo(hwnd, &windowInfo);
			if (!ret) {
				printf("GetWindowInfo hwnd=%p -> fail(%ld)\n", hwnd, GetLastError());
			}
			else {
				printf("GetWindowInfo hwnd=%p -> dwStyle=%ld, dwExStyle=%ld, dwWindowStatus=%ld, cxWindowBorders=%d, cyWindowBorders=%d, wCreatorVersion=%d\n", hwnd, windowInfo.dwStyle, windowInfo.dwExStyle, windowInfo.dwWindowStatus, windowInfo.cxWindowBorders, windowInfo.cyWindowBorders, windowInfo.wCreatorVersion);
			}
			printf("\n");
		}
	}

	return TRUE;
}

int main()
{
	BOOL ret;
	while (true) {
		/*
		typedef struct tagPOINT
		{
		LONG  x;
		LONG  y;
		} POINT, *PPOINT, NEAR *NPPOINT, FAR *LPPOINT;
		*/
		POINT point;
		ret = GetCursorPos(&point);
		if (!ret) {
			printf("GetCursorPos -> fail(%ld)\n", GetLastError());
		}
		else {
			printf("GetCursorPos -> (%ld, %ld)\n", point.x, point.y);

			//��ȡ������
			HWND desktopHwnd = GetDesktopWindow();

			/*
			BOOL EnumChildWindows(
			HWND hWndParent,         // handle to parent window // �����ھ��
			WNDENUMPROC lpEnumFunc,  // callback function // �ص������ĵ�ַ
			LPARAM lParam            // application-defined value // �����Ѷ���Ĳ���
			);
			ֱ�����õ����һ���Ӵ��ڱ�ö�ٻ�ص���������һ��false������һֱ�Զ�ö����ȥ��
			*/
			ret = EnumChildWindows(desktopHwnd, EnumChildProcess, (LPARAM)&point);
		}

		/*
		WINBASEAPI VOID WINAPI Sleep(
		_In_ DWORD dwMilliseconds
		);
		Sleep�Ὣ�̹߳��𣬰�CPU�ø������̣߳���λ�Ǻ���
		*/
		Sleep(20000);
	}

	system("pause");
	return 0;
}