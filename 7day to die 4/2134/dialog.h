//**************************************
//����� ������ MessageBox-� ��� ���� ���� �� 
//������ ������� �� ������ ������ ����� � ����
//� ��� �������, ����� ����� ����� ��������� ��
//������ ����
//**************************************
HWND hwndmessage = NULL;

bool StartDB()
{
	 HWND child = GetActiveWindow();
	 if(child== hwndmessage)
      return MessageBox(hwndmessage,"�� ������� �������� ���������� Debag",
      "ERROR",MB_OKCANCEL)==IDOK;
	 return false;
}

bool GPMIe()
{
	HWND child = GetActiveWindow();
	 if(child== hwndmessage)
      return MessageBox(hwndmessage,"�� ������� �������� ����������",
      "GetProcessMemoryInfo",MB_OKCANCEL)==IDOK;
	  return false;
}

bool GBA32()
{
	HWND child = GetActiveWindow();
	 if(child== hwndmessage)
      return MessageBox(hwndmessage,"�� ������� �������� ����������",
      "GetModuleInformation",MB_OKCANCEL)==IDOK;
	  return false;
}

bool GBA64()
{
	HWND child = GetActiveWindow();
	 if(child == hwndmessage)
      return MessageBox(hwndmessage,"�� ������� �������� ����������",
      "GetModuleInformationEx",MB_OKCANCEL)==IDOK;
	  return false;
}

bool CTHS()
{
	HWND child = GetActiveWindow();
	 if(child== hwndmessage)
      return MessageBox(hwndmessage,"�� ������� �������� ����������",
      "CreateToolhelp32Snapshot",MB_OKCANCEL)==IDOK;
	  return false;
}