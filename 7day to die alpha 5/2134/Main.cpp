//**************************************************
//Cheat by IKOR
//параметры проекта 
//набор символов - использовать многобайтовую кодировку
//НЕ ЗАБУДЬТЕ при компиляции для 64 - битных систем 
//указать платформу x64 иначе 32 - битное приложение не может получить
//доступ к памяти 64 - битных приложений
//приложение НЕ КОНСОЛЬНОЕ, но есть возможность создать консоль см. функции
//*************************************************
#include <windows.h>
#include "classform.h"
#include "main.h"
#include <Commctrl.h>
#pragma comment(lib,"Comctl32.lib")

//глобальные переменные
bool hackVK=false;//это включение и выключение хака (Patch();)
#define FIRST_TIMER 1 //задает промежуток времени между выполнением кода
//HWND hStatusWindowG = NULL; //необходимо для изменения текста, т.к находится в разных функциях


//прототипы всех нужных функция
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
  //регистрируем наш класс
  LPCTSTR lpzClass = ("My Window Class!");
  //проверяем наш класс на регистрацию
  if (!RegMyWindowClass(hInstance, lpzClass))
    return 1;
    
    
  //вычисляем центр экрана пригодится
  RECT screen_rect;
  GetWindowRect(GetDesktopWindow(),&screen_rect); // разрешение экрана
  int x = screen_rect.right / 2 - 300;
  int y = screen_rect.bottom / 2 - 75;
  
  
  //создаемс окно
  HWND hWnd = CreateWindow(lpzClass, TEXT("Cheat 7Days To Die (alpha 5)"),
  WS_OVERLAPPEDWINDOW | WS_VISIBLE , x, y, 220, 200, NULL, NULL,
  hInstance, NULL);
  //если окно не создано завершаем программу
  if(!hWnd) return 2;
  hwndmessage = hWnd;

 //***************************************************
 //здесь создаем формы 
 //***************************************************
CreateForms(hWnd, hInstance);

//показать окно
ShowWindow(hWnd, nCmdShow);
//обновить содержимое окна
UpdateWindow(hWnd);
 
 
 mainLoad();
/* Теперь делаем цикл обработки сообщений
 Именно здесь происходит «вызов» функции окна */
  MSG msg = {0};    // структура сообщения
  int iGetOk = 0;   // переменная состояния
  int nTimerID =SetTimer(hWnd, FIRST_TIMER, 10, NULL); 

  while ((iGetOk = GetMessage(&msg, NULL, 0, 0 )) != 0) // цикл сообщений
  {
	if (iGetOk == -1) return 3;  // если GetMessage вернул ошибку - выход
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  KillTimer(hWnd, nTimerID ); 
  return msg.wParam;  // возвращаем код завершения программы
}


//теперь регистрируем класс окна
ATOM RegMyWindowClass(HINSTANCE hInst, LPCTSTR lpzClassName)
{
  WNDCLASS wcWindowClass = {0};
  // функция обработки сообщений
  wcWindowClass.lpfnWndProc = (WNDPROC)WndProc;
  // стиль окна
  wcWindowClass.style = CS_HREDRAW|CS_VREDRAW;
  // дескриптор экземпляра приложения
  wcWindowClass.hInstance = hInst;
  // название класса
  wcWindowClass.lpszClassName = lpzClassName;
  // загрузка курсора
  wcWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
  // загрузка цвета окон
  wcWindowClass.hbrBackground = (HBRUSH)COLOR_APPWORKSPACE;
  return RegisterClass(&wcWindowClass); // регистрация класса
}

//здесь обработка сообщений
//взаимодействие между юзером и пргой 
LRESULT CALLBACK WndProc(
  HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

  // выборка и обработка сообщений
  switch (message)
  {
  case WM_COMMAND:
	  ButtonClick( hWnd,  message,  wParam,  lParam);
	break;
  //*******************************
  //сюда вставляем обработку сообщений 
  //********************************
  case WM_KEYDOWN:
	keySwitch (wParam) ;


  case WM_DESTROY:
    PostQuitMessage(0);  // реакция на сообщение
	break;
  case WM_TIMER:
	TimeMain( hWnd,  message,  wParam,  lParam);
	break;
  default:
    // все сообщения не обработанные Вами обработает сама Windows
return DefWindowProc(hWnd, message, wParam, lParam);
  }

  return 0;
}

//********************************
//здесь создаем необходимые формы
//
//
//********************************
void CreateForms(HWND hWnd,HINSTANCE	hInstance)
{
	//создаем кнопку
	buttom[1].CreateWindowCl( "button", "Здоровье", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	2, 10, 100, 30, hWnd, (HMENU)0, hInstance, NULL);
	//создаем рамку с текстом
	textform[1].CreateWindowCl("Edit","выключено!" , WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
	buttom[1].cx+110,buttom[1].cy, 100, 30, hWnd,(HMENU)0, hInstance, NULL);
	buttom[1].Pfunc(Patch);
	/*
	сюда вставляем все кнопки и формы(копируем сверху изменяя положение)
	*/
	//**********************************
		//создаем кнопку
	
	buttom[0].CreateWindowCl( "button", "Сила", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	2, 10+30, 100, 30, hWnd, (HMENU)0, hInstance, NULL);
	//создаем рамку с текстом
	textform[0].CreateWindowCl("Edit","выключено!" , WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
	buttom[0].cx+110, buttom[0].cy, 100, 30, hWnd,(HMENU)0, hInstance, NULL);
	buttom[0].Pfunc(Patch);//передаем функцию для выполнения

		

	//**********************************
					  
	setSize( hWnd, 250/*ширину не трогать*/,160/*высота окна*/);
		//создаем статус строку
	mass[1].CreateWindowCl(STATUSCLASSNAME, "Ikor,Email:mr.ikor@mail.ru",
                                 WS_CHILD | WS_VISIBLE | WS_BORDER | SBARS_SIZEGRIP | CCS_BOTTOM,
                                 0, 0, 0, 0, hWnd, (HMENU)10000, hInstance, NULL);
}

//******************************************
//код выполняется через установленное время
//
//
//******************************************
void TimeMain(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{


	int tempn=buttom[0].countCl()/2;
  for (int i=0;i<tempn;i++){
	  if(buttom[i].HackVKL){
		  textform[i].TextEdit((LPARAM)"ВКЛЮЧЕНО");
		  buttom[i].func();
	  }
	  else textform[i].TextEdit((LPARAM)"выключено!");
  }
}

//*********************************
//код выполняется по нажатию кнопки
//
//
//*********************************
 void ButtonClick(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
 {
//перебираем все созданные обьекты/2
int tempn=buttom[0].countCl()/2;
for (int i=0;i<tempn;i++)
buttom[i].hackOn(wParam);//строчка отвечает за нажатие на кнопку(меняет флаг обьекта)

}


 //обработка нажатых клавиш
void keySwitch (WPARAM wParam)
{
switch (wParam){
case 27://esc
	break;

default:
	break;
}
}

//меняем размер окна
void setSize(HWND hWnd,int width, int height)
{
SetWindowPos(hWnd,HWND_TOPMOST  ,0,0,width,height,SWP_NOMOVE);

}