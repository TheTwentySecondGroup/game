
//for C/C++
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include<string>
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

#define STAGE_X 24
#define STAGE_Y 56

//for wiimote
#include <libcwiimote/wiimote.h>
#include <libcwiimote/wiimote_api.h>

//width of window
#define WINDOW_X 1000
//hight of window
#define WINDOW_Y 800 

//FPS
#define FPS_RATE 30


#define STAGE_MAX 4

//object for various things
struct Obj{
    double x;	//キャラのx座標
    double y;	//y座標
    double z;	//z座標
    double dir;	//移動方向
    double xd;	//x方向の移動距離
    double yd;	//y方向の移動距離
	int hp;		//キャラのHP
	int mp;		//キャラのMP
	int mp_heal;//MP回復量
	std::string skill[4];	//キャラごとの魔法を格納
};
//for time 
/*extern time_t start,now;
extern int MaxTime;    
extern int BeforeTime;
*/
//for my position 
extern struct Obj player[4];

extern int Stage;

//store goal position
extern int goalX,goalY;

//for wiimote
extern wiimote_t wiimote;


//main.c
extern SDL_Joystick *joystick;

