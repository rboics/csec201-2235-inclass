#include <stdio.h>
#include <string.h>
#include <process.h>
//Windows networking
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

//__stdcall -> makes sure the compiler uses the C standard for calling this function
int __stdcall HandleClient(SOCKET* clientSocket) {
	SOCKET clientConn = *clientSocket;
	char response[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=us-ascii\r\n\r\n<script>alert('Hello!');</script> Hello World\r\n\r\n";
	char secret[] = "We'll pretend this is the server's private key";
	char socketData[1024]; //1k of data
	for (int i = 0; i < 1024; i++) socketData[i] = '\0';
	if (recv(clientConn, socketData, sizeof(socketData), 0)) {
		printf("Client sent: %s\n", socketData);
		send(clientConn, response, sizeof(response), 0);

	}
	closesocket(clientSocket);
	_endthreadex(0);
	return 0;
}


int main(void) {
	WSADATA winSockData; //Hold information about the Windows socket
	SOCKET serverSocket, clientSocket;	//Server socket is always running
										//When a client connects, the serverSocket will break
										//a clientSocket with an ephemeral port for the client
										//to talk to
	//sockaddr_in struct will contain info about 
	//the server, the client, and the connection
	struct sockaddr_in serverAddress, clientAddress;
	int addrLen = sizeof(clientAddress);
	HANDLE thread;
	int result;
	int port = 8421;

	int threadnum = 0;

	//Initialize Winsock
	//MAKEWORD(2,2) --> version of Winsock to use
	//&winSockData --> location to store the initialized WinSock
	result=WSAStartup(MAKEWORD(2, 2), &winSockData);
	if (result != 0) {
		printf("Failed to initialize WinSock\n");
		exit(-1);
	}

	//AF_INET -> IPV4 (AF_INET6 for IPv6
	//SOCK_STREAM -> TCP (SOCK_DGRAM for UDP);

	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	serverAddress.sin_family = AF_INET;
	// What address will our server listen on (INADDR_ANY -> all interfaces0
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(port);

	// At this point, we've an initialized but unused socket
	// And an address that tells the os to use IPv4 on port 8421 and to listen on all interfaces

	bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

	//Listen for incomming connections, 2nd arg is the # of connections
	listen(serverSocket, 5);

	//Run forever
	while (1) {
		clientSocket = accept(serverSocket, &clientAddress, &addrLen);
		//Application logic was here
		threadnum++;
		thread = _beginthreadex(NULL, 0, &HandleClient, &clientSocket, 0, &threadnum);

	}

	system("pause");
}