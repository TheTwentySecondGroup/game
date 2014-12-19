
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

Tutorial::Tutorial() { //(System *system){
	//sys=system;
	Slide = 0;
	TutorialImage[0] = sys->draw->initTexture("data/image/1.bmp");
	TutorialImage[1] = sys->draw->initTexture("data/image/2.bmp");
	//TutorialImage[2] = sys->draw->initTexture("data/image/3.bmp");
}



Tutorial::~Tutorial() {
	glDeleteTextures(SLIDE_MAX, *TutorialImage);
}
void Tutorial::routine() {
	cout<<"execute tutorial routine()"<<endl;
	if(sys->io->key[KEY_A] == 1) {
		Slide++;
	}

	//if(key[SDLK_BACKSPACE] == SDL_PRESSED) {
		//Button2++;
	//} else {
		//Button2=0;
	//}
	/*

	Uint8 *key = SDL_GetKeyState(NULL);
	if(key[SDLK_RETURN] == SDL_PRESSED) {
		Button1++;
	} else {
		Button1=0;
	}
	if(key[SDLK_BACKSPACE] == SDL_PRESSED) {
		Button2++;
	} else {
		Button2=0;
	}

	*/
	//}
	//if(Button1==1)Slide++;
	//else if(Button2==1)Slide--;
	if(Slide>=SLIDE_MAX) {
		//delTutorial();
		//initEffect();
		//makeEffect(1,120,"Start");
		sys->Stage = -1;
		//initMap(1);
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

		sys->title->drawMenu(100,100,800,100,"its tutorial sample");


	}

	cout<<"execute tutorial draw() 4"<<endl;

	glFlush();
	SDL_GL_SwapBuffers();
}

