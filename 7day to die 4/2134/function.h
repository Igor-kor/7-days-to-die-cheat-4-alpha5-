//*****************************************
//
//необходимо для работы подключить
//<iostream> & <windows.h>
//
//*****************************************

#include <tlhelp32.h>
#include <Psapi.h>
#pragma comment(lib, "psapi.lib")

//******************************************
//
//получение адреса модуля по его названию 
//и Pid процесса
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
//привелегии дебаггера
//пока не используется но на будущее пригодится
//
//*******************************************
BOOL DoRtlAdjustPrivilege()
{
/*
Важная функция. Получаем привилегии дебаггера.
Именно это позволит нам получить нужную информацию
о доступности памяти.
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
//получить размер памяти, занимаемой приложением
//
//
//
//************************************************
DWORD GetMemorySize(HANDLE hProc)
{
	//структура с информацией о процессе
	PROCESS_MEMORY_COUNTERS pmcInfo;

	//получаем информацию о процессе
	if (GetProcessMemoryInfo(hProc, &pmcInfo, sizeof(pmcInfo)))
		return (DWORD)pmcInfo.WorkingSetSize;
	else{
		GPMIe();
		return 0;
	}
}



/////**********************************************
////
////получение базового адреса процесса
////для 32-битных и 64-битных
////и через thelp для всех
////***********************************************
//получить базовый адрес процесса
LPVOID GetBaseAddress32(HANDLE hProc)
{
	//структура с информацией о процессе
	MODULEINFO miInfo;

	//получаем базовый адрес процесса
	if (GetModuleInformation(hProc, NULL,0, sizeof(miInfo)))
		return miInfo.EntryPoint;
	else{
		GBA32();
		return NULL;
	}
}

LPVOID GetBaseAddress64(HANDLE hProc)
{
	//структура с информацией о процессе
	HMODULE miInfo[10];
	DWORD cbNeeded;
	//получаем базовый адрес процесса
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
//для быстрого чтения и записи значений по найденым указателям
//возвращает значение считаное с адреса
//функция для работы с цепочкой указателей
//
//*******************************************

unsigned __int64 ukazatel_read(HANDLE process, unsigned __int64 Base,  unsigned __int64 Pp...)
{ 
unsigned __int64 *ukazatel = &Pp;
unsigned __int64 addres = Base;
unsigned __int64 temp=0;
cout<<"pppp:"<<hex<<addres<<dec<<endl;
//считываем значение по главному адресу	
ReadProcessMemory(process, (LPCVOID)(addres), &temp, sizeof(temp), NULL);

//если есть чтото еще то 
while (*ukazatel != 0 ){
	addres = temp + *ukazatel;
	cout<<"pppp:"<<hex<<addres<<dec<<endl;
	//считываем значение по n-му адресу, плюсуя к первому результату
	ReadProcessMemory(process, (LPCVOID)(addres), &temp, sizeof(temp), NULL);
ukazatel++;
}

return temp;
}


//*******************************************
//
//функция для работы с цепочкой указателей
//
//*******************************************
unsigned __int64 ukazatel_write(HANDLE process,int write ,unsigned __int64 Base,  unsigned __int64 Pp...)
{ 
unsigned __int64 *ukazatel = &Pp;
unsigned __int64 addres = Base;
unsigned __int64 temp=0;
cout<<"pppp:"<<hex<<addres<<dec<<endl;
//считываем значение по главному адресу	
ReadProcessMemory(process, (LPCVOID)(addres), &temp, sizeof(temp), NULL);

//если есть чтото еще то 
while (*ukazatel != 0 ){
	addres = temp + *ukazatel;
	cout<<"pppp:"<<hex<<addres<<dec<<endl;
	//считываем значение по n-му адресу, плюсуя к первому результату
	ReadProcessMemory(process, (LPCVOID)(addres), &temp, sizeof(temp), NULL);
ukazatel++;
}
WriteProcessMemory(process, (LPVOID)(addres), &write,  sizeof(write), NULL);
return 0;
}