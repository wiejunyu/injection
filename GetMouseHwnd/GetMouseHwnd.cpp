// SpyDemo.cpp : 定义控制台应用程序的入口点。
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
			_Out_writes_(nMaxCount) LPTSTR lpString,    //可能是标题名或者file:///打头的文件完整路径
			_In_ int nMaxCount
			);
			如果函数成功，返回值是拷贝的字符串的字符个数，不包括中断的空字符；如果窗口无标题栏或文本，或标题栏为空，或窗口或控制的句柄无效，则返回值为零。若想获得更多错误信息，请调用GetLastError函数。
			*/
			TCHAR windowText[MAX_TEXT_LEN];
			int lenRet = GetWindowText(hwnd, windowText, MAX_TEXT_LEN);
			if (lenRet == 0 && GetLastError() != 0) {
				//GetLastError()〖0〗-操作成功完成
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

			如果函数成功，返回值为拷贝到指定缓冲区的字符个数：如果函数失败，返回值为0。若想获得更多错误信息，请调用GetLastError函数。
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
			printf("GetWindowThreadProcessId hwnd=%p -> processId=%ld, threadId=%ld\n", hwnd, dwProcessId, dwThreadId);

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

			//获取桌面句柄
			HWND desktopHwnd = GetDesktopWindow();

			/*
			BOOL EnumChildWindows(
			HWND hWndParent,         // handle to parent window // 父窗口句柄
			WNDENUMPROC lpEnumFunc,  // callback function // 回调函数的地址
			LPARAM lParam            // application-defined value // 你自已定义的参数
			);
			直到调用到最个一个子窗口被枚举或回调函数返回一个false，否则将一直自动枚举下去。
			*/
			ret = EnumChildWindows(desktopHwnd, EnumChildProcess, (LPARAM)&point);
		}

		/*
		WINBASEAPI VOID WINAPI Sleep(
		_In_ DWORD dwMilliseconds
		);
		Sleep会将线程挂起，把CPU让给其它线程，单位是毫秒
		*/
		Sleep(20000);
	}

	system("pause");
	return 0;
}