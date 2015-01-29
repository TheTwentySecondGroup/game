#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <stdlib.h>
#include <libcwiimote/wiimote.h>
#include <libcwiimote/wiimote_api.h>
#include <pthread.h>
#include <SDL/SDL.h>



void* wiimoteUpdate(void* pParam);
void wiimoteInit(char*);




#ifdef __cplusplus
};
#endif
