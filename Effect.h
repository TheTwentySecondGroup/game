#ifndef __EFFECT_H__
#define __EFFECT_H__

#define EFFECT_MAX 50
struct ef{
   int f;
   double x;
   double y;
   double h;
   double w;
   double z;
   char str[256];

   int restTime;
} ;

extern struct ef Effect[EFFECT_MAX];

void initEffect();
void procEffect();
void hp(double x, double y);
void mp();
void drawA(int x, int y);

void drawText2D(int x,int y,int w,int h,char *str);
void makeEffect(int type,int time,char* str);

#endif
