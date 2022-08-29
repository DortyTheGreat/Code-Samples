#include <unistd.h>   //close
#include "OS_dependencies.h"
#include <string>
class Client{
public:
    int sock;
    char buf[4096];
    Client(std::string ip, unsigned short port){
        //	Create a socket

        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
            return;
        }

        sockaddr_in hint;
        hint.sin_family = AF_INET;
        hint.sin_port = htons(port);
        inet_pton(AF_INET, ip.c_str(), &hint.sin_addr);

         //	Connect to the server on the socket
        int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
        if (connectRes == -1)
        {
            return;
        }

    }

    ~Client(){
        close(sock);
    }

    void send_mesg(const std::string& mesg){
        if (send(sock, mesg.c_str(), mesg.size() + 1, 0) == -1)
        {
            #ifdef _GLIBCXX_IOSTREAM
            std::cout << "Could not send to server! Whoops!\r\n";
            #endif // _GLIBCXX_IOSTREAM
        }
    }

    std::string get_mesg(){
         //		Wait for response
        memset(buf, 0, 4096);
        int bytesReceived = recv(sock, buf, 4096, 0);
        if (bytesReceived == -1)
        {
            return "There was an error getting response from server\r\n";
        }
        else
        {
            //		Display response
           return std::string(buf, bytesReceived);
        }
    }
};
