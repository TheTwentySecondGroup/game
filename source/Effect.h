#ifndef __EFFECT_H__
#define __EFFECT_H__

#define MAX_EFFECT 20
#define COUNT 150
class Effect{
public:
   int f,count,fromPlayerID;
	double x,y,z,dx,dy,dz,dir,r;

   GLuint *effectImage[15];

   Effect();
   void routine();
   void hp(double x, double z);
   void mp();

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
