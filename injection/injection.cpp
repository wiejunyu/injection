#include "stdafx.h";

HANDLE hThread = NULL;
//进程名称查找进程ID
DWORD ProcessFind(LPCTSTR Exename) //进程名称
{
    HANDLE hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (!hProcess)
    {
        return FALSE;
    }
    PROCESSENTRY32 info;
    info.dwSize = sizeof(PROCESSENTRY32);
    if (!Process32First(hProcess, &info))
    {
        return FALSE;
    }
    while (TRUE)
    {
        cout << endl;
        if (_tcscmp(info.szExeFile, Exename) == 0)
        {
            return info.th32ProcessID;//返回进程的ID
        }
        if (!Process32Next(hProcess, &info))
        {
            return FALSE;
        }
    }
    return FALSE;

}

int dll_inject() {
    //Dll文件地址,改成你自己的地址
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

	const TCHAR *pLocDll = TEXT("F:\\工作\\项目\\控制台\\Love\\x64\\Release\\LoveDll.dll");
	const TCHAR *pNameDll = TEXT("LoveDll.dll");
    HANDLE hThread = NULL;

    //记事本进程名称
    DWORD ProcessID = ProcessFind(TEXT("WINWORD.EXE"));
    if (!ProcessID) {
        cout << "查找不到当前程序" << endl;
    }
    else {
        //获取进程ID
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, ProcessID);

        //获取dll大小
        SIZE_T PathSize = (_tcslen(pNameDll) + 1) * sizeof(TCHAR);

        //申请内存
        LPVOID StartAddress = VirtualAllocEx(hProcess, NULL, PathSize, MEM_COMMIT, PAGE_READWRITE);

        //写入内存
        bool bSuccess = WriteProcessMemory(hProcess, StartAddress, pNameDll, PathSize, 0);
        if (!bSuccess)
        {
            cout << "写入失败" << endl;
        }
        else {
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
            
            /*
            HANDLE hThread = CreateRemoteThread(hProcess, 0, 0, (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(_T("kernel32.dll")), "LoadLibrary"), StartAddress, 0, 0);*/

            if (hThread == NULL)
            {
                cout << "在进程中注入失败:";
                cout << GetLastError() << endl;
                return -1;
            }

            WaitForSingleObject(hThread, INFINITE);
            //到这里已经完成dll的加载即注入了，通过dll函数执行我们要完成的任务
            //释放
            VirtualFreeEx(hProcess, StartAddress,0, MEM_RELEASE);
            CloseHandle(hThread);
            CloseHandle(hProcess);
        }
    }
}
int main()
{
    dll_inject();
}
