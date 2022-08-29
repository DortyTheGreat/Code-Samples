#include <iostream>


using namespace std;

int main()
{


    Client clie("228.228.228.228", 12345);







    string userInput;
    while(1){
        //		Enter lines of text
        cout << "> ";
        getline(cin, userInput);
        clie.send_mesg(userInput);
        cout << clie.get_mesg()  << "\r\n";;
        //		Send to server




    }

    //	Close the socket


    return 0;
}
