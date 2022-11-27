#include <string>
#include <iostream>
#include <cstring>
#include "pack109.hpp"
#include <stdio.h>
#include <string.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <iterator>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

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


    pack109::printVec(serialized);

        pack109::encrypt(serialized);

            pack109::printVec(serialized);





    

    return 0;
}
