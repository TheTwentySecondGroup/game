/*
 * Player.h
 *
 *  last update 2015/02/12
 *      Author: Murokawa,Takeda
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
	int attpatern;	//攻撃の種類
	string skill[4];	//キャラごとの魔法を格納


	//1以上の時はダメージを受けない
	int avoidDamageCount;

	void routine();//プレイヤールーチン
	Player();
	~Player();
};




#endif /* SOURCE_PLAYER_H_ */
