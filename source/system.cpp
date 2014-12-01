#include"global.h"
#include "draw.h"
#include "Title.h"
#include "Effect.h"
#include "Tutorial.h"
#include "Map.h"
#include "system.h"
#include "Player.h"
#include "net.h"
using namespace std;

System::System() {
	TTF_Init();
	font = TTF_OpenFont("data/Koruri-20140904/Koruri-Bold.ttf", 20);
	//if(!font)cout<<TTF_GetError()<<endl;
	dx = 0;
	dy = 0;
	count = 0;
	Stage = 0;
	charatype = 0;
	myID = 0;
	Stage = 0;
	selChara = 1;
}
System::~System() {
	TTF_CloseFont(font);

}

int System::selectChara() {
	cout << "execute sys selectChara()" << endl;

	char buf[30];

	//while (1) {
	cout << "selectChara loop   " << selChara << io->key[KEY_RIGHT]
			<< io->key[KEY_LEFT] << endl;
	//sys->io->routine();

	//if (io->key[KEY_RIGHT] == 1) {
	if (io->key[KEY_RIGHT] == 1) {
		if (selChara < 4)
			selChara++;
		else
			// if (selChara == 4)
			selChara = 1;
	}
	if (io->key[KEY_LEFT] == 1) {
		if (selChara > 1)
			selChara--;
		else
			//if (selChara == 1)
			selChara = 4;
	}
	if (io->key[KEY_A] == 1) {
		charatype = selChara;
		Stage = 1;
	}
	draw->drawCharaSelect();
	//}
	//return -1;
}

void System::initChara() {

}

void System::moveChara() {
	Player old = player[myID];
	//Uint8 *key = SDL_GetKeyState(NULL);
	//Sint16 x_move, y_move;
	//Sint axis1 = SDL_JoystickGetAxis(joystick,3);
	//x_move = SDL_JoystickGetAxis(joystick, 0);
	//y_move = SDL_JoystickGetAxis(joystick, 1);
	if (io->key[KEY_RIGHT] > 0) {
		player[myID].dir -= 0.03;
	}

	if (io->key[KEY_LEFT] > 0) {
		player[myID].dir += 0.03;
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

	if (io->key[KEY_UP] > 0) {
		player[myID].x += sin(player[myID].dir) / 5;
		if (player[myID].x > STAGE_X)
			player[myID].x = STAGE_X;
		if (player[myID].x < 1.5)
			player[myID].x = 1.5;

		player[myID].z += cos(player[myID].dir) / 5;
		if (player[myID].z < 1.5)
			player[myID].z = 1.5;
		if (player[myID].z > STAGE_Y)
			player[myID].z = STAGE_Y;

		if (map->data[(int) player[myID].x][(int) player[myID].z] == 2) {
			player[myID] = old;
		}
		printf("%f %f\n", player[myID].x, player[myID].z);
	}

	if (io->key[KEY_DOWN] > 0) {
		player[myID].x -= sin(player[myID].dir) / 5;
		if (player[myID].x < 1.5)
			player[myID].x = 1.5;
		if (player[myID].x > STAGE_X)
			player[myID].x = STAGE_X;

		player[myID].z -= cos(player[myID].dir) / 5;
		if (player[myID].z < 1.5)
			player[myID].z = 1.5;
		if (player[myID].z > STAGE_Y)
			player[myID].z = STAGE_Y;

		if (map->data[(int) player[myID].x][(int) player[myID].z] == 2) {
			player[myID] = old;
		}
	}

	if (io->key[KEY_A] == 1 && player[myID].attflag == 0) {
		player[myID].attflag = 1;
	}

}

int System::judgeHit() {

	return 0;
}

void System::gameMain() {
	//cout << "execute sys gameMain()" << endl;
	if (player[0].attflag == 1) {
		count++;
		if (count == 50) {
			count = 0;
			player[0].attflag = 0;
		}
	}
	moveChara();
	draw->routine();

	//attack(10.0, 10.0, 10.0, 10.0);
	//glFlush();
	//SDL_GL_SwapBuffers();
	//SDL_Delay(30);
}

