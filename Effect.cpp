#include "global.h"
#include "Effect.h"
#include "GLMetaseq.h"
#include "draw.h"
#include "Map.h"

//structure for effect
struct ef Effect[EFFECT_MAX];


//initialize effect
void initEffect(){
    int i;
    for(i=0;i<EFFECT_MAX;i++){
        Effect[i].f=0;
        Effect[i].x=-1;
        Effect[i].y=-1;
        Effect[i].z=-1;
        Effect[i].restTime=0;
    }
}

//type ==1 ->drawText to screen
void makeEffect(int type,int time,char* str){
    int i;
    for(i=0;i<EFFECT_MAX;i++){
        if(Effect[i].f==0){
            if(type==1){
                Effect[i].f=1;
                Effect[i].x=WINDOW_X/2-200;
                Effect[i].y=WINDOW_Y/2-100;
                Effect[i].w=400;
                Effect[i].h=200;
                Effect[i].restTime=time;
                strcpy(Effect[i].str,str);
			}
            return;
        }
    }

}
