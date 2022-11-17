#include <vector>
#include <stdio.h>
#include <string>
#include <math.h>
#include <iostream>
#include "pack109.hpp"

//serialize bool (just equal to the tag)
vec pack109::serialize(bool item) {
  vec bytes;
  if (item == true) {
    bytes.push_back(PACK109_TRUE);
  } else {
    bytes.push_back(PACK109_FALSE);
  }
  return bytes;
}

//deserialize bool (just equal to the tag)
bool pack109::deserialize_bool(vec bytes) {
  if (bytes.size() < 1) {
     throw;
  }

  if (bytes[0] == PACK109_TRUE) {
    return true;
  } else if (bytes[0] == PACK109_FALSE) {
    return false;
  } else {
    throw;
  }

}
//serialize 8 bit int (tag + 1 byte)
vec pack109::serialize(u8 item) {
  vec bytes;
  bytes.push_back(PACK109_U8);
  bytes.push_back(item);
  return bytes;
}

//deserialize 8 bit int (tag + 1 byte)
u8 pack109::deserialize_u8(vec bytes) {
  if (bytes.size() < 2) {
    throw;
  }
  if (bytes[0] == PACK109_U8) {
    return bytes[1];
  } else {
    throw;
  }
}

//serialize unsigned 32 bit int (tag + 4 bytes, 0...4)
vec pack109::serialize(u32 item) {
  vec bytes;

  //put in tag for u32
  bytes.push_back(PACK109_U32);

  //isolate 1 byte at a time
  u32 bit_mask = 0x000000FF;

  //variable to re-use for the loop
  int bytesLong = sizeof(u32);

  for(int i = 1; i < bytesLong + 1; i++) {
    //first: shift right by difference between desired byte and total length
    //8 bits per byte
    unsigned char byteToPush = (unsigned char)(item >> 8*(bytesLong - i));

    //then: isolate current byte
    byteToPush = byteToPush & bit_mask;

    //push in MSB first, then following bytes
    //printf("what's going in: %x\n", byteToPush);
    bytes.push_back(byteToPush);
  }

  return bytes;

}

//deserialize unsigned 32 bit int (tag + 4 bytes, 0...4)
u32 pack109::deserialize_u32(vec bytes) {
  int bytesLong = sizeof(u32);
  u32 num = 0;

  //if not tag + 4 bytes
  if (bytes.size() < bytesLong+1) {
    throw;
  }
  if (bytes[0] == PACK109_U32) {
    for(int i = 1; i < bytesLong + 1; i++) {
      //put current byte on rightmost bits
      num = num | bytes[i];
          printf("%x ", num);

      //printf("num| bytes[i]: %llx\n", num);

      if(i != bytesLong) {  //do not shift on last one
        num = num << 8; //shift to make room for next byte
        //printf("num shifted: %llx\n", num);
      }
    }

    //printf("end num: %x\n", num);
    return num;
  } else {
    throw;
  }
}

//serialize unsigned 64 bit int (tag + 8 bytes, 0...8)
vec pack109::serialize(u64 item) {
  vec bytes;

  //put in tag for u64
  bytes.push_back(PACK109_U64);

  //isolate 1 byte at a time
  u64 bit_mask = 0x00000000000000FF;

  //variable to re-use for the loop
  int bytesLong = sizeof(u64);

  for(int i = 1; i < bytesLong + 1; i++) {
    //first: shift right by difference between desired byte and total length
    //8 bits per byte
    unsigned char byteToPush = (unsigned char)(item >> 8*(bytesLong - i));

    //then: isolate current byte
    byteToPush = byteToPush & bit_mask;

    //push in MSB first, then following bytes
    //printf("what's going in: %x\n", byteToPush);
    bytes.push_back(byteToPush);
  }

  return bytes;

}

//deserialize unsigned 64 bit int (tag + 8 bytes, 0...8)
u64 pack109::deserialize_u64(vec bytes) {
  int bytesLong = sizeof(u64);
  u64 num = 0;

  //if not tag + 8 bytes
  if (bytes.size() < bytesLong+1) {
    throw;
  }
  if (bytes[0] == PACK109_U64) {
    for(int i = 1; i < bytesLong + 1; i++) {
      //put current byte on rightmost bits
      num = num | bytes[i];
          printf("%x ", num);

      //printf("num| bytes[i]: %llx\n", num);

      if(i != bytesLong) {  //do not shift on last one
        num = num << 8; //shift to make room for next byte
        //printf("num shifted: %llx\n", num);
      }
    }

    //printf("end num: %lx\n", num);
    return num;
  } else {
    throw;
  }
}

//serialize signed 8 bit int (tag + 1 byte)
vec pack109::serialize(i8 item) {
  vec bytes;
  bytes.push_back(PACK109_I8);
  bytes.push_back(item);
  return bytes;
}

//deserialize signed 8 bit int (tag + 1 byte)
i8 pack109::deserialize_i8(vec bytes) {
  if (bytes.size() < 2) {
    throw;
  }
  if (bytes[0] == PACK109_I8) {
    return bytes[1];
  } else {
    throw;
  }
}

//serialize signed 32 bit int (tag + 4 bytes, 0...4)
vec pack109::serialize(i32 item) {
  vec bytes;

  //put in tag for i32
  bytes.push_back(PACK109_I32);

  //isolate 1 byte at a time
  u32 bit_mask = 0x000000FF;

  //variable to re-use for the loop
  int bytesLong = sizeof(i32);

  for(int i = 1; i < bytesLong + 1; i++) {
    //first: shift right by difference between desired byte and total length
    //8 bits per byte
    unsigned char byteToPush = (unsigned char)(item >> 8*(bytesLong - i));

    //then: isolate current byte
    byteToPush = byteToPush & bit_mask;

    //push in MSB first, then following bytes
    //printf("what's going in: %x\n", byteToPush);
    bytes.push_back(byteToPush);
  }

  return bytes;

}

//deserialize signed 32 bit int (tag + 4 bytes, 0...4)
i32 pack109::deserialize_i32(vec bytes) {
  int bytesLong = sizeof(i32);
  i32 num = 0;

  //if not tag + 4 bytes
  if (bytes.size() < bytesLong+1) {
    throw;
  }
  if (bytes[0] == PACK109_I32) {
    for(int i = 1; i < bytesLong + 1; i++) {
      //put current byte on rightmost bits
      num = num | bytes[i];
      //printf("num| bytes[i]: %llx\n", num);

      if(i != bytesLong) {  //do not shift on last one
        num = num << 8; //shift to make room for next byte
        //printf("num shifted: %llx\n", num);
      }
    }

    //printf("end num: %x\n", num);
    return num;
  } else {
    throw;
  }
}

//serialize signed 64 bit int (tag + 8 bytes, 0...8)
vec pack109::serialize(i64 item) {
  vec bytes;

  //put in tag for i64
  bytes.push_back(PACK109_I64);

  //isolate 1 byte at a time
  i64 bit_mask = 0x00000000000000FF;

  //variable to re-use for the loop
  int bytesLong = sizeof(i64);

  for(int i = 1; i < bytesLong + 1; i++) {
    //first: shift right by difference between desired byte and total length
    //8 bits per byte
    unsigned char byteToPush = (unsigned char)(item >> 8*(bytesLong - i));

    //then: isolate current byte
    byteToPush = byteToPush & bit_mask;

    //push in MSB first, then following bytes
    //printf("what's going in: %x\n", byteToPush);
    bytes.push_back(byteToPush);
  }

  return bytes;

}

//deserialize signed 64 bit int (tag + 8 bytes, 0...8)
i64 pack109::deserialize_i64(vec bytes) {
  int bytesLong = sizeof(i64);
  i64 num = 0;

  //if not tag + 8 bytes
  if (bytes.size() < bytesLong+1) {
    throw;
  }
  if (bytes[0] == PACK109_I64) {
    for(int i = 1; i < bytesLong + 1; i++) {
      //put current byte on rightmost bits
      num = num | bytes[i];
      //printf("num| bytes[i]: %llx\n", num);

      if(i != bytesLong) {  //do not shift on last one
        num = num << 8; //shift to make room for next byte
        //printf("num shifted: %llx\n", num);
      }
    }

    //printf("end num: %lx\n", num);
    return num;
  } else {
    throw;
  }
}

// serialize single width floating point (tag + 4 bytes, 0...4)
vec pack109::serialize(f32 item){
  vec bytes;
  int bytesLong = sizeof(f32);

  //put in tag for f32
  bytes.push_back(PACK109_F32);

  //reference: https://stackoverflow.com/questions/7245817/converting-float-to-32-bit-hexadecimal-c
  //convert to char array to access 1 byte at a time
  unsigned char* newItem = (unsigned char*)(&item);

  for(int i = bytesLong - 1; i >= 0; i--) {
    //index order is reversed after casting
    //insert each byte at a time
    //printf("%x\n", newItem[i]);
    bytes.push_back(newItem[i]);
  }

  return bytes;

}

// deserialize single width floating point (tag + 4 bytes, 0...4)
f32 pack109::deserialize_f32(vec bytes) {
  int bytesLong = sizeof(f32);
  u32 num = 0;

  //if not tag + 4 bytes
  if (bytes.size() < bytesLong+1) {
    throw;
  }
  if (bytes[0] == PACK109_F32) {
    for(int i = 1; i < bytesLong + 1; i++) {
      //put current byte on rightmost bits
      num = num | bytes[i];
      //printf("num| bytes[i]: %llx\n", num);

      if(i != bytesLong) {  //do not shift on last one
        num = num << 8; //shift to make room for next byte
        //printf("num shifted: %llx\n", num);
      }
    }

    //printf("end num: %x\n", num);
    return *(f32*)(&num);
  } else {
    throw;
  }
}

// serialize double width floating point (tag + 8 bytes, 0...8)
vec pack109::serialize(f64 item){
  vec bytes;
  int bytesLong = sizeof(f64);

  //put in tag for f64
  bytes.push_back(PACK109_F64);

  //reference: https://stackoverflow.com/questions/7245817/converting-float-to-32-bit-hexadecimal-c
  //convert to char array to access 1 byte at a time
  unsigned char* newItem = (unsigned char*)(&item);

  for(int i = bytesLong - 1; i >= 0; i--) {
    //index order is reversed after casting
    //insert each byte at a time
    //printf("%x\n", newItem[i]);
    bytes.push_back(newItem[i]);
  }

  return bytes;

}

// deserialize double width floating point (tag + 8 bytes, 0...8)
f64 pack109::deserialize_f64(vec bytes) {
  int bytesLong = sizeof(f64);
  u64 num = 0;

  //if not tag + 8 bytes
  if (bytes.size() < bytesLong+1) {
    throw;
  }
  if (bytes[0] == PACK109_F64) {
    for(int i = 1; i < bytesLong + 1; i++) {
      //put current byte on rightmost bits
      num = num | bytes[i];
      //printf("num| bytes[i]: %llx\n", num);

      if(i != bytesLong) {  //do not shift on last one
        num = num << 8; //shift to make room for next byte
        //printf("num shifted: %llx\n", num);
      }
    }

    //printf("end num: %x\n", num);
    return *(f64*)(&num);
  } else {
    throw;
  }
}

//serialize a string with length up to 2^8-1 bytes (tag + 1 byte length + data) or up to 2^16 - 1 bytes (tag + 2 bytes length + data)
vec pack109::serialize(string item) {
  vec bytes;

  //determine if it's s8 or s16
  u32 length = item.length();
  //printf("length:%lx\n", length);

  //put in proper tag based on length
  //load in proper length
  if(length > pow(2, 8) - 1) {
    bytes.push_back(PACK109_S16);

    u8 length1 = (u8) ((length & 0x0000FF00) >> 8); //isolate first half of 16 bit length
    //printf("length1:%lx\n", length1);
    bytes.push_back(length1);
    
    u8 length2 = (u8) (length & 0x000000FF); //isolate second half of 16 bit length
    //printf("length2:%lx\n", length2);
    bytes.push_back(length2);
  } else {
    bytes.push_back(PACK109_S8);
    //printf("length u8:%lx\n", (u8)length);
    bytes.push_back((u8)length);
  }

  //insert string data
  for(int i = 0; i < length; i++) {
    //each char = 1 byte, insert one char at a time
    //printf("what's going in: %x\n", item[i]);
    bytes.push_back(item[i]);
  }

  return bytes;

}

//deserialize a string with length up to 2^8-1 bytes (tag + 1 byte length + data) or up to 2^16 - 1 bytes (tag + 2 bytes length + data)
string pack109::deserialize_string(vec bytes) {
  string str = "";

  //if below s8 size (tag + length + data) or above s16 size (tag + length*2 + data)
  if (bytes.size() < 3 || bytes.size() > (3 + pow(2, 16) - 1)) {
    throw;
  }

  //starting byte for data depends on type
  int i = 0;
  int length;

  if (bytes[0] == PACK109_S8) {
    i = 2;              //start at 3rd byte
    length = bytes[1];
  } else if (bytes[0] == PACK109_S16) {
    i = 3;              //start at 4th byte
    length = (((u32)bytes[1]) << 8) | (u32)bytes[2];  //length is 2 bytes after tag
  } else {
    throw;
  }

  for(int j = 1; j <= length; j++) {
    str += bytes[i];
    i++;
  }

  //printf("%s\n", bytes[i]);
  //std::cout << str << std::endl;
  return str;
  
}

//serialize array of u8s with length up to 2^8-1 bytes (tag + 1 byte length + data) or up to 2^16 - 1 bytes (tag + 2 bytes length + data)
vec pack109::serialize(std::vector<u8> item) {
  vec bytes;

  //determine if it's a8 or a16
  u32 length = item.size();
  //printf("length:%lx\n", length);

  //put in proper tag based on length
  //load in proper length
  if(length > pow(2, 8) - 1) {
    bytes.push_back(PACK109_A16);

    u8 length1 = (u8) ((length & 0x0000FF00) >> 8); //isolate first half of 16 bit length
    //printf("length1:%lx\n", length1);
    bytes.push_back(length1);
    
    u8 length2 = (u8) (length & 0x000000FF); //isolate second half of 16 bit length
    //printf("length2:%lx\n", length2);
    bytes.push_back(length2);
  } else {
    bytes.push_back(PACK109_A8);
    //printf("length u8:%lx\n", (u8)length);
    bytes.push_back((u8)length);
  }
  

  //insert data
  //reference: https://www.includehelp.com/stl/appending-a-vector-to-a-vector.aspx
  for(int i = 0; i < length; i++) {
    //serialize each element, then append to bytes vector
    vec elementSer = pack109::serialize(item[i]);
    bytes.insert(bytes.end(), elementSer.begin(), elementSer.end());
    //the above code allowes for concat, bcuz you are basically passing in a vector of bytes
    
  }

  return bytes;

}

//deserialize array of u8s with length up to 2^8-1 bytes (tag + 1 byte length + data) or up to 2^16 - 1 bytes (tag + 2 bytes length + data)
std::vector<u8> pack109::deserialize_vec_u8(vec bytes) {
  std::vector<u8> arr;

  //if below a8 size (tag + length + data) or above a16 size (tag + length*2 + data + tag per data)
  if (bytes.size() < 3 || bytes.size() > (3 + 2*(pow(2, 16) - 1))) {
    throw;
  }

  //starting byte for data depends on type
  int i = 0;

  if (bytes[0] == PACK109_A8) {
    i = 2;              //start at 3rd byte
  } else if (bytes[0] == PACK109_A16) {
    i = 3;              //start at 4th byte
  } else {
    throw;
  }

  while(bytes[i] != NULL) {
    //printf("%s\n", bytes[i]);
    //std::cout << bytes[i] << std::endl;
    //each u8 is 2 bytes (tag + data)
    vec currentItem = {bytes[i], bytes[i+1]};
    arr.push_back(pack109::deserialize_u8(currentItem));
    i+=2;
  }

  //printf("%s\n", bytes[i]);
  //std::cout << str << std::endl;
  return arr;
  
}

//serialize array of u64s with length up to 2^8-1 bytes (tag + 1 byte length + data) or up to 2^16 - 1 bytes (tag + 2 bytes length + data)
vec pack109::serialize(std::vector<u64> item) {
  vec bytes;

  //determine if it's a8 or a16
  u32 length = item.size();
  //printf("length:%lx\n", length);

  //put in proper tag based on length
  //load in proper length
  if(length > pow(2, 8) - 1) {
    bytes.push_back(PACK109_A16);

    u8 length1 = (u8) ((length & 0x0000FF00) >> 8); //isolate first half of 16 bit length
    //printf("length1:%lx\n", length1);
    bytes.push_back(length1);
    
    u8 length2 = (u8) (length & 0x000000FF); //isolate second half of 16 bit length
    //printf("length2:%lx\n", length2);
    bytes.push_back(length2);
  } else {
    bytes.push_back(PACK109_A8);
    //printf("length u8:%lx\n", (u8)length);
    bytes.push_back((u8)length);
  }
  

  //insert data
  //reference: https://www.includehelp.com/stl/appending-a-vector-to-a-vector.aspx
  for(int i = 0; i < length; i++) {
    //serialize each element, then append to bytes vector
    vec elementSer = pack109::serialize(item[i]);
    bytes.insert(bytes.end(), elementSer.begin(), elementSer.end());
  }

  return bytes;

}

//deserialize array of u64s with length up to 2^8-1 bytes (tag + 1 byte length + data) or up to 2^16 - 1 bytes (tag + 2 bytes length + data)
std::vector<u64> pack109::deserialize_vec_u64(vec bytes) {
  std::vector<u64> arr;

  //if below a8 size (tag + length + (tag + 8 bytes) data) or above a16 size (tag + length*2 + (tag + 8 bytes) per data)
  if (bytes.size() < (2+9) || bytes.size() > (3 + (9)*(pow(2, 16) - 1))) {
    throw;
  }

  //starting byte for data depends on type
  int i = 0;

  if (bytes[0] == PACK109_A8) {
    i = 2;              //start at 3rd byte
  } else if (bytes[0] == PACK109_A16) {
    i = 3;              //start at 4th byte
  } else {
    throw;
  }
  
  while(bytes[i] != NULL) {
    //printf("%s\n", bytes[i]);
    //std::cout << bytes[i] << std::endl;
    //each u64 is 9 bytes (tag + 8 bytes of data)
    vec currentItem = {bytes[i], bytes[i+1], bytes[i+2], bytes[i+3], bytes[i+4], bytes[i+5], bytes[i+6], bytes[i+7], bytes[i+8]};
    arr.push_back(pack109::deserialize_u64(currentItem));
    i+=9;
  }

  //printf("%s\n", bytes[i]);
  //std::cout << str << std::endl;
  return arr;
  
}

//serialize array of f64s with length up to 2^8-1 bytes (tag + 1 byte length + data) or up to 2^16 - 1 bytes (tag + 2 bytes length + data)
vec pack109::serialize(std::vector<f64> item) {
  vec bytes;

  //determine if it's a8 or a16
  u32 length = item.size();
  //printf("length:%lx\n", length);

  //put in proper tag based on length
  //load in proper length
  if(length > pow(2, 8) - 1) {
    bytes.push_back(PACK109_A16);

    u8 length1 = (u8) ((length & 0x0000FF00) >> 8); //isolate first half of 16 bit length
    //printf("length1:%lx\n", length1);
    bytes.push_back(length1);
    
    u8 length2 = (u8) (length & 0x000000FF); //isolate second half of 16 bit length
    //printf("length2:%lx\n", length2);
    bytes.push_back(length2);
  } else {
    bytes.push_back(PACK109_A8);
    //printf("length u8:%lx\n", (u8)length);
    bytes.push_back((u8)length);
  }
  

  //insert data
  //reference: https://www.includehelp.com/stl/appending-a-vector-to-a-vector.aspx
  for(int i = 0; i < length; i++) {
    //serialize each element, then append to bytes vector
    vec elementSer = pack109::serialize(item[i]);
    bytes.insert(bytes.end(), elementSer.begin(), elementSer.end());
  }

  return bytes;

}

//deserialize array of f64s with length up to 2^8-1 bytes (tag + 1 byte length + data) or up to 2^16 - 1 bytes (tag + 2 bytes length + data)
std::vector<f64> pack109::deserialize_vec_f64(vec bytes) {
  std::vector<f64> arr;

  //if below a8 size (tag + length + data) or above a16 size (tag + length*2 + (tag + 8 bytes) per data)
  if (bytes.size() < (2+9) || bytes.size() > (3 + (9)*(pow(2, 16) - 1))) {
    throw;
  }

  //starting byte for data depends on type
  int i = 0;

  if (bytes[0] == PACK109_A8) {
    i = 2;              //start at 3rd byte
  } else if (bytes[0] == PACK109_A16) {
    i = 3;              //start at 4th byte
  } else {
    throw;
  }
  
  while(bytes[i] != NULL) {
    //printf("%s\n", bytes[i]);
    //std::cout << bytes[i] << std::endl;
    //each f64 is 9 bytes (tag + 8 bytes of data)
    vec currentItem = {bytes[i], bytes[i+1], bytes[i+2], bytes[i+3], bytes[i+4], bytes[i+5], bytes[i+6], bytes[i+7], bytes[i+8]};
    arr.push_back(pack109::deserialize_f64(currentItem));
    i+=9;
  }

  //printf("%s\n", bytes[i]);
  //std::cout << str << std::endl;
  return arr;
  
}



//serialize array of strings with length up to 2^8-1 bytes (tag + 1 byte length + data) or up to 2^16 - 1 bytes (tag + 2 bytes length + data)
vec pack109::serialize(std::vector<string> item) {
  vec bytes;

  //determine if it's a8 or a16
  u32 length = item.size();
  //printf("length:%lx\n", length);

  //put in proper tag based on length
  //load in proper length
  if(length > pow(2, 8) - 1) {
    bytes.push_back(PACK109_A16);

    u8 length1 = (u8) ((length & 0x0000FF00) >> 8); //isolate first half of 16 bit length
    //printf("length1:%lx\n", length1);
    bytes.push_back(length1);
    
    u8 length2 = (u8) (length & 0x000000FF); //isolate second half of 16 bit length
    //printf("length2:%lx\n", length2);
    bytes.push_back(length2);
  } else {
    bytes.push_back(PACK109_A8);
    //printf("length u8:%lx\n", (u8)length);
    bytes.push_back((u8)length);
  }
  

  //insert data
  //reference: https://www.includehelp.com/stl/appending-a-vector-to-a-vector.aspx
  for(int i = 0; i < length; i++) {
    //serialize each element, then append to bytes vector
    vec elementSer = pack109::serialize(item[i]);
    bytes.insert(bytes.end(), elementSer.begin(), elementSer.end());
  }

  return bytes;

}

//deserialize array of strings with length up to 2^8-1 bytes (tag + 1 byte length + data) or up to 2^16 - 1 bytes (tag + 2 bytes length + data)
std::vector<string> pack109::deserialize_vec_string(vec bytes) {
  std::vector<string> arr;

  //if below a8 size (tag + length + (tag + length + data)) or above a16 size (tag + length*2 + (tag + length*2 + 2^16 -1 bytes) per data)
  if (bytes.size() < (2+3) || bytes.size() > (3 + ((pow(2, 16) - 1) * (3 + pow(2, 16) - 1)))) {
    throw;
  }

  //starting byte for data and total length depends on type
  int i = 0;
  int numItems = 0;

  if (bytes[0] == PACK109_A8) {
    i = 2;                //start at 3rd byte
    numItems = bytes[1];  //for a8, length is 2nd byte
  } else if (bytes[0] == PACK109_A16) {
    i = 3;                                              //start at 4th byte
    numItems = (((u32)bytes[1]) << 8) | (u32)bytes[2];  //for a16 length is 2 bytes after tag
  } else {
    throw;
  }

  if(bytes[i] == PACK109_S8) {
    int itemCounter = 0;

    while(itemCounter < numItems) {
      vec currentItem;
      int length = bytes[i+1];  //length is directly after tag
      //go through tag + length byte + data length
      for(int j = 0; j < length + 2; j++) {
        currentItem.push_back(bytes[i]);
        i++;
      }
      arr.push_back(pack109::deserialize_string(currentItem));
      itemCounter++;
    }
  } else if(bytes[i] == PACK109_S16) {
    int itemCounter = 0;

    while(itemCounter < numItems) {
      vec currentItem;
      int length = (((u32)bytes[i+1]) << 8) | (u32)bytes[i+2];  //length is 2 bytes after tag
      //go through tag + 2 length bytes + data length
      for(int j = 0; j < length + 3; j++) {
        currentItem.push_back(bytes[i]);
        i++;
      }
      arr.push_back(pack109::deserialize_string(currentItem));
      itemCounter++;
    }
  }

  return arr;
  
}

vec pack109::serialize(struct file_struct *file) {
        vec bytes;
        u32 length = file->bytes.size();
        std::cout << length;

        if(length > 255){
            bytes.push_back(PACK109_M16);

            u8 length1 = (u8) ((length & 0x0000FF00) >> 8);
            bytes.push_back(length1);
            u8 length2 = (u8) (length & 0x000000FF);
            bytes.push_back(length2);
        }else{
            bytes.push_back(PACK109_M8);
            bytes.push_back((u8)length);
        }


        return bytes;
    }

//serialize Person Struct
vec pack109::serialize(struct Person item) {
  vec bytes;
  bytes.push_back(PACK109_M8);  //Person always has less than 2^8 elements
  bytes.push_back(0x01);        //Person always has one kv pair

  //add key for map type ("Person")
  string mapType = "Person";
  vec keyPerson = pack109::serialize(mapType);
  bytes.insert(bytes.end(), keyPerson.begin(), keyPerson.end());

  //value associated with mapType key "Person" is a map of 3 kv pairs
  bytes.push_back(0xAE);
  bytes.push_back(0x03);

  //add key for first pair ("age")
  string key1 = "age";
  vec keyAge = pack109::serialize(key1);
  bytes.insert(bytes.end(), keyAge.begin(), keyAge.end());

  //add value for first pair (age val)
  vec age = pack109::serialize(item.age);
  bytes.insert(bytes.end(), age.begin(), age.end());

  //add key for second pair ("height")
  string key2 = "height";
  vec keyHeight = pack109::serialize(key2);
  bytes.insert(bytes.end(), keyHeight.begin(), keyHeight.end());

  //add value for second pair (height val)
  vec height = pack109::serialize(item.height);
  bytes.insert(bytes.end(), height.begin(), height.end());

  //add key for third pair ("name")
  string key3 = "name";
  vec keyName = pack109::serialize(key3);
  bytes.insert(bytes.end(), keyName.begin(), keyName.end());

  //add value for third pair (name val)
  vec name = pack109::serialize(item.name);
  bytes.insert(bytes.end(), name.begin(), name.end());

  return bytes;
}

//deserialize Person Struct
struct Person pack109::deserialize_person(vec bytes) {
  struct Person person;
    
  if (bytes[0] == PACK109_M8) {
    int pairCounter = 0;
    int i = 17; //start at content of age

    //get age value (tag + 1 byte for u8)
    vec age = {bytes[i], bytes[i+1]};
    person.age = pack109::deserialize_u8(age);
    
    //skip past u8 tag + contents(1), s8 tag + length + contents(6), go to content of height
    i += 10;

    //get height value (tag + 4 bytes for f32)
    vec height = {bytes[i], bytes[i+1], bytes[i+2], bytes[i+3], bytes[i+4]};
    person.height = pack109::deserialize_f32(height);

    //skip past f32 tag + float contents(4) + s8 tag + length + contents(4), go to contents of name
    i += 11;

    //get name value (varied length)
    vec name;
    name.push_back(bytes[i]);     //get tag
    //go through length of name
    int length = bytes[i+1];
    name.push_back(bytes[i+1]);   //get length
    i+=2;
    for(int j = 1; j <= length; j++) {
      name.push_back(bytes[i]);
      i++;
    }
    person.name = pack109::deserialize_string(name);
  } else throw;
  
  return person;
}

//print vector
void pack109::printVec(vec &bytes) {
  printf("[ ");
  for (int i = 0; i < bytes.size(); i++) {
    printf("%x ", bytes[i]);
  }
  printf("]\n");
}