/*
 * system.h
 *
 *  last update 2015/02/12
 *      Author: Murokawa,Takeda
 */

#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "global.h"
#include "draw.h"
#include "Tutorial.h"
#include "Model.h"
#include "Title.h"
#include "Player.h"
#include "io.h"
#include "Map.h"
#include "net.h"
#include "Effect.h"
#include "lightEffect.h"
#include <stdio.h>
#include <opencv2/core/core_c.h>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/highgui/highgui_c.h>


using namespace std;

class System {
public:


	//shortcut
	Draw *draw;
	Title *title;
	Tutorial *tutorial;
	GameIO *io;
	Map *map;
	Player *player;
	NetClass *network;
	Effect *effect;
	lightEffect *lighteffect;

	int mode;//モード

	int myID;//ID
	//int myChara;
	int selChara;//選択キャラ
	int selConf;//選択conf
	int Stage;//ステージ
	int charatype;//キャラの種類


	float dx, dy;
	int count;


	//Obj player[4];


	TTF_Font *font;//フォント
	vector<Model> model;//モデル

	GLuint *faceImage[4];//顔画像ハンドル
	GLuint *myFaceImage;//自分の顔

	int sendFaceFlag;//顔画像送信フラグ

	System(int);
	~System();


	int selectChara(); //キャラ選択画面
	void moveChara();	//キャラの移動
	int judgeHit(int mode,Player *pl,Effect *ef);	//当たり判定
	void gameMain();	//ゲームのメイン
	void IPset();//IPaddress設定画面
	void selConfig();// コンフィグ画面
	int VOLset(int vol);//音量調節画面
	void detectCollision();//当たり判定実行関数

//camera用
	CvCapture *capture;
	IplImage *sourceImage;
	int initCamera();//カメラ初期化
	int capImage();//写真所得



	//music
	Mix_Music    *bgm;
	Mix_Chunk    *damage,*wind,*thunder,*ice,*fire,*blade;

};

extern System *sys;
#endif
