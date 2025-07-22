#pragma once

class c_server
{
public:
    c_server(int port);     
    void start();

private:
    int port_num;
    int socket_fd;

    void setup_socket();
    void accept_connections();
};