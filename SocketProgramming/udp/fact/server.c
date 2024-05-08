#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345

int fact(int n)
{
  if(n==0)
  {
    return 1;
  }
  return n*fact(n-1);
}

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    int number;

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
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

    printf("Server is running and listening for incoming connections...\n");

    // Receive number from client
    client_len = sizeof(client_addr);
    if (recvfrom(sockfd, &number, sizeof(number), 0, (struct sockaddr *)&client_addr, &client_len) == -1) {
        perror("recvfrom");
        exit(EXIT_FAILURE);
    }

    printf("the factorial of the Number received from client: %d\n", fact(number));
    
  

    // Close the socket
    close(sockfd);

    return 0;
}
