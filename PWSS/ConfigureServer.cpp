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
		printf("Wyst�pi� b��d podczas tworzenia socketu serwera");
		stateMachine->Kill();
	}

	//ip komputera kt�ry ma by� serwerem
	stateMachine->data->serverAddr.sin_family = AF_INET;
	inet_pton(AF_INET, "0.0.0.0", &(stateMachine->data->serverAddr.sin_addr));

	//nr portu na kt�rym pracowa� ma serwer
	stateMachine->data->serverAddr.sin_port = htons(2000);

	//��czenie socketa z adresem
	if (bind(stateMachine->data->serverSocket, (sockaddr*)&stateMachine->data->serverAddr,
												sizeof(stateMachine->data->serverAddr)) < 0) {
		printf("Wyst�pi� b��d w trakcie wykonywania funkcji bind \n");
		closesocket(stateMachine->data->serverSocket);
		stateMachine->Kill();
	}

	//konfiguracja nas�uchiwania oraz kolejki
	if (listen(stateMachine->data->serverSocket, 5) < 0) {
		printf("Wyst�pi� b��d w trakcie wykonywania funkcji listen \n");
		closesocket(stateMachine->data->serverSocket);
		stateMachine->Kill();
	}

	//dodanie socketa serwera do listy socket�w
	stateMachine->data->socketList.push_back(
		{
			SOCKET(stateMachine->data->serverSocket),
			POLLRDNORM,
			0
		}
	);

	//cache d�ugo�ci adresu klienta
	stateMachine->data->clientLen = sizeof(stateMachine->data->clientAddr);
}

void ConfigureServer::Tick() {
	
}

void ConfigureServer::Exit() {
	
}