#include "CheckForClients.h"
#include "Statemachine.h"

void CheckForClients::Enter()
{
	int eventCount = WSAPoll(&(stateMachine->data->socketList[0]), stateMachine->data->socketList.size(), 0);
}

void CheckForClients::Tick()
{
	for (auto it = stateMachine->data->socketList.begin(); it != stateMachine->data->socketList.end(); ++it) {
		//Jeœli socket zwraca flagê POLLRDNORM oznacza to, ¿e posiada on dane do zapisu
		SOCKET newsockfd;
		if (((*it).revents & POLLRDNORM)) {
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
				std::cout << "Socket " << newsockfd << " zostal polaczony" << std::endl;
				//Otwieramy plik do zapisu, plik ten nazwany jest adresem IP socketu i jego deskryptorem
				FILE* file = {};
				FileAction action(file);
				stateMachine->data->fileMap[newsockfd] = action;
				//Dodajemy plik do mapy plików
			}
		}
		else if (((*it).revents & POLLHUP ) || (*it).revents & POLLERR) {
			closesocket((*it).fd);
			std::cout << "Zamknieto polaczenie " << (*it).fd << std::endl;
			stateMachine->data->socketList.erase(it--);
		}
	}
}
void CheckForClients::Exit()
{

}