
#include "dialog.h"
#include <iostream>
using namespace std;
#include "function.h"
//��� ���������� ��� ��������� �������
#include <fcntl.h>
#include <io.h>

//���������
void CreateConsole();

//************************************
//
//������� ���������� ����� �������� ��������� 
//����, ���� ����������� ��� ��� ���� ���������
//��� ������� ���������
//************************************
void mainLoad()
{
	//������� ���������� ���������	
	if(!DoRtlAdjustPrivilege())StartDB();
	//�������� ������� ��� �������
	 //CreateConsole();
}


//***************************************
//��� ��� ��������� �����
//������� ������� � ������� �����������
//����� � ������ ��������, ���������� �� �������
//� �������� �� �������� �� ���������� (������� �� hackVK)
//***************************************
void Patch(){
	
HWND hWnd = NULL; // ��������� ���� ������� ��������                                    
DWORD pid = 0;   // ����� �������� � ������

	if(FindWindow(NULL, "7 Days To Die"))      // ��������� ������� ���� � ���������� Game
    {
		HANDLE process = NULL;       
		hWnd =  FindWindowA(NULL, "7 Days To Die");
		GetWindowThreadProcessId(hWnd,&pid); // ���������� ����� � ���������� pid

		if (process == NULL && pid != 0) 
			process = OpenProcess( PROCESS_VM_READ|PROCESS_ALL_ACCESS|PROCESS_QUERY_INFORMATION ,
									false, pid);
		cout<<"base address:"<<GetBaseAddress64(process)<<endl
		<<"address size: 0x"<<hex<< GetMemorySize(process)<<dec<<endl;

		//����� ����� ��� �� ��� ����������� � Cheat Engine
		//��� ���������� ������

		//**************************************
		//�����
		//**************************************
		if(buttom[1].HackVKL){
		cout<<"Health:"<<ukazatel_read(process,(unsigned __int64)GetBaseAddress(pid) + 0x00BE4318,
			(unsigned __int64)0x510,(unsigned __int64)0x90,(unsigned __int64)0x30,(unsigned __int64)0x2F8,0)<<endl;
		// ���������� � ���� ��������
		ukazatel_write(process,300,(unsigned __int64)GetBaseAddress(pid) + 0x00BE4318,
			(unsigned __int64)0x510,(unsigned __int64)0x90,(unsigned __int64)0x30,(unsigned __int64)0x2F8,0);
		}
		//*******************************
		//����
		//*******************************	
		if(buttom[0].HackVKL){
		cout<<"Sila:"<<ukazatel_read(process,(unsigned __int64)GetBaseAddress(pid) + 0x00BE4328,
			(unsigned __int64)0x418,(unsigned __int64)0x90,(unsigned __int64)0x30,(unsigned __int64)0x370,0)<<endl;
		// ���������� � ���� ��������
		ukazatel_write(process,100,(unsigned __int64)GetBaseAddress(pid) + 0x00BE4328,
			(unsigned __int64)0x418,(unsigned __int64)0x90,(unsigned __int64)0x30,(unsigned __int64)0x370,0);
		}
		
		//��������� Handle ������� �������	   
		CloseHandle( process );
	}
}


//****************************************
//
//������� �������� ����������� ����
//��:���������� ��� �������
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