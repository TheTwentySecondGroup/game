#include "global.h"
#include "Effect.h"
#include "draw.h"
#include "Map.h"
#include "Title.h"
#include "system.h"

static double r = 0;

Effect::Effect(){
	x = 0.0;
	z = 0.0;
	
	effectImage[0] = sys->draw->initTexture("data/image/lake.bmp");
	effectImage[1] = sys->draw->initTexture("data/image/star.bmp");
    effectImage[2] = sys->draw->initTexture("data/image/mist.bmp");
    effectImage[3] = sys->draw->initTexture("data/image/fire.bmp");
}

void Effect::drawAttack(double x, double z){
	glMaterialf(GL_FRONT,GL_SHININESS,60.0);
	
	glBindTexture(GL_TEXTURE_2D,*effectImage[1]);
	//glRotated((double)r, x, 1.0, z);	//
	glTranslatef(x, 0, 1+z);
	glRotated(r, 0.0, 1.0, 0.0);
	glTranslatef(-x, 0, -(1+z));
	GLfloat vertices[4][3]={
		{1+x, 0.3, z+2},
		{x-1, 0.3, z+2},
		{x-1, 0.3, z},
		{1+x, 0.3, z},
	};
	glBegin(GL_POLYGON);
	glNormal3f(sys->player[sys->myID].xd, sys->player[sys->myID].yd, 0);
	glTexCoord2i(0,0);
	glVertex3fv(vertices[0]);
	glTexCoord2i(0,1);
	glVertex3fv(vertices[1]);
	glTexCoord2i(1,1);
	glVertex3fv(vertices[2]);
	glTexCoord2i(1,0);
	glVertex3fv(vertices[3]);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D,*effectImage[2]);
	GLfloat vertices2[4][3]={
		{1+x, 1.5, z},
		{x-1, 1.5, z},
		{x-1, 0.3, z},
		{1+x, 0.3, z},
	};
	glBegin(GL_POLYGON);
	glNormal3f(sys->player[sys->myID].xd, sys->player[sys->myID].yd, 0);
	glTexCoord2i(0,0);
	glVertex3fv(vertices2[0]);
	glTexCoord2i(0,1);
	glVertex3fv(vertices2[1]);
	glTexCoord2i(1,1);
	glVertex3fv(vertices2[2]);
	glTexCoord2i(1,0);
	glVertex3fv(vertices2[3]);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D,*effectImage[2]);
	GLfloat vertices3[4][3]={
		{1+x, 1.5, 2+z},
		{x-1, 1.5, 2+z},
		{x-1, 0.3, 2+z},
		{1+x, 0.3, 2+z},
	};
	glBegin(GL_POLYGON);
	glNormal3f(sys->player[sys->myID].xd, sys->player[sys->myID].yd, 0);
	glTexCoord2i(0,0);
	glVertex3fv(vertices3[0]);
	glTexCoord2i(0,1);
	glVertex3fv(vertices3[1]);
	glTexCoord2i(1,1);
	glVertex3fv(vertices3[2]);
	glTexCoord2i(1,0);
	glVertex3fv(vertices3[3]);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D,*effectImage[2]);
	GLfloat vertices4[4][3]={
		{x-1, 1.5, 2+z},
		{x-1, 1.5, z},
		{x-1, 0.3, z},
		{x-1, 0.3, 2+z},
	};
	glBegin(GL_POLYGON);
	glNormal3f(sys->player[sys->myID].xd, sys->player[sys->myID].yd, 0);
	glTexCoord2i(0,0);
	glVertex3fv(vertices4[0]);
	glTexCoord2i(0,1);
	glVertex3fv(vertices4[1]);
	glTexCoord2i(1,1);
	glVertex3fv(vertices4[2]);
	glTexCoord2i(1,0);
	glVertex3fv(vertices4[3]);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D,*effectImage[2]);
	GLfloat vertices5[4][3]={
		{1+x, 1.5, 2+z},
		{1+x, 1.5, z},
		{1+x, 0.3, z},
		{1+x, 0.3, 2+z},
	};
	glBegin(GL_POLYGON);
	glNormal3f(sys->player[sys->myID].xd, sys->player[sys->myID].yd, 0);
	glTexCoord2i(0,0);
	glVertex3fv(vertices5[0]);
	glTexCoord2i(0,1);
	glVertex3fv(vertices5[1]);
	glTexCoord2i(1,1);
	glVertex3fv(vertices5[2]);
	glTexCoord2i(1,0);
	glVertex3fv(vertices5[3]);
	glEnd();
	
	if ((r+=20) >= 360) r = 0;
}

void Effect::drawAttack2(double x, double z){
		glMaterialf(GL_FRONT,GL_SHININESS,60.0);

		glDisable(GL_CULL_FACE);
		//前
		glBindTexture(GL_TEXTURE_2D,*effectImage[3]);
		GLfloat vertices1[4][3]={
			{x+0,    0.6, z+3},
			{x+0,    0.5, z+3},
			{x+0.25, 0.6, z+2},
			{x+0.25, 0.7, z+2},
		};
		glBegin(GL_POLYGON);
		glNormal3f(vertices1[0][0], vertices1[0][1], vertices1[0][2]);
		glTexCoord2i(0,0);
		glVertex3fv(vertices1[0]);
		
		glNormal3f(vertices1[1][0], vertices1[1][1], vertices1[1][2]);
		glTexCoord2i(0,1);
		glVertex3fv(vertices1[1]);
		
		glNormal3f(vertices1[2][0], vertices1[2][1], vertices1[2][2]);
		glTexCoord2i(1,1);
		glVertex3fv(vertices1[2]);
		
		glNormal3f(vertices1[3][0], vertices1[3][1], vertices1[3][2]);
		glTexCoord2i(1,0);
		glVertex3fv(vertices1[3]);
		glEnd();

		
		glBindTexture(GL_TEXTURE_2D,*effectImage[0]);
		GLfloat vertices2[4][3]={
			{x+0,    0.6, z+3},
			{x+0,    0.5, z+3},
			{x-0.25, 0.6, z+2},
			{x-0.25, 0.7, z+2},
		};
		glBegin(GL_POLYGON);
		glNormal3f(vertices2[0][0], vertices2[0][1], vertices2[0][2]);
		glTexCoord2i(0,0);
		glVertex3fv(vertices2[0]);
		
		glNormal3f(vertices2[1][0], vertices2[1][1], vertices2[1][2]);
		glTexCoord2i(0,1);
		glVertex3fv(vertices2[1]);
		
		glNormal3f(vertices2[2][0], vertices2[2][1], vertices2[2][2]);
		glTexCoord2i(1,1);
		glVertex3fv(vertices2[2]);
		
		glNormal3f(vertices2[3][0], vertices2[3][1], vertices2[3][2]);
		glTexCoord2i(1,0);
		glVertex3fv(vertices2[3]);
		glEnd();

		
		glBindTexture(GL_TEXTURE_2D,*effectImage[0]);
		GLfloat vertices3[4][3]={
			{x+0.25, 0.7, 2+z},
			{x+0.25, 0.6, 2+z},
			{x+0,    0.7, 1+z},
			{x+0,    0.8, 1+z},
		};
		glBegin(GL_POLYGON);
		glNormal3f(vertices3[0][0], vertices3[0][1], vertices3[0][2]);
		glTexCoord2i(0,0);
		glVertex3fv(vertices3[0]);
		
		glNormal3f(vertices3[1][0], vertices3[1][1], vertices3[1][2]);
		glTexCoord2i(0,1);
		glVertex3fv(vertices3[1]);
		
		glNormal3f(vertices3[2][0], vertices3[2][1], vertices3[2][2]);
		glTexCoord2i(1,1);
		glVertex3fv(vertices3[2]);
		
		glNormal3f(vertices3[3][0], vertices3[3][1], vertices3[3][2]);
		glTexCoord2i(1,0);
		glVertex3fv(vertices3[3]);
		glEnd();

		//右
		glBindTexture(GL_TEXTURE_2D,*effectImage[3]);
		GLfloat vertices4[4][3]={
			{x-0.25, 0.7, 2+z},
			{x-0.25, 0.6, 2+z},
			{x+0,    0.7, 1+z},
			{x+0,    0.8, 1+z},
		};
		glBegin(GL_POLYGON);
		glNormal3f(vertices4[0][0], vertices4[0][1], vertices4[0][2]);
		glTexCoord2i(0,0);
		glVertex3fv(vertices4[0]);
		
		glNormal3f(vertices4[1][0], vertices4[1][1], vertices4[1][2]);
		glTexCoord2i(0,1);
		glVertex3fv(vertices4[1]);
		
		glNormal3f(vertices4[2][0], vertices4[2][1], vertices4[2][2]);
		glTexCoord2i(1,1);
		glVertex3fv(vertices4[2]);
		
		glNormal3f(vertices4[3][0], vertices4[3][1], vertices4[3][2]);
		glTexCoord2i(1,0);
		glVertex3fv(vertices4[3]);
		glEnd();
}

