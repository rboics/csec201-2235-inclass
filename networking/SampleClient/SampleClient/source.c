#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

int main(void) {
	WSADATA sockData;
	SOCKET clientSocket;
	struct sockaddr_in srvaddr;
	char serverIP[15];
	int serverPort;
	char userInput[500];
	char srvResponse[500];
	int bytesRead;


	printf("Enter server IP: ");
	scanf("%s", serverIP);
	printf("Enter server port: ");
	scanf("%d", &serverPort);

	WSAStartup(MAKEWORD(2, 2), &sockData);
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	memset(&srvaddr, 0, sizeof(srvaddr));


	srvaddr.sin_family = AF_INET;
	srvaddr.sin_port = htons(serverPort);
	srvaddr.sin_addr.s_addr = inet_addr(serverIP);
	connect(clientSocket, &srvaddr, sizeof(srvaddr));
	while (1) {
		printf("Enter a message to send across the network: ");
		scanf("%s", userInput);
		int len = strlen(userInput);
		printf("%d\n", len);
		strcpy(&(userInput[len]), "\r\n\r\n\0");
		printf("%d\n", strlen(userInput));
		if (strcmp(userInput, "Done") == 0) break;
		send(clientSocket, userInput, sizeof(userInput), 0);
		bytesRead = recv(clientSocket, srvResponse, 500, 0);
		srvResponse[bytesRead] = '\0';
		printf("Server send: %s\n", srvResponse);
		closesocket(clientSocket);
		connect(clientSocket, &srvaddr, sizeof(srvaddr));

	}
	closesocket(clientSocket);
}
