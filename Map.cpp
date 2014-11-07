#include "Map.h"
#include "global.h"
#include "GLMetaseq.h"
#include "draw.h"
#include "Effect.h"
#include "Title.h"
#include "Tutorial.h"

int Map[MAP_X_MAX][MAP_Y_MAX];

char *MAP_FILE_NAME[] ={"data/map/stage1.data","data/map/stage2.data","data/map/stage3.data","data/map/stage4.data"} ;
int initMap(int stage){

    int i,c;
    FILE* fp = fopen( MAP_FILE_NAME[stage-1] ,"r");
    if(fp == NULL){
        puts("Can't open map data.");
        exit -1;
    }

    for(i=0;i<MAP_X_MAX;i++){
        for(c=0;c<MAP_Y_MAX;c++){
            Map[i][c]=-1;
        }
    }

    for(i=0;i<MAP_X_MAX;i++){
        for(c=0;c<MAP_Y_MAX;c++){
            int data;
            if((data=(fgetc(fp)-48)) != -49){
                if(data==('\n'-48)){
                    break;
                }
                Map[i][c]=data;
                if (data==2){
                    player[0].x=i+0.5;
                    player[0].y=c+0.5;
                    player[0].dir=0;
                    //player[0].Item[0]=0;
					/*
                    int k;
                    for(k=0;k<10;k++){
                        player[0].Item[k]=0;
                    }
                    */
                }
                /*
                if (data==4){
                    goalX=i;
                    goalY=c;
                }
                */
            }
        }
    }
    fclose(fp);

    return 0;
}
void drawMap(){
    int i,c;
    int min_x=(int)player[0].x-8;
    if(min_x<0)min_x=0;
    int max_x=(int)player[0].x+8;
    if(max_x>MAP_X_MAX)max_x=MAP_X_MAX;
    int min_y=(int)player[0].y-8;
    if(min_y<0)min_y=0;
    int max_y=(int)player[0].y+8;
    if(max_y>MAP_Y_MAX)max_y=MAP_Y_MAX;

    for(i=min_x;i<max_x;i++){
        for(c=min_y;c<max_y;c++){
            //block
            /*if(Map[i][c]==1){
                drawCube(i,c);
            }
            */
            //road and start position
            if(Map[i][c]==0 || Map[i][c] == 2){
                drawFloor(i,c);
                drawSky(i,c);
                //drawCelling(i,c);
            }
            //falling
            /*if(Map[i][c]==3){
                drawCelling(i,c);
            }
            */
            /*if(Map[i][c]==4){//goal
                drawFloor(i,c);
                drawCelling(i,c);
            }
			*/

        }
    }
}


