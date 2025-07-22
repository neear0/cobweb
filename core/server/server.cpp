#include "server.hpp"
#include <iostream>
#include <cstring>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#endif

c_server::c_server(int port) : port_num(port), socket_fd(-1) {
#ifdef _WIN32
    WSADATA wsa_data;
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
        std::cerr << "WSAStartup failed\n";
        exit(1);
    }
#endif
}

void c_server::setup_socket() 
{
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        perror("socket");
        exit(1);
    }

    int opt = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port_num);

    if (bind(socket_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
#ifdef _WIN32
        closesocket(socket_fd);
        WSACleanup();
#else
        close(socket_fd);
#endif
        exit(1);
    }

    if (listen(socket_fd, 5) < 0)
    {
        perror("listen");
#ifdef _WIN32
        closesocket(socket_fd);
        WSACleanup();
#else
        close(socket_fd);
#endif
        exit(1);
    }

    std::cout << "[*] Listening on port " << port_num << std::endl;
}

void c_server::accept_connections() {
    while (true) {
        sockaddr_in client_addr{};
#ifdef _WIN32
        int client_len = sizeof(client_addr);
#else
        socklen_t client_len = sizeof(client_addr);
#endif
        int client_fd = accept(socket_fd, (struct sockaddr*)&client_addr, &client_len);

        if (client_fd < 0) {
            perror("accept");
            continue;
        }

        std::cout << "[+] New connection accepted" << std::endl;

#ifdef _WIN32
        closesocket(client_fd);
#else
        close(client_fd);
#endif
    }
}

void c_server::start()
{
    setup_socket();
    accept_connections();

#ifdef _WIN32
    WSACleanup();
#endif
}