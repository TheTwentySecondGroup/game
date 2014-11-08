#include "global.h"
#include "draw.h"
#include "Title.h"
#include "Effect.h"
#include "Tutorial.h"
#include "Map.h"
#include "system.h"
#include <time.h>
//clock_t start,now,end;
struct Obj player[4];
int Stage =0;
int charatype;
//int endFlag=0;
//for wiimote
//wiimote_t wiimote = WIIMOTE_INIT;
int fallingFlag =0;

void* wiimoteUpdate();
int main(int argc, char* argv[]) {
    SDL_Surface *window;
    SDL_Event event; //for SDL event
    int AAA = 0;

    // SDL Initialize
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("failed to initialize SDL.\n");
        exit(-1);
    }

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    //make window
    if((window = SDL_SetVideoMode(WINDOW_X, WINDOW_Y, 32, SDL_OPENGL)) == NULL) {
        printf("failed to initialize videomode.\n");
        exit(-1);
    }
    SDL_WM_SetCaption("Maze of Minos",NULL);

    //initialize my position
    player[0].x=0;
    player[0].y=0;
    player[0].z=0.5;
    /*if(argc > 1 && !wiimote_connect(&wiimote, argv[1])){
        wiimote.led.one  = 1;
        wiimote.mode.ir = 1;

        //make thread for wiimote
        pthread_t wu;
        pthread_create(&wu,NULL,wiimoteUpdate ,NULL);
        printf("wiiremote  connected\n");
    }else{
        printf("wiiremote can't connect\n");
    }
	*/

    //Initialize openGL  etc
    initDraw();
    //Initialize title
    initTitle();
    //Initialize tutorial
    initTutorial();
    //Init Map
    initMap(1);


    while(1){
        //timeProc();
        switch(Stage){
            case 0:
                Title();
                break;
            case 1:
            case 2:
            case 3:
            case 4:
            if(AAA == 0){
            	charatype=selectChara();
            	delTitle();
            	printf("%d\n", charatype);
            	player[0].y = 2;
            	AAA++;
            }
            	gameMain();
                break;
            case -2:
                Tutorial();
                break;
            default:
                delTitle();
                delDraw();
                SDL_Quit();
                exit(0);
                break;
        }

        if(SDL_PollEvent(&event)){
            switch (event.type) {
                case SDL_QUIT:
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        case SDLK_ESCAPE:
                            Stage = -1;
                            break;
                    }
            }
        }
    }
    return 0;
}

/*
void* wiimoteUpdate(void* pParam){
    while(1){
        if(wiimote_is_open(&wiimote)){  
            if(wiimote_update(&wiimote) >= 0){
                //printf("TILT x=%.3f y=%.3f z=%.3f\n", wiimote.tilt.x,wiimote.tilt.y, wiimote.tilt.z);
            }else {
                wiimote_disconnect(&wiimote);
            }

        }
        SDL_Delay(10);
    }
} */

