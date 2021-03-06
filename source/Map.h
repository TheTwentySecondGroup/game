/*
 * Map.h
 *
 *  last update 2015/02/12
 *      Author: Murokawa,Takeda
 */
#ifndef __MAP_H__
#define __MAP_H__
#define MAP_X_MAX 100
#define MAP_Y_MAX 100

class Map {
	public:
//location of map data file 
	char *MAP_FILE_NAME[];

	Map();
	~Map();
	int initMap(int);//マップ初期化
	void drawMap();//マップ描写
	//void drawCube();
	//int initMap();
	//void drawCube(int, int);
//void drawFloor();

	/**
	 -1 = no data
	 0  = road
	 1  = block
	 2  = start
	 3  = no floor
	 4  = goal
	 */
	int data[MAP_X_MAX][MAP_Y_MAX];//マップデータ

};
#endif
