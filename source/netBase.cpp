/*
 * netBase.cpp
 *
 *  Created on: 2014/11/28
 *      Author: chihiro
 */
#include "global.h"
#include "netBase.h"
//#include "net.h"
#include "system.h"

client::client() {
	socket = -1;
	name.clear();
}
void netBase::Close(void) {
	cout << "The connection is closed!" << endl;
	for (int i = 0; i < CLIENT_MAX; i++) {
		close(cli[i].socket);
	}
	return;
}

int netBase::receive_data(int index, void *data, int data_size) {
	int n;
	/*
	 assert((0 <= index) && (index < Num_clients) && (data != NULL) && (0 < data_size));
	 */

	if (index == TO_SERVER) {
		n = read(ser.socket, data, data_size);
	} else {
		//cout << "read() begin" << endl;
		n = read(cli[index].socket, data, data_size);
		//cout << "read() ended" << endl;
	}
	return (n);
}

int netBase::send_data(int index, void *data, int data_size) {
	int i;

	//cout << "send_data index =" << index << "  datasize = " << data_size<< endl;
	assert((data != NULL) && (0 < data_size));

	if (index == TO_SERVER) {
		//for (i = 0; i < cli.size(); i++) {
		if (write(ser.socket, data, data_size) < 0) {
			cout << "TO_SERVER write() is failed! errno = " << errno << endl;
			return 1;
		}
		return 0;
		//}
	} else {
		if (write(cli[index].socket, data, data_size) < 0) {
			cout << "cli[" << index << "] write() is failed! errno=" << errno
					<< endl;
			return 1;
		}
		return 0;
	}
	cout << "send_data unknown index" << endl;
	return 1;
}

int netBase::Accept(int ListenSocket) {
	int i;
	int socket = -1;

	struct sockaddr_in cli_addr;

	//int val = SOCKET_BLOCKING_MODE;
	//ioctl(ListenSocket, FIONBIO, &val);
	unsigned int serverAddrSize = sizeof(struct sockaddr_in);
	socket = accept(ListenSocket, (struct sockaddr *) &cli_addr,
			&serverAddrSize);
	if (socket > 0) {
		//client clitemp;
		//clitemp.socket=socket;
		int soc;
		for (soc = 0; soc < CLIENT_MAX; soc++) {
			if (cli[soc].socket == -1)
				break;
		}
		cli[soc].socket = socket;
		//int val = SOCKET_BLOCKING_MODE;
		//ioctl(clitemp.socket, FIONBIO, &val);
		cli[soc].name = inet_ntoa(cli_addr.sin_addr);
		//cli.push_back(clitemp);

		int res = 0;
		if ((res = send_data(soc, &soc, sizeof(int))) != 0) {
			cout << "server accept send_data()=" << res << endl;
			cli[soc].socket = -1;
			return 1;
		}

		cout << cli[soc].name << " is accepted" << endl;

		//receive_user_name(i, fd);
		return 0;
	}

	cout << "accept() is failed socket =" << socket << "  errno = " << errno
			<< endl;
	;
	return -1;

}

void netBase::sendId(void) {
	int i, j;

	for (i = 0; i < CLIENT_MAX; i++) {
		send_data(i, &i, sizeof(int));
		//for (j = 0; j < Num_clients; j++) {
		//	send_data(i, Clients[j].name, MAX_NAME_SIZE);
		//}
	}
}

int netBase::clientCommand(char command, int index) {
	int data_size;
	int int_data;
	int result = 1;

	char received_data[MAX_BUFFER_LENGTH];
	char sending_data[MAX_BUFFER_LENGTH];
	char char_data[MAX_DATA];

	memset(sending_data, '\0', MAX_BUFFER_LENGTH);
	memset(char_data, '\0', MAX_DATA);

	//client :: sending process
	if (index == TO_SERVER) {
		if (command == POS_COMMAND) {
			int res = 0;
			res += send_data(TO_SERVER, &command, sizeof(command));
			res += send_data(TO_SERVER, &sys->myID, sizeof(sys->myID));
			res += send_data(TO_SERVER, &sys->player[sys->myID].x,
					sizeof(sys->player[sys->myID].x));
			res += send_data(TO_SERVER, &sys->player[sys->myID].y,
					sizeof(sys->player[sys->myID].y));
			res += send_data(TO_SERVER, &sys->player[sys->myID].z,
					sizeof(sys->player[sys->myID].z));
			res += send_data(TO_SERVER, &sys->player[sys->myID].dir,
					sizeof(sys->player[sys->myID].dir));
			return res;

		} else if (command == SYNC_COMMAND) {
			Player playertmp[4];
			//receive_data(TO_SERVER, &c, sizeof(int));
			for (int i = 0; i < CLIENT_MAX; i++) {
				receive_data(TO_SERVER, &playertmp[i].x, sizeof(double));
				receive_data(TO_SERVER, &playertmp[i].y, sizeof(double));
				receive_data(TO_SERVER, &playertmp[i].z, sizeof(double));
				receive_data(TO_SERVER, &playertmp[i].dir, sizeof(double));
				cout << "received player[" << i << "] position "
						<< sys->player[i].x << sys->player[i].y
						<< sys->player[i].z << sys->player[i].dir << endl;

			}
			for (int i = 0; i < CLIENT_MAX; i++) {
				if (i != sys->myID) {
					sys->player[i].x = playertmp[i].x;
					sys->player[i].y = playertmp[i].y;
					sys->player[i].z = playertmp[i].z;
					sys->player[i].dir = playertmp[i].dir;
				}
			}
			return 0;
		}

	}

	return (result);
}

int netBase::serverCommand(char command, int index) {
	int data_size = 0;
//int int_data;
	int result = 0;

	char received_data[MAX_BUFFER_LENGTH];
	memset(received_data, '\0', MAX_BUFFER_LENGTH);
	char sending_data[MAX_BUFFER_LENGTH];
	memset(sending_data, '\0', MAX_BUFFER_LENGTH);
//char char_data[MAX_DATA];

//assert((0 <= index) && (index < MAX_CLIENTS));

	memset(sending_data, '\0', MAX_BUFFER_LENGTH);
//memset(char_data, '\0', MAX_DATA);

//if (index != TO_SERVER) {
//receive the position data from client
	if (command == POS_COMMAND) {
		int Id = 0;
		receive_data(index, &Id, sizeof(int));
		receive_data(index, &sys->player[Id].x, sizeof(double));
		receive_data(index, &sys->player[Id].y, sizeof(double));
		receive_data(index, &sys->player[Id].z, sizeof(double));
		receive_data(index, &sys->player[Id].dir, sizeof(double));
		cout << "receive player[" << Id << "] position " << sys->player[Id].x
				<< sys->player[Id].y << sys->player[Id].z << sys->player[Id].dir
				<< endl;
		return 0;
	} else if (command == SYNC_COMMAND) {
		int res = 0;
		res += send_data(index, &command, sizeof(char));
		for (int i = 0; i < CLIENT_MAX; i++) {
			res += send_data(index, &sys->player[i].x, sizeof(double));
			res += send_data(index, &sys->player[i].y, sizeof(double));
			res += send_data(index, &sys->player[i].z, sizeof(double));
			res += send_data(index, &sys->player[i].dir, sizeof(double));
			cout << "send player[" << i << "] position " << sys->player[i].x
					<< sys->player[i].y << sys->player[i].z
					<< sys->player[i].dir << endl;
		}
		return res;

		/*
		 set_char_data2data_block(sending_data, command, &data_size);
		 set_int_data2data_block(sending_data, cli.size(), &data_size);
		 for (int i = 0; i < cli.size(); i++) {
		 set_double_data2data_block(sending_data, sys->player[i].x,
		 &data_size);
		 set_double_data2data_block(sending_data, sys->player[i].y,
		 &data_size);
		 set_double_data2data_block(sending_data, sys->player[i].z,
		 &data_size);
		 set_double_data2data_block(sending_data, sys->player[i].dir,
		 &data_size);
		 }

		 send_data(ALL_CLIENTS, sending_data, data_size);
		 */
	} else {
		//printf("%s : Command = %c\n", clients->name, command);
		/*
		 data_size = 0;

		 set_char_data2data_block(sending_data, command, &data_size);

		 send_data(ALL_CLIENTS, sending_data, data_size);

		 result = 0;
		 */
		cout << "unknown command" << endl;
	}

	return 1;
}

void netBase::set_int_data2data_block(void *data, int int_data,
		int *data_size) {
	int tmp;

	assert((data != NULL) && (0 <= (*data_size)));

	tmp = htonl(int_data);
	memcpy(data + (*data_size), &tmp, sizeof(int));

	(*data_size) += sizeof(int);
}

void netBase::set_data_block2int_data(int *int_data, void *data,
		int *data_size) {
	int tmp;

	assert((data != NULL) && (0 <= (*data_size)));

	memcpy(&tmp, data + (*data_size), sizeof(int));
	*int_data = ntohl(tmp);

	(*data_size) += sizeof(int);
}

void netBase::set_char_data2data_block(void *data, char char_data,
		int *data_size) {
	assert((data != NULL) && (0 <= (*data_size)));

	*(char *) (data + (*data_size)) = char_data;

	(*data_size) += sizeof(char);
}

void netBase::set_double_data2data_block(void *data, double double_data,
		int *data_size) {
	assert((data != NULL) && (0 <= (*data_size)));

	*(double *) (data + (*data_size)) = double_data;

	(*data_size) += sizeof(double);
}

void netBase::set_string_data2data_block(void *data, char *string_data,
		int string_length, int *data_size) {
	int i;

	assert((data != NULL) && (0 <= (*data_size)));

	for (i = 0; i < string_length; i++) {
		*((char *) (data + (*data_size)) + i) = *(string_data + i);
	}

	(*data_size) += (string_length * sizeof(char));
}

void netBase::set_data_block2string_data(char *string_data, void *data,
		int string_length, int *data_size) {
	int i;

	assert((data != NULL) && (0 <= (*data_size)));

	for (i = 0; i < string_length; i++) {
		*(string_data + i) = *((char *) (data + (*data_size)) + i);
	}

	(*data_size) += (string_length * sizeof(char));
}

netBase::netBase() {
// TODO Auto-generated constructor stub
}

netBase::~netBase() {
// TODO Auto-generated destructor stub
}
