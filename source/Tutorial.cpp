
#include "global.h"
#include "draw.h"
#include "Effect.h"
#include "Title.h"
#include "Tutorial.h"
#include "Map.h"
#include "system.h"

int Slide = 0;
int Button1 = 0;
int Button2 = 0;
GLuint *TutorialImage[3];

Tutorial::Tutorial() { 
    	Slide = 0;
	TutorialImage[0] = sys->draw->pngTexture("data/image/tuto1.png");
	TutorialImage[1] = sys->draw->pngTexture("data/image/tuto2.png");
}

Tutorial::~Tutorial() {
	glDeleteTextures(SLIDE_MAX, *TutorialImage);
}
void Tutorial::routine() {
	if(sys->io->key[KEY_A] == 1) {
		Slide++;
	}
	if(Slide>=SLIDE_MAX) {
		sys->Stage = -1;
		return;
	}

	if(Slide<=0)Slide=0;

	draw(Slide);
}

void Tutorial::draw(int n) {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	sys->draw->init3D();
	{
		sys->map->drawMap();
	}
	sys->draw->init2D();
	{
		glBindTexture( GL_TEXTURE_2D, *TutorialImage[n]);
		glBegin( GL_QUADS );
		glTexCoord2i( 0, 0 );
		glVertex3f( 0, 0, 0 );
		glTexCoord2i( 1, 0 );
		glVertex3f( WINDOW_X, 0, 0 );
		glTexCoord2i( 1, 1 );
		glVertex3f( WINDOW_X, WINDOW_Y, 0 );
		glTexCoord2i( 0, 1 );
		glVertex3f( 0, WINDOW_Y, 0 );
		glEnd();
	}

	glFlush();
	SDL_GL_SwapBuffers();
}

