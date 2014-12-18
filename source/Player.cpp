/*
 * Player.cpp
 *
 *  Created on: 2014/11/23
 *      Author: chihiro
 */

#include "Player.h"
#include "Map.h"
#include "system.h"
#include "global.h"


Player::Player() {


	x = 2.0;
	y = 0;
	z = 2.0;

	dir=0.8;	//移動方向

	for(int i=0;i<MAP_X_MAX;i++){
		int breakflag=0;
		for(int c=0;c<MAP_Y_MAX;c++){
			if(sys->map->data[i][c]==2){
				sys->map->data[i][c]=0;
				x=i+0.5;
				z=c+0.5;
				if(i>6 &&c>6){
					dir= 0.8+3.14;
				}else if(i>6){
					dir = 0.8+3.14+1.52;
				}else if(c>6){
					dir = 0.8+1.52;
				}
				breakflag=1;
				break;
			}
		}
		if(breakflag==1)break;
	}

	chara=-1;
	xd=0;	//x方向の移動距離
	yd=0;	//y方向の移動距離
	hp=100;	//キャラのHP
	mp=0;	//キャラのMP
	mp_heal=0;	//MP回復量
	attflag=0;	//攻撃フラグ
	attpatern=0;


	avoidDamageCount=0;
	//string skill[4];	//キャラごとの魔法を格納
	// TODO Auto-generated constructor stub

}

void Player::routine(){
	if(avoidDamageCount>0)avoidDamageCount--;
}

Player::~Player() {
	// TODO Auto-generated destructor stub
}

