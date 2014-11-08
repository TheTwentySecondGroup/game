#include"global.h"
#include "draw.h"
#include "Title.h"
#include "Effect.h"
#include "Tutorial.h"
#include "Map.h"

int selectChara(){
	SDL_Color white = {255, 255, 255,100};
    SDL_Surface* TextImage;
	SDL_Event event;
	int i, sel=1;
	char buf[30];
	GLuint *charaImage[8];
	charaImage[0] = initTexture("data/image/chara1.bmp");
	charaImage[1] = initTexture("data/image/chara2.bmp");
	charaImage[2] = initTexture("data/image/chara3.bmp");
	charaImage[3] = initTexture("data/image/chara4.bmp");
	charaImage[4] = initTexture("data/image/chara1g.bmp");
	charaImage[5] = initTexture("data/image/chara2g.bmp");
	charaImage[6] = initTexture("data/image/chara3g.bmp");
	charaImage[7] = initTexture("data/image/chara4g.bmp");
	
	while(1){
	if(SDL_PollEvent(&event)){
		switch(event.type){
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym){
			case SDLK_RIGHT:
				if(sel<4) sel++;
				else if(sel == 4) sel = 1;
				break;
			case SDLK_LEFT:
				if(sel>1) sel--;
				else if(sel == 1) sel = 4;
				break;
			case SDLK_RETURN:
				return sel;
			}
		}
	}
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	init3D();
	{
	}
	init2D();
	{
		//character1
		if(sel == 1)
			glBindTexture( GL_TEXTURE_2D, *charaImage[0]);
		else
			glBindTexture( GL_TEXTURE_2D, *charaImage[4]);
			glBegin( GL_QUADS );
			glTexCoord2i( 0, 0 );
			glVertex3f( 0, 0, 0 );
			glTexCoord2i( 1, 0 );
			glVertex3f( 200, 0, 0 );
			glTexCoord2i( 1, 1 );
			glVertex3f( 200, 200, 0 );
			glTexCoord2i( 0, 1 );
			glVertex3f( 0, 200, 0 ); 
		glEnd();
		/*
		strcpy(buf, "ニブルヘイム");
		TextImage=TTF_RenderUTF8_Blended(font,buf,white);
    	GLuint *texText;
    	texText = timeTexture(TextImage);
    	glBindTexture( GL_TEXTURE_2D, *texText);
			glBegin( GL_QUADS );
			glTexCoord2i( 0, 0 );
			glVertex3f( 0, 300, 0 );
			glTexCoord2i( 1, 0 );
			glVertex3f( 150, 300, 0 );
			glTexCoord2i( 1, 1 );
			glVertex3f( 150, 350, 0 );
			glTexCoord2i( 0, 1 );
			glVertex3f( 0, 350, 0 ); 
		glEnd();
		glDeleteTextures(1,texText);
		*/
		//character2
		if(sel == 2)
			glBindTexture( GL_TEXTURE_2D, *charaImage[1]);
		else
			glBindTexture( GL_TEXTURE_2D, *charaImage[5]);
			glBegin( GL_QUADS );
			glTexCoord2i( 0, 0 );
			glVertex3f( 200, 0, 0 );
			glTexCoord2i( 1, 0 );
			glVertex3f( 400, 0, 0 );
			glTexCoord2i( 1, 1 );
			glVertex3f( 400, 200, 0 );
			glTexCoord2i( 0, 1 );
			glVertex3f( 200, 200, 0 ); 
		glEnd();
		/*
		strcpy(buf, "コキュートス");
		TextImage=TTF_RenderUTF8_Blended(font,buf,white);
    	texText = timeTexture(TextImage);
    	*/
    	/*glBindTexture( GL_TEXTURE_2D, *texText);
			glBegin( GL_QUADS );
			glTexCoord2i( 0, 0 );
			glVertex3f( 200, 300, 0 );
			glTexCoord2i( 1, 0 );
			glVertex3f( 300, 300, 0 );
			glTexCoord2i( 1, 1 );
			glVertex3f( 300, 350, 0 );
			glTexCoord2i( 0, 1 );
			glVertex3f( 200, 350, 0 ); 
		glEnd();
		glDeleteTextures(1,texText);
		*/
		//character3
		if(sel == 3)
			glBindTexture( GL_TEXTURE_2D, *charaImage[2]);
		else
			glBindTexture( GL_TEXTURE_2D, *charaImage[6]);
			glBegin( GL_QUADS );
			glTexCoord2i( 0, 0 );
			glVertex3f( 400, 0, 0 );
			glTexCoord2i( 1, 0 );
			glVertex3f( 600, 0, 0 );
			glTexCoord2i( 1, 1 );
			glVertex3f( 600, 200, 0 );
			glTexCoord2i( 0, 1 );
			glVertex3f( 400, 200, 0 ); 
		glEnd();
		/*
		strcpy(buf, "ムスペルスヘイム");
		TextImage=TTF_RenderUTF8_Blended(font,buf,white);
    	texText = timeTexture(TextImage);
    	
    	glBindTexture( GL_TEXTURE_2D, *texText);
			glBegin( GL_QUADS );
			glTexCoord2i( 0, 0 );
			glVertex3f( 400, 300, 0 );
			glTexCoord2i( 1, 0 );
			glVertex3f( 590, 300, 0 );
			glTexCoord2i( 1, 1 );
			glVertex3f( 590, 350, 0 );
			glTexCoord2i( 0, 1 );
			glVertex3f( 400, 350, 0 ); 
		glEnd();
		glDeleteTextures(1,texText);
		*/
		
		//character4
		if(sel == 4)
			glBindTexture( GL_TEXTURE_2D, *charaImage[3]);
		else
			glBindTexture( GL_TEXTURE_2D, *charaImage[7]);
			glBegin( GL_QUADS );
			glTexCoord2i( 0, 0 );
			glVertex3f( 600, 0, 0 );
			glTexCoord2i( 1, 0 );
			glVertex3f( 800, 0, 0 );
			glTexCoord2i( 1, 1 );
			glVertex3f( 800, 200, 0 );
			glTexCoord2i( 0, 1 );
			glVertex3f( 600, 200, 0 ); 
		glEnd();
	}
    glFlush();
    SDL_GL_SwapBuffers();
    }
    return -1;
}

void initChara(){
	
}

void moveChara(){
	
}

int judgeHit(){
	
}

void gameMain(){
	Uint8 *key = SDL_GetKeyState(NULL);
	//while(1){
    	if(key[SDLK_RIGHT] == SDL_PRESSED){
        	player[0].dir+=0.03;
    	}
    	
    	if(key[SDLK_LEFT] == SDL_PRESSED){
    	    player[0].dir-=0.03;
    	}
    	
    	if(key[SDLK_SPACE] == SDL_PRESSED){
    		player[0].z += 0.03;
    	}
    	
    	if(key[SDLK_RETURN] == SDL_PRESSED){
    		player[0].z -= 0.03;
    	}
    	
    	if(key[SDLK_UP] == SDL_PRESSED){
    	    struct Obj myOld = player[0];
    	    player[0].x+=sin(player[0].dir)/5;
    	    if(player[0].x>MAP_X_MAX||player[0].x<0||player[0].y>MAP_Y_MAX||player[0].y<0){
    	    	player[0] = myOld;
    	    }
    	   // player[0]=CDtoMap(player[0],myOld);
    	    myOld = player[0];
    	    player[0].y+=cos(player[0].dir)/5;
    	     if(player[0].x>MAP_X_MAX||player[0].x<0||player[0].y>MAP_Y_MAX||player[0].y<0){
    	    	player[0] = myOld;
    	    }
    	    //player[0]=CDtoMap(player[0],myOld);
    	}
    	
    	if(key[SDLK_DOWN] == SDL_PRESSED){
    	    struct Obj myOld = player[0];
    	    player[0].x-=sin(player[0].dir)/5;
    	    if(player[0].x>MAP_X_MAX||player[0].x<0||player[0].y>MAP_Y_MAX||player[0].y<0){
    	    	player[0] = myOld;
    	    }
    	    //player[0]=CDtoMap(player[0],myOld);
    	    myOld = player[0];
    	    player[0].y-=cos(player[0].dir)/5;
    	    if(player[0].x>MAP_X_MAX||player[0].x<0||player[0].y>MAP_Y_MAX||player[0].y<0){
    	    	player[0] = myOld;
    	    }
    	    //player[0]=CDtoMap(player[0],myOld);
 	   }
 	   //moveChara();
 	   draw();
 	   glFlush();
 	   SDL_GL_SwapBuffers();
 	   SDL_Delay(20);
	//}
}
