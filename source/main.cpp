#include "global.h"
#include "Model.h"
#include "draw.h"
#include "Title.h"
#include "Effect.h"
#include "Tutorial.h"
#include "Map.h"
#include "io.h"
#include "system.h"
#include "Wii.h"

#include <time.h>
//clock_t start,now,end;

using namespace std;
System *sys;

//int endFlag=0;
//for wiimote

int fallingFlag = 0;

int Stage = 1;
int vol = 30;
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

	Model modeltmp0("data/fbx/e.fbx");
	sys->model.push_back(modeltmp0);
	Model modeltmp1("data/fbx/n.fbx");
	sys->model.push_back(modeltmp1);
	Model modeltmp2("data/fbx/m.fbx");
	sys->model.push_back(modeltmp2);

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

	glutInit(&argc, argv);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//make window
	if ((window = SDL_SetVideoMode(WINDOW_X, WINDOW_Y, 32, SDL_OPENGL)) == NULL) {
		printf("failed to initialize videomode.\n");
		exit(-1);
	}
	SDL_WM_SetCaption("Calamity", NULL);


	if (argc == 2 && strcmp(argv[1], "server") == 0) {
		sys = new System(MODE_SERVER);
    } else {
        sys = new System(MODE_CLIENT);



        if(Mix_OpenAudio(22050, AUDIO_S16, 2, 4096) != 0) {
            fprintf(stderr, "Unable to initialize audio: %s\n", Mix_GetError());
            exit(1);
        }
        //Mix_VolumeMusic(30);
        Mix_AllocateChannels(16);

        sys->bgm = Mix_LoadMUS("data/music/Calamity_BGM.wav");
        if (!sys->bgm)
            cout << "Can't read bgm" << SDL_GetError() << endl;
        sys->damage = Mix_LoadWAV("data/music/damage_se.wav");
        if (!sys->damage)
            cout << "Can't read damage" << SDL_GetError() << endl;
        sys->wind = Mix_LoadWAV("data/music/se_wind.wav");
        if (!sys->wind)
            cout << "Can't read wind" << SDL_GetError() << endl;
        sys->blade = Mix_LoadWAV("data/music/ice_blade_se.wav");
        if (!sys->blade)
            cout << "Can't read blade" << SDL_GetError() << endl;
        sys->fire = Mix_LoadWAV("data/music/fire_se.wav");
        if (!sys->fire)
            cout << "Can't read fire" << SDL_GetError() << endl;
        sys->ice = Mix_LoadWAV("data/music/ice_se.wav");
        if (!sys->ice)
            cout << "Can't read ice" << SDL_GetError() << endl;
        sys->thunder = Mix_LoadWAV("data/music/thunder_se.wav");
        if (!sys->thunder)
            cout << "Can't read thunder" << endl;

        Mix_PlayMusic(sys->bgm, -1);


    }

    sys->io = new GameIO();

    sys->draw = new Draw();

    //load map before player
    sys->map = new Map();

    sys->player = new Player[4];

    sys->title = new Title();

    sys->tutorial = new Tutorial();

    sys->effect = new Effect[MAX_EFFECT];

    sys->lighteffect = new lightEffect[NUM_LIGHT_EFFECT];

    sys->lighteffect[0].f = 1;
    sys->lighteffect[0].posX = 15;
    sys->lighteffect[0].posY = 15;

    if (argc == 2 && strcmp(argv[1], "server") == 0) {
        sys->network = new NetClass(MODE_SERVER);
        sys->Stage = -4;
        SDL_Quit();
    } else {
        sys->network = new NetClass(MODE_CLIENT);
        Init();

        //Initialize System
        if (argc >= 2)
            wiimoteInit(argv[1]);
        else
            cout << "wii remote controler is not connected" << endl;

    }

    cout << "Stage =  " << sys->Stage << endl;

    while (1) {
        sys->io->routine();
        for (int i = 0; i < 4; i++) {
            sys->player[i].routine();
        }
        for (int i = 0; i < MAX_EFFECT; i++) {
            sys->effect[i].routine();
        }
        for (int i = 0; i < NUM_LIGHT_EFFECT; i++) {
            if (sys->lighteffect[i].f > 0) {
                sys->lighteffect[i].routine();
            }
        }

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
            case 5:
                sys->selConfig();
                break;
            case 6:
                sys->IPset();
                break;
            case 7:
                Mix_VolumeMusic(vol = sys->VOLset(vol));
                break;
            case -1:
                sys->selectChara();
                break;
            case -2:
                sys->tutorial->routine();
                break;
            case -4:
                sys->detectCollision();
                break;
            default:
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

