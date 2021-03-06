/*
 * draw.h
 *
 *  last update 2015/02/12
 *      Author: Murokawa,Takeda
 */

#ifndef __DRAW_H__
#define __DRAW_H__

using namespace std;

class Draw {
public:
	GLuint *texHandle[10];

	GLuint *charaImage[8];

	GLfloat lightpos[4];
	GLfloat DifLight[4];
	GLfloat GrayMaterial[4];
	GLfloat WhiteMaterial[4];
	GLfloat SpecularLight[4];
	GLfloat GrayLight[4];
	GLfloat WhiteLight[4];
	GLfloat FogColor[4];

//Initialize draw() function
	Draw();
//delete draw
	~Draw();

//generate texture from file
	GLuint *initTexture(string name);

//generate texture from SDL_Surface
	GLuint *timeTexture(SDL_Surface *surface);
	GLuint *pngTexture(string name);

//set 3D
	void init3D();
//set 2D
	void init2D();
//処理ルーチン
	void routine();
//キャラクターセレクト画面描写
	void drawCharaSelect();

//draw floor x,y
	void drawFloor(int, int);

//draw sky
	void drawSky(int x, int y);

//drawLake
	void drawFloor2(int x, int y);

//draw wall
	void drawWall(int x, int y);

//draw cube
	void drawCube(int x, int y);

//draw 2D HP
	void drawHP(int x, int y, int w, int h);
	void drawHP3D(int i);
//draw 2D GameOver Message
	void drawGameOver(int x, int y, int w, int h);
//draw 2D Win Message
	void drawWin(int x, int y, int w, int h);
//calculate and setting glNormal3f
	GLvoid Normal3f(GLfloat fVert1[], GLfloat fVert2[], GLfloat fVert3[]);

//draw cylinder
	void drawCylinder(int div, float r, float h);

// draw indicator
	void drawIndicator();
//for font
	TTF_Font* font;
};

#endif            
