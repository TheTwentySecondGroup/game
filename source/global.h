/*
 * global.h
 *
 *  last update 2015/02/12
 *      Author: Murokawa,Takeda
 */

//for C
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <iostream>
#include<string>
#include<vector>
//for SDL
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_net.h>
#include <SDL/SDL_opengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

//for wiimote
#include <libcwiimote/wiimote.h>
#include <libcwiimote/wiimote_api.h>

#define STAGE_X 22
#define STAGE_Y 44

//width of window
#define WINDOW_X 1000
//hight of window
#define WINDOW_Y 800

//FPS
#define FPS_RATE 30

#define STAGE_MAX 4
#define PI 3.141592

using namespace std;

extern SDL_Joystick *joystick;
//extern System *sys;
//for time FPS調節用
extern time_t start, now;
extern int MaxTime;
extern int BeforeTime;
//for my position 
//extern struct Obj myPos;


void timeReset();
void timeProc();
void timeEnd();


