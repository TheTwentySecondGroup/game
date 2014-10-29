
//for C
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <iostream>

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

#include "Model.h"

//width of window
#define WINDOW_X 800
//hight of window
#define WINDOW_Y 600 

//FPS
#define FPS_RATE 30


#define STAGE_MAX 4

//object for various things
struct Obj{
    double x;
    double y;
    double z;
    double dir;
    double f;
    double xd;
    double yd;
    int Item[10];
};
//for time 
extern time_t start,now;
extern int MaxTime;    
extern int BeforeTime;
//for my position 
extern struct Obj myPos;

extern int Stage;

//store goal position
extern int goalX,goalY;

//for wiimote
extern wiimote_t wiimote;

 
//main.c
void GameMain();
void restart();
void timeReset();
void timeProc();
void timeEnd();
/*
//CD.c
//for collision detection
struct Obj CDtoMap(struct Obj,struct Obj);
struct Obj CDEnemytoMap(struct Obj,struct Obj);
int CDtoEnemy(struct Obj);
void CDtoItem(struct Obj);
*/



extern Model* model;
