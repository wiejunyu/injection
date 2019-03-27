#include "stdafx.h"
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
		ret = PtInRect(&rect, *(POINT *)lParam);
		if (ret) {
			cout << "GetWindowRect hwnd = " << hwnd << " -> rect=(left=" << rect.left << ", top=" << rect.top << ", right=" << rect.right << ", bottom=" << rect.bottom << ")" << endl;

			TCHAR windowText[MAX_TEXT_LEN];
			int lenRet = GetWindowText(hwnd, windowText, MAX_TEXT_LEN);
			if (lenRet == 0 && GetLastError() != 0) {
				cout << "GetWindowText hwnd=" << hwnd << " -> fail(" << GetLastError() << ")" << endl;
			}
			else {
				cout << "GetWindowText hwnd=" << hwnd << " -> windowText=" << windowText << ", lenRet=" << lenRet << endl;
			}

			//��������ɹ�������ֵΪ������ָ�����������ַ��������������ʧ�ܣ�����ֵΪ0�������ø��������Ϣ�������GetLastError������

			TCHAR className[MAX_TEXT_LEN];
			lenRet = GetClassName(hwnd, className, MAX_TEXT_LEN);
			if (lenRet == 0) {
				cout << "GetClassName hwnd=" << hwnd << " -> fail(" << GetLastError() << ")" << endl;
			}
			else {
				cout << "GetClassName hwnd=" << hwnd << " -> className=" << className << ", lenRet=" << lenRet << endl;
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
			cout << "GetWindowThreadProcessId hwnd=" << hwnd << " -> processId=" << dwProcessId << ", threadId=" << dwThreadId << endl;
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
				cout << "GetWindowModuleFileName hwnd=" << hwnd << " -> fail(" << GetLastError() << ")" << endl;
			}
			else {
				cout << "GetWindowModuleFileName hwnd=" << hwnd << " -> fileName=" << fileName << endl;
			}
			WINDOWINFO windowInfo;
			windowInfo.cbSize = sizeof(WINDOWINFO);
			ret = GetWindowInfo(hwnd, &windowInfo);
			if (!ret) {
				cout << "GetWindowInfo hwnd=" << hwnd << " -> fail(" << GetLastError() << endl;
			}
			else {
				cout << "GetWindowInfo hwnd=" << hwnd << " -> dwStyle=" << windowInfo.dwStyle << ", dwExStyle=" << windowInfo.dwExStyle << ", dwWindowStatus=" << windowInfo.dwWindowStatus << ", cxWindowBorders=" << windowInfo.cxWindowBorders << ", cyWindowBorders=" << windowInfo.cyWindowBorders << ", wCreatorVersion=" << windowInfo.wCreatorVersion << endl;
			}
			cout << endl;
		}
	}
	return TRUE;
}

int main()
{
	bool ret;
	while (true) {
		POINT point;
		ret = GetCursorPos(&point);
		if (!ret) {
			cout << "GetCursorPos -> fail(" << GetLastError() << ")" << endl;
		}
		else {
			cout << "GetCursorPos -> (" << point.x << ", " << point.y << ")" << endl;

			//��ȡ������sd
			HWND desktopHwnd = GetDesktopWindow();
			ret = EnumChildWindows(desktopHwnd, EnumChildProcess, (LPARAM)&point);
		}

		/*
		Sleep�Ὣ�̹߳��𣬰�CPU�ø������̣߳���λ�Ǻ���
		*/
		Sleep(20000);
	}

	system("pause");
	return 0;
}