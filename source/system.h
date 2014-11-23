#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "global.h"
#include "draw.h"
#include "Tutorial.h"
#include "Model.h"
#include "Title.h"
#include "Player.h"

using namespace std;

class System {
public:
	//shortcut
	Draw *draw;

	Title *title;

	Tutorial *tutorial;



	//vector<Player> player;
	Player *player;

	int myID;

	float dx, dy;
	int count;

	//Obj player[4];

	int Stage;
	int charatype;

	TTF_Font *font;
	SDL_Joystick *joystick;
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
