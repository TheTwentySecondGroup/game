#include "global.h"
#include "Model.h"


void draw();
Model* model;
Obj myPos;
wiimote_t wiimote;
int Stage = 1;
time_t start,now,end;
int MaxTime;    
int BeforeTime;



float angle=0.0f;

void idle(void){
    angle+=2.0f;
    //Sleep(1);
    glutPostRedisplay();
}

void Init(){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
   // glEnable(GL_CULL_FACE);
   // glCullFace(GL_BACK);



    model = new Model;

    cout<<"Init() executed\n";
    cout<<"-----------------------\n\n\n";
}

int main(int argc, char *argv[])
{
    SDL_Surface *window;
    SDL_Event event; //for SDL event

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
    SDL_WM_SetCaption("testProgram",NULL);

    //initialize my position
     myPos.x=0;
     myPos.y=0.5;
     myPos.z=0;

    /*
    if(argc > 1 && !wiimote_connect(&wiimote, argv[1])){
        wiimote.led.one  = 1;
        wiimote.mode.ir = 1;

        //make thread for wiimote
        pthread_t wu;
        //pthread_create(&wu,NULL,wiimoteUpdate ,NULL);
        printf("wiiremote  connected\n");
    }else{
        printf("wiiremote can't connect\n");
    }

*/
    glutInit(&argc, argv);


    //initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);

    //format to black
    glClearColor(0.0, 0.0, 0.0, 0.0);
    //glutDisplayFunc(display);
    //glutIdleFunc(idle);    



    Init();
    //glutMainLoop();


    


    //mainloop
    while(1){
        timeProc();
        //printf("%f sec\n",difftime(now,start));

        switch(Stage){
            case 0:
                //Title(window);
                break;
            case 1:
                GameMain();
                break;
            case 2:
                //Tutorial();
                break;
            default:
                //delTitle();
                //delDraw();
                SDL_Quit();
                exit(0);
                break;
        }

        //if end
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
        int curTime =SDL_GetTicks();
        int difTime = curTime-BeforeTime;
        if(difTime < 1000/FPS_RATE)SDL_Delay(1000/FPS_RATE - difTime);
        BeforeTime=curTime;

    }
    return 0;
}

void timeEnd(){
    end=time(NULL);
}
void timeProc(){                                         
    now=time(NULL);
}
void timeReset(){
    MaxTime=100;
    start=time(NULL);
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

void GameMain(){
              /*
    //wiiremote
    if(wiimote_is_open(&wiimote)){  
        if(wiimote.keys.bits & WIIMOTE_KEY_UP){
            struct Obj myOld = myPos;
            myPos.x+=sin(myPos.dir)/15;
            //myPos=CDtoMap(myPos,myOld);
            myOld = myPos;
            myPos.y+=cos(myPos.dir)/15;
            //myPos=CDtoMap(myPos,myOld);
        }
        if(wiimote.keys.bits & WIIMOTE_KEY_DOWN){
            struct Obj myOld = myPos;
            myPos.x-=sin(myPos.dir)/15;
            //myPos=CDtoMap(myPos,myOld);
            myOld = myPos;
            myPos.y-=cos(myPos.dir)/15;
            myPos=CDtoMap(myPos,myOld);
        }
        if(wiimote.keys.bits & WIIMOTE_KEY_RIGHT){
            myPos.dir+=0.03;
        }
        if(wiimote.keys.bits & WIIMOTE_KEY_LEFT){
            myPos.dir-=0.03;
        }

    } else{
*/
        //keyboad
        Uint8 *key = SDL_GetKeyState(NULL);
        if(key[SDLK_RIGHT] == SDL_PRESSED){
            myPos.dir-=0.03;
        }
        if(key[SDLK_LEFT] == SDL_PRESSED){
            myPos.dir+=0.03;
        }
        if(key[SDLK_UP] == SDL_PRESSED){
            struct Obj myOld = myPos;
            myPos.x+=sin(myPos.dir)/5;
           // myPos=CDtoMap(myPos,myOld);
            myOld = myPos;
            myPos.z+=cos(myPos.dir)/5;
            //myPos=CDtoMap(myPos,myOld);
        }
        if(key[SDLK_DOWN] == SDL_PRESSED){
            struct Obj myOld = myPos;
            myPos.x-=sin(myPos.dir)/5;
            //myPos=CDtoMap(myPos,myOld);
            myOld = myPos;
            myPos.z-=cos(myPos.dir)/5;
            //myPos=CDtoMap(myPos,myOld);
        }


    draw();
}
