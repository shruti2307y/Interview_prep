## Introduction
In C++, socket programming refers to the method of communication between two sockets on the network using a C++ program. We use the socket API to create a connection between the two programs running on the network, one of which receives the data by listening to the particular address port, and the other sends the data. One of the features of the socket programming is that it allows the bidirectional communication between the nodes.

## Resources:
* https://www.geeksforgeeks.org/socket-programming-in-cpp/
* https://www.youtube.com/playlist?list=PLhnN2F9NiVmAMn9iGB_Rtjs3aGef3GpSm
* https://www.youtube.com/watch?v=XXfdzwEsxFk
## Types of socket

1. Stream Socket: TCP
2. Datagram socket: UDP

## Server Stages

#### 1. getaddrinfo 
kinda similar to DNS lookup
```c++
sockaddr_in serverAddress;  
serverAddress.sin_family = AF_INET;  
serverAddress.sin_port = htons(8080);  
serverAddress.sin_addr.s_addr = INADDR_ANY;
```
#### 2. socket

```c++
int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
```
here AF_INET tells code to use socket ports for communication over unix comm, SOCK_STREAM means use TCP
Returned value is the file descriptor of socket file that is being created for accepting connection over.

#### 3.bind
```c++
bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
```
Given a file descriptor, tell the kernel to associate it with a given IP and Port.

#### 4. Listen
Given a file descriptor that has been bind-ed to a iP/port, tell the operating system that you wish to start receiving connections.
```c++
listen(serverSocket, 5);
```
#### 5. Accept
Given a file descriptor that has already been activated via listen, create a new FD that can be used to communicate with an individual client.
By default this call block until a client shows up.
```c++
int clientSocket = accept(serverSocket, nullptr, nullptr);
```

#### 6.Send and Recv
Given a connected file descriptor, submit bytes to the OS for delivery / ask the OS to deliver bytes
- ﻿﻿Works very similarly to read & write.
- ﻿﻿send & recv operate on user level memory & kernel level buffers, they do NOT do the sending themselves
```c++
char buffer[1024] = {0};  
recv(clientSocket, buffer, sizeof(buffer), 0);  
cout << "Message from client: " << buffer << endl;

const char* message = "Hello, server!";  
send(clientSocket, message, strlen(message), 0);
```

#### 7. Close
Given a connected file descriptor, tell the kernel that it can terminate this connection.
- ﻿﻿Kernel continues sending buffered bytes
- ﻿﻿At end of buffered bytes, sends special "EOF" message (interpreted as len=0 result for recv
```c++
close(clientSocket);
```
