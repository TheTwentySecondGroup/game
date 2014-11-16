#ifndef __SYSTEM_H__
#define __SYSTEM_H__

int selectChara();
void moveChara();	//キャラの移動
int judgeHit();	//当たり判定
void attack(float x, float y, float dx, float dy);
void gameMain();	//ゲームのメイン


#endif
