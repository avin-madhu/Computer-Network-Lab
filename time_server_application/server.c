#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#define PORT 12345
#define BUFFER_SIZE 256
int main()
{
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_address, client_address;
    time_t t; // variable to hold current time
    time(&t); // put the current time in t
    char *hello = ctime(&t); // convert into human-readable way
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_address, 0, sizeof(server_address));
    memset(&client_address, 0, sizeof(client_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    if (bind(sockfd, (const struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    socklen_t address_length = sizeof(client_address);
    int n = recvfrom(sockfd, buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *)&client_address, &address_length);
    if (n < 0) {
        perror("Receive failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    buffer[n] = '\0';
    printf("Time at Client: %s\n", buffer);
    sendto(sockfd, hello, strlen(hello) + 1, MSG_CONFIRM, (const struct sockaddr *)&client_address, address_length);
    printf("The time of server sent to client\n");
    close(sockfd);
    return 0;
}
