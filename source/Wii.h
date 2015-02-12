/*
 * Wii.h
 *
 *  last update 2015/02/12
 *      Author: Murokawa,Takeda
 */

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <stdlib.h>
#include <libcwiimote/wiimote.h>
#include <libcwiimote/wiimote_api.h>
#include <pthread.h>
#include <SDL/SDL.h>


void* wiimoteUpdate(void* pParam);//情報アップデート
void wiimoteInit(char*);//初期化
int checkpress();//キー状態確認



#ifdef __cplusplus
};
#endif
