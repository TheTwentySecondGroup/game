/*
 * net.h
 *
 *  Created on: 2014/11/26
 *      Author: chihiro
 */

#ifndef SOURCE_NET_H_
#define SOURCE_NET_H_

using namespace std;
#include <iostream>
#include "global.h"
#include "system.h"
#include "netBase.h"

#define MODE_CLIENT 0
#define MODE_SERVER 1
#define PORT 10088

void* serverMain(void* pParam);
void* clientMain(void* pParam);

class NetClass:public netBase{
private:

	int Send_receive_manager(void);

public:
	pthread_t ser_t, cli_t;

	NetClass();
	NetClass(int mode);
	~NetClass();
	int setServer();
	int routineServer();

	int setClient(char*);
	int routineClient();

	int waitingClient();

};

#endif /* SOURCE_NET_H_ */
