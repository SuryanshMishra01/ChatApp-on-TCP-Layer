#include<iostream>
#include <limits>
#include<winsock2.h>
#include <ws2tcpip.h>
#include<cstring>
#pragma comment(lib, "Ws2_32.lib")


using namespace std;




int main() {

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) cout << "WSAStartup failed !!\n";

	cout << "Initializing the client ..." << endl;

	SOCKET webClient = socket(AF_INET, SOCK_STREAM, 0);
	if (webClient == INVALID_SOCKET) {
		cout << "Socket Creation Failed !!" << endl;
		WSACleanup();
		return 0;
	}

	sockaddr_in serverAddress = { 0 };

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(8080);
	inet_pton(AF_INET, "192.168.1.9", &serverAddress.sin_addr);

	if (connect(webClient, (sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
		cout << "Connection Failed !!\n"<<WSAGetLastError();
		
	}
	else {
		cout << "Connected successfully to the server !!"<<endl;
		while (true) {
			cout << "Enter the msg to send to server: \n";
			char msg[2048];
			cin.getline(msg,sizeof(msg));
			if (strcmp(msg,"ShutDown") == 0) {
				closesocket(webClient);
				cout << "Close request initiated !!\n";
				WSACleanup();
				break;
			}
			send(webClient, msg, strlen(msg), 0);

			
			
			
		}
		
	}

	
	closesocket(webClient);
	cout << "Closed the client !!\n";
	

	WSACleanup();


	return 0;



}