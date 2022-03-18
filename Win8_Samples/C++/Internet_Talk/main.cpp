
//Revision Dorty.Gosunov Standalone v1 Made At 01.04.2021

#include <string.h>
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include <locale>
#include <sstream>

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>


using namespace std;
condition_variable cv;
#pragma comment(lib,"ws2_32.lib")

string value;

void read_value() {
    cin >> value;
    cv.notify_one();
}

WSADATA wsaData;
SOCKET Socket;
SOCKADDR_IN SockAddr;
int lineCount=0;
int rowCount=0;
struct hostent *host;
locale local;
char buffer[10000];
int i = 0 ;
int nDataLength;
string website_HTML;
string url = "chat.gosunov.ru";

string Suppa = "getmessages?for=Dima";

string get_http = "GET /"+Suppa+" HTTP/1.1\r\nHost: " + url + "\r\nConnection: close\r\n\r\n";

int BuffSize = 200;


string YourLogin;
string LoginOfTalk="";

// website url

void UpdateTalkingData(string Partner){
Suppa = "getmessages?for=" + Partner;
get_http = "GET /"+Suppa+" HTTP/1.1\r\nHost: " + url + "\r\nConnection: close\r\n\r\n";
}

void WriteInfoFromServer(){

    Suppa = "getmessages?for=" + YourLogin;
    get_http = "GET /"+Suppa+" HTTP/1.1\r\nHost: " + url + "\r\nConnection: close\r\n\r\n";

    for(int i =0;i<BuffSize;i++){
        buffer[i]=' ';
    }

    website_HTML = "";
        i = 0 ;
        rowCount=0;
        lineCount=0;
//string Suppa = "sendmessage?for=Dima&text=Gay";


    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0){
        cout << "WSAStartup failed.\n";
        system("pause");
        //return 1;
    }

    Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    host = gethostbyname(url.c_str());

    SockAddr.sin_port=htons(80);
    SockAddr.sin_family=AF_INET;
    SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

    if(connect(Socket,(SOCKADDR*)(&SockAddr),sizeof(SockAddr)) != 0){
        cout << "Could not connect";
        system("pause");
        //return 1;
    }

    // send GET / HTTP
    send(Socket,get_http.c_str(), strlen(get_http.c_str()),0 );

    // recieve html
    while ((nDataLength = recv(Socket,buffer,BuffSize,0)) > 0){
        int i = 0;
        while ( i<BuffSize){

            website_HTML+=buffer[i];
            i += 1;
        }
    }

    //closesocket(Socket);
    WSACleanup();

    // Display HTML source
    //cout<< endl << endl<<website_HTML << endl << "_______" << endl;;

    string karret="";
    bool flag = 0;
    int counter = 0;
    int AmountOfMetas = 100;

    string Meta[100];
    for(int i=0;i<AmountOfMetas;i++){
        Meta[i]="";
    }
    string Separator = "++";
    string filter = ""; //[UTypeDef=1]<DoRTY_Cucumber>

    //cout << website_HTML << endl;

    for(int i=0;i<website_HTML.size()+1;i++){

        if( website_HTML[i] == '\n' || (i==website_HTML.size())){
                if(flag){


                if(counter < AmountOfMetas){
                Meta[counter] = karret;
                }else{
                cout << "Data " <<counter-AmountOfMetas <<":{" <<  karret << "}" << endl;
                }

                karret="";counter++;
                }else{
                if(karret == filter){
                    flag=1;
                    //cout <<endl << "Filter Has Been Found \/  \/  \/ " << endl << endl;
                }

            //cout << "PreData:{" <<karret <<"}" << endl;
            karret="";
                }
        }else{
        if(website_HTML[i] != '\r') {karret+=website_HTML[i];}
        }


    }

    // pause


    //cout << endl << "META:" << endl;
    for(int i=0;i<counter-1;i++){
        cout   << Meta[i] << endl;
    }

    //cout<<"\n\nPress ANY key to close.\n\n";
    //cin.ignore(); cin.get();




 return;
}

void WriteToSomebody(string Text,string Partner){

        for(int i =0;i<BuffSize;i++){
        buffer[i]=' ';
    }
    website_HTML = "";
        i = 0 ;
        rowCount=0;
        lineCount=0;
//string Suppa = "sendmessage?for=Dima&text=Gay";


    Suppa = "sendmessage?for=" + Partner + "&text=" +(YourLogin + ":" + Text);
    get_http = "GET /"+Suppa+" HTTP/1.1\r\nHost: " + url + "\r\nConnection: close\r\n\r\n";


    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0){
        cout << "WSAStartup failed.\n";
        system("pause");
        //return 1;
    }

    Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    host = gethostbyname(url.c_str());

    SockAddr.sin_port=htons(80);
    SockAddr.sin_family=AF_INET;
    SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

    if(connect(Socket,(SOCKADDR*)(&SockAddr),sizeof(SockAddr)) != 0){
        cout << "Could not connect";
        system("pause");
        //return 1;
    }

    // send GET / HTTP
    send(Socket,get_http.c_str(), strlen(get_http.c_str()),0 );

    // recieve html
    while ((nDataLength = recv(Socket,buffer,BuffSize,0)) > 0){
        int i = 0;
        while ( i<BuffSize){

            website_HTML+=buffer[i];
            i += 1;
        }
    }

    //closesocket(Socket);
    //WSACleanup();

    // Display HTML source
    //cout<< endl << endl<<website_HTML << endl << "_______" << endl;;

    string karret="";
    bool flag = 0;
    int counter = 0;
    int AmountOfMetas = 100;

    string Meta[100];
    for(int i=0;i<AmountOfMetas;i++){
        Meta[i]="";
    }
    string Separator = "++";
    string filter = ""; //[UTypeDef=1]<DoRTY_Cucumber>

    //cout << website_HTML << endl;

    for(int i=0;i<website_HTML.size()+1;i++){

        if( website_HTML[i] == '\n' || (i==website_HTML.size())){
                if(flag){


                if(counter < AmountOfMetas){
                Meta[counter] = karret;
                }else{
                cout << "Data " <<counter-AmountOfMetas <<":{" <<  karret << "}" << endl;
                }

                karret="";counter++;
                }else{
                if(karret == filter){
                    flag=1;
                    //cout <<endl << "Filter Has Been Found \/  \/  \/ " << endl << endl;
                }

            //cout << "PreData:{" <<karret <<"}" << endl;
            karret="";
                }
        }else{
        if(website_HTML[i] != '\r') {karret+=website_HTML[i];}
        }


    }

    // pause


    //cout << endl << "META:" << endl;
    for(int i=0;i<counter-1;i++){
        cout   << Meta[i] << endl;
    }

    //cout<<"\n\nPress ANY key to close.\n\n";
    //cin.ignore(); cin.get();




 return;

}

int main( void ){
    cout << "Input Your Login: "; cin >> YourLogin; cout << endl;
    cout << "Input Login Of Your Friend: "; cin >> LoginOfTalk; cout << endl;



    cout << "Doing: " << url << " {/} " << Suppa;
//HTTP GET

cout << endl << "ACTUAL: " << get_http;

//system("chcp 65001");
while(1){
        thread th(read_value);

    mutex mtx;
    unique_lock<mutex> lck(mtx);
while (cv.wait_for(lck, chrono::seconds(2)) == cv_status::timeout)
    {
WriteInfoFromServer();
}
    th.join();
if(value != ""){WriteToSomebody(value,LoginOfTalk);}
//Sleep(1000);
}
}
