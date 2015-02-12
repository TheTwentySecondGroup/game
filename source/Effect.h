/*
 * Effect.h
 *
 *  last update 2015/02/12
 *      Author: Murokawa
 */

#ifndef __EFFECT_H__
#define __EFFECT_H__

#define MAX_EFFECT 20
#define COUNT 150
class Effect{
	public:
		//座標など各情報格納変数
		int f,count,fromPlayerID;
		double x,y,z,dx,dy,dz,dir,r;

		//画像用ハンドル
		GLuint *effectImage[15];

		Effect();

		//処理ルーチン
		void routine();

		// void hp(double x, double z);
		// void mp();


		//攻撃エフェクト表示関数
		void draw();
		void drawAttack();
		void drawAttack2();
		void drawAttack3();
		void drawAttack4();
		void drawAttack5();
		void drawAttack6();
		void drawAttack7();
		void drawAttack8();
};

#endif
