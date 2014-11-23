#include"global.h"
#include "draw.h"
#include "Title.h"
#include "Effect.h"
#include "Tutorial.h"
#include "Map.h"
#include "system.h"
#include "Player.h"

using namespace std;
//System *sys;
System::System(){

	font = TTF_OpenFont("fonts-japanese-mincho.ttf",200);
	dx=0;
	dy=0;
	count=0;
	Stage=0;
	charatype=0;
	myID=0;

	title = new Title;
	draw = new Draw;
	tutorial = new Tutorial;
	player = new Player[4];



	joystick=SDL_JoystickOpen(0);	// ジョイスティックを開いて構造体に割り当てる（有効にする）．ここではジョイスティックは1つとして引数に0を指定
	SDL_JoystickEventState(SDL_ENABLE);	// ジョイスティック関連のイベントを取得可能にする



}
System::~System(){
	TTF_CloseFont(font);

}


int System::selectChara() {
	int KeyFlag = 0;
	Uint8 jbutton = SDL_JoystickGetButton(joystick, 3);

	SDL_Color white = { 255, 255, 255, 100 };
	SDL_Surface* TextImage;
	SDL_Event event;
	int i, sel = 1;
	char buf[30];
	GLuint *charaImage[8];
	charaImage[0] = draw->initTexture("data/image/chara1.bmp");
	charaImage[1] = draw->initTexture("data/image/chara2.bmp");
	charaImage[2] = draw->initTexture("data/image/chara3.bmp");
	charaImage[3] = draw->initTexture("data/image/chara4.bmp");
	charaImage[4] = draw->initTexture("data/image/chara1g.bmp");
	charaImage[5] = draw->initTexture("data/image/chara2g.bmp");
	charaImage[6] = draw->initTexture("data/image/chara3g.bmp");
	charaImage[7] = draw->initTexture("data/image/chara4g.bmp");

	while (1) {
		Sint16 axis = SDL_JoystickGetAxis(joystick, 0);
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_RIGHT:
					if (sel < 4)
						sel++;
					else if (sel == 4)
						sel = 1;
					break;
				case SDLK_LEFT:
					if (sel > 1)
						sel--;
					else if (sel == 1)
						sel = 4;
					break;
				case SDLK_RETURN:
					return sel;
				}
				break;
			case SDL_JOYBUTTONDOWN:
				if (event.jbutton.button == 3){
					return sel;
				}
				break;
			}
		}
		if (axis == 0) {
			KeyFlag = 0;
		}
		if (axis >= 256 && KeyFlag == 0) {
			KeyFlag = 1;
			if (sel < 4)
				sel += 1;
			else if (sel == 4)
				sel = 1;
			axis = 0;
		}
		if (axis <= -256 && KeyFlag == 0) {
			KeyFlag = 1;
			if (sel > 1)
				sel -= 1;
			else if (sel == 1)
				sel = 4;
			axis = 0;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		draw->init3D();
		{
		}
		draw->init2D();
		{
			//character1
			if (sel == 1)
				glBindTexture( GL_TEXTURE_2D, *charaImage[0]);
			else
				glBindTexture( GL_TEXTURE_2D, *charaImage[4]);
			glBegin( GL_QUADS);
			glTexCoord2i(0, 0);
			glVertex3f(0, 0, 0);
			glTexCoord2i(1, 0);
			glVertex3f(200, 0, 0);
			glTexCoord2i(1, 1);
			glVertex3f(200, 200, 0);
			glTexCoord2i(0, 1);
			glVertex3f(0, 200, 0);
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
			if (sel == 2)
				glBindTexture( GL_TEXTURE_2D, *charaImage[1]);
			else
				glBindTexture( GL_TEXTURE_2D, *charaImage[5]);
			glBegin( GL_QUADS);
			glTexCoord2i(0, 0);
			glVertex3f(200, 0, 0);
			glTexCoord2i(1, 0);
			glVertex3f(400, 0, 0);
			glTexCoord2i(1, 1);
			glVertex3f(400, 200, 0);
			glTexCoord2i(0, 1);
			glVertex3f(200, 200, 0);
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
			if (sel == 3)
				glBindTexture( GL_TEXTURE_2D, *charaImage[2]);
			else
				glBindTexture( GL_TEXTURE_2D, *charaImage[6]);
			glBegin( GL_QUADS);
			glTexCoord2i(0, 0);
			glVertex3f(400, 0, 0);
			glTexCoord2i(1, 0);
			glVertex3f(600, 0, 0);
			glTexCoord2i(1, 1);
			glVertex3f(600, 200, 0);
			glTexCoord2i(0, 1);
			glVertex3f(400, 200, 0);
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
			if (sel == 4)
				glBindTexture( GL_TEXTURE_2D, *charaImage[3]);
			else
				glBindTexture( GL_TEXTURE_2D, *charaImage[7]);
			glBegin( GL_QUADS);
			glTexCoord2i(0, 0);
			glVertex3f(600, 0, 0);
			glTexCoord2i(1, 0);
			glVertex3f(800, 0, 0);
			glTexCoord2i(1, 1);
			glVertex3f(800, 200, 0);
			glTexCoord2i(0, 1);
			glVertex3f(600, 200, 0);
			glEnd();
		}
		glFlush();
		SDL_GL_SwapBuffers();
	}
	return -1;
}

void System::initChara() {

}

void System::moveChara() {
	Player old = player[myID];
	Uint8 *key = SDL_GetKeyState(NULL);
	Sint16 x_move, y_move;
	//Sint axis1 = SDL_JoystickGetAxis(joystick,3);
	x_move = SDL_JoystickGetAxis(joystick, 0);
	y_move = SDL_JoystickGetAxis(joystick, 1);
	if (key[SDLK_RIGHT] == SDL_PRESSED) {
		player[myID].dir += 0.03;
	}

	if (key[SDLK_LEFT] == SDL_PRESSED) {
		player[myID].dir -= 0.03;
	}
	/*
	 if(key[SDLK_SPACE] == SDL_PRESSED){
	 if(player[0].z<1.4)
	 player[0].z += 0.03;
	 }

	 if(key[SDLK_RETURN] == SDL_PRESSED){
	 if(player[0].z>0.5)
	 player[0].z -= 0.03;
	 }
	 */


	if (key[SDLK_UP] == SDL_PRESSED) {
		player[myID].x += sin(player[myID].dir) / 5;
		if (player[myID].x > STAGE_X)
			player[myID].x = STAGE_X;
		if (player[myID].x < 1.5)
			player[myID].x = 1.5;

		player[myID].y += cos(player[myID].dir) / 5;
		if (player[myID].y < 1.5)
			player[myID].y = 1.5;
		if (player[myID].y > STAGE_Y)
			player[myID].y = STAGE_Y;

		if (Map[(int) player[myID].x][(int) player[myID].y] == 2) {
			player[myID] = old;
		}
	}

	if (key[SDLK_DOWN] == SDL_PRESSED) {
		player[myID].x -= sin(player[myID].dir) / 5;
		if (player[myID].x < 1.5)
			player[myID].x = 1.5;
		if (player[myID].x > STAGE_X)
			player[myID].x = STAGE_X;

		player[myID].y -= cos(player[myID].dir) / 5;
		if (player[myID].y < 1.5)
			player[myID].y = 1.5;
		if (player[myID].y > STAGE_Y)
			player[myID].y = STAGE_Y;

		if (Map[(int) player[myID].x][(int) player[myID].y] == 2) {
			player[myID] = old;
		}
	}

	if (key[SDLK_SPACE] == SDL_PRESSED && player[myID].attflag == 0) {
		player[myID].attflag = 1;
	}

	//ゲームパッド
	if (x_move < 0) {
		player[myID].dir -= 0.03;
	} else if (x_move > 0) {
		player[myID].dir += 0.03;
	}
	if (y_move > 0) {
		//x方向
		player[myID].x -= sin(player[myID].dir) / 5;
		if (player[myID].x < 1.5)
			player[myID].x = 1.5;
		if (player[myID].x > STAGE_X)
			player[myID].x = STAGE_X;

		//y方向
		player[myID].y -= cos(player[myID].dir) / 5;
		if (player[myID].y < 1.5)
			player[myID].y = 1.5;
		if (player[myID].y > STAGE_Y)
			player[myID].y = STAGE_Y;

		if (Map[(int) player[myID].x][(int) player[myID].y] == 2) {
			player[myID] = old;
		}
	} else if (y_move < 0) {
		//x方向
		player[myID].x += sin(player[myID].dir) / 5;
		if (player[myID].x > STAGE_X)
			player[myID].x = STAGE_X;
		if (player[myID].x < 1.5)
			player[myID].x = 1.5;

		//y方向
		player[myID].y += cos(player[myID].dir) / 5;
		if (player[myID].y < 1.5)
			player[myID].y = 1.5;
		if (player[myID].y > STAGE_Y)
			player[myID].y = STAGE_Y;

		if (Map[(int) player[myID].x][(int) player[myID].y] == 2) {
			player[myID] = old;
		}
	}
}

int System::judgeHit() {

	return 0;
}

void System::gameMain() {
	if (player[0].attflag == 1) {
		count++;
		if (count == 50) {
			count = 0;
			player[0].attflag = 0;
		}
	}
	moveChara();
	draw->rDraw();
	//attack(10.0, 10.0, 10.0, 10.0);
	glFlush();
	SDL_GL_SwapBuffers();
	SDL_Delay(30);
}

