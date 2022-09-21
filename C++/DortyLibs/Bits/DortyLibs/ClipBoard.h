
#include "BasicWindowsLib.h"
/// Source : http://netcode.ru/cpp/?artID=248&katID=3&lang&skatID=22
/// Fixed : https://www.cyberforum.ru/cpp-beginners/thread55526.html
/// Date Modded By Me :(21.02.2022) (dd.mm.yyyy)



void to_clip(std::string Str){

    DWORD CodePage=0x419;
  if(OpenClipboard(STD_HWND))//открываем буфер обмена
  {
    HGLOBAL hgBuffer=GlobalAlloc(GMEM_DDESHARE,Str.size()+1);//выделяем память
    char* chBuffer=(char*)GlobalLock(hgBuffer); //блокируем память
    strcpy(chBuffer,Str.c_str());
    EmptyClipboard(); //очищаем буфер
    HGLOBAL Data=GlobalAlloc(GMEM_MOVEABLE+GMEM_DDESHARE,4);  // Назначить кодовую страницу для буфера обмена
    char* DataPtr=(char*)GlobalLock(Data);
    memcpy(DataPtr,(const VOID*)&CodePage,4);
    GlobalUnlock(Data);
    SetClipboardData(CF_LOCALE,Data);
    GlobalUnlock(hgBuffer);//разблокируем память
    SetClipboardData(CF_TEXT, hgBuffer);//помещаем текст в буфер обмена
    //SetClipboardData(CF_LOCALE, (HANDLE)0x409);
    CloseClipboard(); //закрываем буфер обмена
  }

}

string from_clip(){
    string fromClipboard;//в эту переменную сохраним текст из буфера обмена
    if ( OpenClipboard(STD_HWND) )//открываем буфер обмена
    {
       HANDLE hData = GetClipboardData(CF_TEXT);//извлекаем текст из буфера обмена
       char* chBuffer= (char*)GlobalLock(hData);//блокируем память
       fromClipboard = chBuffer;
       GlobalUnlock(hData);//разблокируем память
       CloseClipboard();//закрываем буфер обмена
    }

    return fromClipboard;
}
