#include <vector>
#include <string>
#include <cstdlib>

#ifndef PACK109_HPP
#define PACK109_HPP

typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long u64;
typedef signed char i8;
typedef signed int i32;
typedef signed long i64;
typedef float f32;
typedef double f64;
typedef std::vector<u8> vec;
typedef std::string string;

#define PACK109_TRUE  0xa0
#define PACK109_FALSE 0xa1
#define PACK109_U8    0xa2
#define PACK109_U32   0xa3
#define PACK109_U64   0xa4
#define PACK109_I8    0xa5
#define PACK109_I32   0xa6
#define PACK109_I64   0xa7
#define PACK109_F32   0xa8
#define PACK109_F64   0xa9
#define PACK109_S8    0xaa
#define PACK109_S16   0xab
#define PACK109_A8    0xac
#define PACK109_A16   0xad
#define PACK109_M8    0xae
#define PACK109_M16   0xaf



struct Person {
  u8 age;
  f32 height;
  string name;
};

//generic file struct
struct file_struct{
  string name;
  vec bytes;
  bool operator==(const file_struct& other) const {
    return this->name == other.name;
  }
  //  bool operator==(nullptr_t) const {
  //    return false;
  //  }

  bool operator==(long int value) const {
        // return true if the value of the file_struct is equal to the given value
        // and false otherwise
        if (value == 0){
          return true;
        }
        else{
          return false;
        }
    }

  bool operator<(const file_struct& other) const {
    
    return this->name < other.name;
  }
};

struct Request {
  string name; // The name of the requested file, e.g. document.txt
};



// //THE FOLLOWING ARE UNIX SOCKET STRUCTS
// //generic socket address struct
// struct sockaddr {
//    unsigned short   sa_family; //represents address family, for internet apps, use AF_INET
//    char             sa_data[14]; // represents the 14 bytes of protocol specific addresses, based on the above family. for internet family, will use port number IP address represented by sockaddr_in
// };

// //structure is used only in the above structure as a structure field and holds 32 bit netid/hostid.
// struct in_addr {
//    unsigned long s_addr; //32-bit IP address in Network Byte Order.
// };


// //second struct to reference sockets elements
// struct sockaddr_in {
//    short int            sin_family; //represents address family
//    unsigned short int   sin_port; //16-bit port number in Network Byte Order.
//    struct in_addr       sin_addr; //32-bit IP address in Network Byte Order.
//    unsigned char        sin_zero[8]; //You just set this value to NULL as this is not being used.
// };



// //used to keep info related to the host
// struct hostent {
//    char *h_name; //official name of host e.g google.com
//    char **h_aliases; //holds list of name aliases
//    int h_addrtype;  //contains address family, and in internet based apps it is always AF_INET
//    int h_length;    //holds lenght of ip address, 4 for internet address
//    char **h_addr_list; //holds the list of addresses, for the internet ,the array of pointers h_addr_list[0], h_addr_list[1], and so on, are points to structure in_addr.
	
// #define h_addr  h_addr_list[0] //allows for backward compatability
// };

// //used to keep info related to the service and associated ports
// struct servent {
//    char  *s_name; //This is the official name of the service. For example, HTTP, SMTP, FTP POP3, etc.
//    char  **s_aliases; //It holds the list of service aliases. Most of the time this will be set to NULL.
//    int   s_port;  //will have associated port number. For example, for HTTP, this will be 80.
//    char  *s_proto; //It is set to the protocol used. Internet services are provided using either TCP or UDP.
// };



namespace pack109 {
  void printVec(vec &bytes);

  // Boolean

  vec serialize(bool item);
  bool deserialize_bool(vec bytes);

  // Integers

  vec serialize(u8 item);
  u8 deserialize_u8(vec bytes);

  vec serialize(u32 item);
  u32 deserialize_u32(vec bytes);

  vec serialize(u64 item);
  u64 deserialize_u64(vec bytes);

  vec serialize(i8 item);
  i8 deserialize_i8(vec bytes);

  vec serialize(i32 item);
  i32 deserialize_i32(vec bytes);

  vec serialize(i64 item);
  i64 deserialize_i64(vec bytes);

  // Floats

  vec serialize(f32 item);
  f32 deserialize_f32(vec bytes);

  vec serialize(f64 item);
  f64 deserialize_f64(vec bytes);

  // Strings

  vec serialize(string item);
  string deserialize_string(vec bytes);
  
  // Arrays
  vec serialize(std::vector<u8> item);
  vec serialize(std::vector<u64> item);
  vec serialize(std::vector<f64> item);
  vec serialize(std::vector<string> item);


  std::vector<u8> deserialize_vec_u8(vec bytes);
  std::vector<u64> deserialize_vec_u64(vec bytes);
  std::vector<f64> deserialize_vec_f64(vec bytes);
  std::vector<string> deserialize_vec_string(vec bytes);

  std::vector<std::string> split(const std::string &s, char delim);
  void encrypt(vec &bytes);


  // Maps
  vec serialize(struct Person item);
  struct Person deserialize_person(vec bytes);

  vec serialize (struct Request &reqFile);

  vec serialize(struct file_struct &file);

  struct file_struct deserialize_file(vec bytes);

}

#endif
