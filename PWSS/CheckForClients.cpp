#include "CheckForClients.h"
#include "Statemachine.h"

void CheckForClients::Enter()
{
	int eventCount = WSAPoll(&stateMachine->data->socketList[0], stateMachine->data->socketList.size(), 2500);
}

void CheckForClients::Tick()
{
	for (auto it = stateMachine->data->socketList.begin(); it != stateMachine->data->socketList.end(); ++it) {
		//Je�li socket zwraca flag� POLLRDNORM oznacza to, �e posiada on dane do zapisu
		SOCKET newsockfd;
		if ((*it).fd == stateMachine->data->serverSocket) {
			//Je�li tym socketem jest socket serwera to oznacza to, �e ten skomunikowa� si� z nowym socketem
			newsockfd = accept(stateMachine->data->serverSocket, (struct sockaddr*)&stateMachine->data->clientAddr, &stateMachine->data->clientLen);
			if (newsockfd < 0) {
				perror("ERROR on accept");
			}
			stateMachine->data->socketList.push_back({
				newsockfd,
				POLLRDNORM
				});
			it = stateMachine->data->socketList.begin();

			//Dodajemy nowy socket do listy socket�w
			std::cout << "Socket " << newsockfd << " zostal polaczony" << std::endl;
			FILE* file;
			char ip4[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, &(stateMachine->data->clientAddr.sin_addr), ip4, INET_ADDRSTRLEN);
			std::string path = "C:\\Users\\Wydrzu\\source\\repos\\PW�S5_kw_klient\\Debug\\";
			path.append(ip4);
			path.append(std::to_string(newsockfd));
			fopen_s(&file, path.c_str(), "wb");
			//Otwieramy plik do zapisu, plik ten nazwany jest adresem IP socketu i jego deskryptorem
			FileAction action(file);
			stateMachine->data->fileMap[newsockfd] = action;
			//Dodajemy plik do mapy plik�w
		}
		else if ((*it).revents & POLLHUP || (*it).revents & POLLERR) {
			closesocket((*it).fd);
			std::cout << "Zamknieto polaczenie " << (*it).fd << std::endl;
			stateMachine->data->socketList.erase(it--);
		}
	}
}
void CheckForClients::Exit()
{

}