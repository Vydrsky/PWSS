#include "ConfigureServer.h"
#include "Statemachine.h"

void ConfigureServer::Enter() {

	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		stateMachine->Kill();
	}
	//inicjalizacji biblioteki winsock

	stateMachine->data->serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (stateMachine->data->serverSocket < 0) {
		perror("Error at socket:");
		stateMachine->Kill();
	}
	//stworzenie socketa dla serwera

	stateMachine->data->serverAddr.sin_family = AF_INET;
	inet_pton(AF_INET, "0.0.0.0", &(stateMachine->data->serverAddr.sin_addr));
	//ip komputera z którym siê ³¹czymy
	stateMachine->data->serverAddr.sin_port = htons(2000);
	//nr portu na który chcemy siê po³¹czyæ

	if (bind(stateMachine->data->serverSocket, (sockaddr*)&stateMachine->data->serverAddr,
												sizeof(stateMachine->data->serverAddr)) < 0) {
		printf("Wyst¹pi³ b³¹d w trakcie wykonywania funkcji bind \n");
		stateMachine->Kill();
	}
	//³¹czenie socketa z adresem

	listen(stateMachine->data->serverSocket, 5);
	//konfiguracja nas³uchiwania oraz kolejki

	stateMachine->data->socketList.push_back(
		{
			SOCKET(stateMachine->data->serverSocket),
			POLLRDNORM,
			0
		}
	);
	//dodanie socketa serwera do listy socketów

	//TODO
	struct sockaddr_in clientAddr;
	socklen_t clientLen = sizeof(clientAddr);
	std::map<SOCKET, FileAction> mapaPlikow;
}

void ConfigureServer::Tick() {
	
}

void ConfigureServer::Exit() {
	
}