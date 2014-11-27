/*
 * Player.cpp
 *
 *  Created on: 2014/11/23
 *      Author: chihiro
 */

#include "Player.h"


Player::Player() {
	x=0;	//キャラのx座標
	y=0;	//y座標
	z=0;	//z座標
	dir=0;	//移動方向
	xd=0;	//x方向の移動距離
	yd=0;	//y方向の移動距離
	hp=0;	//キャラのHP
	mp=0;	//キャラのMP
	mp_heal=0;	//MP回復量
	attflag=0;	//攻撃フラグ
	attpatern=0;
	//string skill[4];	//キャラごとの魔法を格納
	// TODO Auto-generated constructor stub

}

Player::~Player() {
	// TODO Auto-generated destructor stub
}

