
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
	Slide = -1;
	TutorialImage[0] = sys->draw->initTexture("data/image/1.bmp");
	TutorialImage[1] = sys->draw->initTexture("data/image/2.bmp");
	TutorialImage[2] = sys->draw->initTexture("data/image/3.bmp");


}

Tutorial::~Tutorial() {
	Slide = -1;
	glDeleteTextures(SLIDE_MAX, *TutorialImage);
}
void Tutorial::routine() {
	//wiiremocon
	/*if(wiimote_is_open(&wiimote)){
	 if((wiimote.keys.bits & WIIMOTE_KEY_A)>0){
	 Button1++;
	 }else{
	 Button1=0;
	 }
	 if(wiimote.keys.bits & WIIMOTE_KEY_B){
	 Button2++;
	 }else{
	 Button2=0;
	 }
	 } else{*/
	//keyboad
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
	//}
	if(Button1==1)Slide++;
	else if(Button2==1)Slide--;
	if(Slide>=SLIDE_MAX) {
		//delTutorial();
		//initEffect();
		//makeEffect(1,120,"Start");
		Stage = 1;
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
	}
	sys->draw->init2D();
	{

		glBindTexture( GL_TEXTURE_2D, *TutorialImage[0]);
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

		drawText();
	}
	glFlush();
	SDL_GL_SwapBuffers();
}

void Tutorial::drawText() {
	char buf[64];
	strcpy(buf,"    If you use cross-key, you can move.   ");

	SDL_Color white = {255, 255, 255,100};
	SDL_Surface* TextImage;
	TextImage=TTF_RenderUTF8_Blended(sys->draw->font,buf,white);
	GLuint *texText;
	texText = sys->draw->timeTexture(TextImage);

	glBindTexture( GL_TEXTURE_2D, *texText);
	glBegin( GL_QUADS );
	glColor4f(1.0,1.0,1.0,1.0);
	glTexCoord2i( 0, 0 );
	glVertex3f( 0, WINDOW_Y-100, 0 );
	glTexCoord2i( 1, 0 );
	glVertex3f( WINDOW_X, WINDOW_Y-100,0 );
	glTexCoord2i( 1, 1 );
	glVertex3f( WINDOW_X,WINDOW_Y, 0 );
	glTexCoord2i( 0, 1 );
	glVertex3f( 0,WINDOW_Y, 0 );
	glEnd();
	glDeleteTextures(1,texText);
}


