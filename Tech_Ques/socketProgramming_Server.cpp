#include <iostream>
#include <winsock2.h>
#include <cstring>
#include <ws2def.h>
#include <ws2ipdef.h>
#include <ws2tcpip.h>
using namespace std;

#pragma comment(lib, "ws2_32.lib")

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // 1. Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // 2. Attach socket to port
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // any IP
    address.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));

    // 3. Listen
    listen(server_fd, 3);

    cout << "Server listening...\n";

    // 4. Accept connection
    client_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);

    // 5. Receive message
    char buffer[1024] = {0};
    recv(client_socket, buffer, 1024, 0);
    cout << "Client: " << buffer << endl;

    // 6. Send response
    const char* msg = "Hello from server";
    send(client_socket, msg, strlen(msg), 0);

    // 7. Close
    closesocket(client_socket);
    closesocket(server_fd);

    return 0;
}