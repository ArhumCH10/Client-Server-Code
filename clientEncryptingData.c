// Client side implementation of TCP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT     8080
#define MAXLINE  1024

// Driver code
int main() {
    int sockfd;
    char buffer[MAXLINE];
    char *hello;
    struct sockaddr_in servaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr));
    int n, len;
    char ch;
    int size=0;
    FILE* fp = fopen("data.txt","r");

    // Allocate memory for hello
    hello = (char*)malloc(MAXLINE*sizeof(char));

    do {
        ch = fgetc(fp);
       hello[size] = ch;
        size++;
       
    } while (ch != EOF);

    hello[size] = '\0';
    printf("%s\n",hello);
   for (int i=0;i<size;i++) {
        if(hello[i] >= 'a' && hello[i] <= 'z') {
            hello[i] += 3;
        }
        else if (hello[i] >= 'A' && hello[i] <= 'Z') {
            hello[i] += 2;
        }
        else if (hello[i] >= '0' && hello[i] <= '9') {
            hello[i] += 1;
        }
    }
      printf("%s\n",hello);
    send(sockfd, (const char *)hello, strlen(hello),0);
    printf("Hello message sent.\n");

    n = recv(sockfd, (char *)buffer, MAXLINE, 0);
    buffer[n] = '\0';
    printf("Server : %s\n", buffer);

    close(sockfd);

    // Free the allocated memory
    free(hello);

    return 0;
}

