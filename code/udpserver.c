// Server side implementation of UDP client-server model
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

        //common block which is present in both client and server which performs all the checks and establishes the connection
        
	int sockfd;

	//this is the message that will be sent from the sever to the client
	
	char final[50];
	
	//the server message ends
	
	struct sockaddr_in servaddr, cliaddr;
	
	// Creating socket file descriptor
	
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
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
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	
	// the common block ends 
	
	
	//this is the block where we'd process the information collected from the client
	
	char buffer[MAX];
	char firstNum[MAX];
	char secondNum[MAX];
	
	//to hold firstNum and lastNum
	int j, k; 
	
	//to hold the length of all the incoming strings for processing 
	int x, y, n;
	
	
	int len;
	
	//to hold the final result
	float result;
	len = sizeof(cliaddr); //len is value/resuslt
	
	while(1)
	{
	
		bzero(buffer, sizeof(buffer));
		bzero(firstNum, sizeof(firstNum));
		bzero(secondNum, sizeof(secondNum));
		
		j,k,result = 0;
		
		//reading the data from the client
		//operation
		
		n = recvfrom(sockfd, (char *)buffer, MAXLINE,
				MSG_WAITALL, ( struct sockaddr *) &cliaddr,
				&len);
				
		buffer[n] = '\0';
		printf("Client : %s\n", buffer);
		
		//firstNum
		
		x = recvfrom(sockfd, (char *)firstNum, MAXLINE,
				MSG_WAITALL, ( struct sockaddr *) &cliaddr,
				&len);
		firstNum[x] = '\0';
		printf("Client : %s\n", firstNum);
				
		//secondNum
		
		y = recvfrom(sockfd, (char *)secondNum, MAXLINE,
				MSG_WAITALL, ( struct sockaddr *) &cliaddr,
				&len);
		secondNum[y] = '\0';
		printf("Client : %s\n", secondNum);
		
		//assigning values 
		
		j = atoi(firstNum);
		k = atoi(secondNum);
		
		switch(buffer[0])
		{
		
			case '+': result = (float)j + k;
				  sprintf(final, "%f", result);
				  break; 
			case '-': result = (float)j - k; 
				  sprintf(final, "%f", result);
				  break;
			case '*': result = (float)j * k; 
				  sprintf(final, "%f", result);
				  break;
			case '/': 
				  if (k==0) 
				  {
				  	strcpy(final,"Sorry, but the denominator can't be zero");
				  }
				  else 
				  {
				  	result = (float)j/k;
				  	sprintf(final, "%f", result);
				  }
				  break;
			default: break;
		
		}
	
	//sending the data to the server
	sendto(sockfd, (const char *)final, strlen(final),
		MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
			len);
	
	}
	
	// the processing block ends
	
	printf("Arithematic expression result sent.\n");
	
	return 0;
}

