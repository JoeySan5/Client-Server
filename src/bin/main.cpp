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




	struct file_struct deserFileGlobal;
	struct Request deserReqGlobal;







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

	while(1){
		hs.print();
		newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);//accept connection
		printf("\n%d",newSocket);
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
        if(childpid == 0){

			printf("child process");
			close(sockfd);
			


				int n;
		 		n = recv(newSocket, buffer.data(), 4999, 0);//receive message from client
                  if (n != -1) {
                     buffer.resize(n); //n will be smaller than the number of elements in the vector, therefore will resize
                     }
                 if ( n < 0 ) printf( "recv failed" );
                 if ( n == 0 ) printf("%s", "All good"); /* got end-of-stream */

				 encrypt(buffer);
				// printVec(buffer);
				 close(fd[0]);
				 write(fd[1], buffer.data(), buffer.size());
    			 close(fd[1]);
				 printf("child process2");

				 
				hs.print();

				 

			exit(0);

               
		}
		else{
			printf("parent process");
			int status;
			wait(&status);
			// The wait system-call puts the process to sleep and waits for a child-process to end. 
			// It then fills in the argument with the exit code of the child-process (if the argument is not NULL).
			
			close(fd[1]);
    		size_t n= read(fd[0], readBuffer.data(), readBuffer.size());
			if (n != -1) {
   				readBuffer.resize(n); //n will be smaller than the number of elements in the vector, therefore will resize
 				}
 				if ( n < 0 ) printf( "recv failed" );
    			if ( n == 0 ) printf("%s", "Allg good"); /* got end-of-stream */

				printf("parent process1");


				//printf("%s", "IN PARENT PROCESS");
				//printVec(readBuffer);
				vec checkVec = {174, 1, 170, 7};

				vec sub_vec = slice(readBuffer, 0, 3);
				//printVec(sub_vec);

				// [4]
				// if (checkVec != sub_vec){
				// 	deserFileGlobal =pack109::deserialize_file(readBuffer);
				// hs.insert(deserFileGlobal.name,deserFileGlobal.bytes);
				// }
				// else{
				// 		deserReqGlobal = pack109::deserialize_request(readBuffer);
				// }

				printf("parent process2");

				
    		 	close(fd[0]);
		
			
				close(newSocket);
				printf("parent process3");
		}
		


		if(argv[1] == "quit"){
			close(sockfd);
			close(newSocket);
			break;
		}
		

	 }




    
	printf("%s", "Outside of loop... Final hashset:");
	hs.print();


    
    return 0;
}


