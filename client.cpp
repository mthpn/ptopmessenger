#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void) {
  // 1. Создание сокета
  int client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket == -1) {
    std::cerr << "[!] Error creating socket." << std::endl;
    return 1;
  }

  // 2. Настройка адреса сервера
  sockaddr_in server_address;
  memset(&server_address, 0, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(8080);
  inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);

  // 3. Подключение к серверу
  if (connect(client_socket, (sockaddr *)&server_address, sizeof(server_address))) {
    std::cerr << "[!] Error connecting to server." << std::endl;
    return 1;
  }
  std::cout << "[*] Connected to server." << std::endl;

  // 4. Отправка данных
  const char* message = "Whatever";
  send(client_socket, message, strlen(message), 0);

  // 5. Получение ответа
  char buffer[1024];
  recv(client_socket, buffer, sizeof(buffer), 0);
  std::cout << "[*] Server response: " << buffer << std::endl;

  // 6. Закрытие соединения
  close(client_socket);

  return 0;
}
