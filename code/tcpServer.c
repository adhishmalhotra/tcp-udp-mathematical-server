#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr
   
// this is the block/function where we'd process the information collected from the client. 

void tcpCallServer(int sockfd)
{
    char buffer[MAX];
    char firstNum[MAX];
    char secondNum[MAX];
    int result, x, y;
    
    
    while (1) {
    	result,x,y = 0;
        bzero(buffer, MAX);
        bzero(firstNum, MAX);
        bzero(secondNum, MAX);
   	
        //reading the data from the client
        
        //operation
        read(sockfd, buffer, sizeof(buffer));
        
        //first number
        read(sockfd, firstNum, sizeof(firstNum));
        
        //second number
        read(sockfd, secondNum, sizeof(secondNum));
        
	x = atoi(firstNum);
    	y = atoi(secondNum);

	switch (buffer[0]){
		case '+':
			result=x+y;
			break;
		case '-':
			result=x-y;
			break;
		case '/':
			result = (y==0) ? printf("Sorry, but the denominator can't be zero\n"):x/y;
			
			break;
		case '*':
			result=x*y;
			break;
		default:
			break;
	}      
       
  
        
        //printing the information that was received from the client along with the result
        
        printf("Operation:%s\n", buffer);
        printf("First Number:%s\n", firstNum);
        printf("Second Number:%s\n", secondNum);
        printf("Result:%d\n",result);

	//sending the result back to the client
	
        write(sockfd, &result, sizeof(result));
  
    }
}
   
// Driver function
int main()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
   
    //creating the socket and checking whether its created properly
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));
   
    // assigning IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
   
    //binding the socket and IP address
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");
   

    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    len = sizeof(cli);
   
    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        printf("server accept failed...\n");
        exit(0);
    }
    else
        printf("server accept the client...\n");
   
    //calling the function that was declared above
    tcpCallServer(connfd);
   
    // After chatting close the socket
    close(sockfd);
}
