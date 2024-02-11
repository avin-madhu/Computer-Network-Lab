// client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 6000
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE] = {0};

    // Create socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Get user input
        printf("Enter message to send to server (type 'exit' to quit): ");
        fgets(buffer, sizeof(buffer), stdin);

        // Send data to the server
        send(client_socket, buffer, strlen(buffer), 0);

        // Check for exit command
        if (strncmp(buffer, "exit", 4) == 0) {
            break;
        }

        // Clear the buffer
        memset(buffer, 0, sizeof(buffer));

        // Receive and display the echoed message from the server
        if (recv(client_socket, buffer, BUFFER_SIZE, 0) < 0) {
            perror("Receive failed");
            exit(EXIT_FAILURE);
        }

        printf("Server response: %s\n", buffer);

        // Clear the buffer
        memset(buffer, 0, sizeof(buffer));
    }

    // Close the socket
    close(client_socket);

    return 0;
}
