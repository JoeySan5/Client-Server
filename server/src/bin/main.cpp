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
#include <vector>
#include <sys/wait.h>

using namespace pack109;
using namespace std;

//[0]
template<typename T>
std::vector<T> slice(std::vector<T> const &v, int m, int n)
{
    auto first = v.cbegin() + m;
    auto last = v.cbegin() + n + 1;
 
    std::vector<T> vec(first, last);
    return vec;
}

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
	vec exit_vec = {174, 1, 170, 4, 70, 105, 108, 101, 174, 2, 170, 4, 110, 97, 109, 101, 170, 4, 101, 
	120, 105, 116, 170, 5, 98, 121, 116, 101, 115, 172, 4, 162, 101, 162, 120, 162, 105, 162, 116 };

	int fd[2];
	


    sockfd = socket(AF_INET, SOCK_STREAM, 0);//create adult socket
	printf("%d",sockfd);
	if(sockfd < 0){
    printf("Error creating socket");
    exit(EXIT_FAILURE);
    }
    
    bzero((char*)&serverAddr,  sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8081);
	serverAddr.sin_addr.s_addr = INADDR_ANY;
        
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




	struct file_struct deserFile;
	struct Request deserReq;







	// int pipe(int fds[2]);

	// Parameters :
	// fd[0] will be the fd(file descriptor) for the 
	// read end of pipe.
	// fd[1] will be the fd for the write end of pipe.
	// Returns : 0 on Success.
	// -1 on error.
	//[1]

	int pipe_result;
	pipe_result =pipe(fd);

	//[2]

	if (pipe_result<0)
	printf("error");

	addr_size = sizeof(newAddr);

	//[3]

	//Entering loop
	while(1){
		hs.print();
		newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);//accept connection
		printf("\n%d",newSocket);
		if(newSocket < 0){
			printf("%s", "connection not accepted ");
			exit(EXIT_FAILURE);
		}

		printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
		
		childpid = fork();

		if(childpid<0) {
    		printf("Couldn't create child process");
    		return -1;
  		}		
        if(childpid == 0){

			printf("child process");
			close(sockfd);
			


				int n;
		 		n = recv(newSocket, buffer.data(), 4999, 0);//receive message from client
                  if (n != -1) {
                     buffer.resize(n); //n will be smaller than the number of elements in the vector, therefore will resize
                     }
                 if ( n < 0 ) {
					printf( "recv failed" );
					close(sockfd);
					close(newSocket);
					exit(EXIT_FAILURE);
				 };
                 if ( n == 0 ) printf("%s", "All good for recv"); /* got end-of-stream */

				 encrypt(buffer);

				
				// close(fd[0]);
				 write(fd[1], buffer.data(), buffer.size());
    			// close(fd[1]);
				 printf("child process2");

				 
				hs.print();

				 

			exit(0);

               
		}
		else{
			printf("parent process");
			int status;
			int s = wait(&status);
			if (s == -1){
				printf("Error returned from child process");
				close(sockfd);
				close(newSocket);
				exit(EXIT_FAILURE);
			}
			// The wait system-call puts the process to sleep and waits for a child-process to end. 
			// It then fills in the argument with the exit code of the child-process (if the argument is not NULL).
			
			//close(fd[1]);
    		size_t n= read(fd[0], readBuffer.data(), readBuffer.size());
			if (n != -1) {
   				readBuffer.resize(n); //n will be smaller than the number of elements in the vector, therefore will resize
 				}
 				if ( n < 0 ) printf( "recv failed" );
    			if ( n == 0 ) printf("%s", "empty read"); /* got end-of-stream */

				printf("parent process1");

				//checks if client is exiting program, which will therefore close the server
				//in parent process so it exits program completely
				 if (readBuffer == exit_vec){
					close(sockfd);
					close(newSocket);
					printf("\nExit command sent from Client... \nExiting Server");
					exit(EXIT_SUCCESS);
				}
				//close(fd[0]);
				

				printf("\nIN PARENT PROCESS");
				//printVec(readBuffer);
				//this is a comparison vec to check for sending files
				vec check_vec_send = {174, 1, 170, 4};

				//comparison vec to check for requesting files
				vec check_vec_req = {174, 1, 170, 7};

				//slice of vec recieved from client to check if send/req
				vec sub_vec = slice(readBuffer, 0, 3);

				//[4]
				//Checks type of serialized file
				if (sub_vec == check_vec_send){
					deserFile = pack109::deserialize_file(readBuffer);
					hs.insert(deserFile.name,deserFile.bytes);
				}
				else if (sub_vec == check_vec_req){
					deserReq = pack109::deserialize_request(readBuffer);
				}

				printf("parent process2");

				
    		 	
		
			
				close(newSocket);
				printf("parent process3");
		}
		


		
		

	}




    
	printf("%s", "Outside of loop... Final hashset:");
	hs.print();


    
    return 0;
}


