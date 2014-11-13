#include "global.h"
#include "draw.h"
#include "Title.h"
#include "Tutorial.h"
#include "Map.h"

int sel = 1;
int KeyFlag=0;
GLuint *titleImage[7];

void drawMenuCube(int x,int y,GLuint *texture,double sw){
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,WhiteMaterial);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,WhiteMaterial);
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,WhiteMaterial);
    glMaterialf(GL_FRONT,GL_SHININESS,60.0);

    glBindTexture( GL_TEXTURE_2D, *texture );

    GLfloat vertices [4][3]={
        {1, sw+y,  2.5-x},
        {1, sw+y, 1.5-x},
        { 2, sw+y, 1.5-x},
        { 2, sw+y,  2.5-x},
    };
    glBegin(GL_POLYGON);
    glNormal3f(player[0].xd , player[0].yd , 0);
    glTexCoord2i(0,0);
    glVertex3fv(vertices[0]);
    glTexCoord2i(0,1);
    glVertex3fv(vertices[1]);
    glTexCoord2i(1,1);
    glVertex3fv(vertices[2]);
    glTexCoord2i(1,0);
    glVertex3fv(vertices[3]);
    glEnd();
}
void initTitle(){
    player[0].x=2.5;
    player[0].y=0;
    player[0].dir=0;
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0,GL_AMBIENT,GrayLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,DifLight);
    glLightfv(GL_LIGHT0,GL_SPECULAR,SpecularLight);



    SDL_Color color1 = {255, 255, 0};
    SDL_Color color2 = {255, 255, 255};

	titleImage[0] = initTexture("data/image/sam.bmp");
	SDL_Surface *tmp1,*tmp2,*tmp3,*tmp4,*tmp5,*tmp6,*tmp7;
    tmp1 = TTF_RenderUTF8_Blended(font,"1 VS 1",color1);
    titleImage[1] =timeTexture(tmp1);
    tmp2 = TTF_RenderUTF8_Blended(font,"2 VS 2",color1);
    titleImage[2] =timeTexture(tmp2);
    tmp3 = TTF_RenderUTF8_Blended(font,"BATTLE ROYAL",color1);
    titleImage[3] =timeTexture(tmp3);
    tmp4 = TTF_RenderUTF8_Blended(font,"1 VS 1",color2);
    titleImage[4] =timeTexture(tmp4);
    tmp5 = TTF_RenderUTF8_Blended(font,"2 VS 2",color2);
	titleImage[5] =timeTexture(tmp5);
	tmp6 = TTF_RenderUTF8_Blended(font,"BATTLE ROYAL",color2);
	titleImage[6] =timeTexture(tmp6);
}

void Title(){
    //keyboad
    Uint8 *key = SDL_GetKeyState(NULL);
    Uint8 jbutton = SDL_JoystickGetButton(joystick, 3);
    Sint16 axis = SDL_JoystickGetAxis(joystick,1);

    if((KeyFlag ==0 )&&(key[SDLK_UP] == SDL_PRESSED)){
        KeyFlag =1 ;
        if(sel>KEY_MIN)sel -=1;
    }else if((KeyFlag ==0)&&(key[SDLK_DOWN] == SDL_PRESSED)){
        KeyFlag = 1;
        if(sel<KEY_MAX)sel +=1;
    }else if(key[SDLK_DOWN] != SDL_PRESSED && key[SDLK_UP]!= SDL_PRESSED && axis == 0){
        KeyFlag=0;
    }
    if(key[SDLK_RETURN] == SDL_PRESSED){
    	initTutorial();
		Stage = -2;
	}
	if(jbutton == 1){
		initTutorial();
		Stage = -2;
	}
	if(axis >= 256 && KeyFlag == 0){
		KeyFlag = 1;
		if(sel < KEY_MAX)
		sel += 1;
		axis = 0;
	}
	if(axis <= -256 && KeyFlag == 0){
		KeyFlag = 1;
		if(sel > KEY_MIN)
		sel -= 1;
		axis = 0;
	}

    drawTitle();
    SDL_Delay(1000/60);
}

void drawTitle(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    init3D();
    {
        //glDisable(GL_LIGHTING);
        glDisable(GL_FOG);
        //init
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        double xd= sin(player[0].dir);
        double yd=   cos(player[0].dir) ;
        gluLookAt(player[0].x - xd/20 ,player[0].y - yd/20,player[0].z, // position of camera
                player[0].x  , player[0].y ,player[0].z, //look-at point
                0.0,0.0,1.0);

        //Light
        lightpos[0]=player[0].x-5*xd;
        lightpos[1]=player[0].y-5*yd;
        lightpos[2]=player[0].z;
        lightpos[3]=1;
        glLightfv(GL_LIGHT0,GL_POSITION,lightpos); // position of light0
        GLfloat Light0Dir[]={xd,yd,0};
        glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,Light0Dir);
        glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 30.0f );
        glLightf( GL_LIGHT0, GL_SPOT_EXPONENT, 2.0f );
        glLightfv(GL_LIGHT0,GL_AMBIENT,WhiteLight);
        glLightfv(GL_LIGHT0,GL_DIFFUSE,DifLight);
        glLightfv(GL_LIGHT0,GL_SPECULAR,SpecularLight);
        glEnable(GL_LIGHTING);
        glEnable(GL_NORMALIZE); 


        //draw wall
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,WhiteMaterial);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,WhiteMaterial);
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,WhiteMaterial);
        glMaterialf(GL_FRONT,GL_SHININESS,60.0);
        glBindTexture( GL_TEXTURE_2D, *titleImage[0] );
        GLfloat vertices [4][3]={
            {2, 8,  3.0},
            {2, 8, -1.5},
            { 8, 8, -1.5},
            { 8, 8,  3.0},
        };
        glBegin(GL_POLYGON);
        glNormal3f(player[0].xd , player[0].yd , 0);
        glTexCoord2i(0,0);
        glVertex3fv(vertices[0]);
        glTexCoord2i(0,1);
        glVertex3fv(vertices[1]);
        glTexCoord2i(1,1);
        glVertex3fv(vertices[2]);
        glTexCoord2i(1,0);
        glVertex3fv(vertices[3]);
		glEnd();
		
		//draw menu
		int c;
		for(c=1;c<=KEY_MAX;c++){
			//draw on button
			if(sel == c)drawMenuCube(c, 7,  titleImage[c],0);
			//draw off button
			else drawMenuCube(c, 7,  titleImage[c+3],1.5);
		}
	}
	//init2D();
	glFlush();
	SDL_GL_SwapBuffers();
}

void delTitle(){
    glDeleteTextures(6,*titleImage);

}
