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
