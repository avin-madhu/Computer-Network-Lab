#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int sockfd, connfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[BUFFER_SIZE];

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        error("Error opening socket");
    }

    // Initialize server address
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    // Bind the socket
    if ((bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr))) != 0) {
        error("Error binding");
    }

    // Listen for incoming connections
    if ((listen(sockfd, 5)) != 0) {
        error("Error listening");
    }

    printf("Server listening on port %d...\n", PORT);

    addr_size = sizeof(client_addr);
    // Accept connection from client
    connfd = accept(sockfd, (struct sockaddr *)&client_addr, &addr_size);
    if (connfd < 0) {
        error("Error accepting connection");
    }

    while (1) {
        // Receive message from client
        bzero(buffer, BUFFER_SIZE);
        read(connfd, buffer, sizeof(buffer));
        printf("Client: %s\n", buffer);

        // Send message to client
        printf("Server: ");
        fgets(buffer, sizeof(buffer), stdin);
        write(connfd, buffer, strlen(buffer));

        // Exit loop if client sends "exit"
        if (strncmp(buffer, "exit", 4) == 0) {
            break;
        }
    }

    // Close the socket
    close(sockfd);
    return 0;
}






