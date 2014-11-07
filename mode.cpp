#include"global.h"
#include"mode.h"
#include "draw.h"
#include "Title.h"
#include "Tutorial.h"
#include "Effect.h"
#include "Map.h"

GLuint *image[3];

void mode1(){
	image[0] = initTexture("data/image/1.bmp");
	//glClearColor(0.0, 0.0, 1.0, 0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//glFlush();
	 init3D();
    {
		//draw wall
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,WhiteMaterial);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,WhiteMaterial);
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,WhiteMaterial);
        glMaterialf(GL_FRONT,GL_SHININESS,60.0);
        glBindTexture( GL_TEXTURE_2D, *image[0] );
        GLfloat vertices [4][3]={
            {2, 8,  3.0},
            {2, 8, -1.5},
            { 8, 8, -1.5},
            { 8, 8,  3.0},
        };
        glBegin(GL_POLYGON);
        glNormal3f(player[0].xd , player[0].yd , 0);
        glTexCoord2i(0,0);
        glVertex3f(0, 0, 0);
        glTexCoord2i(0,1);
        glVertex3f(WINDOW_X, 0, 0);
        glTexCoord2i(1,1);
        glVertex3f(WINDOW_X, WINDOW_Y, 0);
        glTexCoord2i(1,0);
        glVertex3f(0, WINDOW_Y, 0);
		glEnd();
	}
	glFlush();
	SDL_GL_SwapBuffers();
}

void mode2();
void mode3();
