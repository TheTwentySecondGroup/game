#include "Map.h"
#include "global.h"
#include "draw.h"
#include "Effect.h"
#include "Title.h"
#include "Tutorial.h"
#include "system.h"

int Map[MAP_X_MAX][MAP_Y_MAX];

char *MAP_FILE_NAME[] = { "data/map/stage1.data", "data/map/stage2.data",
		"data/map/stage3.data", "data/map/stage4.data" };
int initMap(int stage) {

	int i, c;
	FILE* fp = fopen(MAP_FILE_NAME[stage - 1], "r");
	if (fp == NULL) {
		puts("Can't open map data.");
		exit - 1;
	}

	for (i = 0; i < MAP_X_MAX; i++) {
		for (c = 0; c < MAP_Y_MAX; c++) {
			Map[i][c] = -1;
		}
	}

	for (i = 0; i < MAP_X_MAX; i++) {
		for (c = 0; c < MAP_Y_MAX; c++) {
			int data;
			if ((data = (fgetc(fp) - 48)) != -49) {
				if (data == ('\n' - 48)) {
					break;
				}
				Map[i][c] = data;
			}
		}
	}
	fclose(fp);

	return 0;
}
void drawMap() {
	int i, c;
	int min_x = (int) sys->player[sys->myID].x - 30;
	if (min_x < 0)
		min_x = 0;
	int max_x = (int) sys->player[sys->myID].x + 30;
	if (max_x > MAP_X_MAX)
		max_x = MAP_X_MAX;
	int min_y = (int) sys->player[sys->myID].y - 30;
	if (min_y < 0)
		min_y = 0;
	int max_y = (int) sys->player[sys->myID].y + 30;
	if (max_y > MAP_Y_MAX)
		max_y = MAP_Y_MAX;
	sys->draw->drawSky(1, 1);
	for (i = min_x; i < max_x; i++) {
		for (c = min_y; c < max_y; c++) {
			//block
			if (Map[i][c] == 1) {
				sys->draw->drawWall(i, c);
			}

			//road and start position
			if (Map[i][c] == 0) {
				sys->draw->drawFloor(i, c);
				//drawSky(i,c);
			}

			if (Map[i][c] == 2) {
				sys->draw->drawFloor(i, c);
				//drawSky(i,c);
			}
			//falling
			if (Map[i][c] == 3) {
				sys->draw->drawFloor2(i, c);
				//drawSky(i,c);
				//drawA(i,c);
			}

			/*if(Map[i][c]==4){//goal
			 drawFloor(i,c);
			 drawCelling(i,c);
			 }
			 */
		}
	}
}
