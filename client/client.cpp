// client.cpp
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <cstring>

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    int PORT = 8081;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout << "\n Socket creation error \n" << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
//    if (inet_pton(AF_INET, "serverhttp://localhost", &serv_addr.sin_addr) <= 0) { // 'server' is the service name in docker-compose
    if (inet_pton(AF_INET, "0.0.0.0", &serv_addr.sin_addr) <= 0) { // 'server' is the service name in docker-compose
        std::cout << "\nInvalid address/ Address not supported \n" << std::endl;
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << "\nConnection Failed \n" << std::endl;
        return -1;
    }
    std::string hello = "Hello from client";
    send(sock, hello.c_str(), hello.length(), 0);
    std::cout << "Hello message sent" << std::endl;
    read(sock, buffer, 1024);
    std::cout << "Server message: " << buffer << std::endl;

    close(sock);
    return 0;
}
