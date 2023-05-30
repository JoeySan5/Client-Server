
### Project contains two main parts: 

1. File Server - A file server is a program that hosts files for clients. It receives files that clients want to store, and sends them back to the client (or other clients) when they are requested. 
2. Client - This program connects to the server and can send files to it, which will be stored on the file server. The client can also request files from the file server. 


### Program Part 1: Server 
- The server will start, bind a socket to a port, and listen for a connection.
- The server will create an empty hash map to store received files in memory. 
- The server will then enter an infinite loop and wait for new connections.
- When the server receives a connection, it will fork a new process and attempt to receive a message. When the child process receives a message, it will follow the following steps:
  - Read the message to a buffer
  - Decrypt the message
  - Deserialize the message to the appropriate struct, either a `File` or `Request`.
    - If the message is a `File`, then the server will insert the filename and file into the hash map.
    - If the message is a `Request`, then the server will look for the requested file in hash map. 
      - If the requested file does not exist, nothing will be sent back to the client.
      - If the file does exist it will be serialized into a `File` message, encrypted, and sent to the client.
  - When the message is sent, the file server should terminate the connection with the client
- Meanwhile, the parent process will be listening for new connections. When a new connection comes in, it will fork a new process and service that connection as laid out above.
- Here is the difficulty with this program. When a new process is forked, it loses contact with the parent process. Everything that happens in the forked process will stay in that process. So the file that's received and stored in the child process will not appear in the hash map of the parent process. Therefore, if a new connection requests that file, it will be as if it has never been sent in the first place.
  -This is solved with pipes communicating in between the child and parent process

### File Server Part 2: Client 
The client program accepts the following flags:


--hostname address:port - Where address is a IPv4 hostname, and port is the desired port of the file server. If this flag isn't provided, the default address is taken to be "localhost" and the default port is taken to be "123
"


--send filename


Where filename is a path to a file on your local computer.

--request filename

Where filename is the name of a file stored on the file server
For example, you could call the client like this:

./client --hostname localhost:1234 --send files/document.txt


Or like this:

./client --hostname localhost:8081 --request document.txt

If you call the program with the --send and --request options at the same time, it should exit with an error.

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


## Works Cited

[0]: https://www.techiedelight.com/get-slice-sub-vector-from-vector-cpp/
[1]: https://www.geeksforgeeks.org/c-program-demonstrate-fork-and-pipe/
[2]: https://www.geeksforgeeks.org/pipe-system-call/
[3]: https://stackoverflow.com/questions/16328118/simple-tcp-server-with-multiple-clients-c-unix
[4]: https://www.appsloveworld.com/cplus/100/102/istream-iterator-to-iterate-through-bytes-in-a-binary-file
