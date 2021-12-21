#include "CheckForClients.h"
#include "Statemachine.h"

void CheckForClients::Enter()
{
	int eventCount = WSAPoll(&stateMachine->data->socketList[0], stateMachine->data->socketList.size(), 2500);
}

void CheckForClients::Tick()
{
	for (auto it = stateMachine->data->socketList.begin(); it != stateMachine->data->socketList.end(); ++it) {
		//Jeœli socket zwraca flagê POLLRDNORM oznacza to, ¿e posiada on dane do zapisu
		SOCKET newsockfd;
		if ((*it).fd == stateMachine->data->serverSocket) {
			//Jeœli tym socketem jest socket serwera to oznacza to, ¿e ten skomunikowa³ siê z nowym socketem
			newsockfd = accept(stateMachine->data->serverSocket, (struct sockaddr*)&stateMachine->data->clientAddr, &stateMachine->data->clientLen);
			if (newsockfd < 0) {
				perror("ERROR on accept");
			}
			stateMachine->data->socketList.push_back({
				newsockfd,
				POLLRDNORM
				});
			it = stateMachine->data->socketList.begin();

			//Dodajemy nowy socket do listy socketów
			std::cout << "Socket " << newsockfd << " rozpoczal zapis" << std::endl;
			FILE* file;
			char ip4[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, &(stateMachine->data->clientAddr.sin_addr), ip4, INET_ADDRSTRLEN);
			std::string path = "C:\\Users\\Marek\\source\\repos\\pwsstcpserver\\Debug\\";
			path.append(ip4);
			path.append(std::to_string(newsockfd));
			//fopen_s(&file, path.c_str(), "wb");
			//Otwieramy plik do zapisu, plik ten nazwany jest adresem IP socketu i jego deskryptorem
			//FileAction action(file);
			//mapaPlikow[newsockfd] = action;
			//Dodajemy plik do mapy plików
		}
	}
}
void CheckForClients::Exit()
{

}