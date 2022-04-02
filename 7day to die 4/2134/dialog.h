//**************************************
//здесь просто MessageBox-ы для того чтоб не 
//писать реакцию на каждую ошибку прямо в коде
//и для отладки, также легче будет перевести на
//другой язык
//**************************************
HWND hwndmessage = NULL;

bool StartDB()
{
	 HWND child = GetActiveWindow();
	 if(child== hwndmessage)
      return MessageBox(hwndmessage,"Не удалось получить привелегии Debag",
      "ERROR",MB_OKCANCEL)==IDOK;
	 return false;
}

bool GPMIe()
{
	HWND child = GetActiveWindow();
	 if(child== hwndmessage)
      return MessageBox(hwndmessage,"Не удалось получить информацию",
      "GetProcessMemoryInfo",MB_OKCANCEL)==IDOK;
	  return false;
}

bool GBA32()
{
	HWND child = GetActiveWindow();
	 if(child== hwndmessage)
      return MessageBox(hwndmessage,"Не удалось получить информацию",
      "GetModuleInformation",MB_OKCANCEL)==IDOK;
	  return false;
}

bool GBA64()
{
	HWND child = GetActiveWindow();
	 if(child == hwndmessage)
      return MessageBox(hwndmessage,"Не удалось получить информацию",
      "GetModuleInformationEx",MB_OKCANCEL)==IDOK;
	  return false;
}

bool CTHS()
{
	HWND child = GetActiveWindow();
	 if(child== hwndmessage)
      return MessageBox(hwndmessage,"Не удалось получить информацию",
      "CreateToolhelp32Snapshot",MB_OKCANCEL)==IDOK;
	  return false;
}