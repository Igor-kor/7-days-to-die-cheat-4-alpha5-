//����� ������ ����� ��� �������� ����
#define COUNT_BUTTOM 10

class mainForm 
{
public:
HWND hWnd;
HMENU hMenu;
int cx;
int cy;
int cwidth;
int cheight;
LPCTSTR className;
LPCTSTR windowName;
bool HackVKL;
void (*func)(void);

//�������� ����
void CreateWindowCl(LPCTSTR lpClassName,LPCTSTR lpWindowName,DWORD dwStyle,
int x,int y,int nWidth,int nHeight,
HWND hWndParent,HMENU nhMenu,HINSTANCE hInstance,LPVOID lpParam)
{
	countCl(1);
	if(nhMenu==(HMENU)0)nhMenu=hMenu;
	//�� ��������� ����� ����� �� ������������!!!
hWnd = CreateWindow(lpClassName,lpWindowName,dwStyle,x,y,nWidth,nHeight,hWndParent,nhMenu,hInstance,lpParam);
 cx = x;
 cy = y;
 cwidth = nWidth;
 cheight = nHeight;
 hMenu = nhMenu;
}

//������ ����� ��������
void TextEdit(LPARAM TEXT)
{
	SendMessage(hWnd, WM_SETTEXT, NULL, TEXT);
}


//�����������
mainForm()
{
	
	HackVKL = false;
	static int ihMenu=10000;
	hWnd=NULL;
	hMenu=(HMENU)ihMenu;
	ihMenu++;
	cx=0;
	cy=0;
	cwidth=0;
	cheight=0;
}

//�������� ���
void hackOn( WPARAM wParam)
{
	 if(LOWORD(wParam) == LOWORD(hMenu))
		 HackVKL = !HackVKL ;
}

//�������� ��������� �� �������
void Pfunc(void(*fun1)(void)){
	func=fun1;
}

int countCl(int i=0)
{
return COUNT_BUTTOM;

}
//�����
}buttom[COUNT_BUTTOM],textform[COUNT_BUTTOM],mass[2];