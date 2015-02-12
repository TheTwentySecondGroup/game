/*
 * lightEffect.h
 *
 *  last update 2015/02/12
 *      Author: Takeda
 */
#ifndef __LIGHT_EFFECT_H__
#define __LIGHT_EFFECT_H__

#define MAX_LIGHT_EFFECT 100
#define LIGHT_COUNT 128
#define NUM_LIGHT_EFFECT 4
class lightEffect{
public:
   //f 状態
   //count 経過時間
   int f,count[MAX_LIGHT_EFFECT];

   //エフェクト本体の座標
   double posX,posY;

   //粒子毎の相対座標
   double x[MAX_LIGHT_EFFECT],y[MAX_LIGHT_EFFECT],z[MAX_LIGHT_EFFECT],dx[MAX_LIGHT_EFFECT],dy[MAX_LIGHT_EFFECT],dz[MAX_LIGHT_EFFECT];

   lightEffect();
   void routine();//処理ルーチン


   void draw();//描写
};

#endif
