#ifdef _WIN32
/// /// -lws2_32
#include <winsock2.h>
#include <ws2tcpip.h>

int inet_pton(int af, const char *src, void *dst)
{
  struct sockaddr_storage ss;
  int size = sizeof(ss);
  char src_copy[INET6_ADDRSTRLEN+1];

  ZeroMemory(&ss, sizeof(ss));
  /* stupid non-const API */
  strncpy (src_copy, src, INET6_ADDRSTRLEN+1);
  src_copy[INET6_ADDRSTRLEN] = 0;

  if (WSAStringToAddress(src_copy, af, NULL, (struct sockaddr *)&ss, &size) == 0) {
    switch(af) {
      case AF_INET:
    *(struct in_addr *)dst = ((struct sockaddr_in *)&ss)->sin_addr;
    return 1;
      case AF_INET6:
    *(struct in6_addr *)dst = ((struct sockaddr_in6 *)&ss)->sin6_addr;
    return 1;
    }
  }
  return 0;
}

const char *inet_ntop(int af, const void *src, char *dst, socklen_t size)
{
  struct sockaddr_storage ss;
  unsigned long s = size;

  ZeroMemory(&ss, sizeof(ss));
  ss.ss_family = af;

  switch(af) {
    case AF_INET:
      ((struct sockaddr_in *)&ss)->sin_addr = *(struct in_addr *)src;
      break;
    case AF_INET6:
      ((struct sockaddr_in6 *)&ss)->sin6_addr = *(struct in6_addr *)src;
      break;
    default:
      return NULL;
  }
  /* cannot direclty use &size because of strict aliasing rules */
  return (WSAAddressToString((struct sockaddr *)&ss, sizeof(ss), NULL, dst, &s) == 0)?
          dst : NULL;
}

#else // _WIN32

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#endif

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <sstream>

using namespace std;

#ifndef _WIN32

#define SOCKET long long

#endif // _WIN32
int main()
{
    #ifdef _WIN32
    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);

    int wsOk = WSAStartup(ver, &wsData);
    if (wsOk != 0)
    {
        cerr << "Can't Initialize winsock! Quitting" << endl;
        return -1;
    }
    #endif // _WIN32

    // Create a socket
    int listening = socket(AF_INET, SOCK_STREAM, 0);

    if (listening == -1)
    {
        cerr << "Can't create a socket! Quitting" << endl;
        return -2;
    }

    // Bind the ip address and port to a socket
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);


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
                    ///cout << "here 1!" << endl;
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

					///cout << "here 2!" << endl;

					// Send message to other clients, and definiately NOT the listening socket

					for (int i = 0; i < master.fd_count; i++)
					{
					    ///cout << "here 3!" << endl;
						SOCKET outSock = master.fd_array[i];
						if (outSock == listening){
                            cout << "listening!" << endl;
						}

						if (outSock == sock){
                            cout << "sock!" << endl;
						}

						if (outSock != listening && 1)
						{
							ostringstream ss;
							ss << "SOCKET #" << sock << ": " << buf << "\r\n";
							string strOut = ss.str();
							cout << sock<<"# req : " << buf << '\n';
							cout << "resp : " << strOut << '\n';
							send(outSock, strOut.c_str(), strOut.size() + 1, 0);
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


    return 0;
}
