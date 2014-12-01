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


	int myID;
	//int myChara;
	int selChara;
	int Stage;
	int charatype;


	float dx, dy;
	int count;


	//Obj player[4];


	TTF_Font *font;
	vector<Model> model;

	System();
	~System();
	void initChara();
	int selectChara();
	void moveChara();	//キャラの移動
	int judgeHit();	//当たり判定
	void gameMain();	//ゲームのメイン

};

extern System *sys;
#endif
