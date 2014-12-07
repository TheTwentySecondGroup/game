#ifndef __EFFECT_H__
#define __EFFECT_H__

#define MAX_EFFECT 20
class Effect{
public:
   int f,count,fromPlayerID;
	double x,y, z,dir,r;

   GLuint *effectImage[15];

   Effect();
   void routine();
   void hp(double x, double z);
   void mp();

   void draw();
   void drawAttack(double px, double pz);
   void drawAttack2(double px, double pz);
   void drawAttack3(double px, double pz);
   void drawAttack4(double px, double pz);
   void drawAttack5(double px, double pz);
   /*
   void drawAttack(double px, double pz);
   void drawAttack2(double px, double pz);
   void drawAttack3(double px, double pz, double pr);
   void drawAttack4(double px, double pz);*/
};

#endif
