/*
 * Tutorial.h
 *
 *  last update 2015/02/12
 *      Author: Murokawa,Takeda
 */
#ifndef __TUTORIAL_H__
#define __TUTORIAL_H__

#define SLIDE_MAX 2
class Tutorial {
public:
	//System *sys;
	int Slide;//カレントスライド

	void routine();//処理ルーチン
	void draw(int n);//描写

	Tutorial();
	~Tutorial();


	//void drawText();//文字表示
};
#endif
