#include "global.h"
#include "GLMetaseq.h"
#include "draw.h"
#include "Effect.h"
#include "Title.h"
#include "Tutorial.h"
#include "Map.h"
#include "system.h"

int Slide=0;
int Button1=0;
int Button2=0;
GLuint *TutorialImage[3];

void initTutorial(){
	Slide=-1;
	TutorialImage[0] = initTexture("data/image/1.bmp");
	TutorialImage[1] = initTexture("data/image/2.bmp");
	TutorialImage[2] = initTexture("data/image/3.bmp");
}


void Tutorial(){
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
        if(key[SDLK_RETURN] == SDL_PRESSED){
            Button1++;
        }else{
            Button1=0;
        }
        if(key[SDLK_BACKSPACE] == SDL_PRESSED){
            Button2++;
        }else{
            Button2=0;
        }
    //}
    if(Button1==1)Slide++;
    else if(Button2==1)Slide--;
    if(Slide>=SLIDE_MAX){
        delTutorial();
        initEffect();
        makeEffect(1,120,"Start");
        Stage = 1;
        //initMap(1);
        return;
    }
    if(Slide<=0)Slide=0;


    drawTutorial(sel);
}
void drawTutorial(int n){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    init3D();
    {
    }
    init2D();
    {

        glBindTexture( GL_TEXTURE_2D, *TutorialImage[n-1]);
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


        drawTutorialText();
    }
    glFlush();
    SDL_GL_SwapBuffers(); 
}

void drawTutorialText(){
	char buf[64];
	strcpy(buf,"    If you use cross-key, you can move.   ");

    SDL_Color white = {255, 255, 255,100};
    SDL_Surface* TextImage ;
    TextImage=TTF_RenderUTF8_Blended(font,buf,white);
    GLuint *texText;
    texText = timeTexture(TextImage);


    glBindTexture( GL_TEXTURE_2D, *texText);
    glBegin( GL_QUADS );
    glColor4f(1.0,1.0,1.0,1.0);
    glTexCoord2i( 0, 0 );
    glVertex3f( 0, WINDOW_Y-100, 0 );
    glTexCoord2i( 1, 0 );
    glVertex3f( WINDOW_X,  WINDOW_Y-100,0 );
    glTexCoord2i( 1, 1 );
    glVertex3f( WINDOW_X,WINDOW_Y, 0 );
    glTexCoord2i( 0, 1 );
    glVertex3f( 0,WINDOW_Y, 0 ); 
    glEnd();
    glDeleteTextures(1,texText);
}

void delTutorial(){  
    Slide=-1;
    glDeleteTextures(SLIDE_MAX,*TutorialImage);

}
