#include "Wii.h"


wiimote_t wiimote =WIIMOTE_INIT;

void wiimoteInit(char* argv) {
	if (!wiimote_connect(&wiimote, argv)) {
		wiimote.led.one = 1;
		wiimote.mode.ir = 1;

		//make thread for wiimote
		pthread_t wu;
		//timeProc();u;
		pthread_create(&wu, NULL, wiimoteUpdate, NULL);
		printf("wiiremote connected\n");
	} else {
		printf("wiiremote can't connect\n");
	}
}

void* wiimoteUpdate(void* pParam) {
	while (1) {
		if (wiimote_is_open(&wiimote)) {
			if (wiimote_update(&wiimote) >= 0) {
			} else {
				wiimote_disconnect(&wiimote);
			}
		}
		SDL_Delay(10);
	}
}

int checkpress(){
	if(wiimote.keys.one)    return 5;
	if(wiimote.keys.two)   return 6;
	if(wiimote.keys.right && wiimote.keys.down)  return 7;
	if(wiimote.keys.right && wiimote.keys.up)  return 8;
	if(wiimote.keys.left && wiimote.keys.down)  return 9;
	if(wiimote.keys.left && wiimote.keys.up)  return 10;
	if(wiimote.keys.right)	return 1;
	if(wiimote.keys.left) return 2;
	if(wiimote.keys.up)   return 3;
	if(wiimote.keys.down) return 4;
	if(wiimote.keys.a)  return 11;
	return 0;
}

