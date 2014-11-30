#include "global.h"
#include "Model.h"
#include "draw.h"
#include "Title.h"
#include "Effect.h"
#include "Tutorial.h"
#include "Map.h"
#include "io.h"
#include "system.h"

#include <time.h>
//clock_t start,now,end;
using namespace std;
System *sys;

//int endFlag=0;
//for wiimote
//wiimote_t wiimote = WIIMOTE_INIT;
int fallingFlag = 0;

//void* wiimoteUpdate();



wiimote_t wiimote;
int Stage = 1;
time_t start, now, end;
int MaxTime;
int BeforeTime;

float angle = 0.0f;

void Init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	// glEnable(GL_CULL_FACE);
	// glCullFace(GL_BACK);

	Model modeltmp("UnityChan/Models/unitychan.fbx");

	sys->model.push_back(modeltmp);

	cout << "Init() executed\n";
	cout << "-----------------------\n\n\n";
}

void timeEnd() {
	end = time(NULL);
}
void timeProc() {
	now = time(NULL);
}
void timeReset() {
	MaxTime = 100;
	start = time(NULL);
}



int main(int argc, char* argv[]) {
	SDL_Surface *window;
	SDL_Event event; //for SDL event
	int AAA = 0;

	// SDL Initialize
	if (SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_JOYSTICK) < 0) {
		printf("failed to initialize SDL.\n");
		exit(-1);
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//make window
	if ((window = SDL_SetVideoMode(WINDOW_X, WINDOW_Y, 32, SDL_OPENGL)) == NULL) {
		printf("failed to initialize videomode.\n");
		exit(-1);
	}
	SDL_WM_SetCaption("test program", NULL);


	sys = new System();

	sys->io = new GameIO();

	sys->draw = new Draw();


	sys->player = new Player[4];

	sys->title = new Title();

	sys->tutorial = new Tutorial();

	sys->map = new Map();

	sys->network = new NetClass();

	Init();

	//Initialize System



	//initialize my position
	sys->player[0].x = 0;
	sys->player[0].y=0.5;
	sys->player[0].z = 0;


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
	//sys->draw = new Draw();

	//Initialize title
	//sys->title =
	//sys->title = new Title(sys);
	//Initialize tutorial
	//Init Map
	//cout<<"Stage1 =  "<<sys->Stage<<endl;


	cout<<"Stage =  "<<sys->Stage<<endl;

	while (1) {
		sys->io->routine();
		cout<<"test"<<endl;
		//timeProc();
		switch (sys->Stage) {
		case 0:
			sys->title->routine();
			break;
		case 1:
		case 2:
		case 3:
		case 4:
			sys->gameMain();
			break;
		case -1:
			sys->selectChara();
			break;
		case -2:
			sys->tutorial->routine();
			break;
		case -4:
			//for server
			break;
		default:
			//delTitle();
			//delete draw;
			SDL_Quit();
			exit(0);
			break;
		}

		if (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					Stage = -1;
					break;
				}
				break;
			case SDL_JOYBUTTONDOWN:
				if (event.jbutton.button == 10) {
					Stage = -1;
					break;
				}
				break;
			}
		}

		int curTime = SDL_GetTicks();
		int difTime = curTime - BeforeTime;
		if (difTime < 1000 / FPS_RATE)
			SDL_Delay(1000 / FPS_RATE - difTime);
		BeforeTime = curTime;

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
