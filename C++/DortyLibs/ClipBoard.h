
#include "BasicWindowsLib.h"
/// Source : http://netcode.ru/cpp/?artID=248&katID=3&lang&skatID=22
/// Fixed : https://www.cyberforum.ru/cpp-beginners/thread55526.html
/// Date Modded By Me :(21.02.2022) (dd.mm.yyyy)



void to_clip(std::string Str){

    DWORD CodePage=0x419;
  if(OpenClipboard(STD_HWND))//��������� ����� ������
  {
    HGLOBAL hgBuffer=GlobalAlloc(GMEM_DDESHARE,Str.size()+1);//�������� ������
    char* chBuffer=(char*)GlobalLock(hgBuffer); //��������� ������
    strcpy(chBuffer,Str.c_str());
    EmptyClipboard(); //������� �����
    HGLOBAL Data=GlobalAlloc(GMEM_MOVEABLE+GMEM_DDESHARE,4);  // ��������� ������� �������� ��� ������ ������
    char* DataPtr=(char*)GlobalLock(Data);
    memcpy(DataPtr,(const VOID*)&CodePage,4);
    GlobalUnlock(Data);
    SetClipboardData(CF_LOCALE,Data);
    GlobalUnlock(hgBuffer);//������������ ������
    SetClipboardData(CF_TEXT, hgBuffer);//�������� ����� � ����� ������
    //SetClipboardData(CF_LOCALE, (HANDLE)0x409);
    CloseClipboard(); //��������� ����� ������
  }

}

string from_clip(){
    string fromClipboard;//� ��� ���������� �������� ����� �� ������ ������
    if ( OpenClipboard(STD_HWND) )//��������� ����� ������
    {
       HANDLE hData = GetClipboardData(CF_TEXT);//��������� ����� �� ������ ������
       char* chBuffer= (char*)GlobalLock(hData);//��������� ������
       fromClipboard = chBuffer;
       GlobalUnlock(hData);//������������ ������
       CloseClipboard();//��������� ����� ������
    }

    return fromClipboard;
}
