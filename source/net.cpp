/*
 * net.cpp
 *
 *  Created on: 2014/11/26
 *      Author: chihiro
 */
#include "global.h"
#include "system.h"

#include "net.h"
#include "signal.h"

using namespace std;

/*-----------------------------------
 * server thread
 *---------------------------------*/
void* waitingClient(void*) {
	usleep(1000000);
	while (1) {
		sys->network->waitingClient();
		usleep(1000000); //stop 1000 ms
	}
}
void* serverMain(void*) {

	signal(SIGPIPE, SIG_IGN);
	usleep(500000); //stop 0.5s for safe
	sys->network->setServer();
	pthread_t wa;
	pthread_create(&wa, NULL, waitingClient, NULL);

	while (1) {
		//sys->network->setServer();
		while (1) {
			//if (sys->network->cli.size() > 0) {
			if (sys->network->routineServer() != 0)
				break;
			//}
			usleep(1000); //wait 1ms
		}
	}

}

/*-----------------------------------
 * client thread
 *---------------------------------*/
void* clientMain(void*) {
	signal(SIGPIPE, SIG_IGN);
	usleep(1000000); //stop 1s for safe
	while (1) {

		if (sys->network->setClient("127.0.0.1") == 0) {
			cout << "client setConnect()==0" << endl;
			while (1) {
				if (sys->network->routineClient() != 0) {
					break;
				}

				usleep(10000); //wait 10ms
			}

		} else {
			cout << "setClient() is faild" << endl;

		}
		usleep(1000000); //stop 1s
	}
}

/*-----------------------------------
 * net class
 *---------------------------------*/
//return 0 =>success
int NetClass::setServer() {
	struct sockaddr_in server_address;

	int maxfd;
	int optimum_value = 1;

	memset((char*) &server_address, '\0', sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);

	if ((listenSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		cout << "socket() is failed" << endl;
		return 1;
	}

	setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, &optimum_value,
			sizeof(optimum_value));

	if (bind(listenSocket, (struct sockaddr*) &server_address,
			sizeof(server_address)) == -1) {
		cout << "bind() is failed" << endl;
		return 1;
	}

	if (listen(listenSocket, 4) == -1) {
		cout << "listen() is failed" << endl;
		return 1;
	}
	return 0;
}

int NetClass::routineServer() {
	int result = 0;

	char command;

	for (int i = 0; i < CLIENT_MAX; i++) {

		//cout<<"routineServer() executed"<<i<<endl;
		if (cli[i].socket == -1) {
			//cout<<"routineServer() socket throughed"<<i<<endl;
			continue;
		}
		fd_set fds;
		FD_ZERO(&fds);
		FD_SET(cli[i].socket, &fds);

		struct timeval tv;
		tv.tv_sec = 0;
		tv.tv_usec = 10;

		int n = select(cli[i].socket + 1, &fds, NULL, NULL, &tv);
		if (n == 0) {
			//cout << "cli[" << i << "] routineServer timeout" << endl;
			//cli[i].socket=-1;
			//close(cli[i].socket);
			//cli.erase(cli.begin()+i);
			//usleep(1000000000);
			//return 1;
			continue;
		}
		//cout <<"cli["<<i<<"] routineServer select passed"<<endl;

		if (FD_ISSET(cli[i].socket, &fds)) {
			command = 'N';

			//cout << "cli[" << i << "] routineServer FD" << endl;
			if (receive_data(i, &command, sizeof(char)) < 0 && command != 'N') {
				cout << "command=" << command << "  errno=" << errno << endl;
				return 1;
			}
			if (command == 'N') {
				cli[i].socket = -1;
				return 1;
			}
			cout << "get command " << command << endl;
			result = serverCommand(command, i);

			if (result != 0) {
				//cli[i].socket=-1;
				return result;
			}
		}

		//位置座標動機
		if (sys->network->cli[i].socket > 0) {
			if (serverCommand(SYNC_COMMAND, i) != 0) {
				cli[i].socket = -1;
				return 1;
			}
		}

		//第二引数意味なし
		//if (syncEffectFlag > 0)
			serverCommand(E_SYNC_COMMAND, 0);



		/*for (int i = 0; i < MAX_EFFECT; i++) {
			cout << "effect["<<i<<"] "<<sys->effect[i].f << " " << sys->effect[i].x << " "
					<< sys->effect[i].y;
			cout << " " << sys->effect[i].z << " " << sys->effect[i].dir << " "
					<< sys->effect[i].count << "\n";
		}*/
	}

	return 0;
}

int NetClass::waitingClient() {
	int n = Accept(listenSocket);
	return n;

}

int NetClass::setClient(char* serverName) {
	int res;
	struct hostent *server;
	struct sockaddr_in server_addr;

	int num_characters; //
	char user_name[MAX_BUFFER_LENGTH];

	memset((char*) &server_addr, '\0', sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = inet_addr(serverName);

	if ((ser.socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {

		cout << "client:socket() is failed errno =" << errno << endl;
		return 1;
	}

	if (connect(ser.socket, (struct sockaddr*) &server_addr,
			sizeof(server_addr)) != 0) {
		cout << "client:connect() is failed errno =" << errno << endl;
		close(ser.socket);
		ser.socket = -1;
		return 1;
	}
	cout << "connect==0  ser.socket=" << ser.socket << endl;
	usleep(100000);
	if ((res = receive_data(TO_SERVER, &sys->myID, sizeof(int))) < 0) {
		cout << "receive_data() = " << res << "errno = " << errno << endl;
		close(ser.socket);
		ser.socket = -1;
		return 1;
	}

	cout << "get myID =" << sys->myID << endl;
	return 0;
}
int NetClass::routineClient() {

	int result = 0;
	int data_size = 0;

	char buf[MAX_BUFFER_LENGTH];

//timeout
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(ser.socket, &fds);
	/*
	 struct timeval tv;
	 tv.tv_sec=1;
	 tv.tv_usec=0;
	 if (select(ser.socket+1, &fds, NULL, NULL, &tv) ==0) {
	 cout << "client timeout" << endl;
	 return 0;
	 }
	 */
//位置情報送信
	if (clientCommand(POS_COMMAND, TO_SERVER) != 0) {
		cout << "clientCommand !=0" << endl;
		return 1;
	}

	if (syncEffectFlag != -1) {
		clientCommand(EFFECT_COMMAND, TO_SERVER);
	}

	/*for (int i = 0; i < MAX_EFFECT; i++) {
		cout << "effect["<<i<<"] "<<sys->effect[i].f << " " << sys->effect[i].x << " "
				<< sys->effect[i].y;
		cout << " " << sys->effect[i].z << " " << sys->effect[i].dir << " "
				<< sys->effect[i].count << "\n";
	}*/

//受信
	if (FD_ISSET(ser.socket, &fds)) {
		memset(buf, '\0', MAX_BUFFER_LENGTH);
		data_size = receive_data(TO_SERVER, buf, sizeof(char));

		//if data is exist
		if (data_size > 0) {
			result = clientCommand(buf[0], TO_SERVER);
		}
	}


	return 0;
}

NetClass::NetClass(int mode) {
	if (mode == MODE_SERVER) {
		pthread_create(&ser_t, NULL, serverMain, NULL);
		cout << " make serverMain thread" << endl;
	} else if (mode == MODE_CLIENT) {
		pthread_create(&cli_t, NULL, clientMain, NULL);
		cout << " make clientMain thread" << endl;
	} else {
		cout << "error unknown mode" << endl;
	}
}

NetClass::NetClass() {

	cout << "error mode was not selected" << endl;
}
NetClass::~NetClass() {
// TODO Auto-generated destructor stub
}
