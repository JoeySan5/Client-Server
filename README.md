
Project contains two main parts: 
1. File Server - A file server is a program that hosts files for clients. It receives files that clients want to store, and sends them back to the client (or other clients) when they are requested. 
2. Client - This program connects to the server and can send files to it, which will be stored on the file server. The client can also request files from the file server. 

## Part 2 - File Server

There are three cuts to this exam. You can choose the one you wish to complete based on how ambitious you are. The harder the cut, the higher the maximum grade you can earn. You should specify in the cut you chose at the beginning of your oral explanation.

No matter which version you choose, the file server program should accept the following flag:

1. `--hostname address:port` - Where `address` is a 32 bit IP address, and `port` is the desired port of the file server.

If you call the program without a `--hostname`, it should use the default of `localhost:8081`.


---

### Cut 1 - Single Serve

The maximum grade for this cut is a **`B (85%)`**.

- Q1-1. The server will start, bind a socket to a port, and listen for a connection.
- When an connection is established, it will attempt to read a message from the client. The message will either be a `File` message or a `Request` message.
- The server will service the message in the following steps:
  - Q1-2. Read the message to a buffer
  - Q1-3. Decrypt the message
  - Q1-4 Deserialize the message to the appropriate struct, either a `File` or `Request`.
    - Q1-5. If the message is a `File`, then the server will save the file to disk in a folder called `received`.
    - Q1-6. If the message is a `Request`, then the server will look for the requested file in the `received` folder. 
      - If the requested file does not exist, nothing will be sent back to the client.
      - Q1-7. If the file does exist it will be read into memory, serialized into a `File` message, encrypted, and sent to the client.
    - After servicing this one message, the file server will exit.
    - If you want to send or request another file from the file server, you must restart the file server so it can service another request.

---

### Cut 2 - Sustained Connection

The maximum grade for this cut is an **`A (93%)`**.

- Q2-1. The server will start, bind a socket to a port, and listen for a connection.
- Q2-2. The server will create an empty hash map to store received files in memory.
  - You have to write the hash map yourself. You can't use a library that you did not write. You can use your Homework 6 code or the posted solution as a starting point. Remember to cite this code if you use it. If you look at any source for help, be sure to cite it.
  - The hash map will use the filename string as a key, and the file as a value (this can be either the received `File`, or the file data `vector<u8>`).
  - The hashmap will act much like the hash set, except it will have two additional methods:
    - Q2-3. `bool insert(String key, File value);` - inserts the k/v pair into the hash map. Returns true if the key already existed, and replaces the stored value with the supplied value. Returns false if the key did not exist already.
    - Q2-4. `File get(String key);` - Returns the file associated with the supplied key. If the key doesn't exist, this function throws an exception.
- When the server receives a connection, it will enter an infinite loop.
  - This loop will attempt to receive data from the client. When it receives a message, it will follow the following steps:
    - Q2-5. Read the message to a buffer
    - Q2-6. Decrypt the message
    - Q2-7. Deserialize the message to the appropriate struct, either a `File` or `Request`.
      - Q2-8. If the message is a `File`, then the server will insert the filename and file into the hash map.
      - Q2-9.If the message is a `Request`, then the server will look for the requested file in hash map. 
        - If the requested file does not exist, nothing will be sent back to the client.
        - Q2-10. If the file does exist it will be serialized into a `File` message, encrypted, and sent to the client.
  - After servicing this message, the file server will loop and wait for a new message from the client.
  - The file server will not terminate until the user terminates the program or the client terminates the connection.
  - To properly test this cut of the file server, you will have to modify your client to be able to send multiple messages without terminating the connection.

---

### Cut 3 - Multiple Connections

The maximum grade for this cut is an **`A+ (100%)`**.

- Q3-1. The server will start, bind a socket to a port, and listen for a connection.
- Q3-2. The server will create an empty hash map to store received files in memory. See the previous section for instructions on how to do that.
- The server will then enter an infinite loop and wait for new connections.
- Q3-3. When the server receives a connection, it will fork a new process and attempt to receive a message. When the child process receives a message, it will follow the following steps:
  - Q3-4. Read the message to a buffer
  - Q3-5. Decrypt the message
  - Q2-6. Deserialize the message to the appropriate struct, either a `File` or `Request`.
    - Q3-7. If the message is a `File`, then the server will insert the filename and file into the hash map.
    - Q3-8. If the message is a `Request`, then the server will look for the requested file in hash map. 
      - If the requested file does not exist, nothing will be sent back to the client.
      - Q3-9. If the file does exist it will be serialized into a `File` message, encrypted, and sent to the client.
  - When the message is sent, the file server should terminate the connection with the client
- Meanwhile, the parent process will be listening for new connections. When a new connection comes in, it will fork a new process and service that connection as laid out above.
- Q3-10. Here is the difficulty with this cut of the problem. When a new process is forked, it loses contact with the parent process. Everything that happens in the forked process will stay in that process. So the file that's received and stored in the child process will not appear in the hash map of the parent process. Therefore, if a new connection requests that file, it will be as if it has never been sent in the first place.
  - You can use a number of tools to solve this:
    - You could open a second socket between the parent and child process and send the file through that channel (this is probably the easiest method since you already have the knowledge to do this).
    - You could use shared memory (see `shmem()`).
    - You could use [boost IPC](https://www.boost.org/doc/libs/1_68_0/doc/html/interprocess.html).
    - You could use files.

## Message Protocol

### Serialized File

If you have a file called `file.txt` with the contents `Hello`, then the serialzied, unencrypted message should look like this:

```
┌───────────────────────────────────────────────────────────────────────────────┐
│0xae     // map tag                                                            │
│0x01     // 1 kv pair                                                          │
├───────────────────────────────────────────────────────┬───────────┬───────────┤
│0xaa     // string8 tag                                │           │           │
│0x04     // 4 characters                               │ key       │           │
│File     // the string "File"                          │           │           │
├───────────────────────────────────────────────────────┼───────────┤  pair 1   │
│0xae     // the value associated with the key is a map │           │           │
│0x02     // 2 kv pairs                                 │           │           │
├────────────────────────────────┬───────────┬──────────┤           │           │
│0xaa     // string8 tag         │           │          │           │           │
│0x04     // 4 characters        │ key       │          │           │           │
│name     // the string "name"   │           │          │           │           │
├────────────────────────────────┼───────────┤ pair 1   │           │           │
│0xaa     // string8 tag         │           │          │           │           │
│0x08     // 8 characters        │ value     │          │           │           │
│file.txt // the filename        │           │          │           │           │
├────────────────────────────────┼───────────┼──────────┤           │           │
│0xaa     // string8 tag         │           │          │ value     │           │
│0x05     // 5 characters        │ key       │          │           │           │
│bytes    // the string "bytes"  │           │          │           │           │
├────────────────────────────────┼───────────┤ pair 2   │           │           │
│0xac     // array8 tag          │ value     │          │           │           │
│0x05     // 5 elements          │           │          │           │           │
|0xa2     // unsigned byte tag   │           │          │           │           │
│H        // a byte              │           │          │           │           │
|0xa2     // unsigned byte tag   │           │          │           │           │
│e        // a byte              │           │          │           │           │
|0xa2     // unsigned byte tag   │           │          │           │           │
│l        // a byte              │           │          │           │           │
|0xa2     // unsigned byte tag   │           │          │           │           │
│l        // a byte              │           │          │           │           │
|0xa2     // unsigned byte tag   │           │          │           │           │
│o        // a byte              │           │          │           │           │
└────────────────────────────────┴───────────┴──────────┴───────────┴───────────┘           
```

In decimal:
```
[174, 1, 170, 4, 70, 105, 108, 101, 174, 2, 170, 4, 110, 97, 109, 101, 170, 8, 102, 105, 108, 101, 46, 116, 120, 116, 170, 5, 98, 121, 116, 101, 115, 172, 5, 162, 72, 162, 101, 162, 108, 162, 108, 162, 111]
```

### Serialized Request

If you have a file called `file.txt` that you are requesting, then the unencrypted message should look like this:

```
┌───────────────────────────────────────────────────────────────────────────────┐
│0xae     // map tag                                                            │
│0x01     // 1 kv pair                                                          │
├───────────────────────────────────────────────────────┬───────────┬───────────┤
│0xaa     // string8 tag                                │           │           │
│0x07     // 7 characters                               │ key       │           │
│Request  // the string "Request"                       │           │           │
├───────────────────────────────────────────────────────┼───────────┤  pair 1   │
│0xae     // the value associated with the key is a map │           │           │
│0x01     // 1 kv pair                                  │           │           │
├──────────────────────────────┬───────────┬────────────┤           │           │
│0xaa     // string8 tag       │           │            │           │           │
│0x04     // 4 characters      │ key       │            │ value     │           │
│name     // the string "name" │           │            │           │           │
├──────────────────────────────┼───────────┤ pair 1     │           │           │
│0xaa     // string8 tag       │           │            │           │           │
│0x08     // 8 characters      │ value     │            │           │           │
│file.txt // the filename      │           │            │           │           │
└──────────────────────────────┴───────────┴────────────┴───────────┴───────────┘           
```

In decimal:
```
[174, 1, 170, 7, 82, 101, 113, 117, 101, 115, 116, 174, 1, 170, 4, 110, 97, 109, 101, 170, 8, 102, 105, 108, 101, 46, 116, 120, 116]
```


https://drive.google.com/file/d/1ZS583L_GPJ2Gy64kh8HcWb1IuQpyoo_U/view?usp=share_link 

## Works Cited

[0]: https://www.techiedelight.com/get-slice-sub-vector-from-vector-cpp/
[1]: https://www.geeksforgeeks.org/c-program-demonstrate-fork-and-pipe/
[2]: https://www.geeksforgeeks.org/pipe-system-call/
[3]: https://stackoverflow.com/questions/16328118/simple-tcp-server-with-multiple-clients-c-unix
[4]: https://www.appsloveworld.com/cplus/100/102/istream-iterator-to-iterate-through-bytes-in-a-binary-file
