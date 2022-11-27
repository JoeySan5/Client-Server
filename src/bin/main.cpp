#include <string>
#include <iostream>
#include <cstring>
#include "pack109.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <iterator>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

using namespace std;




int main(int argc, char const *argv[])
{

    bool host_flag = false;
    bool send_flag = false;
    bool request_flag = false;
    pack109::serialize(13);
    std::string address_port;
    std::string address;
    std::string port;
    std::string file_path;
    std::string file_name;
    


    for (int i = 1; i < argc; i++) {

        if (strcmp(argv[i], "--hostname") == 0) {
            // Set the flag here, we'll use it later
            host_flag = true;
            address_port = argv[i+1];
           // std::cout <<address_port;
        }
        if (strcmp(argv[i], "--send") == 0) {
            file_path = argv[i+1];
            send_flag = true;
        }
        if( (strcmp(argv[i], "--request") == 0) ){
            file_path = argv[i+1];
            request_flag = true;
        }
        
    }

    if( ((request_flag == true) && (send_flag == true)) || ((request_flag == false) && (send_flag == false)) ){
            printf("ENDING PROGRAM");
            return 2;
        }

    if (host_flag == false){
        address = "localhost";
        port = "123";
        std::cout <<address<< port;

    }
    else if(host_flag == true){
        std::vector<std::string> v = pack109::split(address_port, ':');
        address = v[0];
        port = v[1];
      //  std::cout <<address <<"\n"<< port;
        //printf("HELLO");
    }

     //to get name of file (w/ out path)
	 std::vector<std::string> v = pack109::split(file_path, '/');
	 file_name = v[v.size() -1];
     //std::cout << file_name;


    streampos size; //this type is used for buffer and file positioning, can be converted to int to show size of a file
    vec bytes;

	//ifstream to read in a file
	ifstream my_file(file_path, ios::in|ios::binary);//this line allows for .open() to be called as well//ios::in allows for input operations & ios::binary allows to open in binary mode ios::ate sets pos to the end of the file
	if (my_file.is_open()){
  bytes.insert(bytes.end(),std::istreambuf_iterator<char>(my_file),std::istreambuf_iterator<char>()); //concats to the end of bytes, from beg of my_file to the end 
  //must use istreambuf_iterator when working with binary
        
    cout << "the entire file content is in memory\n";
    for (int i = 0; i < bytes.size(); i++) {
    printf("%x ", bytes[i]);
  }

  }
  else {
    cout << "Unable to open file";
    return 2;
}

    struct file_struct file = {file_name, bytes};
    
    //storing file struct as a serialized vec of bytes in "serialized"
    vec serialized = pack109::serialize(file);

        pack109::printVec(serialized);


    pack109::encrypt(serialized);


    //BEGINNING OF SOCKET INITIALIZATION

    int sockfd, portno, n; //sockfd is a socket descriptor that points to the file table that contains info on what action will take place (read,write etc)
    //portno is the port number
    //n is the return value for the read() and write() calls; i.e. it contains the number of characters read or written.

    struct sockaddr_in serv_addr; //contain the address of the server which we want to connect to
    struct hostent *server; //defines the host computer on the internet

    char buffer[256]; //server reads characters from the socket connection into this buffer.

    portno = stoi(port); //convert string to int

    sockfd = socket(AF_INET, SOCK_STREAM, 0); //this creates a new socket. first arg is internet based app(internet domain for any 2 hosts), 
    //second arg is continous stream in which characters are read(like a pipe)
    //third arg should be 0 and OS will choose TCP for stream socket and UCP for datagram sockets


    if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }

     
   if ((server = gethostbyname("127.0.0.1")) == nullptr){
        perror("errorhostname");
        exit(EXIT_FAILURE);
   } // this reutns a struct of hostent, which contains info of the host, *h_addr contains the IP address
   //for future , use get addrinfo for better efficiency

        printf("%s %s", server->h_name, "nuts");

   //a buffer is a region of memory temporarily holding data while it(the data) is being moved to another place
    bzero((char *) &serv_addr, sizeof(serv_addr)); //bzero causes for all serv_addr members to be zeros
    serv_addr.sin_family = AF_INET; //declares that the address family is internet based
    bcopy((char *)server->h_name, (char *)&serv_addr.sin_addr.s_addr, server->h_length); //bcopy(char*src,char*dest,int length) copies length bytes from src to dest. they may overlap
    serv_addr.sin_port = htons(portno);//htons() converts 16-bit number in host byte order and returns a 16-bit number in network byte order used in TCP/IP networks

    
    //Connecting to Server

     if (connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0){ //connect() takes in file descriptor, address ofhost toconnect to(including port #), and size of address, returns 0 on success, -1 on fail

       perror("ERROR connecting");
       exit(1);
   }

     printf("Please enter the message: ");
   bzero(buffer,256);
   fgets(buffer,255,stdin);
   
   /* Send message to the server */
   n = write(sockfd, buffer, strlen(buffer));
   
   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }
   
   /* Now read server response */
   bzero(buffer,256);
   n = read(sockfd, buffer, 255);
   
   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }
	
   printf("%s\n",buffer);



    return 0;
}
