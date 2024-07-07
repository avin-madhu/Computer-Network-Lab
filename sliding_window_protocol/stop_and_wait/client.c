#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#define port 12348
#define buff_size 256

int main()
{
  int frame[2];
  frame[0] = 1;
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1)
  {
    perror("socket");
    exit(1);
  }
  int opt = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  
  struct sockaddr_in client_address;

  client_address.sin_family = AF_INET;
  client_address.sin_port = htons(port);
  client_address.sin_addr.s_addr = INADDR_ANY;

  int conncheck = connect(sockfd, (struct sockaddr*) &client_address, sizeof(client_address));

  if (conncheck == -1)
  {
    perror("Connect");
    exit(1);
  }

  printf("Enter the number of frames to send: ");
  scanf("%d", &frame[1]);
  while(frame[1]>0)
    {
      // frame[0] = 0
      frame[0] = (frame[0] + 1)%2;
      int sendcheck = send(sockfd,frame, sizeof(frame), 0);
      printf("\nFrame[%d] sent\n", frame[0]);
      if (sendcheck == -1)
      {
        perror("send");
        exit(1);
      }
      
      recv(sockfd, frame, sizeof(frame), 0);
      printf("\nAcknowledgment for Frame[%d] recived\n", frame[0]);
    }
  
   close(sockfd);
  
  return 0;
}
