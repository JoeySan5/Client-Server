#include "pack109.hpp"
#include "hashset.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <fstream>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstdlib> 
#include <thread>

using namespace pack109;
using namespace std;

int main(int argc, char const *argv[])
{

    int sockfd, ret;//  original socket file descriptor and return value
	struct sockaddr_in serverAddr;// server address
	int newSocket;//new socket file descriptor
	struct sockaddr_in newAddr;//client address
	socklen_t addr_size;//size of client address
	vec buffer(5000);//buffer to hold btyes of messages
	pid_t childpid;// child process id

    sockfd = socket(AF_INET, SOCK_STREAM, 0);//create adult socket
	if(sockfd < 0){
    printf("Error creating socket");
    exit(EXIT_FAILURE);
    }
    
    bzero((char*)&serverAddr,  sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8081);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        
    ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){//bind socket to address
    printf("Error connecting to the socket");
    exit(EXIT_FAILURE);
    }
    
    

    if(listen(sockfd, 10)== 0){
		printf("Listening for connections on port 8081\n");
	}
    else{//listen for connections
         printf("Error listening for connections");
         exit(EXIT_FAILURE);
    }

    HashSet<file_struct> hs; //hashset for files 

	while(1){
		newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);//accept connection
		if(newSocket < 0){
			exit(EXIT_FAILURE);
		}
		printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
    printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));

    }

        
    return 0;
}


