#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <functional>
#include <list>

#include <thread>
#include <mutex>
#include <shared_mutex>

#ifdef _WIN32 // Windows NT

#include <WinSock2.h>
#include <mstcpip.h>

#else // *nix

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#endif

#include "general.h"

#ifdef _WIN32 // Windows NT
typedef int SockLen_t;
typedef SOCKADDR_IN SocketAddr_in;
typedef SOCKET Socket;
typedef u_long ka_prop_t;
#else // POSIX
typedef socklen_t SockLen_t;
typedef struct sockaddr_in SocketAddr_in;
typedef int Socket;
typedef int ka_prop_t;
#endif

// ������������ Keep-Alive ����������
struct KeepAliveConfig{
  ka_prop_t ka_idle = 120;
  ka_prop_t ka_intvl = 3;
  ka_prop_t ka_cnt = 5;
};

// ����� Tcp �������
struct TcpServer {
  // ����� ������� ������� (���������� ���������� ����)
  struct Client;
  // ��� ���������� ������ �������
  typedef std::function<void(DataBuffer, Client&)> handler_function_t;
  // ��� ����������� �����������/������������ �������
  typedef std::function<void(Client&)> con_handler_function_t;

  // ���� ������� �������
  enum class status : uint8_t {
    up = 0,
    err_socket_init = 1,
    err_socket_bind = 2,
    err_scoket_keep_alive = 3,
    err_socket_listening = 4,
    close = 5
  };

private:
  // ����� �������
  Socket serv_socket;
  // ���� �������
  uint16_t port;
  // ��� �������
  status _status = status::close;
  // ���������� ������ �� �������
  handler_function_t handler;
  // ���������� ����������� �������
  con_handler_function_t connect_hndl = [](Client&){};
  // ���������� ������������ �������
  con_handler_function_t disconnect_hndl = [](Client&){};
  // �����-���������� �����������
  std::thread accept_handler_thread;
  // ����� �������� ������
  std::thread data_waiter_thread;
  // ��� ��������� �������
  typedef std::list<std::unique_ptr<Client>>::iterator ClientIterator;

  // Keep-Alive ������������
  KeepAliveConfig ka_conf;

  // ������ ��������
  std::list<std::unique_ptr<Client>> client_list;
  // ������� ��� ������������� ������� ����������� � �������� ������
  std::mutex client_mutex;

  // ��� ������ Windows ��� �� ���������
  // ��������� ������������ ������ WinSocket
#ifdef _WIN32 // Windows NT
  WSAData w_data;
#endif

  // �������� Keep-Alive ��� ������
  bool enableKeepAlive(Socket socket);
  // ����� ����������� �����������
  void handlingAcceptLoop();
  // ����� �������� ������
  void waitingDataLoop();

public:
  // ���������� ����������� � ���������:
  // * �����
  // * ����������� ������
  // * ������������ Keep-Alive
  TcpServer(const uint16_t port,
            handler_function_t handler,
            KeepAliveConfig ka_conf = {});
  // ����������� � ���������:
  // * �����
  // * ����������� ������
  // * ����������� �����������
  // * ����������� ����������
  // * ������������ Keep-Alive
  TcpServer(const uint16_t port,
            handler_function_t handler,
            con_handler_function_t connect_hndl,
            con_handler_function_t disconnect_hndl,
            KeepAliveConfig ka_conf = {});

  // ����������
  ~TcpServer();

  // �������� ���������� ������
  void setHandler(handler_function_t handler);
  // Getter �����
  uint16_t getPort() const;
  // Setter �����
  uint16_t setPort(const uint16_t port);
  // Getter ���� ������� �������
  status getStatus() const {return _status;}
  // ����� ������� �������
  status start();
  // ����� ��������� �������
  void stop();
  // ����� ��� ����� ������������� ����������� ������� �������
  void joinLoop();

  // ��������� ����������� �� ������� � ������� �������
  bool connectTo(uint32_t host, uint16_t port, con_handler_function_t connect_hndl);

  // ��������� ������ ���� �������� �������
  void sendData(const void* buffer, const size_t size);
  // ��������� ������ ������� �� ����� � �����
  bool sendDataBy(uint32_t host, uint16_t port, const void* buffer, const size_t size);
  // ��������� ������� �� ����� � �����
  bool disconnectBy(uint32_t host, uint16_t port);
  // ��������� ���� ��������
  void disconnectAll();
};

// ����� ������� (�� ������� �������)
struct TcpServer::Client : public TcpClientBase {
  friend struct TcpServer;

  // ������� ��� ������������� ��������� ������
  std::mutex access_mtx;
  // ����� �������
  SocketAddr_in address;
  // ����� �������
  Socket socket;
  // ��� ������� �������
  status _status = status::connected;

public:
  // ����������� � ���������:
  // * ������ �������
  // * ������ �������
  Client(Socket socket, SocketAddr_in address);
  // ����������
  virtual ~Client() override;
  // Getter �����
  virtual uint32_t getHost() const override;
  // Getter �����
  virtual uint16_t getPort() const override;
  // Getter ���� ������� �����������
  virtual status getStatus() const override {return _status;}
  // ��������� �������
  virtual status disconnect() override;
  // �������� ������ �� �������
  virtual DataBuffer loadData() override;
  // ��������� ������ �������
  virtual bool sendData(const void* buffer, const size_t size) const override;
  // ���������� "�������" �������
  virtual SocketType getType() const override {return SocketType::server_socket;}
};

#endif // TCPSERVER_H
