/*
 * io.cpp
 *
 *  Created on: 2014/11/25
 *      Author: chihiro
 */
#include "global.h"
#include "io.h"
#include "Wii.h"

using namespace std;

void GameIO::routine() {
	//cout << "execute io routine()" << endl;
	//keyboad
	Uint8 *SdlKey = SDL_GetKeyState(NULL);
	Sint16 axis0, axis1;

	if (SdlKey[SDLK_ESCAPE] == SDL_PRESSED) {
		exit(EXIT_FAILURE);
	}

	if (joystick == NULL) {
		axis0 = 0;
		axis1 = 0;
	} else {
		axis0 = SDL_JoystickGetAxis(joystick, 0);
		axis1 = SDL_JoystickGetAxis(joystick, 1);
		cout <<SDL_NumJoysticks()<<"  " <<joystick << "axis0" << axis0 << "axis1" << axis1;
	}

	if (SdlKey[SDLK_UP] == SDL_PRESSED || axis1 < -30 || checkpress() == 1 || checkpress() == 7 || checkpress() == 8) {
		if (key[KEY_UP] < KEY_MAX_COUNT)
			key[KEY_UP]++;
	} else {
		key[KEY_UP] = 0;
	}

	if (SdlKey[SDLK_DOWN] == SDL_PRESSED || axis1 > 30 || checkpress() ==2 || checkpress() == 9 || checkpress() == 10) {
		if (key[KEY_DOWN] < KEY_MAX_COUNT)
			key[KEY_DOWN]++;
	} else {
		key[KEY_DOWN] = 0;
	}

	if (SdlKey[SDLK_RIGHT] == SDL_PRESSED || axis0 > 30 || checkpress() == 4 || checkpress() == 7 || checkpress() == 9) {
		if (key[KEY_RIGHT] < KEY_MAX_COUNT)
			key[KEY_RIGHT]++;
	} else {
		key[KEY_RIGHT] = 0;
	}

	if (SdlKey[SDLK_LEFT] == SDL_PRESSED || axis0 < -30 || checkpress() == 3 || checkpress() == 8 || checkpress() == 10) {
		if (key[KEY_LEFT] < KEY_MAX_COUNT)
			key[KEY_LEFT]++;
	} else {
		key[KEY_LEFT] = 0;
	}

	Uint8 jbutton[4];
	for (int i = 0; i < 4; i++) {
		jbutton[i] = SDL_JoystickGetButton(joystick, i);
	}

	if (SdlKey[SDLK_RETURN] == SDL_PRESSED || jbutton[3] == 1 || checkpress() == 11) {
		if (key[KEY_A] < KEY_MAX_COUNT)
			key[KEY_A]++;
	} else {
		key[KEY_A] = 0;
	}

	if (SdlKey[SDLK_1] == SDL_PRESSED || jbutton[0] == 1 || checkpress() == 5) {
		if (key[KEY_B] < KEY_MAX_COUNT)
			key[KEY_B]++;
	} else {
		key[KEY_B] = 0;
	}

	if (SdlKey[SDLK_2] == SDL_PRESSED || jbutton[1] == 1 || checkpress() == 6) {
		if (key[KEY_C] < KEY_MAX_COUNT)
			key[KEY_C]++;
	} else {
		key[KEY_C] = 0;
	}

	if (SdlKey[SDLK_3] == SDL_PRESSED || jbutton[2] == 1) {
		if (key[KEY_D] < KEY_MAX_COUNT)
			key[KEY_D]++;
	} else {
		key[KEY_D] = 0;
	}

	if (SdlKey[SDLK_4] == SDL_PRESSED || jbutton[3] == 1) {
		if (key[KEY_E] < KEY_MAX_COUNT)
			key[KEY_E]++;
	} else {
		key[KEY_E] = 0;
	}
/}

GameIO::GameIO() {

	// TODO Auto-generated constructor stub
	for (int i = 0; i < KEY_MAX; i++)
		key[i] = 0;
	joystick = NULL;
	if (SDL_NumJoysticks() > 0 &&strcmp(SDL_JoystickName(0),"VirtualBox mouse integration")!=0&& strcmp(SDL_JoystickName(0),"ST LIS3LV02DL Accelerometer")!=0) {
		joystick = SDL_JoystickOpen(0); // ジョイスティックを開いて構造体に割り当てる（有効にする）．ここではジョイスティックは1つとして引数に0を指定
		SDL_JoystickEventState(SDL_ENABLE); // ジョイスティック関連のイベントを取得可能にする
	}
}

GameIO::~GameIO() {
	// TODO Auto-generated destructor stub
}

