#include "stdafx.h";

HANDLE hThread = NULL;
//�������Ʋ��ҽ���ID
DWORD ProcessFind(LPCTSTR Exename) //��������
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
            return info.th32ProcessID;//���ؽ��̵�ID
        }
        if (!Process32Next(hProcess, &info))
        {
            return FALSE;
        }
    }
    return FALSE;

}

int dll_inject() {
    //Dll�ļ���ַ,�ĳ����Լ��ĵ�ַ
    const TCHAR *pLocDll = TEXT("F:\\����\\��Ŀ\\����̨\\injection\\injection\\x64\\Release\\injectionDll.dll");

    HANDLE hThread = NULL;

    //���±���������
    DWORD ProcessID = ProcessFind(TEXT("notepad.exe"));
    if (!ProcessID) {
        cout << "���Ҳ�����ǰ����" << endl;
    }
    else {
        //��ȡ����ID
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, ProcessID);

        //��ȡdll��С
        SIZE_T PathSize = (_tcslen(TEXT("injectionDll.dll")) + 1) * sizeof(TCHAR);

        //�����ڴ�
        LPVOID StartAddress = VirtualAllocEx(hProcess, NULL, PathSize, MEM_COMMIT, PAGE_READWRITE);

        //д���ڴ�
        bool bSuccess = WriteProcessMemory(hProcess, StartAddress, TEXT("injectionDll.dll"), PathSize, 0);
        if (!bSuccess)
        {
            cout << "д��ʧ��" << endl;
        }
        else {
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
            
            /*
            HANDLE hThread = CreateRemoteThread(hProcess, 0, 0, (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(_T("kernel32.dll")), "LoadLibrary"), StartAddress, 0, 0);*/

            if (hThread == NULL)
            {
                cout << "�ڽ�����ע��ʧ��:";
                cout << GetLastError() << endl;
                return -1;
            }

            WaitForSingleObject(hThread, INFINITE);
            //�������Ѿ����dll�ļ��ؼ�ע���ˣ�ͨ��dll����ִ������Ҫ��ɵ�����
            //�ͷ�
            VirtualFreeEx(hProcess, StartAddress,0, MEM_RELEASE);
            CloseHandle(hThread);
            CloseHandle(hProcess);
        }
    }
}
int main()
{
    dll_inject();
    system("pause");
}
