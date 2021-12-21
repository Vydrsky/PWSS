#include "ConfigureServer.h"
#include "Statemachine.h"

void ConfigureServer::Enter() {

	//inicjalizacji biblioteki winsock
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		stateMachine->Kill();
	}

	//stworzenie socketa dla serwera
	stateMachine->data->serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (stateMachine->data->serverSocket < 0) {
		printf("Wyst¹pi³ b³¹d podczas tworzenia socketu serwera");
		stateMachine->Kill();
	}

	//ip komputera który ma byæ serwerem
	stateMachine->data->serverAddr.sin_family = AF_INET;
	inet_pton(AF_INET, "0.0.0.0", &(stateMachine->data->serverAddr.sin_addr));

	//nr portu na którym pracowaæ ma serwer
	stateMachine->data->serverAddr.sin_port = htons(2000);

	//³¹czenie socketa z adresem
	if (bind(stateMachine->data->serverSocket, (sockaddr*)&stateMachine->data->serverAddr,
												sizeof(stateMachine->data->serverAddr)) < 0) {
		printf("Wyst¹pi³ b³¹d w trakcie wykonywania funkcji bind \n");
		closesocket(stateMachine->data->serverSocket);
		stateMachine->Kill();
	}

	//konfiguracja nas³uchiwania oraz kolejki
	if (listen(stateMachine->data->serverSocket, 5) < 0) {
		printf("Wyst¹pi³ b³¹d w trakcie wykonywania funkcji listen \n");
		closesocket(stateMachine->data->serverSocket);
		stateMachine->Kill();
	}

	//dodanie socketa serwera do listy socketów
	stateMachine->data->socketList.push_back(
		{
			SOCKET(stateMachine->data->serverSocket),
			POLLRDNORM,
			0
		}
	);

	//cache d³ugoœci adresu klienta
	stateMachine->data->clientLen = sizeof(stateMachine->data->clientAddr);
}

void ConfigureServer::Tick() {
	
}

void ConfigureServer::Exit() {
	
}