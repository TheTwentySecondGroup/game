#include"global.h"
#include "draw.h"
#include "Title.h"
#include "Effect.h"
#include "Tutorial.h"
#include "Map.h"
#include "system.h"
#include "Player.h"
#include "net.h"
System::System(int m) {
	mode = m;
	TTF_Init();
	font = TTF_OpenFont("data/Koruri-20140904/Koruri-Bold.ttf", 100);
	//if(!font)cout<<TTF_GetError()<<endl;
	dx = 0;
	dy = 0;
	count = 0;
	Stage = 0;
	charatype = 0;
	myID = 0;
	Stage = 0;
	selChara = 1;
}
using namespace std;

System::~System() {
	TTF_CloseFont(font);

}

int System::selectChara() {

	char buf[30];

	//while (1) {
	//sys->io->routine();

	//if (io->key[KEY_RIGHT] == 1) {
	if (io->key[KEY_RIGHT] == 1) {
		if (selChara < 4)
			selChara++;
		else
			selChara = 1;
	}
	if (io->key[KEY_LEFT] == 1) {
		if (selChara > 1)
			selChara--;
		else
			//if (selChara == 1)
			selChara = 4;
	}
	if (io->key[KEY_A] == 1) {
		charatype = selChara;
		player[0].chara = selChara;
		Stage = 1;
	}
	draw->drawCharaSelect();
	//}
	//return -1;
}

void System::initChara() {

}

void System::moveChara() {
	double rad;
	Player old = player[myID];

	if (io->key[KEY_RIGHT] > 0) {
		if ((player[myID].dir -= 0.03) <= -6.03) {
			player[myID].dir = 0;
		}
		//cout << player[myID].dir << endl;
	}

	if (io->key[KEY_LEFT] > 0) {
		if ((player[myID].dir += 0.03) > 6.03) {
			player[myID].dir = 0;
		}
		//cout << player[myID].dir << endl;
	}

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

	if (io->key[KEY_DOWN] > 0) {
		//x axis
		player[myID].x -= sin(player[myID].dir) / 3;
		if (player[myID].x < 1.5)
			player[myID].x = 1.5;
		if (player[myID].x > STAGE_X)
			player[myID].x = STAGE_X;

		if (map->data[(int) player[myID].x][(int) player[myID].z] == 1) {
			player[myID].x += sin(player[myID].dir) / 3;
		} else {
			player[myID].x += sin(player[myID].dir) / 6;
		}
		if (map->data[(int) (player[myID].x - sin(player[myID].dir))][(int) player[myID].z] == 1) {
			player[myID].x = old.x;
		}

		//z axis
		player[myID].z -= cos(player[myID].dir) / 3;
		if (player[myID].z < 1.5)
			player[myID].z = 1.5;
		if (player[myID].z > STAGE_Y)
			player[myID].z = STAGE_Y;

		if (map->data[(int) player[myID].x][(int) (player[myID].z - cos(player[myID].dir))] == 1) {
			player[myID].z = old.z;
		}
	}
	rad = (player[myID].dir * 56.5) * (PI / 180.0);

	if (io->key[KEY_B] == 1 && player[myID].attflag == 0 && player[myID].chara == 1) {
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

	/*ATTACK3(仮)*/
	if (io->key[KEY_D] == 1 && player[myID].attflag == 0) {
		player[myID].attflag = 1;
		player[myID].attpatern = 3;
		for (int serchEffect = 0; serchEffect < MAX_EFFECT; serchEffect++) {
			if (effect[serchEffect].f == 0) {
				effect[serchEffect].fromPlayerID = myID;
				effect[serchEffect].f = 3;
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
		player[myID].attflag = 1;
		player[myID].attpatern = 5;
		for (int serchEffect = 0; serchEffect < MAX_EFFECT; serchEffect++) {
			if (effect[serchEffect].f == 0) {
				effect[serchEffect].f = 5;
				effect[serchEffect].x = player[myID].x + 4 * sin(rad);
				effect[serchEffect].z = player[myID].z + 4 * cos(rad);
				effect[serchEffect].dir = player[myID].dir;
				network->syncEffectFlag = serchEffect;
				break;
			}
		}
	}
	/*ATTACK6*/
	if (io->key[KEY_G] == 1 && player[myID].attflag == 0) {
		player[myID].attflag = 1;
		player[myID].attpatern = 6;
		for (int serchEffect = 0; serchEffect < MAX_EFFECT; serchEffect++) {
			if (effect[serchEffect].f == 0) {
				effect[serchEffect].f = 6;
				effect[serchEffect].x = player[myID].x + 2.5 * sin(rad);
				effect[serchEffect].z = player[myID].z + 2.5 * cos(rad);
				effect[serchEffect].dir = player[myID].dir;
				network->syncEffectFlag = serchEffect;
				break;
			}
		}
	}

	/*ATTACK7*/
	if (io->key[KEY_C] == 1 && player[myID].attflag == 0 && player[myID].chara == 1) {
		player[myID].attflag = 1;
		player[myID].attpatern = 7;
		for (int serchEffect = 0; serchEffect < MAX_EFFECT; serchEffect++) {
			if (effect[serchEffect].f == 0) {
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
		player[myID].attflag = 1;
		player[myID].attpatern = 8;
		for (int serchEffect = 0; serchEffect < MAX_EFFECT; serchEffect++) {
			if (effect[serchEffect].f == 0) {
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
	if (mode >= 1) {
		//cout<<"-----------judge  distance "<<abs(pl->x - ef->x)* abs(pl->z - ef->z)<<endl;
		if ((abs(pl->x - ef->x) <= 1) && (abs(pl->z - ef->z) <= 1)) {
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

void System::detectCollision() {

	//cout<<"execute detectCollision()"<<endl;
	for (int i = 0; i < MAX_EFFECT; i++) {

		if (effect[i].f > 0) {
			for (int c = 0; c < 4; c++) {
				if (player[c].hp <= 0) {
					continue;
				}
				//effect[i].x = player[c].x;
				//effect[i].z = player[c].z;
				if (player[c].chara != -1 && player[c].avoidDamageCount == 0 && effect[i].fromPlayerID != c
						&& judgeHit(effect[i].f, &player[c], &effect[i]) > 0) {
					player[c].avoidDamageCount = 30;
					player[c].hp -= 10;
				}
			}

		}

	}

}

