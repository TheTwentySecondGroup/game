/*
 * system.cpp
 *
 *  last update 2015/02/12
 *      Author: Murokawa,Takeda
 */

#include"global.h"
#include "draw.h"
#include "Title.h"
#include "Effect.h"
#include "Tutorial.h"
#include "Map.h"
#include "system.h"
#include "Player.h"
#include "net.h"
#include <fstream>
#include <sstream>
#include "Wii.h"
using namespace std;

System::System(int m) {
	mode = m;
	TTF_Init();
	font = TTF_OpenFont("data/Koruri-20140904/Koruri-Bold.ttf", 100);
	dx = 0;
	dy = 0;
	count = 0;
	Stage = 0;
	charatype = 0;
	myID = 0;
	Stage = 0;
	selChara = 1;
	selConf = 1;
	sendFaceFlag=0;
	for(int i=0;i<4;i++)faceImage[i]=NULL;
}

System::~System() {
	TTF_CloseFont(font);
}

int System::initCamera() {

	capture = NULL;
	capture = cvCreateCameraCapture(0);
	if (capture == NULL) {
		cout << "Can't open /dev/video0" << endl;
		return -1;
	}

	// キャプチャサイズの設定
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 160);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 120);

	return 0;
}
int System::capImage() {
    for(int i=0;i<5;i++){
        sourceImage = cvQueryFrame(capture);

        if (sourceImage == NULL) {
            cout << "Can't get camera's image" << endl;
        }        else {
            break;
        }
    }
    if(!sourceImage)return 1;
 
    cvSetImageROI(sourceImage, cvRect(20, 40, 64, 64));
    
    
    
    char tmp[10];
       cvSaveImage("data/me.bmp",sourceImage);
       myFaceImage = draw->initTexture("data/me.bmp");
    sendFaceFlag=1;
    return 0;
}

int System::selectChara() {

    char buf[30];

    if (io->key[KEY_RIGHT] == 1) {
        if (selChara < 3)
            selChara++;
        else
            selChara = 1;
    }
    if (io->key[KEY_LEFT] == 1) {
        if (selChara > 1)
            selChara--;
        else
            selChara = 3;
    }
    if (io->key[KEY_A] == 1) {
        charatype = selChara;
        if(charatype == 3){
            initCamera();
            if(capImage()==0){
                 cout<<"get cameraImage"<<endl;
            }
        }
        player[0].chara = selChara;
        Stage = 1;
    }
    draw->drawCharaSelect();
    return 0;
}



/*キャラの移動と攻撃の受付*/
void System::moveChara() {

	double rad;
	Player old = player[myID];

	//視点を右方向に回す
	if (io->key[KEY_RIGHT] > 0) {
		if ((player[myID].dir -= 0.03) <= -6.03) {
			player[myID].dir = 0;
		}
	}
	//視点を左方向に回す
	if (io->key[KEY_LEFT] > 0) {
		if ((player[myID].dir += 0.03) > 6.03) {
			player[myID].dir = 0;
		}
	}
	//前進
	if (io->key[KEY_UP] > 0) {
		//x axis
		player[myID].x += sin(player[myID].dir) / 6;
		if (player[myID].x > STAGE_X)
			player[myID].x = STAGE_X;
		if (player[myID].x < 1.5)
			player[myID].x = 1.5;

		if (map->data[(int) (player[myID].x + sin(player[myID].dir))][(int) player[myID].z] == 1) {
			player[myID].x = old.x;
		}

		//z axis
		player[myID].z += cos(player[myID].dir) / 6;
		if (player[myID].z < 1.5)
			player[myID].z = 1.5;
		if (player[myID].z > STAGE_Y)
			player[myID].z = STAGE_Y;

		if (map->data[(int) player[myID].x][(int) (player[myID].z + cos(player[myID].dir))] == 1) {
			player[myID].z = old.z;
		}
	}
	//後進
	if (io->key[KEY_DOWN] > 0) {
		//x axis
		player[myID].x -= sin(player[myID].dir) / 3;
		if (player[myID].x < 1.5)
			player[myID].x = 1.5;
		if (player[myID].x > STAGE_X)
			player[myID].x = STAGE_X;

		if (map->data[(int) player[myID].x][(int) player[myID].z] == 1) {
			player[myID].x += sin(player[myID].dir) / 6;
		} else {
			player[myID].x += sin(player[myID].dir) / 6;
		}
		if (map->data[(int) (player[myID].x - sin(player[myID].dir))][(int) player[myID].z] == 1) {
			player[myID].x = old.x;
		}

		//z axis
		player[myID].z -= cos(player[myID].dir) / 6;
		if (player[myID].z < 1.5)
			player[myID].z = 1.5;
		if (player[myID].z > STAGE_Y)
			player[myID].z = STAGE_Y;

		if (map->data[(int) player[myID].x][(int) (player[myID].z - cos(player[myID].dir))] == 1) {
			player[myID].z = old.z;
		}
	}
	rad = (player[myID].dir * 56.5) * (PI / 180.0);
	//攻撃ボタンが押された時の処理
	if (io->key[KEY_B] == 1 && player[myID].attflag == 0 && player[myID].chara == 1) {
		Mix_PlayChannel(-1, sys->wind, 0);
		player[myID].attflag = 1;
		player[myID].attpatern = 1;
		for (int serchEffect = 0; serchEffect < MAX_EFFECT; serchEffect++) {
			if (effect[serchEffect].f == 0) {
				effect[serchEffect].fromPlayerID = myID;
				effect[serchEffect].f = 1;
				effect[serchEffect].x = player[myID].x + 4 * sin(rad);
				effect[serchEffect].z = player[myID].z + 4 * cos(rad);
				effect[serchEffect].dir = player[myID].dir;
				network->syncEffectFlag = serchEffect;
				break;
			}
		}
	}

	if (io->key[KEY_B] == 1 && player[myID].attflag == 0 && player[myID].chara == 2) {
		Mix_PlayChannel(-1, sys->fire, 0);
		player[myID].attflag = 1;
		player[myID].attpatern = 2;
		for (int serchEffect = 0; serchEffect < MAX_EFFECT; serchEffect++) {
			if (effect[serchEffect].f == 0) {
				effect[serchEffect].fromPlayerID = myID;
				effect[serchEffect].f = 2;
				effect[serchEffect].x = player[myID].x + 2.5 * sin(rad);
				effect[serchEffect].z = player[myID].z + 2.5 * cos(rad);
				effect[serchEffect].dir = player[myID].dir;
				network->syncEffectFlag = serchEffect;
				break;
			}
		}
	}
	/*ATTACK4*/
	if (io->key[KEY_C] == 1 && player[myID].attflag == 0 && player[myID].chara == 2) {
		Mix_PlayChannel(-1, sys->thunder, 0);
		player[myID].attflag = 1;
		player[myID].attpatern = 4;
		for (int serchEffect = 0; serchEffect < MAX_EFFECT; serchEffect++) {
			if (effect[serchEffect].f == 0) {
				effect[serchEffect].fromPlayerID = myID;
				effect[serchEffect].f = 4;
				effect[serchEffect].x = player[myID].x + 4 * sin(rad);
				effect[serchEffect].z = player[myID].z + 4 * cos(rad);
				effect[serchEffect].dir = player[myID].dir;
				network->syncEffectFlag = serchEffect;
				break;
			}
		}
	}

	/*ATTACK5*/
	if (io->key[KEY_B] == 1 && player[myID].attflag == 0 && player[myID].chara == 3) {
		Mix_PlayChannel(-1, sys->ice, 0);
		player[myID].attflag = 1;
		player[myID].attpatern = 5;
		for (int serchEffect = 0; serchEffect < MAX_EFFECT; serchEffect++) {
			if (effect[serchEffect].f == 0) {
				effect[serchEffect].fromPlayerID = myID;
				effect[serchEffect].f = 5;
				effect[serchEffect].x = player[myID].x + 4 * sin(rad);
				effect[serchEffect].z = player[myID].z + 4 * cos(rad);
				effect[serchEffect].dir = player[myID].dir;
				network->syncEffectFlag = serchEffect;
				break;
			}
		}
	}
	/*ATTACK7*/
	if (io->key[KEY_C] == 1 && player[myID].attflag == 0 && player[myID].chara == 1) {
		Mix_PlayChannel(-1, sys->blade, 0);
		player[myID].attflag = 1;
		player[myID].attpatern = 7;
		for (int serchEffect = 0; serchEffect < MAX_EFFECT; serchEffect++) {
			if (effect[serchEffect].f == 0) {
				effect[serchEffect].fromPlayerID = myID;
				effect[serchEffect].f = 7;
				effect[serchEffect].x = player[myID].x + 2.5 * sin(rad);
				effect[serchEffect].z = player[myID].z + 2.5 * cos(rad);
				effect[serchEffect].dir = player[myID].dir;
				network->syncEffectFlag = serchEffect;
				//network->clientCommand(EFFECT_COMMAND,TO_SERVER);
				break;
			}
		}
	}

	/*ATTACK8*/
	if (io->key[KEY_C] == 1 && player[myID].attflag == 0 && player[myID].chara == 3) {
		Mix_PlayChannel(-1, sys->blade, 0);
		player[myID].attflag = 1;
		player[myID].attpatern = 8;
		for (int serchEffect = 0; serchEffect < MAX_EFFECT; serchEffect++) {
			if (effect[serchEffect].f == 0) {
				effect[serchEffect].fromPlayerID = myID;
				effect[serchEffect].f = 8;
				effect[serchEffect].x = player[myID].x + 4 * sin(rad);
				effect[serchEffect].z = player[myID].z + 4 * cos(rad);
				effect[serchEffect].dir = player[myID].dir;
				network->syncEffectFlag = serchEffect;
				break;
			}
		}
	}
}

int System::judgeHit(int mode, Player *pl, Effect *ef) {
	if (mode == 1 || mode == 4 || mode == 5) {
		if ((abs(pl->x - ef->x) <= 1) && (abs(pl->z - ef->z) <= 1)) {
			return 1;
		}
	}
	else if(mode == 2 || mode == 7 || mode == 8){
	    if((abs(pl->x - ef->x) <= 0.25) && (abs(pl->z - ef->z) <= 0.25)){
		return 1;
	    }
	}
	return 0;
}

void System::gameMain() {
      if (player[myID].hp > 0)
        moveChara();
    draw->routine();

}

int p = 1, n1 = 0, n2 = 1;
string s1("192.168.");
string s2("0");
string s3("1");
string s4(".");

/*接続先サーバーのIPアドレスを指定*/
void System::IPset() {
     std::ostringstream ss;
	//背景を表示
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    sys->draw->init3D();
    {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        double xd = sin(0);
        double zd = cos(0);

        gluLookAt(sys->lighteffect[0].posX - xd * 2,   1,
                sys->lighteffect[0].posY - zd * 2, // position of camera
                sys->lighteffect[0].posX,   0, sys->lighteffect[0].posY, //look-at point
                0, 1.0f, 0);

        //Light
        glEnable(GL_LIGHTING);
        glEnable(GL_NORMALIZE);

        glEnable(GL_LIGHT0);

        //light1
        sys->draw->lightpos[0] = sys->lighteffect[0].posX;
        sys->draw->lightpos[1] = 5;
        sys->draw->lightpos[2] = sys->lighteffect[0].posY;
        sys->draw->lightpos[3] = 1;

        glLightfv(GL_LIGHT0, GL_POSITION, sys->draw->lightpos);
        GLfloat Light1Dir[] = { 0, -1, 0 };
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Light1Dir);
        glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 80.0f);
        glLightf( GL_LIGHT0, GL_SPOT_EXPONENT, 10.0f);
        glLightfv(GL_LIGHT0, GL_AMBIENT, sys->draw->WhiteLight);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, sys->draw->DifLight);
        glLightfv(GL_LIGHT0, GL_SPECULAR, sys->draw->SpecularLight);

        sys->map->drawMap();

        for (int i = 0; i < NUM_LIGHT_EFFECT; i++) {
            if (sys->lighteffect[i].f > 0) {
                sys->lighteffect[i].draw();
            }
        }
    }

    draw->init2D();
    {
        title->drawMenu(100, 100, 800, 150, "Input server IP");
        title->drawMenu(100, 200, 800, 250, s1 + s2 + s4 + s3);
    }
    if (io->key[KEY_RIGHT] > 0) {
        if (p == 1)
            p++;
    }
    if (io->key[KEY_LEFT] > 0) {
        if (p == 2)
            p--;
    }
    if (io->key[KEY_UP] > 0) {
        if (p == 1) {
            ss << ++n1;
            s2 = ss.str();
        } else if (p == 2) {
            ss << ++n2;
            s3 = ss.str();
        }
    }
    if (io->key[KEY_DOWN] > 0) {
        if (p == 1 && n1 > 0) {
            ss << --n1;
            s2 = ss.str();
        } else if (p == 2 && n2 > 1) {
            ss << --n2;
            s3 = ss.str();
        }
    }

    glFlush();
    SDL_GL_SwapBuffers();
    SDL_Delay(80);
    if (io->key[KEY_A] == 1) {
        std::ofstream ofs("data/ip.txt");
        ofs << s1 + s2 + s4 + s3 << endl;
        Stage = 0;
    }
}

/*設定項目を選択*/
void System::selConfig(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    sys->draw->init3D();
    {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        double xd = sin(0);
        double zd = cos(0);

        gluLookAt(sys->lighteffect[0].posX - xd * 2,   1,
                sys->lighteffect[0].posY - zd * 2, // position of camera
                sys->lighteffect[0].posX,   0, sys->lighteffect[0].posY, //look-at point
                0, 1.0f, 0);

        //Light
        glEnable(GL_LIGHTING);
        glEnable(GL_NORMALIZE);

        glEnable(GL_LIGHT0);

        //light1
        sys->draw->lightpos[0] = sys->lighteffect[0].posX;
        sys->draw->lightpos[1] = 5;
        sys->draw->lightpos[2] = sys->lighteffect[0].posY;
        sys->draw->lightpos[3] = 1;

        glLightfv(GL_LIGHT0, GL_POSITION, sys->draw->lightpos);
        GLfloat Light1Dir[] = { 0, -1, 0 };
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Light1Dir);
        glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 80.0f);
        glLightf( GL_LIGHT0, GL_SPOT_EXPONENT, 10.0f);
        glLightfv(GL_LIGHT0, GL_AMBIENT, sys->draw->WhiteLight);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, sys->draw->DifLight);
        glLightfv(GL_LIGHT0, GL_SPECULAR, sys->draw->SpecularLight);

        sys->map->drawMap();

        for (int i = 0; i < NUM_LIGHT_EFFECT; i++) {
            if (sys->lighteffect[i].f > 0) {
                sys->lighteffect[i].draw();
            }
        }
    }

    draw->init2D();
    {
	if(selConf==1){
	    title->drawMenu(50, 100, 90,200, "->");
	}
	else if(selConf==2){
	    title->drawMenu(50, 400, 90, 450, "->");
	}
	title->drawMenu(110, 100, 800, 200, "IPSET");
	title->drawMenu(110, 400, 800, 450, "VOLUMESET");
    }
    if(io->key[KEY_UP] > 1){
	if(selConf==2)
	    selConf--;
    }
    else if(io->key[KEY_DOWN] > 1){
	if(selConf==1)
	    selConf++;
    }
    else if(io->key[KEY_A] == 1){
	if(selConf == 1){
	    Stage = 6;
	}
	else if(selConf == 2){
	    Stage = 7;
	}
    }
    glFlush();
    SDL_GL_SwapBuffers();
}

/*BGMとSEの音量を設定*/
int System::VOLset(int vol){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	    sys->draw->init3D();
	    {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        double xd = sin(0);
        double zd = cos(0);

        gluLookAt(sys->lighteffect[0].posX - xd * 2,   1,
                sys->lighteffect[0].posY - zd * 2, // position of camera
                sys->lighteffect[0].posX,   0, sys->lighteffect[0].posY, //look-at point
                0, 1.0f, 0);

        //Light
        glEnable(GL_LIGHTING);
        glEnable(GL_NORMALIZE);
        glEnable(GL_LIGHT0);

        //light1
        sys->draw->lightpos[0] = sys->lighteffect[0].posX;
        sys->draw->lightpos[1] = 5;
        sys->draw->lightpos[2] = sys->lighteffect[0].posY;
        sys->draw->lightpos[3] = 1;

        glLightfv(GL_LIGHT0, GL_POSITION, sys->draw->lightpos);
        GLfloat Light1Dir[] = { 0, -1, 0 };
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Light1Dir);
        glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 80.0f);
        glLightf( GL_LIGHT0, GL_SPOT_EXPONENT, 10.0f);
        glLightfv(GL_LIGHT0, GL_AMBIENT, sys->draw->WhiteLight);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, sys->draw->DifLight);
        glLightfv(GL_LIGHT0, GL_SPECULAR, sys->draw->SpecularLight);

        sys->map->drawMap();

        for (int i = 0; i < NUM_LIGHT_EFFECT; i++) {
            if (sys->lighteffect[i].f > 0) {
                sys->lighteffect[i].draw();
            }
        }
    }

    stringstream ss;
    ss << vol;
    string str = ss.str();
    draw->init2D();
    {
	title->drawMenu(250, 100, 500, 200, "VOLUME");
	title->drawMenu(400, 300, 480, 350, str);
    }

    if(io->key[KEY_UP] > 1){
	if(vol < 128)
	    vol++;
    }
    else if(io->key[KEY_DOWN] > 1){
	if(vol > 0)
	    vol--;
    }
    SDL_Delay(50);
    glFlush();
    SDL_GL_SwapBuffers();
    if(io->key[KEY_A] == 1){
	Stage = 0;
    }

    return vol;
}
void System::detectCollision() {

    for (int i = 0; i < MAX_EFFECT; i++) {

        if (effect[i].f > 0) {
            for (int c = 0; c < 4; c++) {
                if (player[c].hp <= 0) {
                    continue;
                }
                if (player[c].chara != -1 && player[c].avoidDamageCount == 0 && effect[i].fromPlayerID != c
                        && judgeHit(effect[i].f, &player[c], &effect[i]) > 0) {
                    player[c].avoidDamageCount = 30;
                    player[c].hp -= 10;
                }
            }

        }

    }
}
