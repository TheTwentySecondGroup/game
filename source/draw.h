#ifndef __DRAW_H__
#define __DRAW_H__

using namespace std;

class Draw{
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

	void routine();

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

void drawAttack(double x, double z);

//calculate and setting glNormal3f
	GLvoid Normal3f(GLfloat fVert1[], GLfloat fVert2[], GLfloat fVert3[]);

//for font
	TTF_Font* font;

// for light
	/*light0 position
	 [0]=my x position
	 [1]=my y position
	 [2]=my z position
	 [3]=1.0  never change*/


};

#endif            
