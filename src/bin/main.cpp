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
#include <sstream>

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
	vec readBuffer(5000);//buffer to 
	pid_t childpid;// child process id

	int fd[2];


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

    HashSet<file_struct> hs(10); //hashset for files 

	vec newVec;
	newVec.push_back(4);
	newVec.push_back(6);
	vec oldVec;
		oldVec.push_back(3);
			newVec.push_back(8);



	struct file_struct deserFile = {"hello", newVec};
	struct file_struct deserFile1 = {"hello", newVec};
	struct file_struct deserFile2 = {"goodbye", oldVec};
	struct file_struct deserFileGlobal;


	hs.insert(deserFile);
		hs.insert(deserFile1);
			hs.insert(deserFile2);




	hs.print();

		// int pipe(int fds[2]);

		// Parameters :
		// fd[0] will be the fd(file descriptor) for the 
		// read end of pipe.
		// fd[1] will be the fd for the write end of pipe.
		// Returns : 0 on Success.
		// -1 on error.
	

  int pipe_result;
  pipe_result =pipe(fd);
  //https://www.geeksforgeeks.org/c-program-demonstrate-fork-and-pipe/
  //https://www.geeksforgeeks.org/pipe-system-call/

  if (pipe_result<0)
    printf("error");

	

	while(1){
		hs.print();
		newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);//accept connection
		if(newSocket < 0){
			printf("%s", "connectino not accpeted ");
			exit(EXIT_FAILURE);
		}
		printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
		childpid = fork();
		if(childpid<0) {
    		printf("Couldn't create child process");
    		return -1;
  		}		
        else if(childpid == 0){
			close(sockfd);

			//while(1){

				int n;
		 		n = recv(newSocket, buffer.data(), 4999, 0);//receive message from client
                  if (n != -1) {
                     buffer.resize(n); //n will be smaller than the number of elements in the vector, therefore will resize
                     }
                 if ( n < 0 ) printf( "recv failed" );
                 if ( n == 0 ) printf("%s", "All good"); /* got end-of-stream */

				 encrypt(buffer);
				 printVec(buffer);
				 close(fd[0]);
				 write(fd[1], buffer.data(), buffer.size());
    			 close(fd[1]);

				//  struct file_struct deserFile5 =pack109::deserialize_file(buffer);
				//  hs.insert(deserFile5);
				 //hs.print();

				 


               
			//}
		}
		else{
			close(fd[1]);
    		size_t n= read(fd[0], readBuffer.data(), readBuffer.size());
			if (n != -1) {
   				readBuffer.resize(n); //n will be smaller than the number of elements in the vector, therefore will resize
 				}
 				if ( n < 0 ) printf( "recv failed" );
    			if ( n == 0 ) printf("%s", "Allg good"); /* got end-of-stream */


				printf("%s", "IN PARENT PROCESS");
				printVec(readBuffer);
				deserFileGlobal =pack109::deserialize_file(readBuffer);
				hs.insert(deserFileGlobal);
   
    			close(fd[0]);
				close(newSocket);
		}

	 }

    

	hs.print();


        


		// 		if(strcmp(buffer.data(), ":quit") == 0){//if client sends :quit
		// 			printf("Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
		// 			break;
		// 		}else{
        //             vec newVec(5000);
        //             memcpy(newVec.data(), buffer, 4999);
		// 			encrypt(newVec);
        //             memcpy(buffer.data(), newVec.data(), 4999);
        //             printVec(buffer);
		// 			send(newSocket, buffer.data(), buffer.size(), 0);//send message back to client
		// 			bzero(buffer.data(), buffer.size());
		// 		}
    return 0;
}


