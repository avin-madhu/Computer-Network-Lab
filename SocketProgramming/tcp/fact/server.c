#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345

int main() {
    int sockfd, new_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    int number;

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Initialize server address struct
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(sockfd, 5) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Listening for incoming connections...\n");

    // Accept incoming connection
    client_len = sizeof(client_addr);
    if ((new_socket = accept(sockfd, (struct sockaddr *)&client_addr, &client_len)) == -1) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    printf("Connection accepted\n");

    printf("Enter the number to send: ");
    scanf("%d", &number);
   
    if (send(new_socket, &number, sizeof(number), 0) == -1) {
        perror("send");
        exit(EXIT_FAILURE);
    }

    printf("Number sent to client: %d\n", number);

    // Close sockets
    close(new_socket);
    close(sockfd);

    return 0;
}
