#include<iostream>
#include<winsock2.h>
#include <ws2tcpip.h>
#include<thread>


#pragma comment(lib, "Ws2_32.lib")


using namespace std;

void static handleClient(SOCKET newSock,int clientNo) {
	char buff[1024];

	while (true) {
		memset(buff, 0, sizeof(buff));
		int bytesRecieved = recv(newSock,buff,sizeof(buff),0);
		if (bytesRecieved <= 0) {
			cout << "Client " <<clientNo<<" disconnected with -> "<<bytesRecieved << endl;
			
			closesocket(newSock);
			break;

		}
		else {
			cout << "Data recieved by client " << clientNo << ": \n";
			cout << buff << endl;

		}
	

	}

}



int main() {
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0) cout<<"WSAStartup failed !!\n";

	cout << "Creating Server on localhost ...\n";
	SOCKET webServer = socket(AF_INET, SOCK_STREAM, 0);
	
	if (webServer == INVALID_SOCKET) {
		cout << "Server creation failed !!" << endl;
		WSACleanup();
		return 1;
	}

	sockaddr_in serverAddress{};

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(8080);
	inet_pton(AF_INET, "192.168.1.9", &serverAddress.sin_addr);

	if (bind(webServer, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
		cout << "Binding Failed !! "<<WSAGetLastError();
	}
	else {
		cout << "Binding done and Server created successfully !!\n";
	}

	

	listen(webServer, 5);
	cout << "Server is ready \n";
	int clientNo = 0;

	while (true) {

		SOCKET newSocket = accept(webServer, nullptr, nullptr);

		if (newSocket == INVALID_SOCKET)cout << "Socket is Invalid\n";
		else {
			clientNo++;
			cout << "Client Connected " << clientNo << "!!" << endl;
			thread t =  thread (handleClient, newSocket, clientNo);
			t.detach();


		}
	}
	
	


	

	closesocket(webServer);
	cout << "Server Closed successfully !!\n";

	WSACleanup();


	




}

