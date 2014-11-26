#include "Map.h"
#include "global.h"
#include "draw.h"
#include "Effect.h"
#include "Title.h"
#include "Tutorial.h"
#include "system.h"



Map::Map(){
	MAP_FILE_NAME[0] = "data/map/stage1.data";
	MAP_FILE_NAME[1] = "data/map/stage2.data";
	MAP_FILE_NAME[2] = "data/map/stage3.data";
	MAP_FILE_NAME[3] = "data/map/stage4.data" ;

	initMap(1);


}


int  Map::initMap(int stage) {
	int i, c;
	FILE* fp = fopen(MAP_FILE_NAME[stage - 1], "r");
	if (fp == NULL) {
		puts("Can't open map data.");
		exit -1;
	}

	for (i = 0; i < MAP_X_MAX; i++) {
		for (c = 0; c < MAP_Y_MAX; c++) {
			data[i][c] = -1;
		}
	}

	for (i = 0; i < MAP_X_MAX; i++) {
		for (c = 0; c < MAP_Y_MAX; c++) {
			int tmpdata;
			if ((tmpdata = (fgetc(fp) - 48)) != -49) {
				if (tmpdata == ('\n' - 48)) {
					break;
				}
				data[i][c] = tmpdata;
			}
		}
	}
	fclose(fp);

	return 0;
}
void Map::drawMap() {
	cout<<"execute map drawMap() "<<endl;
	int i, c;
	int min_x = (int) sys->player[sys->myID].x - 24;
	if (min_x < 0)
		min_x = 0;
	int max_x = (int) sys->player[sys->myID].x + 24;
	if (max_x > MAP_X_MAX)
		max_x = MAP_X_MAX;
	int min_y = (int) sys->player[sys->myID].z - 30;
	if (min_y < 0)
		min_y = 0;
	int max_y = (int) sys->player[sys->myID].z + 30;
	if (max_y > MAP_Y_MAX)
		max_y = MAP_Y_MAX;
	sys->draw->drawSky(1, 1);
	for (i = min_x; i < max_x; i++) {
		for (c = min_y; c < max_y; c++) {
			//block
			if (data[i][c] == 1) {
				sys->draw->drawWall(i, c);
			}

			//road and start position
			if (data[i][c] == 0) {
				sys->draw->drawFloor(i, c);
				//drawSky(i,c);
			}

			if (data[i][c] == 2) {
				sys->draw->drawFloor(i, c);
				//drawSky(i,c);
			}
			//falling
			if (data[i][c] == 3) {
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
