#include <string>
#include <iostream>
#include <cstring>
#include "pack109.hpp"
#include <stdio.h>
#include <string.h>
#include <vector>
#include <sstream>

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
    std::string file_name;
    


    for (int i = 1; i < argc; i++) {

printf("%d", i);
        if (strcmp(argv[i], "--hostname") == 0) {
            // Set the flag here, we'll use it later
            host_flag = true;
            address_port = argv[i+1];
           // std::cout <<address_port;
        }

        

    //accept following flag:
    //--hostname address:port - Where address is a IPv4 hostname, 
    //and port is the desired port of the file server. 
    //If this flag isn't provided, the default address is taken to be "localhost" and the default port is taken to be "123

    return 0;
}
