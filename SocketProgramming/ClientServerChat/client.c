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
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        error("Error opening socket");
    }

    // Initialize server address
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);

    // Connect to server
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) != 0) {
        error("Error connecting to server");
    }

    while (1) {
        // Send message to server
        printf("Client: ");
        fgets(buffer, sizeof(buffer), stdin);
        write(sockfd, buffer, strlen(buffer));

        // Receive message from server
        bzero(buffer, BUFFER_SIZE);
        read(sockfd, buffer, sizeof(buffer));
        printf("Server: %s\n", buffer);

        // Exit loop if server sends "exit"
        if (strncmp(buffer, "exit", 4) == 0) {
            break;
        }
    }

    // Close the socket
    close(sockfd);
    return 0;
}

