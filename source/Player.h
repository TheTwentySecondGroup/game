/*
 * Player.h
 *
 *  Created on: 2014/11/23
 *      Author: chihiro
 */

#ifndef SOURCE_PLAYER_H_
#define SOURCE_PLAYER_H_
#include <string>
using namespace std;

class Player {
public:
	int chara;
	double x;	//キャラのx座標
	double y;	//y座標
	double z;	//z座標
	double dir;	//移動方向
	double xd;	//x方向の移動距離
	double yd;	//y方向の移動距離
	int hp;	//キャラのHP
	int mp;	//キャラのMP
	int mp_heal;	//MP回復量
	int attflag;	//攻撃フラグ
	string skill[4];	//キャラごとの魔法を格納


	Player();
	~Player();
};




#endif /* SOURCE_PLAYER_H_ */
