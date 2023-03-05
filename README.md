# Simple file transfer in C

It's a file transfer wrote in C language that uses TCP protocol. **Please do not send sensitive data.  The app has no encryption.**

## How to use

You should compile and run server's file in the server. The server will stay listening at the port 5000 waiting for transfered files from the client app.

To use the client's app you should compile and run with the server's address (i.e: ./client 192.168.0.10) and enter the file path when requested. In the end of the program you will receive the transfer rate in mega bits per seconds (Mbps).
