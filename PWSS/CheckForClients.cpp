#include "CheckForClients.h"
#include "Statemachine.h"

void CheckForClients::Enter()
{
	int eventCount = WSAPoll(&(stateMachine->data->socketList[0]), stateMachine->data->socketList.size(), 0);
}

void CheckForClients::Tick()
{
	int vSize = stateMachine->data->socketList.size();
	for (int i = 0; i<vSize;++i) {
		//Jeœli socket zwraca flagê POLLRDNORM oznacza to, ¿e posiada on dane do zapisu
		SOCKET newsockfd;
		if ((stateMachine->data->socketList[i].revents & POLLRDNORM)) {
			if (stateMachine->data->socketList[i].fd == stateMachine->data->serverSocket) {
				//Jeœli tym socketem jest socket serwera to oznacza to, ¿e ten skomunikowa³ siê z nowym socketem
				newsockfd = accept(stateMachine->data->serverSocket, (struct sockaddr*)&stateMachine->data->clientAddr, &stateMachine->data->clientLen);
				if (newsockfd < 0) {
					perror("ERROR on accept");
				}
				stateMachine->data->socketList.push_back({
					newsockfd,
					POLLRDNORM
					});
				vSize++;
				//Dodajemy nowy socket do listy socketów
				std::cout << "Socket " << newsockfd << " zostal polaczony" << std::endl;
				//Otwieramy plik do zapisu, plik ten nazwany jest adresem IP socketu i jego deskryptorem
				FILE* file = {};
				FileAction action(file);
				stateMachine->data->fileMap[newsockfd] = action;
				//Dodajemy plik do mapy plików
			}
		}
		else if ((stateMachine->data->socketList[i].revents & POLLHUP ) || stateMachine->data->socketList[i].revents & POLLERR) {
			closesocket(stateMachine->data->socketList[i].fd);
			std::cout << "Zamknieto polaczenie " << stateMachine->data->socketList[i].fd << std::endl;
			stateMachine->data->socketList.erase(stateMachine->data->socketList.begin() + i);
			i--;
			vSize--;
		}
	}
}
void CheckForClients::Exit()
{

}