// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT	 8080 
#define MAXLINE 1024 

// Driver code 
int main() { 
	int sockfd; 
	char buffer[MAXLINE]; 
	char *hello; 
	struct sockaddr_in servaddr, cliaddr; 
	
	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(PORT); 
	
	// Bind the socket with the server address 
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	listen (sockfd,5);
	int newfd;
	hello = (char*)malloc(MAXLINE*sizeof(char));
        int len= sizeof(cliaddr), n; 
        newfd= accept(sockfd, (struct sockaddr*) &cliaddr, &len);
		
        n = recv(newfd, (char *)buffer, MAXLINE,0); 
	buffer[n] = '\0'; 
		
	printf("Client : %s\n", buffer); 
	int size = strlen(buffer);
	
	for (int i=0;i<size;i++) {
        if(buffer[i] >= 'a' && buffer[i] <= 'z') {
            buffer[i] -= 3;
        }
        else if (buffer[i] == '|' || buffer[i] == '{' || buffer[i] == '}')
        {
            buffer[i] -= 3;
        }
        else if (buffer[i] >= 'A' && buffer[i] <= 'Z') {
            buffer[i] -= 2;
        }
        else if (buffer[i] >= '0' && buffer[i] <= '9') {
            buffer[i] -= 1;
        }
    }	
		
        send(newfd, (const char *)buffer, strlen(buffer),0); 
	printf("Hello message sent.\n"); 
	close(newfd);
	
	return 0; 
} 

