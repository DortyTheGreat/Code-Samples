#include "TcpServer.cpp"

#ifdef _WIN32
// ������� ��� ��������� ��������� �� OS
#define WIN(exp) exp
#define NIX(exp)


#else
// ������� ��� ��������� ��������� �� OS
#define WIN(exp)
#define NIX(exp) exp
#endif

#include <iostream>

// ���������� �������� ������
DataBuffer TcpServer::Client::loadData() {
  // ���� ������ �� ��������� ������� ������ ������
  if(_status != SocketStatus::connected) return DataBuffer();
  using namespace std::chrono_literals;
  DataBuffer buffer;
  int err;

  // ������ ������� ������ � ������������� ������
  // MSG_DONTWAIT - Unix ���� �������������� ������ ��� recv
  // FIONBIO - Windows-���� �������������� ������ ��� ioctlsocket
  WIN(if(u_long t = true; SOCKET_ERROR == ioctlsocket(socket, FIONBIO, &t)) return DataBuffer();)
  int answ = recv(socket, (char*)&buffer.size, sizeof (buffer.size), NIX(MSG_DONTWAIT)WIN(0));

  // ��������� ����������
  if(!answ) {
    disconnect();
    return DataBuffer();
  } else if(answ == -1) {
    // ������ ���� ������
    WIN(
      err = convertError();
      if(!err) {
        SockLen_t len = sizeof (err);
        getsockopt (socket, SOL_SOCKET, SO_ERROR, WIN((char*))&err, &len);
      }
    )NIX(
      SockLen_t len = sizeof (err);
      getsockopt (socket, SOL_SOCKET, SO_ERROR, WIN((char*))&err, &len);
      if(!err) err = errno;
    )

    // ���������� �������������� ������ ��� Windows
    WIN(if(u_long t = false; SOCKET_ERROR == ioctlsocket(socket, FIONBIO, &t)) return DataBuffer();)

    // ��������� ������ ��� �������
    switch (err) {
      case 0: break;
        // Keep alive timeout
      case ETIMEDOUT:
      case ECONNRESET:
      case EPIPE:
        disconnect();
        [[fallthrough]];
        // No data
      case EAGAIN: return DataBuffer();
      default:
        disconnect();
        std::cerr << "Unhandled error!\n"
                    << "Code: " << err << " Err: " << std::strerror(err) << '\n';
      return DataBuffer();
    }
  }

  // ���� ����������� ������ �������, �� ������� ������ ������
  if(!buffer.size) return DataBuffer();
  // ���� ������ �� ������� �������� ������ � ���� ��� ������ ������
  buffer.data_ptr = (char*)malloc(buffer.size);
  // ������ ������ � ����������� ������
  recv(socket, (char*)buffer.data_ptr, buffer.size, 0);
  // ������� ������� � ������������ �������
  return buffer;
}

// ��������� ���������� �������
TcpClientBase::status TcpServer::Client::disconnect() {
  _status = status::disconnected;
  // ���� ����� �� �������� ���������� ���������
  if(socket == WIN(INVALID_SOCKET)NIX(-1)) return _status;
  // ���������� ������
  shutdown(socket, SD_BOTH);
  // �������� ������
  WIN(closesocket)NIX(close)(socket);
  // ������������ � ������ �� ��������� ��������
  socket = WIN(INVALID_SOCKET)NIX(-1);
  return _status;
}

// �������� ������
bool TcpServer::Client::sendData(const void* buffer, const size_t size) const {
  // ���� ����� ������ ������� false
  if(_status != SocketStatus::connected) return false;
  // ������������ ��������� � ������� � ������
  void* send_buffer = malloc(size + sizeof (int));
  memcpy(reinterpret_cast<char*>(send_buffer) + sizeof(int), buffer, size);
  *reinterpret_cast<int*>(send_buffer) = size;

  // ��������� ���������
  if(send(socket, reinterpret_cast<char*>(send_buffer), size + sizeof (int), 0) < 0) return false;
  // ��������� ������ ���������
  free(send_buffer);
  return true;
}

// ����������� �������
TcpServer::Client::Client(Socket socket, SocketAddr_in address)
  : address(address), socket(socket) {}

// ���������� ������� � ��������� ������
TcpServer::Client::~Client() {
  if(socket == WIN(INVALID_SOCKET)NIX(-1)) return;
  shutdown(socket, SD_BOTH);
  WIN(closesocket(socket);)
  NIX(close(socket);)
}

// �������� ���� �������
uint32_t TcpServer::Client::getHost() const {return NIX(address.sin_addr.s_addr) WIN(address.sin_addr.S_un.S_addr);}
// �������� ���� �������
uint16_t TcpServer::Client::getPort() const {return address.sin_port;}
