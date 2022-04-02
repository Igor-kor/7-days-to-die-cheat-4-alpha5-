
#include "dialog.h"
#include <iostream>
using namespace std;
#include "function.h"
//это необходимо для созданной консоли
#include <fcntl.h>
#include <io.h>

//прототипы
void CreateConsole();

//************************************
//
//функция вызывается после создания основного 
//окна, сюда прописываем все что надо загрузить
//при запуске программы
//************************************
void mainLoad()
{
	//получим привелегии дебаггера	
	if(!DoRtlAdjustPrivilege())StartDB();
	//создание консоли для отладки
	 //CreateConsole();
}


//***************************************
//Сам хак находится здесь
//главная функция в которой выполняется
//поиск и замена значений, вызывается по таймеру
//и работает не зависимо от интерфейса (зависит от hackVK)
//***************************************
void Patch(){
	
HWND hWnd = NULL; // заголовок окна нужного процесса                                    
DWORD pid = 0;   // номер процесса в списке

	if(FindWindow(NULL, "7 Days To Die"))      // проверяем наличие окна с заголовком Game
    {
		HANDLE process = NULL;       
		hWnd =  FindWindowA(NULL, "7 Days To Die");
		GetWindowThreadProcessId(hWnd,&pid); // запоминаем номер в переменную pid

		if (process == NULL && pid != 0) 
			process = OpenProcess( PROCESS_VM_READ|PROCESS_ALL_ACCESS|PROCESS_QUERY_INFORMATION ,
									false, pid);
		cout<<"base address:"<<GetBaseAddress64(process)<<endl
		<<"address size: 0x"<<hex<< GetMemorySize(process)<<dec<<endl;

		//здесь пишем все то что проделывали в Cheat Engine
		//для нахождения адреса

		//**************************************
		//жизнь
		//**************************************
		if(buttom[1].HackVKL){
		cout<<"Health:"<<ukazatel_read(process,(unsigned __int64)GetBaseAddress(pid) + 0x00BE4318,
			(unsigned __int64)0x510,(unsigned __int64)0x90,(unsigned __int64)0x30,(unsigned __int64)0x2F8,0)<<endl;
		// записываем в него значение
		ukazatel_write(process,300,(unsigned __int64)GetBaseAddress(pid) + 0x00BE4318,
			(unsigned __int64)0x510,(unsigned __int64)0x90,(unsigned __int64)0x30,(unsigned __int64)0x2F8,0);
		}
		//*******************************
		//сила
		//*******************************	
		if(buttom[0].HackVKL){
		cout<<"Sila:"<<ukazatel_read(process,(unsigned __int64)GetBaseAddress(pid) + 0x00BE4328,
			(unsigned __int64)0x418,(unsigned __int64)0x90,(unsigned __int64)0x30,(unsigned __int64)0x370,0)<<endl;
		// записываем в него значение
		ukazatel_write(process,100,(unsigned __int64)GetBaseAddress(pid) + 0x00BE4328,
			(unsigned __int64)0x418,(unsigned __int64)0x90,(unsigned __int64)0x30,(unsigned __int64)0x370,0);
		}
		
		//закрываем Handle который открыли	   
		CloseHandle( process );
	}
}


//****************************************
//
//функция создания консольного окна
//ЗЫ:необходимо для отладки
//****************************************
void CreateConsole()
{
	if (AllocConsole()) 
		{ 
		int hCrt = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), 4); 
		*stdout = *(::_fdopen(hCrt, "w")); 
		::setvbuf(stdout, NULL, _IONBF, 0); 
		*stderr = *(::_fdopen(hCrt, "w")); 
		::setvbuf(stderr, NULL, _IONBF, 0);
		std::ios::sync_with_stdio();
	}
}