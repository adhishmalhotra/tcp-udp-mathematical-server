// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MAX 80
#define PORT	 8080
#define MAXLINE 1024

// Driver code
int main() {

	int sockfd;
	char buffer[MAXLINE];
	struct sockaddr_in	 servaddr;

	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;

	//this is the block where we'd be collecting the data from the client 
	
	char operation[MAX];
	char firstNum[MAX];
	char secondNum[MAX];
	int i, j, k;
	printf("Want to Disconnect? Type exit\n");
	int n, len;
	while(1)
	{
	
		bzero(operation, sizeof(operation));
		bzero(firstNum, sizeof(firstNum));
		bzero(secondNum, sizeof(secondNum));
		
		i=0;
		j=0;
		k=0;
		
		
		//data collection 
		
		printf("Enter the operation to be performed:");
		while((operation[i++] = getchar()) != '\n');
		
		if (strncmp(operation, "exit", 4) == 0)
		{
		printf("Client peacing out!\n");
		break;
		}
		
		printf("Enter the First Number:");
		while((firstNum[j++] = getchar()) != '\n');
		
		printf("Enter the Second Number:");
		while((secondNum[k++] = getchar()) != '\n');
		
		//data sending
		sendto(sockfd, (const char *)operation, strlen(operation),
		MSG_CONFIRM, (const struct sockaddr *) &servaddr,
			sizeof(servaddr));
			
		sendto(sockfd, (const char *)firstNum, strlen(firstNum),
		MSG_CONFIRM, (const struct sockaddr *) &servaddr,
			sizeof(servaddr));
			
		
		sendto(sockfd, (const char *)secondNum, strlen(secondNum),
		MSG_CONFIRM, (const struct sockaddr *) &servaddr,
			sizeof(servaddr));
			
		printf("Arithematic expression sent.\n");
		
		//receiving the reply from the server for the above calculation
		
		n = recvfrom(sockfd, (char *)buffer, MAXLINE,
				MSG_WAITALL, (struct sockaddr *) &servaddr,
				&len);
		buffer[n] = '\0';
		printf("Result of the arithematic expression from the server : %s\n", buffer);
		
	
	}
	
	//the block ends
	
	close(sockfd);
	return 0;
	
}

