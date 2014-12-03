#ifndef __EFFECT_H__
#define __EFFECT_H__

class Effect{
public:
   double x;
   double z;

   GLuint *effectImage[10];

   Effect();
   void hp(double x, double z);
   void mp();
   void drawAttack(double px, double pz);
   void drawAttack2(double px, double pz);
   void drawAttack3(double px, double pz, double pr);
};

#endif
