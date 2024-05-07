#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345

int factorial(int n) {
    if (n == 0) 
      return 1;
    return n * factorial(n - 1);
}

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    int number, result;

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        // perror("socket");
        exit(EXIT_FAILURE);
    }

    // Initialize server address struct
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY; 
    // Change to your server IP address

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server\n");

    // Receive number from server
    if (recv(sockfd, &number, sizeof(number), 0) == -1) {
        perror("recv");
        exit(EXIT_FAILURE);
    }

    printf("Number received from server: %d\n", number);

    // Calculate factorial
    result = factorial(number);

    // Display result
    printf("Factorial of %d is: %d\n", number, result);

    // Close the socket
    close(sockfd);

    return 0;
}
