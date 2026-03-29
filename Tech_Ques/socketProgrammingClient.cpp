#include <iostream>
#include <cstring>
#include<bits/stdc++.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;

    // 1. Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    // 2. Connect
    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    // 3. Send message
    const char* msg = "Hello from client";
    send(sock, msg, strlen(msg), 0);

    // 4. Receive response
    char buffer[1024] = {0};
    recv(sock, buffer, 1024, 0);
    cout << "Server: " << buffer << endl;

    // 5. Close
    closesocket(sock);
   

    return 0;
}