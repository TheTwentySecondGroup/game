/*
 * netBase.cpp
 *
 *  Created on: 2014/11/28
 *      Author: chihiro
 */
#include "global.h"
#include "netBase.h"
#include "Effect.h"
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
		n = recv(ser.socket, data, data_size, 0);
	} else {
		//cout << "read() begin" << endl;
		n = recv(cli[index].socket, data, data_size, 0);
		//cout << "read() ended" << endl;
	}

	if (n == data_size)
		return (n);

	return 0;
}

int netBase::receiveData(int index, void *data, int data_size) {
	int n, recvd = 0;

	while (1) {
		if (index == TO_SERVER) {
			recvd += recv(ser.socket, data + recvd, data_size - recvd, 0);
			cout << "recvd" << recvd << endl;
		} else {
			//cout << "read() begin" << endl;
			recvd += recv(cli[index].socket, data + recvd, data_size - recvd, 0);
			cout << "recvd" << recvd << endl;
			//cout << "read() ended" << endl;
		}
		if (recvd >= data_size)
			break;

	}
	return 0;
}

int netBase::sendData(int index, void *data, int data_size) {
	int i;

	//cout << "send_data index =" << index << "  datasize = " << data_size<< endl;
	assert((data != NULL) && (0 < data_size));

	if (index == TO_SERVER) {
		int cur = 0;
		while (1) {

			if ((cur = send(ser.socket, data + cur, data_size - cur, 0)) < 0) {
				cout << "TO_SERVER write() is failed! errno = " << errno << endl;
				return 1;
			}

			cout << "sended" << cur << endl;
			if (data_size <= cur)
				break;

		}
		return 0;
	} else {

		int cur = 0;
		while (1) {
			if ((cur = send(cli[index].socket, data + cur, data_size - cur, 0)) < 0) {
				cout << "cli[" << index << "] write() is failed! errno=" << errno << endl;
				return 1;
			}

			cout << "sended" << cur << endl;
			if (cur >= data_size)
				break;
		}
		return 0;
	}
	cout << "send_data unknown index" << endl;
	return 1;
}

int netBase::send_data(int index, void *data, int data_size) {
	int i;

	//cout << "send_data index =" << index << "  datasize = " << data_size<< endl;
	assert((data != NULL) && (0 < data_size));

	if (index == TO_SERVER) {
		int cur = 0;
		while (1) {

			if ((cur = send(ser.socket, data + cur, data_size - cur, 0)) < 0) {
				cout << "TO_SERVER write() is failed! errno = " << errno << endl;
				return 1;
			}
			if (data_size <= cur)
				break;

		}
		return 0;
	} else {
		int cur = 0;
		while (1) {
			if ((cur = send(cli[index].socket, data, data_size, 0)) < 0) {
				cout << "cli[" << index << "] write() is failed! errno=" << errno << endl;
				return 1;
			}

			if (cur >= data_size)
				break;
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
	socket = accept(ListenSocket, (struct sockaddr *) &cli_addr, &serverAddrSize);
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

	cout << "accept() is failed socket =" << socket << "  errno = " << errno << endl;
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
	//int int_data;
	int result = 1;

	//char received_data[MAX_BUFFER_LENGTH];
	//char sending_data[MAX_BUFFER_LENGTH];
	//char char_data[MAX_DATA];

	//memset(sending_data, '\0', MAX_BUFFER_LENGTH);
	//memset(char_data, '\0', MAX_DATA);

	//client :: sending process
	if (index == TO_SERVER) {
		if (command == FACE_COMMAND) {
			int res = 0;
			FILE *fp;
			string tmp = "data/me.bmp";

			fp = fopen(tmp.c_str(), "rb");
			long int size = 0;
			char* tmpimage;
			if (fp != NULL) {
				fseek(fp, 0, SEEK_END);
				size = ftell(fp);
				fclose(fp);
			}
			cout << size << endl;
			fp = fopen(tmp.c_str(), "rb");
			if (fp != NULL) {
				tmpimage = (char *) malloc((int) size);
				fread((void*) tmpimage, (int) size, size, fp);
				fclose(fp);
			}
			res += send_data(TO_SERVER, &command, sizeof(command));
			res += send_data(TO_SERVER, &sys->myID, sizeof(sys->myID));

			res += send_data(TO_SERVER, &size, sizeof(int));
			res += sendData(TO_SERVER, tmpimage, (int) size);
			free((void*) tmpimage);
			sys->sendFaceFlag = 0;
			cout << "send FACE_COMMAND is OK" << endl;
			return res;

		} else if (command == FACE_SYNC_COMMAND) {
			int Id = 0;
			receive_data(TO_SERVER, &Id, sizeof(int));
			receive_data(TO_SERVER, &tmpImageSize[Id], sizeof(int));
			//if(tmpImage[Id]!=NULL)free(tmpImage[Id]);
			tmpImage[Id] = (char*) malloc((int) tmpImageSize[Id]);
			receiveData(TO_SERVER, tmpImage[Id], tmpImageSize[Id]);
			cout << "get imagedata from " << Id << "size " << tmpImageSize[Id] << endl;

			FILE *fp;
			char tmpchar[20];
			memset(tmpchar, '0', 20);
			sprintf(tmpchar, "data/%d_%d.bmp", Id, sys->myID);
			fp = fopen(tmpchar, "wb");
			if (fp != NULL) {
				fwrite((void*) tmpImage[Id], tmpImageSize[Id], 1, fp);
				fclose(fp);
				if (tmpImageSize[Id] > 0) {
					string tmpstring = tmpchar;
					sys->faceImage[Id] = sys->draw->initTexture(tmpstring);
				}
			} else {
				cout << tmpchar << " fp is null" << endl;
			}

		} else if (command == POS_COMMAND) {
			int res = 0;
			res += send_data(TO_SERVER, &command, sizeof(command));
			res += send_data(TO_SERVER, &sys->myID, sizeof(sys->myID));
			res += send_data(TO_SERVER, &sys->selChara, sizeof(int));
			res += send_data(TO_SERVER, &sys->player[sys->myID].x, sizeof(sys->player[sys->myID].x));
			res += send_data(TO_SERVER, &sys->player[sys->myID].y, sizeof(sys->player[sys->myID].y));
			res += send_data(TO_SERVER, &sys->player[sys->myID].z, sizeof(sys->player[sys->myID].z));
			res += send_data(TO_SERVER, &sys->player[sys->myID].dir, sizeof(sys->player[sys->myID].dir));
			return res;

		} else if (command == SYNC_COMMAND) {
			Player playertmp[4];
			//receive_data(TO_SERVER, &c, sizeof(int));
			for (int i = 0; i < CLIENT_MAX; i++) {
				receive_data(TO_SERVER, &playertmp[i].hp, sizeof(int));
				receive_data(TO_SERVER, &playertmp[i].mp, sizeof(int));
				receive_data(TO_SERVER, &playertmp[i].chara, sizeof(int));
				receive_data(TO_SERVER, &playertmp[i].x, sizeof(double));
				receive_data(TO_SERVER, &playertmp[i].y, sizeof(double));
				receive_data(TO_SERVER, &playertmp[i].z, sizeof(double));
				receive_data(TO_SERVER, &playertmp[i].dir, sizeof(double));
				/*
				 cout << "received player[" << i << "] position "
				 << sys->player[i].x << sys->player[i].y
				 << sys->player[i].z << sys->player[i].dir << endl;
				 */
			}
			for (int i = 0; i < CLIENT_MAX; i++) {
				if (i != sys->myID) {
					sys->player[i].hp = playertmp[i].hp;
					sys->player[i].mp = playertmp[i].mp;
					sys->player[i].chara = playertmp[i].chara;
					sys->player[i].x = playertmp[i].x;
					sys->player[i].y = playertmp[i].y;
					sys->player[i].z = playertmp[i].z;
					sys->player[i].dir = playertmp[i].dir;
				} else {
					//if get damage
					if (sys->player[i].hp != playertmp[i].hp) {
						Mix_PlayChannel(-1, sys->damage, 0);
					}
					sys->player[i].hp = playertmp[i].hp;
					sys->player[i].mp = playertmp[i].mp;
					sys->player[i].chara = sys->selChara;
				}
			}
			return 0;
		} else if (command == EFFECT_COMMAND) {
			int res = 0;

			int Id = syncEffectFlag;
			syncEffectFlag = -1;

			//cout << "Id = " << Id << endl;

			res += send_data(TO_SERVER, &command, sizeof(command));
			//for (int i = 0; i < MAX_EFFECT; i++) {

			res += send_data(TO_SERVER, &Id, sizeof(int));
			//res += send_data(TO_SERVER,sys->effect,sizeof(sys->effect));

			res += send_data(TO_SERVER, &sys->effect[Id].f, sizeof(int));
			res += send_data(TO_SERVER, &sys->effect[Id].fromPlayerID, sizeof(int));
			res += send_data(TO_SERVER, &sys->effect[Id].count, sizeof(int));
			res += send_data(TO_SERVER, &sys->effect[Id].x, sizeof(double));
			res += send_data(TO_SERVER, &sys->effect[Id].y, sizeof(double));
			res += send_data(TO_SERVER, &sys->effect[Id].z, sizeof(double));
			res += send_data(TO_SERVER, &sys->effect[Id].r, sizeof(double));
			res += send_data(TO_SERVER, &sys->effect[Id].dir, sizeof(double));

			return res;

		} else if (command == E_SYNC_COMMAND) {
			//for (int i = 0; i < MAX_EFFECT; i++) {
			int Id = 0;

			receive_data(TO_SERVER, &Id, sizeof(int));
			receive_data(TO_SERVER, &sys->effect[Id].f, sizeof(int));
			receive_data(TO_SERVER, &sys->effect[Id].fromPlayerID, sizeof(int));
			receive_data(TO_SERVER, &sys->effect[Id].count, sizeof(int));
			receive_data(TO_SERVER, &sys->effect[Id].x, sizeof(double));
			receive_data(TO_SERVER, &sys->effect[Id].y, sizeof(double));
			receive_data(TO_SERVER, &sys->effect[Id].z, sizeof(double));
			receive_data(TO_SERVER, &sys->effect[Id].r, sizeof(double));
			receive_data(TO_SERVER, &sys->effect[Id].dir, sizeof(double));
			//}
			return 0;
		}

	}

	return (result);
}

int netBase::serverCommand(char command, int index) {
	int result = 0;

	if (command == FACE_COMMAND) {
		int Id = 0;
		receive_data(index, &Id, sizeof(int));
		receive_data(index, &tmpImageSize[Id], sizeof(int));

		//if(tmpImage[Id]!=NULL)free(tmpImage[Id]);
		tmpImage[Id] = (char *) malloc(tmpImageSize[Id]);

		receiveData(index, tmpImage[Id], tmpImageSize[Id]);

		for (int c = 0; c < 4; c++) {
			syncImageFlag[c] = 1;
		}
		/*
		 char com = FACE_SYNC_COMMAND;
		 for (int c = 0; c < 4; c++) {
		 if (cli[c].socket > 0) {
		 send_data(c, &com, sizeof(char));
		 send_data(c, &Id, sizeof(int));
		 send_data(c, &fsize, sizeof(int));
		 sendData(c, tmpImage[Id], (int) fsize);
		 }
		 }*/
		return 0;
	} else if (command == POS_COMMAND) {
		int Id = 0;
		receive_data(index, &Id, sizeof(int));
		receive_data(index, &sys->player[Id].chara, sizeof(int));
		receive_data(index, &sys->player[Id].x, sizeof(double));
		receive_data(index, &sys->player[Id].y, sizeof(double));
		receive_data(index, &sys->player[Id].z, sizeof(double));
		receive_data(index, &sys->player[Id].dir, sizeof(double));
		/*
		 cout << "receive player[" << Id << "] position " << sys->player[Id].x
		 << sys->player[Id].y << sys->player[Id].z << sys->player[Id].dir
		 << endl;*/
		return 0;
	} else if (command == SYNC_COMMAND) {
		int res = 0;
		res += send_data(index, &command, sizeof(char));
		for (int i = 0; i < CLIENT_MAX; i++) {

			res += send_data(index, &sys->player[i].hp, sizeof(int));
			res += send_data(index, &sys->player[i].mp, sizeof(int));
			res += send_data(index, &sys->player[i].chara, sizeof(int));
			res += send_data(index, &sys->player[i].x, sizeof(double));
			res += send_data(index, &sys->player[i].y, sizeof(double));
			res += send_data(index, &sys->player[i].z, sizeof(double));
			res += send_data(index, &sys->player[i].dir, sizeof(double));
			cout << "send player[" << i << "] position " << sys->player[i].x << sys->player[i].y << sys->player[i].z
					<< sys->player[i].dir << " chara=" << sys->player[i].chara << endl;
		}
		return res;
	} else if (command == EFFECT_COMMAND) {
		int Id = 0, recvdint = 0;

		//for(int c=0;c<MAX_EFFECT;c++){
		receive_data(index, &Id, sizeof(int));
		receive_data(index, &sys->effect[Id].f, sizeof(int));
		receive_data(index, &sys->effect[Id].fromPlayerID, sizeof(int));
		receive_data(index, &sys->effect[Id].count, sizeof(int));
		receive_data(index, &sys->effect[Id].x, sizeof(double));
		receive_data(index, &sys->effect[Id].y, sizeof(double));
		receive_data(index, &sys->effect[Id].z, sizeof(double));
		receive_data(index, &sys->effect[Id].r, sizeof(double));
		receive_data(index, &sys->effect[Id].dir, sizeof(double));

		syncEEffectFlag[Id] = 1;
		//}
		return 0;
	} else if (command == E_SYNC_COMMAND) {
		int res = 0;
		for (int i = 0; i < MAX_EFFECT; i++) {
			if (syncEEffectFlag[i] == 1) {
				for (int c = 0; c < 4; c++) {
					if (cli[c].socket > 0) {
						res += send_data(c, &command, sizeof(char));
						res += send_data(c, &i, sizeof(int));
						res += send_data(c, &sys->effect[i].f, sizeof(int));
						res += send_data(c, &sys->effect[i].fromPlayerID, sizeof(int));
						res += send_data(c, &sys->effect[i].count, sizeof(int));
						res += send_data(c, &sys->effect[i].x, sizeof(double));
						res += send_data(c, &sys->effect[i].y, sizeof(double));
						res += send_data(c, &sys->effect[i].z, sizeof(double));
						res += send_data(c, &sys->effect[i].r, sizeof(double));
						res += send_data(c, &sys->effect[i].dir, sizeof(double));
					}
				}
				syncEEffectFlag[i] = 0;
				return 0;
			}
		}
		return res;

	} else {
		cout << "unknown command" << endl;
	}

	return 1;
}

netBase::netBase() {
	syncEffectFlag = -1;
	for (int i = 0; i < MAX_EFFECT; i++) {
		syncEEffectFlag[i] = 0;
	}
	for (int c = 0; c < 4; c++) {
		syncImageFlag[c] = 0;

		FILE *fp;
		fp = fopen("data/image/dummy.bmp", "rb");

		if (fp != NULL) {
			fseek(fp, 0, SEEK_END);
			tmpImageSize[c] = ftell(fp);
			fclose(fp);
		}
		fp = fopen("data/image/dummy.bmp", "rb");
		if (fp != NULL) {
			tmpImage[c] = (char *) malloc((int) tmpImageSize[c]);
			fread((void*) tmpImage[c], (int) tmpImageSize[c], tmpImageSize[c], fp);
			fclose(fp);
		}

	}
	// TODO Auto-generated constructor stub
}

netBase::~netBase() {
	// TODO Auto-generated destructor stub
}
