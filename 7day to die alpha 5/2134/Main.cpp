//**************************************************
//Cheat by IKOR
//��������� ������� 
//����� �������� - ������������ ������������� ���������
//�� �������� ��� ���������� ��� 64 - ������ ������ 
//������� ��������� x64 ����� 32 - ������ ���������� �� ����� ��������
//������ � ������ 64 - ������ ����������
//���������� �� ����������, �� ���� ����������� ������� ������� ��. �������
//*************************************************
#include <windows.h>
#include "classform.h"
#include "main.h"
#include <Commctrl.h>
#pragma comment(lib,"Comctl32.lib")

//���������� ����������
bool hackVK=false;//��� ��������� � ���������� ���� (Patch();)
#define FIRST_TIMER 1 //������ ���������� ������� ����� ����������� ����
//HWND hStatusWindowG = NULL; //���������� ��� ��������� ������, �.� ��������� � ������ ��������


//��������� ���� ������ �������
void setSize(HWND hWnd,int width, int height);
void keySwitch (WPARAM wParam);
void ButtonClick(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void TimeMain(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void CreateForms(HWND hWnd,HINSTANCE	hInstance);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM RegMyWindowClass(HINSTANCE, LPCTSTR);



int WINAPI WinMain(HINSTANCE	hInstance,
                   HINSTANCE	hPrevInstance,
                   LPSTR	lpCmdLine,
                   int	        nCmdShow)
{               
  //������������ ��� �����
  LPCTSTR lpzClass = ("My Window Class!");
  //��������� ��� ����� �� �����������
  if (!RegMyWindowClass(hInstance, lpzClass))
    return 1;
    
    
  //��������� ����� ������ ����������
  RECT screen_rect;
  GetWindowRect(GetDesktopWindow(),&screen_rect); // ���������� ������
  int x = screen_rect.right / 2 - 300;
  int y = screen_rect.bottom / 2 - 75;
  
  
  //�������� ����
  HWND hWnd = CreateWindow(lpzClass, TEXT("Cheat 7Days To Die (alpha 5)"),
  WS_OVERLAPPEDWINDOW | WS_VISIBLE , x, y, 220, 200, NULL, NULL,
  hInstance, NULL);
  //���� ���� �� ������� ��������� ���������
  if(!hWnd) return 2;
  hwndmessage = hWnd;

 //***************************************************
 //����� ������� ����� 
 //***************************************************
CreateForms(hWnd, hInstance);

//�������� ����
ShowWindow(hWnd, nCmdShow);
//�������� ���������� ����
UpdateWindow(hWnd);
 
 
 mainLoad();
/* ������ ������ ���� ��������� ���������
 ������ ����� ���������� ������ ������� ���� */
  MSG msg = {0};    // ��������� ���������
  int iGetOk = 0;   // ���������� ���������
  int nTimerID =SetTimer(hWnd, FIRST_TIMER, 10, NULL); 

  while ((iGetOk = GetMessage(&msg, NULL, 0, 0 )) != 0) // ���� ���������
  {
	if (iGetOk == -1) return 3;  // ���� GetMessage ������ ������ - �����
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  KillTimer(hWnd, nTimerID ); 
  return msg.wParam;  // ���������� ��� ���������� ���������
}


//������ ������������ ����� ����
ATOM RegMyWindowClass(HINSTANCE hInst, LPCTSTR lpzClassName)
{
  WNDCLASS wcWindowClass = {0};
  // ������� ��������� ���������
  wcWindowClass.lpfnWndProc = (WNDPROC)WndProc;
  // ����� ����
  wcWindowClass.style = CS_HREDRAW|CS_VREDRAW;
  // ���������� ���������� ����������
  wcWindowClass.hInstance = hInst;
  // �������� ������
  wcWindowClass.lpszClassName = lpzClassName;
  // �������� �������
  wcWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
  // �������� ����� ����
  wcWindowClass.hbrBackground = (HBRUSH)COLOR_APPWORKSPACE;
  return RegisterClass(&wcWindowClass); // ����������� ������
}

//����� ��������� ���������
//�������������� ����� ������ � ����� 
LRESULT CALLBACK WndProc(
  HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

  // ������� � ��������� ���������
  switch (message)
  {
  case WM_COMMAND:
	  ButtonClick( hWnd,  message,  wParam,  lParam);
	break;
  //*******************************
  //���� ��������� ��������� ��������� 
  //********************************
  case WM_KEYDOWN:
	keySwitch (wParam) ;


  case WM_DESTROY:
    PostQuitMessage(0);  // ������� �� ���������
	break;
  case WM_TIMER:
	TimeMain( hWnd,  message,  wParam,  lParam);
	break;
  default:
    // ��� ��������� �� ������������ ���� ���������� ���� Windows
return DefWindowProc(hWnd, message, wParam, lParam);
  }

  return 0;
}

//********************************
//����� ������� ����������� �����
//
//
//********************************
void CreateForms(HWND hWnd,HINSTANCE	hInstance)
{
	//������� ������
	buttom[1].CreateWindowCl( "button", "��������", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	2, 10, 100, 30, hWnd, (HMENU)0, hInstance, NULL);
	//������� ����� � �������
	textform[1].CreateWindowCl("Edit","���������!" , WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
	buttom[1].cx+110,buttom[1].cy, 100, 30, hWnd,(HMENU)0, hInstance, NULL);
	buttom[1].Pfunc(Patch);
	/*
	���� ��������� ��� ������ � �����(�������� ������ ������� ���������)
	*/
	//**********************************
		//������� ������
	
	buttom[0].CreateWindowCl( "button", "����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	2, 10+30, 100, 30, hWnd, (HMENU)0, hInstance, NULL);
	//������� ����� � �������
	textform[0].CreateWindowCl("Edit","���������!" , WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
	buttom[0].cx+110, buttom[0].cy, 100, 30, hWnd,(HMENU)0, hInstance, NULL);
	buttom[0].Pfunc(Patch);//�������� ������� ��� ����������

		

	//**********************************
					  
	setSize( hWnd, 250/*������ �� �������*/,160/*������ ����*/);
		//������� ������ ������
	mass[1].CreateWindowCl(STATUSCLASSNAME, "Ikor,Email:mr.ikor@mail.ru",
                                 WS_CHILD | WS_VISIBLE | WS_BORDER | SBARS_SIZEGRIP | CCS_BOTTOM,
                                 0, 0, 0, 0, hWnd, (HMENU)10000, hInstance, NULL);
}

//******************************************
//��� ����������� ����� ������������� �����
//
//
//******************************************
void TimeMain(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{


	int tempn=buttom[0].countCl()/2;
  for (int i=0;i<tempn;i++){
	  if(buttom[i].HackVKL){
		  textform[i].TextEdit((LPARAM)"��������");
		  buttom[i].func();
	  }
	  else textform[i].TextEdit((LPARAM)"���������!");
  }
}

//*********************************
//��� ����������� �� ������� ������
//
//
//*********************************
 void ButtonClick(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
 {
//���������� ��� ��������� �������/2
int tempn=buttom[0].countCl()/2;
for (int i=0;i<tempn;i++)
buttom[i].hackOn(wParam);//������� �������� �� ������� �� ������(������ ���� �������)

}


 //��������� ������� ������
void keySwitch (WPARAM wParam)
{
switch (wParam){
case 27://esc
	break;

default:
	break;
}
}

//������ ������ ����
void setSize(HWND hWnd,int width, int height)
{
SetWindowPos(hWnd,HWND_TOPMOST  ,0,0,width,height,SWP_NOMOVE);

}