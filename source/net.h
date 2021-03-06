/*
 * net.h
 *
 *  Created on: 2014/11/26
 *  last update 2015/02/12
 *      Author: Takeda
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
public:
	//handle
	pthread_t ser_t, cli_t;
	char IP[16];//ip address

	NetClass();
	NetClass(int mode);
	~NetClass();

	/*
	 *サーバー用セットアップ関数
	 * */
	int setServer();//set up server 
	
	
	
	
	/*
	 *サーバールーチン
	 * */
	int routineServer(); //routine of server


	/*
	 *クライアント用セットアップ関数
	 * */
	int setClient(char*);//set up client



	/*
	 *クライアントルーチン
	 * */
	int routineClient();//routine of client


	/*
	 *待ち受けソケット待機用
	 * */
	int waitingClient();
};

#endif /* SOURCE_NET_H_ */
