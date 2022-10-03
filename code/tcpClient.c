#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr


//this is the block where we'd be collecting data from the client
void tcpCallClient(int sockfd)
{
    char operation[MAX];
    char firstNum[MAX];
    char secondNum[MAX];
    
    
    int n,k,j,x,y;
    printf("Want to Disconnect? Type exit\n");
    while (1) {
    
        bzero(operation, sizeof(operation));
        bzero(firstNum, sizeof(firstNum));
        bzero(secondNum, sizeof(secondNum));
        
        n = 0;
        k = 0;
        j = 0;
        
        //data collection
        printf("Please enter an operation:");
        while ((operation[n++] = getchar()) != '\n');
        
        if (strncmp(operation, "exit", 4) == 0)
	{
		printf("Client peacing out!\n");
		break;
	}
            
	printf("Enter the First Number:");
	while ((firstNum[k++] = getchar()) != '\n');
            
	printf("Enter the Second Number:");
	while ((secondNum[j++] = getchar()) != '\n');
            

        //data sending
        write(sockfd, operation, sizeof(operation));
        write(sockfd, firstNum, sizeof(firstNum));
        write(sockfd, secondNum, sizeof(secondNum));
        
	
	//receiving the reply from the server for the above calculation        
        read(sockfd, &x, sizeof(x));
        printf("Result of the arithematic expression from the server : %d\n", x);
     
    }
}
   
int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
   
    // Creating socket file descriptor
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));
   
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
   
    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");
   
    //execute the function defined above
    tcpCallClient(sockfd);
   
    // close the socket
    close(sockfd);
}
