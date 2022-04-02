//*****************************************
//
//���������� ��� ������ ����������
//<iostream> & <windows.h>
//
//*****************************************

#include <tlhelp32.h>
#include <Psapi.h>
#pragma comment(lib, "psapi.lib")

//******************************************
//
//��������� ������ ������ �� ��� �������� 
//� Pid ��������
//
//******************************************
LPVOID GetModuleBase(LPSTR lpModuleName, DWORD dwProcessId)
{
   MODULEENTRY32 lpModuleEntry = {0};
   HANDLE hSnapShot = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE|TH32CS_SNAPMODULE32, dwProcessId );
   if(hSnapShot == INVALID_HANDLE_VALUE){
	//   cout<<"ERROR";
      return NULL;
   }
   lpModuleEntry.dwSize = sizeof(lpModuleEntry);
   BOOL bModule = Module32First( hSnapShot, &lpModuleEntry );
   while(bModule)
   {
      if(!strcmp( lpModuleEntry.szModule, lpModuleName ) )
      {
         CloseHandle( hSnapShot );
         return lpModuleEntry.modBaseAddr;
      }
      bModule = Module32Next( hSnapShot, &lpModuleEntry );
   }
   CloseHandle( hSnapShot );
   return NULL;
}


//*******************************************
//
//���������� ���������
//���� �� ������������ �� �� ������� ����������
//
//*******************************************
BOOL DoRtlAdjustPrivilege()
{
/*
������ �������. �������� ���������� ���������.
������ ��� �������� ��� �������� ������ ����������
� ����������� ������.
*/
#define SE_DEBUG_PRIVILEGE 20L
#define AdjustCurrentProcess 0
BOOL bPrev = FALSE;
LONG (WINAPI *RtlAdjustPrivilege)(DWORD, BOOL, INT, PBOOL);
*(FARPROC *)&RtlAdjustPrivilege = GetProcAddress(GetModuleHandle("ntdll.dll"), "RtlAdjustPrivilege");
if(!RtlAdjustPrivilege) return FALSE;
RtlAdjustPrivilege(SE_DEBUG_PRIVILEGE, TRUE, AdjustCurrentProcess, &bPrev);
return TRUE;
}


//************************************************
//�������� ������ ������, ���������� �����������
//
//
//
//************************************************
DWORD GetMemorySize(HANDLE hProc)
{
	//��������� � ����������� � ��������
	PROCESS_MEMORY_COUNTERS pmcInfo;

	//�������� ���������� � ��������
	if (GetProcessMemoryInfo(hProc, &pmcInfo, sizeof(pmcInfo)))
		return (DWORD)pmcInfo.WorkingSetSize;
	else{
		GPMIe();
		return 0;
	}
}



/////**********************************************
////
////��������� �������� ������ ��������
////��� 32-������ � 64-������
////� ����� thelp ��� ����
////***********************************************
//�������� ������� ����� ��������
LPVOID GetBaseAddress32(HANDLE hProc)
{
	//��������� � ����������� � ��������
	MODULEINFO miInfo;

	//�������� ������� ����� ��������
	if (GetModuleInformation(hProc, NULL,0, sizeof(miInfo)))
		return miInfo.EntryPoint;
	else{
		GBA32();
		return NULL;
	}
}

LPVOID GetBaseAddress64(HANDLE hProc)
{
	//��������� � ����������� � ��������
	HMODULE miInfo[10];
	DWORD cbNeeded;
	//�������� ������� ����� ��������
	if (EnumProcessModulesEx(hProc, &miInfo[0],sizeof(miInfo),&cbNeeded,LIST_MODULES_ALL))
		return miInfo[0];
	else{
		GBA64();
		return NULL;
	}
}

// Gets the memory address where the base module was loaded.
unsigned __int64 GetBaseAddress(DWORD dwProcessID)
{
    unsigned __int64 dwAddress = NULL;
    HANDLE hthSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcessID);
    if (hthSnapshot!=INVALID_HANDLE_VALUE) 
    {
        MODULEENTRY32 me = { sizeof(me) };
        if (Module32First(hthSnapshot, &me))
        {
            CloseHandle(hthSnapshot);
            dwAddress = (unsigned __int64)me.modBaseAddr;
        }
    }
	else CTHS();
    return dwAddress;
}

//**********************************************************
//
//��� �������� ������ � ������ �������� �� �������� ����������
//���������� �������� �������� � ������
//������� ��� ������ � �������� ����������
//
//*******************************************

unsigned __int64 ukazatel_read(HANDLE process, unsigned __int64 Base,  unsigned __int64 Pp...)
{ 
unsigned __int64 *ukazatel = &Pp;
unsigned __int64 addres = Base;
unsigned __int64 temp=0;
cout<<"pppp:"<<hex<<addres<<dec<<endl;
//��������� �������� �� �������� ������	
ReadProcessMemory(process, (LPCVOID)(addres), &temp, sizeof(temp), NULL);

//���� ���� ����� ��� �� 
while (*ukazatel != 0 ){
	addres = temp + *ukazatel;
	cout<<"pppp:"<<hex<<addres<<dec<<endl;
	//��������� �������� �� n-�� ������, ������ � ������� ����������
	ReadProcessMemory(process, (LPCVOID)(addres), &temp, sizeof(temp), NULL);
ukazatel++;
}

return temp;
}


//*******************************************
//
//������� ��� ������ � �������� ����������
//
//*******************************************
unsigned __int64 ukazatel_write(HANDLE process,int write ,unsigned __int64 Base,  unsigned __int64 Pp...)
{ 
unsigned __int64 *ukazatel = &Pp;
unsigned __int64 addres = Base;
unsigned __int64 temp=0;
cout<<"pppp:"<<hex<<addres<<dec<<endl;
//��������� �������� �� �������� ������	
ReadProcessMemory(process, (LPCVOID)(addres), &temp, sizeof(4), NULL);

//���� ���� ����� ��� �� 
while (*ukazatel != 0 ){
	cout<<"ukaz:"<<temp<<"+"<<hex<<*ukazatel<<dec<<endl;
	addres = temp + *ukazatel;
	cout<<"pp4:"<<hex<<addres<<dec<<endl;
	//��������� �������� �� n-�� ������, ������ � ������� ����������
	ReadProcessMemory(process, (LPCVOID)(addres), &temp, sizeof(4), NULL);
ukazatel++;
}
WriteProcessMemory(process, (LPVOID)(addres), &write,  sizeof(4), NULL);
return 0;
}

//*******************************************************
//
//
//inject dll �������� ������ � 32-��������� ����������
//
//*******************************************************
int Inject(const DWORD pID, const char* dllName) 
{ 
        HANDLE pHandle;
        DWORD loadLibAddr;
        LPVOID rString;
        HANDLE hThread;

        if(!pID) 
                return 1;
        pHandle = OpenProcess(PROCESS_ALL_ACCESS, 0, pID);
        loadLibAddr = (DWORD)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA"); // get the LoadLibraryA() address from kernel32.dll
        rString = (LPVOID)VirtualAllocEx(pHandle, 0, strlen(dllName), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE); 
        WriteProcessMemory(pHandle, (LPVOID)rString, dllName, strlen(dllName), 0);
        hThread = CreateRemoteThread(pHandle, 0, 0, (LPTHREAD_START_ROUTINE)loadLibAddr, (LPVOID)rString, 0, 0);
        CloseHandle(pHandle); // close the opened handle 
        return 0; // everything is done, so quit
} 

bool InjectDll(DWORD pID, char* path)
{
HANDLE proc_handle;
LPVOID RemoteString;
LPVOID LoadLibAddy;
  if(pID == 0)
	  return false;
  proc_handle = OpenProcess(PROCESS_VM_READ|PROCESS_ALL_ACCESS|PROCESS_QUERY_INFORMATION|PROCESS_VM_WRITE|PROCESS_VM_OPERATION , false, pID);
  if(proc_handle == 0)
	  return false;
 
  //�������� ������ ��� �������� �����
  RemoteString = VirtualAllocEx(proc_handle,NULL,strlen(path),MEM_RESERVE | MEM_COMMIT,PAGE_READWRITE);
   cout<<"RemoteString"<<RemoteString<<endl;
  //���������� �������� �����
  if(WriteProcessMemory(proc_handle,RemoteString,path,strlen(path),NULL)==NULL)
	  cout<<"Error WriteMemoyr";
   //������� ����� �������
  LoadLibAddy = GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")),"LoadLibraryA");
  cout<<"LoadLibAddy"<<LoadLibAddy<<endl;
  if(CreateRemoteThread(proc_handle,NULL,0,(LPTHREAD_START_ROUTINE)LoadLibAddy,RemoteString,NULL,NULL)==NULL)
	  cout<<"Error CreateRemote...\n";
  CloseHandle(proc_handle);
  return true;
}


bool FileExist(char* name){

	return _access(name,0) != -1;
}

void EnableDebugPriv()
{
HANDLE hToken;
LUID sedebugnameValue;
TOKEN_PRIVILEGES tkp;
if ( ! OpenProcessToken( GetCurrentProcess(),
  TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken ) )
  return;
if ( ! LookupPrivilegeValue( NULL, SE_DEBUG_NAME, &sedebugnameValue ) ){
  CloseHandle( hToken );
  return;
}
tkp.PrivilegeCount = 1;
tkp.Privileges[0].Luid = sedebugnameValue;
tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
if ( ! AdjustTokenPrivileges( hToken, FALSE, &tkp, sizeof tkp, NULL, NULL ) )
  CloseHandle( hToken );
}