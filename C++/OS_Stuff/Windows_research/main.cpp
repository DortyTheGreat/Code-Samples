#include <iostream>
#include "../DortyLibs/BasicWindowsLib.h"
#include <cassert>
#include <string.h>
#include <locale.h>


using namespace std;

/// Send Input
int SendKeystrokesToNotepad( string mesg )
{
    INPUT *keystroke;
    UINT i, character_count, keystrokes_to_send, keystrokes_sent;
    HWND notepad;

    ///assert( mesg != NULL );

    //Get the handle of the Notepad window.
    notepad = FindWindow( ( "Notepad" ), NULL );
    if( notepad == NULL )
        return 0;

    //Bring the Notepad window to the front.
    if( !SetForegroundWindow( notepad ) )
        return 0;

    //Fill in the array of keystrokes to send.
    character_count = ( mesg.size() );
    keystrokes_to_send = character_count * 2;
    keystroke = new INPUT[ keystrokes_to_send ];
    for( i = 0; i < character_count; ++i )
    {
        keystroke[ i * 2 ].type = INPUT_KEYBOARD;
        keystroke[ i * 2 ].ki.wVk = 0;
        keystroke[ i * 2 ].ki.wScan = mesg[ i ];
        keystroke[ i * 2 ].ki.dwFlags = KEYEVENTF_UNICODE;
        keystroke[ i * 2 ].ki.time = 0;
        keystroke[ i * 2 ].ki.dwExtraInfo = GetMessageExtraInfo();

        keystroke[ i * 2 + 1 ].type = INPUT_KEYBOARD;
        keystroke[ i * 2 + 1 ].ki.wVk = 0;
        keystroke[ i * 2 + 1 ].ki.wScan = mesg[ i ];
        keystroke[ i * 2 + 1 ].ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
        keystroke[ i * 2 + 1 ].ki.time = 0;
        keystroke[ i * 2 + 1 ].ki.dwExtraInfo = GetMessageExtraInfo();
    }

    //Send the keystrokes.
    keystrokes_sent = SendInput( ( UINT )keystrokes_to_send, keystroke, sizeof( *keystroke ) );
    delete [] keystroke;

    return keystrokes_sent == keystrokes_to_send;
}




/// FINALO
int SendKeystrokesToNotepad2( const TCHAR *const text )
{
    HWND notepad, edit;

    assert( text != NULL );

    //Get the handle of the Notepad window.
    notepad = FindWindow( ( "Notepad" ), NULL );
    if( notepad == NULL )
        return 0;

    //Get the handle of the Notepad window's edit control.
    edit = FindWindowEx( notepad, NULL, ( "Edit" ), NULL );
    if( edit == NULL )
        return 0;

    SendMessage( edit, EM_REPLACESEL, ( WPARAM )TRUE, ( LPARAM )text );
    return 1;
}

int main()
{

    cout << SendKeystrokesToNotepad2("abobus");

    cout << "Hello world!" << endl;
    return 0;
}
