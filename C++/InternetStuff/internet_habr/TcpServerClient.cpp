#include "TcpServer.cpp"

#ifdef _WIN32
// Макросы для выражений зависимых от OS
#define WIN(exp) exp
#define NIX(exp)


#else
// Макросы для выражений зависимых от OS
#define WIN(exp)
#define NIX(exp) exp
#endif

#include <iostream>

// Реализация загрузки данных
DataBuffer TcpServer::Client::loadData() {
  // Если клиент не подключён вернуть пустой буффер
  if(_status != SocketStatus::connected) return DataBuffer();
  using namespace std::chrono_literals;
  DataBuffer buffer;
  int err;

  // Чтение длинный данных в неблокирующем режиме
  // MSG_DONTWAIT - Unix флаг неблокирующего режима для recv
  // FIONBIO - Windows-флаг неблокирующего режима для ioctlsocket
  WIN(if(u_long t = true; SOCKET_ERROR == ioctlsocket(socket, FIONBIO, &t)) return DataBuffer();)
  int answ = recv(socket, (char*)&buffer.size, sizeof (buffer.size), NIX(MSG_DONTWAIT)WIN(0));

  // Обработка отключения
  if(!answ) {
    disconnect();
    return DataBuffer();
  } else if(answ == -1) {
    // Чтение кода ошибки
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

    // Отключение неблокирующего режима для Windows
    WIN(if(u_long t = false; SOCKET_ERROR == ioctlsocket(socket, FIONBIO, &t)) return DataBuffer();)

    // Обработка ошибки при наличии
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

  // Если прочитанный размер нулевой, то вернуть пустой буффер
  if(!buffer.size) return DataBuffer();
  // Если размер не нулевой выделить буффер в куче для чтения данных
  buffer.data_ptr = (char*)malloc(buffer.size);
  // Чтение данных в блокирующем режиме
  recv(socket, (char*)buffer.data_ptr, buffer.size, 0);
  // Возврат буффера с прочитанными данными
  return buffer;
}

// Обработка отключения клиента
TcpClientBase::status TcpServer::Client::disconnect() {
  _status = status::disconnected;
  // Если сокет не валидный прекратить обработку
  if(socket == WIN(INVALID_SOCKET)NIX(-1)) return _status;
  // Отключение сокета
  shutdown(socket, SD_BOTH);
  // Закрытие сокета
  WIN(closesocket)NIX(close)(socket);
  // Установление в сокета не валидного значения
  socket = WIN(INVALID_SOCKET)NIX(-1);
  return _status;
}

// Отправка данных
bool TcpServer::Client::sendData(const void* buffer, const size_t size) const {
  // Если сокет закрыт вернуть false
  if(_status != SocketStatus::connected) return false;
  // Сформировать сообщение с длинной в начале
  void* send_buffer = malloc(size + sizeof (int));
  memcpy(reinterpret_cast<char*>(send_buffer) + sizeof(int), buffer, size);
  *reinterpret_cast<int*>(send_buffer) = size;

  // Отправить сообщение
  if(send(socket, reinterpret_cast<char*>(send_buffer), size + sizeof (int), 0) < 0) return false;
  // Вычистить буффер сообщения
  free(send_buffer);
  return true;
}

// Конструктор клиента
TcpServer::Client::Client(Socket socket, SocketAddr_in address)
  : address(address), socket(socket) {}

// Деструктор клиента с закрытием сокета
TcpServer::Client::~Client() {
  if(socket == WIN(INVALID_SOCKET)NIX(-1)) return;
  shutdown(socket, SD_BOTH);
  WIN(closesocket(socket);)
  NIX(close(socket);)
}

// Получить хост клиента
uint32_t TcpServer::Client::getHost() const {return NIX(address.sin_addr.s_addr) WIN(address.sin_addr.S_un.S_addr);}
// Получить порт клиента
uint16_t TcpServer::Client::getPort() const {return address.sin_port;}
