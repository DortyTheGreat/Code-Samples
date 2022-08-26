/// https://bitbucket.org/sloankelly/youtube-source-repository/src/master/cpp/networking/MultipleClientsBarebonesServer/MultipleClientsBarebonesServer/main.cpp

/// linux https://youtu.be/cNdlrbZSkyQ

/// also for linux https://github.com/bozkurthan/Simple-TCP-Server-Client-CPP-Example/blob/master/tcp-Server.cpp

/// -lws2_32
/// ws2_32

#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <sstream>


#pragma comment (lib, "ws2_32.lib")

using namespace std;

//Example: b1 == 192, b2 == 168, b3 == 0, b4 == 100
struct IPv4
{
    unsigned char b1, b2, b3, b4;
};

bool getMyIP(IPv4 & myIP)
{
    char szBuffer[1024];

    #ifdef WIN32
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 0);
    if(::WSAStartup(wVersionRequested, &wsaData) != 0)
        return false;
    #endif


    if(gethostname(szBuffer, sizeof(szBuffer)) == SOCKET_ERROR)
    {
      #ifdef WIN32
      WSACleanup();
      #endif
      return false;
    }

    struct hostent *host = gethostbyname(szBuffer);
    if(host == NULL)
    {
      #ifdef WIN32
      WSACleanup();
      #endif
      return false;
    }

    //Obtain the computer's IP
    myIP.b1 = ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b1;
    myIP.b2 = ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b2;
    myIP.b3 = ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b3;
    myIP.b4 = ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b4;

    #ifdef WIN32
    WSACleanup();
    #endif
    return true;
}

int main()
{
    IPv4 ip;

    getMyIP(ip);
    cout << "My IP: " << int(ip.b1) << " " << int(ip.b2) << " " << int(ip.b3) << " " << int(ip.b4) << " " << endl;

    // Init WinSock
    WSADATA wsa_Data;
    int wsa_ReturnCode = WSAStartup(0x101,&wsa_Data);

    // Get the local hostname
    char szHostName[255];
    gethostname(szHostName, 255);
    struct hostent *host_entry;
    host_entry=gethostbyname(szHostName);
    char * szLocalIP;
    szLocalIP = inet_ntoa (*(struct in_addr *)*host_entry->h_addr_list);
    WSACleanup();

    cout << szLocalIP << endl;




	// Initialze winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
	{
		cerr << "Can't Initialize winsock! Quitting" << endl;
		return -1;
	}

	// Create a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		cerr << "Can't create a socket! Quitting" << endl;
		return -2;
	}

	// Bind the ip address and port to a socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(7250);
	hint.sin_addr.S_un.S_addr = INADDR_ANY; // Could also use inet_pton ....

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	// Tell Winsock the socket is for listening
	listen(listening, SOMAXCONN);

	// Create the master file descriptor set and zero it
	fd_set master;
	FD_ZERO(&master);

	// Add our first socket that we're interested in interacting with; the listening socket!
	// It's important that this socket is added for our server or else we won't 'hear' incoming
	// connections
	FD_SET(listening, &master);

	// this will be changed by the \quit command (see below, bonus not in video!)
	bool running = true;

    cout << "Server is running" << endl;

	while (running)
	{
		// Make a copy of the master file descriptor set, this is SUPER important because
		// the call to select() is _DESTRUCTIVE_. The copy only contains the sockets that
		// are accepting inbound connection requests OR messages.

		// E.g. You have a server and it's master file descriptor set contains 5 items;
		// the listening socket and four clients. When you pass this set into select(),
		// only the sockets that are interacting with the server are returned. Let's say
		// only one client is sending a message at that time. The contents of 'copy' will
		// be one socket. You will have LOST all the other sockets.

		// SO MAKE A COPY OF THE MASTER LIST TO PASS INTO select() !!!

		fd_set copy = master;


		// See who's talking to us
		int socketCount = select(0, &copy, nullptr, nullptr, nullptr);

		// Loop through all the current connections / potential connect
		for (int i = 0; i < socketCount; i++)
		{
		    cout << "in sock loop" << endl;
			// Makes things easy for us doing this assignment
			SOCKET sock = copy.fd_array[i];

			// Is it an inbound communication?
			if (sock == listening)
			{
			    cout << "new user" << endl;
				// Accept a new connection
				SOCKET client = accept(listening, nullptr, nullptr);

				// Add the new connection to the list of connected clients
				FD_SET(client, &master);

				// Send a welcome message to the connected client
				string welcomeMsg = "Welcome to the Awesome Chat Server!\r\n";
				send(client, welcomeMsg.c_str(), welcomeMsg.size() + 1, 0);
			}
			else // It's an inbound message
			{
			    cout << "inboud mesg!" << endl;
				char buf[4096];
				ZeroMemory(buf, 4096);

				// Receive message
				int bytesIn = recv(sock, buf, 4096, 0);
				if (bytesIn <= 0)
				{
				    cout << "bye-bye!" << endl;
					// Drop the client
					closesocket(sock);
					FD_CLR(sock, &master);
				}
				else
				{
                    cout << "here 1!" << endl;
					// Check to see if it's a command. \quit kills the server
					if (buf[0] == '\\')
					{
						// Is the command quit?
						string cmd = string(buf, bytesIn);
						if (cmd == "\\quit")
						{
							running = false;
							break;
						}

						// Unknown command
						continue;
					}

					cout << "here 2!" << endl;

					// Send message to other clients, and definiately NOT the listening socket

					for (int i = 0; i < master.fd_count; i++)
					{
					    cout << "here 3!" << endl;
						SOCKET outSock = master.fd_array[i];
						if (outSock == listening){
                            cout << "listening!" << endl;
						}

						if (outSock == sock){
                            cout << "sock!" << endl;
						}

						if (outSock != listening && 1)
						{
						    cout << "here 4!" << endl;
							ostringstream ss;
							ss << "SOCKET #" << sock << ": " << buf << "\r\n";
							string strOut = ss.str();

							send(outSock, strOut.c_str(), strOut.size() + 1, 0);
							cout << "here 5!" << endl;
						}
					}
				}
			}
		}
	}

	// Remove the listening socket from the master file descriptor set and close it
	// to prevent anyone else trying to connect.
	FD_CLR(listening, &master);
	closesocket(listening);

	// Message to let users know what's happening.
	string msg = "Server is shutting down. Goodbye\r\n";

	while (master.fd_count > 0)
	{
		// Get the socket number
		SOCKET sock = master.fd_array[0];

		// Send the goodbye message
		send(sock, msg.c_str(), msg.size() + 1, 0);

		// Remove it from the master file list and close the socket
		FD_CLR(sock, &master);
		closesocket(sock);
	}

	// Cleanup winsock
	WSACleanup();

	system("pause");
}
