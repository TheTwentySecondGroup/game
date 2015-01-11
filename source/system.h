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
	int judgeHit(int mode,Player *pl,Effect *ef);	//当たり判定
	void gameMain();	//ゲームのメイン

	void detectCollision();

};

extern System *sys;
#endif
