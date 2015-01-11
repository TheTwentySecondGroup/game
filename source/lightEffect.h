#ifndef __LIGHT_EFFECT_H__
#define __LIGHT_EFFECT_H__

#define MAX_LIGHT_EFFECT 100
#define LIGHT_COUNT 128
#define NUM_LIGHT_EFFECT 4
class lightEffect{
public:
   int f,count[MAX_LIGHT_EFFECT];
   double posX,posY;
   double x[MAX_LIGHT_EFFECT],y[MAX_LIGHT_EFFECT],z[MAX_LIGHT_EFFECT],dx[MAX_LIGHT_EFFECT],dy[MAX_LIGHT_EFFECT],dz[MAX_LIGHT_EFFECT];

   lightEffect();
   void routine();


   void draw();
   void drawAttack();
};

#endif
