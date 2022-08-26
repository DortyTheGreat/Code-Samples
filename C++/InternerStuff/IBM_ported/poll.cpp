/***********************************************************************************************/
/*                                                                                             */
/*                                      File : poll.cpp                                        */
/*                                                                                             */
/*                      poll UNIX function implementation for WINDOWS                          */
/*                                                                                             */
/*                                                                                             */
/***********************************************************************************************/
/**
 * Copyright (C) 2016 Benoit Rock
 *                    rock.s.architecture.free.fr/poll.html
 *
 * Rock's Architecture is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

extern "C"
{
	#include <sys\types.h>
	#include <winsock2.h>
}

#include "poll.h"

#include <iostream>

#define	POLLIN		0x0001
#define	POLLPRI		0x0002
#define	POLLOUT		0x0004
#define	POLLERR		0x0008
#define	POLLHUP		0x0010
#define	POLLNVAL	0x0020
#define	POLLRDNORM	0x0040
#define POLLNORM	POLLRDNORM
#define POLLWRNORM      POLLOUT
#define	POLLRDBAND	0x0080
#define	POLLWRBAND	0x0100

#ifdef DEBUG
void DetermineError()
{
	switch(WSAGetLastError())
	{
		case WSAEACCES :
		{
			cerr << "Permission denied." << endl << "An attempt was made to access a socket in a way forbidden by its access permissions. An example is using a broadcast address for sendto without broadcast permission being set using setsockopt(SO_BROADCAST)." << endl
			break;
		}
		case WSAEADDRINUSE :
		{
			cerr << "Address already in use." << endl << "Only one usage of each socket address (protocol/IP address/port) is normally permitted. This error occurs if an application attempts to bind a socket to an IP address/port that has already been used for an existing socket, or a socket that wasn't closed properly, or one that is still in the process of closing. For server applications that need to bind multiple sockets to the same port number, consider using setsockopt(SO_REUSEADDR). Client applications usually need not call bind at all - connect will choose an unused port automatically. When bind is called with a wild-card address (involving ADDR_ANY), a WSAEADDRINUSE error could be delayed until the specific address is "committed." This could happen with a call to other function later, including connect, listen, WSAConnect or WSAJoinLeaf." << endl;
			break;
		}
		case WSAEADDRNOTAVAIL :
		{
			cerr << "Cannot assign requested address." << endl << "The requested address is not valid in its context. Normally results from an attempt to bind to an address that is not valid for the local machine. This can also result from connect, sendto, WSAConnect, WSAJoinLeaf, or WSASendTo when the remote address or port is not valid for a remote machine (e.g. address or port 0)." << endl;
			break;
		}
		case WSAEAFNOSUPPORT :
		{
			cerr << "Address family not supported by protocol family." << endl << "An address incompatible with the requested protocol was used. All sockets are created with an associated "address family" (i.e. AF_INET for Internet Protocols) and a generic protocol type (i.e. SOCK_STREAM). This error will be returned if an incorrect protocol is explicitly requested in the socket call, or if an address of the wrong family is used for a socket, e.g. in sendto." << endl;
			break;
		}
		case WSAEALREADY :
		{
			cerr << "Operation already in progress." << endl << "An operation was attempted on a non-blocking socket that already had an operation in progress - i.e. calling connect a second time on a non-blocking socket that is already connecting, or canceling an asynchronous request (WSAAsyncGetXbyY) that has already been canceled or completed." << endl;
			break;
		}
		case WSAECONNABORTED :
		{
			cerr << "Software caused connection abort." << endl << "An established connection was aborted by the software in your host machine, possibly due to a data transmission timeout or protocol error." << endl;
			break;
		}
		case WSAECONNREFUSED :
		{
			cerr << "Connection refused." << endl << "No connection could be made because the target machine actively refused it. This usually results from trying to connect to a service that is inactive on the foreign host - i.e. one with no server application running." << endl;
			break;
		}
		case WSAECONNRESET :
		{
			cerr << "Connection reset by peer." << endl << "A existing connection was forcibly closed by the remote host. This normally results if the peer application on the remote host is suddenly stopped, the host is rebooted, or the remote host used a "hard close" (see setsockopt for more information on the SO_LINGER option on the remote socket.) This error may also result if a connection was broken due to "keep-alive" activity detecting a failure while one or more operations are in progress. Operations that were in progress fail with WSAENETRESET. Subsequent operations fail with WSAECONNRESET." << endl;
			break;
		}
		case WSAEDESTADDRREQ :
		{
			cerr << "Destination address required." << endl << "A required address was omitted from an operation on a socket. For example, this error will be returned if sendto is called with the remote address of ADDR_ANY." << endl;
			break;
		}
		case SAEFAULT :
		{
			cerr << "Bad address." << endl << "The system detected an invalid pointer address in attempting to use a pointer argument of a call. This error occurs if an application passes an invalid pointer value, or if the length of the buffer is too small. For instance, if the length of an argument which is a struct sockaddr is smaller than sizeof(struct sockaddr)." << endl;
			break;
		}
		case WSAEHOSTDOWN :
		{
			cerr << "Host is down." << endl << "A socket operation failed because the destination host was down. A socket operation encountered a dead host. Networking activity on the local host has not been initiated. These conditions are more likely to be indicated by the error WSAETIMEDOUT." << endl;
			break;
		}
		case WSAEHOSTUNREACH
		{
			cerr << "No route to host." << endl << "A socket operation was attempted to an unreachable host. See WSAENETUNREACH" << endl;
			break;
		}
		case WSAEINPROGRESS :
		{
			cerr << "Operation now in progress." << endl << "A blocking operation is currently executing. Windows Sockets only allows a single blocking operation to be outstanding per task (or thread), and if any other function call is made (whether or not it references that or any other socket) the function fails with the WSAEINPROGRESS error." << endl;
			break;
		}
		case WSAEINTR :
		{
			cerr << "Interrupted function call." << endl << "A blocking operation was interrupted by a call to WSACancelBlockingCall." << endl;
			break;
		}
		case WSAEINVAL :
		{
			cerr << "Invalid argument." << endl << "Some invalid argument was supplied (for example, specifying an invalid level to the setsockopt function). In some instances, it also refers to the current state of the socket - for instance, calling accept on a socket that is not listening." << endl;
			break;
		}
		case WSAEISCONN :
		{
			cerr << "Socket is already connected." << endl << "A connect request was made on an already connected socket. Some implementations also return this error if sendto is called on a connected SOCK_DGRAM socket (For SOCK_STREAM sockets, the to parameter in sendto is ignored), although other implementations treat this as a legal occurrence." << endl;
			break;
		}
		case WSAEMFILE :
		{
			cerr << "Too many open files." << endl << "Too many open sockets. Each implementation may have a maximum number of socket handles available, either globally, per process or per thread." << endl;
			break;
		}
		case WSAEMSGSIZE :
		{
			cerr << "Message too long." << endl << "A message sent on a datagram socket was larger than the internal message buffer or some other network limit, or the buffer used to receive a datagram into was smaller than the datagram itself." << endl;
			break;
		}
		case WSAENETDOWN :
		{
			cerr << "Network is down." << endl << "A socket operation encountered a dead network. This could indicate a serious failure of the network system (i.e. the protocol stack that the WinSock DLL runs over), the network interface, or the local network itself." << endl;
			break;
		}
		case WSAENETRESET :
		{
			cerr << "Network dropped connection on reset." << endl << "The connection has been broken due to "keep-alive" activity detecting a failure while the operation was in progress. It can also be returned by setsockopt if an attempt is made to set SO_KEEPALIVE on a connection that has already failed." << endl;
			break;
		}
		case WSAENETUNREACH :
		{
			cerr << "Network is unreachable." << endl << "A socket operation was attempted to an unreachable network. This usually means the local software knows no route to reach the remote host." << endl;
			break;
		}
		case WSAENOBUFS :
		{
			cerr << "No buffer space available." << endl << "An operation on a socket could not be performed because the system lacked sufficient buffer space or because a queue was full." << endl;
			break;
		}
		case WSAENOPROTOOPT :
		{
			cerr << "Bad protocol option." << endl << "An unknown, invalid or unsupported option or level was specified in a getsockopt or setsockopt call." << endl;
			break;
		}
		case WSAENOTCONN :
		{
			cerr << "Socket is not connected." << endl << "A request to send or receive data was disallowed because the socket is not connected and (when sending on a datagram socket using sendto) no address was supplied. Any other type of operation might also return this error - for example, setsockopt setting SO_KEEPALIVE if the connection has been reset." << endl;
			break;
		}
		case WSAENOTSOCK :
		{
			cerr << "Socket operation on non-socket." << endl << "An operation was attempted on something that is not a socket. Either the socket handle parameter did not reference a valid socket, or for select, a member of an fd_set was not valid." << endl;
			break;
		}
		case WSAEOPNOTSUPP :
		{
			cerr << "Operation not supported." << endl << "The attempted operation is not supported for the type of object referenced. Usually this occurs when a socket descriptor to a socket that cannot support this operation, for example, trying to accept a connection on a datagram socket." << endl;
			break;
		}
		case WSAEPFNOSUPPORT :
		{
			cerr << "Protocol family not supported." << endl << "The protocol family has not been configured into the system or no implementation for it exists. Has a slightly different meaning to WSAEAFNOSUPPORT, but is interchangeable in most cases, and all Windows Sockets functions that return one of these specify WSAEAFNOSUPPORT." << endl;
			break;
		}
		case WSAEPROCLIM :
		{
			cerr << "Too many processes." << endl << "A Windows Sockets implementation may have a limit on the number of applications that may use it simultaneously. WSAStartup may fail with this error if the limit has been reached." << endl;
			break;
		}
		case WSAEPROTONOSUPPORT :
		{
			cerr << "Protocol not supported." << endl << "The requested protocol has not been configured into the system, or no implementation for it exists. For example, a socket call requests a SOCK_DGRAM socket, but specifies a stream protocol." << endl;
			break;
		}
		case WSAEPROTOTYPE :
		{
			cerr << "Protocol wrong type for socket." << endl << "A protocol was specified in the socket function call that does not support the semantics of the socket type requested. For example, the ARPA Internet UDP protocol cannot be specified with a socket type of SOCK_STREAM." << endl;
			break;
		}
		case WSAESHUTDOWN :
		{
			cerr << "Cannot send after socket shutdown." << endl << "A request to send or receive data was disallowed because the socket had already been shut down in that direction with a previous shutdown call. By calling shutdown a partial close of a socket is requested, which is a signal that sending or receiving or both has been discontinued." << endl;
			break;
		}
		case WSAESOCKTNOSUPPORT :
		{
			cerr << "Socket type not supported." << endl << "The support for the specified socket type does not exist in this address family. For example, the optional type SOCK_RAW might be selected in a socket call, and the implementation does not support SOCK_RAW sockets at all." << endl;
			break;
		}
		case WSAETIMEDOUT :
		{
			cerr << "Connection timed out." << endl << "A connection attempt failed because the connected party did not properly respond after a period of time, or established connection failed because connected host has failed to respond." << endl;
			break;
		}
		case WSATYPE_NOT_FOUND :
		{
			cerr << "Class type not found." << endl << "The specified class was not found." << endl;
			break;
		}
		case WSAEWOULDBLOCK :
		{
			cerr << "Resource temporarily unavailable." << endl << "This error is returned from operations on non-blocking sockets that cannot be completed immediately, for example recv when no data is queued to be read from the socket. It is a non-fatal error, and the operation should be retried later. It is normal for WSAEWOULDBLOCK to be reported as the result from calling connect on a non-blocking SOCK_STREAM socket, since some time must elapse for the connection to be established." << endl;
			break;
		}
		case WSAHOST_NOT_FOUND :
		{
			cerr << "Host not found." << endl << "No such host is known. The name is not an official hostname or alias, or it cannot be found in the database(s) being queried. This error may also be returned for protocol and service queries, and means the specified name could not be found in the relevant database." << endl;
			break;
		}
		case WSA_INVALID_HANDLE :
		{
			cerr << "(OS dependent)" << endl << "Specified event object handle is invalid." << endl << "An application attempts to use an event object, but the specified handle is not valid." << endl;
			break;
		}
		case WSA_INVALID_PARAMETER :
		{
			cerr << "(OS dependent)" << endl << "One or more parameters are invalid." << endl << "An application used a Windows Sockets function which directly maps to a Win32 function. The Win32 function is indicating a problem with one or more parameters." << endl;
			break;
		}
		case WSAINVALIDPROCTABLE :
		{
			cerr << "(OS dependent)" << endl << "Invalid procedure table from service provider." << endl << "A service provider returned a bogus proc table to WS2_32.DLL. (Usually caused by one or more of the function pointers being NULL.)" << endl;
			break;
		}
		case WSAINVALIDPROVIDER :
		{
			cerr << "(OS dependent)" << endl << "Invalid service provider version number." << endl << "A service provider returned a version number other than 2.0." << endl;
			break;
		}
		case WSA_IO_INCOMPLETE :
		{
			cerr << "(OS dependent)" << endl << "Overlapped I/O event object not in signaled state." << endl << "The application has tried to determine the status of an overlapped operation which is not yet completed. Applications that use WSAGetOverlappedResult (with the fWait flag set to false) in a polling mode to determine when an overlapped operation has completed will get this error code until the operation is complete." << endl;
			break;
		}
		case WSA_IO_PENDING :
		{
			cerr << "(OS dependent)" << endl << "Overlapped operations will complete later." << endl << "The application has initiated an overlapped operation which cannot be completed immediately. A completion indication will be given at a later time when the operation has been completed." << endl;
			break;
		}
		case WSA_NOT_ENOUGH_MEMORY :
		{
			cerr << "(OS dependent)" << endl << "Insufficient memory available." << endl << "An application used a Windows Sockets function which directly maps to a Win32 function. The Win32 function is indicating a lack of required memory resources." << endl;
			break;
		}
		case WSANOTINITIALISED :
		{
			cerr << "Successful WSAStartup not yet performed." << endl << "Either the application hasn't called WSAStartup or WSAStartup failed. The application may be accessing a socket which the current active task does not own (i.e. trying to share a socket between tasks), or WSACleanup has been called too many times." << endl;
			break;
		}
		case WSANO_DATA :
		{
			cerr << "Valid name, no data record of requested type." << endl << "The requested name is valid and was found in the database, but it does not have the correct associated data being resolved for. The usual example for this is a hostname -> address translation attempt (using gethostbyname or WSAAsyncGetHostByName) which uses the DNS (Domain Name Server), and an MX record is returned but no A record - indicating the host itself exists, but is not directly reachable." << endl;
			break;
		}
		case WSANO_RECOVERY :
		{
			cerr << "This is a non-recoverable error." << endl << "This indicates some sort of non-recoverable error occurred during a database lookup. This may be because the database files (e.g. BSD-compatible HOSTS, SERVICES or PROTOCOLS files) could not be found, or a DNS request was returned by the server with a severe error." << endl;
			break;
		}
		case WSAPROVIDERFAILEDINIT :
		{
			cerr << "(OS dependent)" << endl << "Unable to initialize a service provider." << endl <<
				"Either a service provider's DLL could not be loaded (LoadLibrary failed) or the provider's WSPStartup/NSPStartup function failed." << endl;
			break;
		}
		case WSASYSCALLFAILURE :
		{
			cerr << "(OS dependent)" << endl << "System call failure." << endl <<  "Returned when a system call that should never fail does. For example, if a call to WaitForMultipleObjects fails or one of the registry functions fails trying to manipulate theprotocol/namespace catalogs." << endl;
			break;
		}
		case WSASYSNOTREADY :
		{
			cerr << "Network subsystem is unavailable." << endl << "This error is returned by WSAStartup if the Windows Sockets implementation cannot function at this time because the underlying system it uses to provide network services is currently unavailable. Users should check: << endl
				 <<	"that the appropriate Windows Sockets DLL file is in the current path," << endl
				 << "that they are not trying to use more than one Windows Sockets implementation simultaneously. If there is more than one WINSOCK DLL on your system, be sure the first one in the path is appropriate for the network subsystem currently loaded." << endl
				 << "the Windows Sockets implementation documentation to be sure all necessary components are currently installed and configured correctly." << endl;
			break;
		}
		case WSATRY_AGAIN :
		{
			cerr << "Non-authoritative host not found." << endl << "This is usually a temporary error during hostname resolution and means that the local server did not receive a response from an authoritative server. A retry at some time later may be successful." << endl;
			break;
		}
		case WSAVERNOTSUPPORTED :
		{
			cerr << "WINSOCK.DLL version out of range." << endl << "The current Windows Sockets implementation does not support the Windows Sockets specification version requested by the application. Check that no old Windows Sockets DLL files are being accessed." << endl;
			break;
		}
		case WSAEDISCON :
		{
			cerr << "Graceful shutdown in progress." << endl << "Returned by WSARecv and WSARecvFrom to indicate the remote party has initiated a graceful shutdown sequence." << endl;
			break;
		}
		case WSA_OPERATION_ABORTED :
		{
			cerr << "(OS dependent)" << endl << "Overlapped operation aborted." << endl <<
			"An overlapped operation was canceled due to the closure of the socket, or the execution of the SIO_FLUSH command in WSAIoctl." << endl;
			break;
		}
	}//end switch
}
#endif //DEBUG

/************************************************************************************************/

int poll(struct pollfd *tabPollfd, unsigned long size, int timeOut)
{
	WSAEVENT *hTable;
	DWORD result = 0;
	int ret = 0;
	int indice;

	if(timeOut == -1)
		timeOut = INFINITE;

	hTable = new WSAEVENT [size];

	for (unsigned long i = 0; i < size; i++)
	{
		//les evenements traités auparavant sont resetes
		tabPollfd[i].revents = 0;

		//creation d'un evenement
		WSAEVENT wsaEvent=  WSACreateEvent();
		if( wsaEvent != WSA_INVALID_EVENT)
		{
			hTable[i] = wsaEvent;
		}
		else
		{
			std::cerr << "poll WSACreateEvent : Socket Error" << std::endl;
#ifdef DEBUG
			DetermineError();
#endif //DEBUG
			ret = -1;
			break;
		}

		if(!ret)
		{
			//association de l'evenement a la socket
			if(WSAEventSelect(tabPollfd[i].fd, hTable[i], FD_READ | FD_ACCEPT | FD_CLOSE | FD_CONNECT) == SOCKET_ERROR)
			{
				std::cerr << "poll WSAEventSelect : Socket Error" << std::endl;
#ifdef DEBUG
				DetermineError();
#endif //DEBUG
				ret = -1;
				break;
			}
		}

	}

	if(!ret)
	{
		//attente de l'arrivee d'un evenement sur une socket
		result = WSAWaitForMultipleEvents(size, hTable, FALSE, timeOut,TRUE);

		if(result == WSA_WAIT_FAILED)
		{
			std::cerr << "poll WSAWaitForMultipleEvents : Wait Failed Error" << std::endl;
#ifdef DEBUG
			DetermineError();
#endif //DEBUG
			ret = -1;
		}
		else
		{
			if(result != WSA_WAIT_TIMEOUT)
			{
				//determination de l'indice dans le tableau
				indice = result - WSA_WAIT_EVENT_0;
				WSANETWORKEVENTS NetworkEvents;

				//analyse du type d'evenement survenu
				if(WSAEnumNetworkEvents(tabPollfd[indice].fd, hTable[indice], &NetworkEvents) != SOCKET_ERROR)
				{
					if(NetworkEvents.lNetworkEvents == FD_ACCEPT ||
					   NetworkEvents.lNetworkEvents == FD_READ   ||
					   NetworkEvents.lNetworkEvents == FD_CLOSE  ||
					   NetworkEvents.lNetworkEvents == FD_CONNECT)
					{
						tabPollfd[indice].revents = POLLNORM;
					}
					else
					{
						tabPollfd[indice].revents = POLLNORM -1;
					}
					ret = 1;
				}
				else
				{
					std::cerr << "poll WSAEnumNetworkEvents : Socket Error" << std::endl;
#ifdef DEBUG
					DetermineError();
#endif //DEBUG
					ret = -1;
				}
			}
		}

		if(!ret || ret == 1)
		{
			for(int i = 0; i < size; i++)
			{
				//desassociation des evenements aux sockets
				if(WSAEventSelect (tabPollfd[i].fd, NULL, 0) == SOCKET_ERROR)
				{
					std::cerr << "poll WSAEventSelect : Socket Error" << std::endl;
#ifdef DEBUG
					DetermineError();
#endif //DEBUG
					ret = -1;
					break;
				}

				if(!ret || ret == 1)
				{
					//liberation des evenements
					if( WSACloseEvent(hTable[i]) == false)
					{
						std::cerr << "poll WSACloseEvent : error" << std::endl;
#ifdef DEBUG
						DetermineError();
#endif //DEBUG
						ret = -1;
						break;
					}

					if(!ret || ret == 1)
					{
						//on force au mode bloquant
						u_long argp = 0;
						if(ioctlsocket ( tabPollfd[i].fd, FIONBIO, &argp) == SOCKET_ERROR)
						{
							std::cerr << "poll ioctlsocket : Socket error" << std::endl;
#ifdef DEBUG
							DetermineError();
#endif //DEBUG
							ret = -1;
							break;
						}
					}

				}
			}
		}
	}
	delete [] hTable;

	return ret;
}
/************************************************************************************************/
