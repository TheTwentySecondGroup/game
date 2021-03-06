/*
 * Title.h
 *
 *  last update 2015/02/12
 *      Author: Murokawa,Takeda
 */
#ifndef __TITLE_H__
#define __TITLE_H__

#define CHOICE_MIN 1
#define CHOICE_MAX 3

//#include "system.h"

namespace std {

class Title {
public:

	int sel;//カーソル
	int KeyFlag;//キーフラグ
	GLuint *titleImage[7];//画像ハンドル
	string menuString[CHOICE_MAX];//メニューの文字
	Title();

	~Title();
	void routine();//タイトルルーチン
	void drawTitle();//タイトル画面描写
	//void delTitle();
	//void drawMenuCube(int x, int y, GLuint *texture, double sw);
	void drawMenu(int x, int y, int w, int h,string mes) ;//メニュー表示関数
};
}
#endif
