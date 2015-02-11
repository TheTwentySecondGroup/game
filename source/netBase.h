/*
 * netBase.h
 *
 *  Created on: 2014/11/28
 *  last update 2015/02/12
 *      Author: Takeda
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
#include "Effect.h"


#define POS_COMMAND 'P'
#define SYNC_COMMAND 'S'
#define EFFECT_COMMAND 'E'
#define E_SYNC_COMMAND 'W'
#define FACE_COMMAND 'I'
#define FACE_SYNC_COMMAND 'A'


//1==non-blocking 0==blocking
#define SOCKET_BLOCKING_MODE 0
#define SOCKET_NONBLOCKING_MODE 1
#define ALL_CLIENTS -1
#define TO_SERVER -2
#define SEND_TO_SERVER -3
#define MAX_BUFFER_LENGTH 256
#define MAX_DATA 1024
#define CLIENT_MAX 4


//クライアント用クラス
class client{
public:
  int socket;
  string name;
  client();
};


//ネットワーク基礎クラス
class netBase {
public:
	//vector<client> cli;
	client cli[CLIENT_MAX];//クライアント
	client ser;//サーバー

	int listenSocket;//待ち受けソケット

	//sync effect etc
	//for client
	int syncEffectFlag;//エフェクト同期用フラグ
	//for server
	int syncEEffectFlag[MAX_EFFECT];//エフェクト同期用フラグ

	char* tmpImage[4];//顔画像送信用

	int tmpImageSize[4];//顔画像サイズ

	int syncImageFlag[4];//顔画像同期用フラグ


	netBase();
	virtual ~netBase();

	void Close(void);
	int receive_data(int index, void *data, int data_size);//データ受信用関数
	int send_data(int index, void *data, int data_size);//データ送信用関数


	int sendData(int index, void *data, int data_size) ;//データ送信用関数2
	int receiveData(int index, void *data, int data_size);//データ受信用関数2



	int Accept(int);//accept用関数



	//for client
	//int Connect(void);
	int routineClient(void);//クライアントルーチン



	int serverCommand(char command, int index);//サーバー用コマンド実行関数
	int clientCommand(char command, int index);//クライアント用コマンド実行関数

};


#endif /* SOURCE_NETBASE_H_ */
