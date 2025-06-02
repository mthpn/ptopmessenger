#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(void) {
  // Создание сокета
  int server_socket = socket(AF_INET, SOCK_STREAM, 0);
  // Проверка, что сокет был создан без ошибок
  if (server_socket == -1) {
    std::cerr << "[!] Error creating socket." << std::endl;
    return 1;
  }

  // 2. Настройка адреса сервера
  sockaddr_in server_address;
  memset(&server_address, 0, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(8080);
  server_address.sin_addr.s_addr = INADDR_ANY;

  // 3. Привязка сокета к адресу

  // bind - привязка сокета к адресу
  // server_socket - дескриптор сокета
  // (sockaddr *) - приведение типа к указателю на структуру sockaddr (обобщенная структура для представления адресов)
  // &server_address - взятие адреса структуры с конфигурацией сервера
  if (bind(server_socket, (sockaddr *)&server_address, sizeof(server_address))) {
    std::cerr << "[!] Error binding socket." << std::endl;
    return 1;
  }

  // 4. Ожидание подключений
  listen(server_socket, 5); // 5 - размер очереди ожидающих подключений
  std::cout << "[*] Server started. Listening for connections..." << std::endl;

  // 5. Принятие подключения
  sockaddr_in client_address;
  socklen_t client_addr_size = sizeof(client_address);
  // accept - принимает новое подключение
  int client_socket = accept(server_socket, (sockaddr *)&client_address, &client_addr_size);
  std::cout << "[*] Client connected." << std::endl;

  // 6. Обмен данными
  char buffer[1024];
  recv(client_socket, buffer, sizeof(buffer), 0);
  std::cout << "[*] Received: " << buffer << std::endl;

  const char *response = "[12] OK";
  send(client_socket, response, strlen(response), 0);

  // 7. Закрытие соединений
  close(client_socket);
  close(server_socket);

  return 0;
}
