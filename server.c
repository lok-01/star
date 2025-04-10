#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Create socket file descriptor
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(5000);

    // Bind the socket to port 5000
    bind(server_fd, (struct sockaddr*)&address, sizeof(address));

    // Listen for a connection
    listen(server_fd, 3);

    printf("Waiting for client...\n");

    // Accept the connection
    new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);

    printf("Client connected.\n");

    // Receive messages until "Over" is received
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        read(new_socket, buffer, sizeof(buffer));
        if (strcmp(buffer, "Over") == 0)
            break;
        printf("Client: %s\n", buffer);
    }

    close(new_socket);
    close(server_fd);
    return 0;
}
