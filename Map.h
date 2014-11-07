
#ifndef __MAP_H__
#define __MAP_H__

//location of map data file 
extern char *MAP_FILE_NAME[];



#define MAP_X_MAX 100
#define MAP_Y_MAX 100


extern int initMap(int );
extern void drawMap();
extern void drawCube();
extern int initMap();
extern void drawCube(int,int);
//extern void drawFloor();

/**
    -1 = no data
    0  = road
    1  = block
    2  = start
    3  = no floor
    4  = goal
*/
extern int Map[MAP_X_MAX][MAP_Y_MAX];
#endif
