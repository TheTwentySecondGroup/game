/*
 * io.cpp
 *
 *  Created on: 2014/11/25
 *      Author: chihiro
 */
#include "global.h"
#include "io.h"

using namespace std;

void GameIO::routine() {
	cout << "execute io routine()" << endl;
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
	}

	if (SdlKey[SDLK_UP] == SDL_PRESSED) {
		if (key[KEY_UP] < KEY_MAX_COUNT)
			key[KEY_UP]++;
	} else {
		key[KEY_UP] = 0;
	}

	if (SdlKey[SDLK_DOWN] == SDL_PRESSED) {
		if (key[KEY_DOWN] < KEY_MAX_COUNT)
			key[KEY_DOWN]++;
	} else {
		key[KEY_DOWN] = 0;
	}

	if (SdlKey[SDLK_RIGHT] == SDL_PRESSED) {
		if (key[KEY_RIGHT] < KEY_MAX_COUNT)
			key[KEY_RIGHT]++;
	} else {
		key[KEY_RIGHT] = 0;
	}

	if (SdlKey[SDLK_LEFT] == SDL_PRESSED) {
		if (key[KEY_LEFT] < KEY_MAX_COUNT)
			key[KEY_LEFT]++;
	} else {
		key[KEY_LEFT] = 0;
	}

	Uint8 jbutton[4];
	for (int i = 0; i < 4; i++) {
		jbutton[i] = SDL_JoystickGetButton(joystick, i + 1);
	}

	if (SdlKey[SDLK_RETURN] == SDL_PRESSED || SdlKey[SDLK_z] == SDL_PRESSED
			|| jbutton[2] == 1) {
		//if(SdlKey[SDLK_RETURN] == SDL_PRESSED){
		//cout<<key[KEY_A]<<"----------------------------------------------------------"<<endl;
		if (key[KEY_A] < KEY_MAX_COUNT)
			key[KEY_A]++;
	} else {
		key[KEY_A] = 0;

	}


}

GameIO::GameIO() {
	// TODO Auto-generated constructor stub
	for (int i = 0; i < KEY_MAX; i++)
		key[i] = 0;

	joystick = SDL_JoystickOpen(0);	// ジョイスティックを開いて構造体に割り当てる（有効にする）．ここではジョイスティックは1つとして引数に0を指定
	SDL_JoystickEventState(SDL_ENABLE);	// ジョイスティック関連のイベントを取得可能にする

}

GameIO::~GameIO() {
	// TODO Auto-generated destructor stub
}

