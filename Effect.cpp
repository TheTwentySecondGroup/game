#include "global.h"
#include "Effect.h"
#include "draw.h"
#include "Map.h"
#include "Title.h"
#include "system.h"

//structure for effect
struct ef Effect[EFFECT_MAX];


//initialize effect
void initEffect(){
    int i;
    for(i=0;i<EFFECT_MAX;i++){
        Effect[i].f=0;
        Effect[i].x=-1;
        Effect[i].y=-1;
        Effect[i].z=-1;
        Effect[i].restTime=0;
    }
}

//type ==1 ->drawText to screen
void makeEffect(int type,int time,char* str){
    int i;
    for(i=0;i<EFFECT_MAX;i++){
        if(Effect[i].f==0){
            if(type==1){
                Effect[i].f=1;
                Effect[i].x=WINDOW_X/2-200;
                Effect[i].y=WINDOW_Y/2-100;
                Effect[i].w=400;
                Effect[i].h=200;
                Effect[i].restTime=time;
                strcpy(Effect[i].str,str);
			}
            return;
        }
    }

}

void hp(double x, double y, double dir){
//glDisable(GL_CULL_FACE);
glViewport(0, 700, WINDOW_X, WINDOW_Y);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(30.0, (GLdouble) WINDOW_X / (GLdouble) WINDOW_Y, 0.01, 15.0);
	glBindTexture(GL_TEXTURE_2D,*texHandle[6]);
	GLfloat vertices[4][3]={
		{x, y+4, 1.4},
		{x-1.4, y+4, 1.4},
		{x-1.4, y+4, 1.3},
		{x, y+4, 1.3},
	};
	glBegin(GL_POLYGON);
	glNormal3f(player[0].xd, player[0].yd, 0);
	glTexCoord2i(0,0);
	glVertex3fv(vertices[0]);
	glTexCoord2i(0,1);
	glVertex3fv(vertices[1]);
	glTexCoord2i(1,1);
	glVertex3fv(vertices[2]);
	glTexCoord2i(1,0);
	glVertex3fv(vertices[3]);
	glEnd();
	//glEnable(GL_CULL_FACE);
}

void drawA(int x, int y){
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,GrayMaterial);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,GrayMaterial);
	glMaterialf(GL_FRONT,GL_SHININESS,60.0);
	
	glBindTexture(GL_TEXTURE_2D,*texHandle[4]);
	
	GLfloat vertices[4][3]={
		{2+x, 2+y, 0.1},
		{0+x, 2+y, 0.1},
		{0+x, 0+y, 0.1},
		{2+x, 0+y, 0.1},
	};
	glBegin(GL_POLYGON);
	glNormal3f(player[0].xd, player[0].yd, 0);
	glTexCoord2i(0,0);
	glVertex3fv(vertices[0]);
	glTexCoord2i(0,1);
	glVertex3fv(vertices[1]);
	glTexCoord2i(1,1);
	glVertex3fv(vertices[2]);
	glTexCoord2i(1,0);
	glVertex3fv(vertices[3]);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D,*texHandle[5]);
	GLfloat vertices2[4][3]={
		{2+x, 0+y, 1.5},
		{0+x, 0+y, 1.5},
		{0+x, 0+y, 0.1},
		{2+x, 0+y, 0.1},
	};
	glBegin(GL_POLYGON);
	glNormal3f(player[0].xd, player[0].yd, 0);
	glTexCoord2i(0,0);
	glVertex3fv(vertices2[0]);
	glTexCoord2i(0,1);
	glVertex3fv(vertices2[1]);
	glTexCoord2i(1,1);
	glVertex3fv(vertices2[2]);
	glTexCoord2i(1,0);
	glVertex3fv(vertices2[3]);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D,*texHandle[5]);
	GLfloat vertices3[4][3]={
		{2+x, 2+y, 1.5},
		{0+x, 2+y, 1.5},
		{0+x, 2+y, 0.1},
		{2+x, 2+y, 0.1},
	};
	glBegin(GL_POLYGON);
	glNormal3f(player[0].xd, player[0].yd, 0);
	glTexCoord2i(0,0);
	glVertex3fv(vertices3[0]);
	glTexCoord2i(0,1);
	glVertex3fv(vertices3[1]);
	glTexCoord2i(1,1);
	glVertex3fv(vertices3[2]);
	glTexCoord2i(1,0);
	glVertex3fv(vertices3[3]);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D,*texHandle[5]);
	GLfloat vertices4[4][3]={
		{x, 2+y, 1.5},
		{x, 0+y, 1.5},
		{x, 0+y, 0.1},
		{x, 2+y, 0.1},
	};
	glBegin(GL_POLYGON);
	glNormal3f(player[0].xd, player[0].yd, 0);
	glTexCoord2i(0,0);
	glVertex3fv(vertices4[0]);
	glTexCoord2i(0,1);
	glVertex3fv(vertices4[1]);
	glTexCoord2i(1,1);
	glVertex3fv(vertices4[2]);
	glTexCoord2i(1,0);
	glVertex3fv(vertices4[3]);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D,*texHandle[5]);
	GLfloat vertices5[4][3]={
		{2+x, 2+y, 1.5},
		{2+x, 0+y, 1.5},
		{2+x, 0+y, 0.1},
		{2+x, 2+y, 0.1},
	};
	glBegin(GL_POLYGON);
	glNormal3f(player[0].xd, player[0].yd, 0);
	glTexCoord2i(0,0);
	glVertex3fv(vertices5[0]);
	glTexCoord2i(0,1);
	glVertex3fv(vertices5[1]);
	glTexCoord2i(1,1);
	glVertex3fv(vertices5[2]);
	glTexCoord2i(1,0);
	glVertex3fv(vertices5[3]);
	glEnd();
}
