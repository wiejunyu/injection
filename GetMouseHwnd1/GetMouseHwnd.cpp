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

			//如果函数成功，返回值为拷贝到指定缓冲区的字符个数：如果函数失败，返回值为0。若想获得更多错误信息，请调用GetLastError函数。

			TCHAR className[MAX_TEXT_LEN];
			lenRet = GetClassName(hwnd, className, MAX_TEXT_LEN);
			if (lenRet == 0) {
				cout << "GetClassName hwnd=" << hwnd << " -> fail(" << GetLastError() << ")" << endl;
			}
			else {
				cout << "GetClassName hwnd=" << hwnd << " -> className=" << className << ", lenRet=" << lenRet << endl;
			}

			/*
			找出某个窗口的创建者（线程或进程），返回创建者的标志符
			哪个线程创建了这个窗口,返回的就是这个线程的id号 （进程只有一个线程的话，那么线程标志符与进程标志符就是指同一个标志符）
			WINUSERAPI DWORD WINAPI GetWindowThreadProcessId(
			_In_ HWND hWnd,
			_Out_opt_ LPDWORD lpdwProcessId //进程号的存放地址（变量地址）
			);
			返回线程号
			*/
			DWORD dwProcessId;
			DWORD dwThreadId = GetWindowThreadProcessId(hwnd, &dwProcessId);
			cout << "GetWindowThreadProcessId hwnd=" << hwnd << " -> processId=" << dwProcessId << ", threadId=" << dwThreadId << endl;
			/*
			WINUSERAPI UINT WINAPI GetWindowModuleFileName(
			_In_ HWND hwnd,
			_Out_writes_to_(cchFileNameMax, return) LPTSTR pszFileName, //模块完整路径
			_In_ UINT cchFileNameMax
			);
			返回值是复制到缓冲区的字符总数。
			*/
			TCHAR fileName[MAX_PATH];
			lenRet = GetWindowModuleFileName(hwnd, fileName, MAX_PATH);
			if (lenRet == 0) {
				//错误码〖126〗-找不到指定的模块。
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

			//获取桌面句柄sd
			HWND desktopHwnd = GetDesktopWindow();
			ret = EnumChildWindows(desktopHwnd, EnumChildProcess, (LPARAM)&point);
		}

		/*
		Sleep会将线程挂起，把CPU让给其它线程，单位是毫秒
		*/
		Sleep(20000);
	}

	system("pause");
	return 0;
}