# QTcpServer
A simple Tcp server uising QT5 creator

**QTcpServer** is a simple tcp server which allows conversation between client and server;

Submitted by: **Xiaohu Zheng**

Time spent: **1** day in total

Note:
From the server side:
1. We first created a QTcpServer object witch listens to all network interfaces;
2. Whenever there is a new connection signal from (tcp socket), it will then print a message to the message box. (IP adress & Port Number)

From the client side:
1. we first create a new QTcpSocket object witch will then send its ip adress and port number to request a connection to the host server;
2. when it established connection successfully, it will emit a connected signal, and then we also print a message to the message box to notify the user.

For both sides:
1. whenever we click the "send" botton, we will get all the data from the typing box and then write it to the stack;
2. whenever there is something in the stack, A readyread signal is emiited, so that we will write the data to the display(message) box;
2. whenever we click the "disconnect" botton, we will disconnect the client from the host server, and notify the user.

## Video Walkthrough
<img src='' title='Video Walkthrough' width='' alt='Video Walkthrough' />

GIF created with LICEcap.
