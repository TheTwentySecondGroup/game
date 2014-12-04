/*
 * netBase.h
 *
 *  Created on: 2014/11/28
 *      Author: chihiro
 */

#ifndef SOURCE_NETBASE_H_
#define SOURCE_NETBASE_H_

using namespace std;


#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
//#include <netdb.h>
#include <assert.h>


#define POS_COMMAND 'P'
#define SYNC_COMMAND 'S'
#define EFFECT_COMMAND 'E'
#define E_SYNC_COMMAND 'W'


//1==non-blocking 0==blocking
#define SOCKET_BLOCKING_MODE 0
#define SOCKET_NONBLOCKING_MODE 1
#define ALL_CLIENTS -1
#define TO_SERVER -2
#define SEND_TO_SERVER -3
#define MAX_BUFFER_LENGTH 256
#define MAX_DATA 1024
#define CLIENT_MAX 4

class client{
public:
  int socket;
  string name;
  client();
};

class netBase {
public:
	//vector<client> cli;
	client cli[CLIENT_MAX];
	client ser;

	int listenSocket;

	netBase();
	virtual ~netBase();

	void Close(void);
	int receive_data(int index, void *data, int data_size);
	int send_data(int index, void *data, int data_size);
	int Accept(int);

	void sendId(void);


	//for client
	//int Connect(void);
	int routineClient(void);




//	int multi_accept(int request_socket, int num_clients);
	void receive_user_name(int i, int fd) ;
	void set_mask(int num_clients, int maxfd);
	void send_all_names(void) ;
	int execute_command(char command, int index);

	int serverCommand(char command, int index);
	int clientCommand(char command, int index);




	void set_double_data2data_block(void *data, double double_data,int *data_size);
	void set_int_data2data_block(void *data, int int_data, int *data_size);
	void set_data_block2int_data(int *int_data, void *data, int *data_size);
	void set_char_data2data_block(void *data, char char_data, int *data_size);
	void set_string_data2data_block(void *data, char *string_data, int string_length, int *data_size);
	void set_data_block2string_data(char *string_data, void *data, int string_length, int *data_size);


};


#endif /* SOURCE_NETBASE_H_ */
