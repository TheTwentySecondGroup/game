
#ifndef __DRAW_H__
#define __DRAW_H__


//Initialize draw() function
void initDraw();
//delete draw
void delDraw();

//generate texture from file
GLuint *initTexture(char name[]);

//generate texture from SDL_Surface
GLuint *timeTexture(SDL_Surface *surface);
GLuint *pngTexture(char name[]);

//set 3D
void init3D();
//set 2D
void init2D();

void draw();

//draw floor x,y
void drawFloor(int, int);

//draw sky
void drawSky(int x, int y);

//drawLake
void drawFloor2(int x, int y);

//draw wall
void drawWall(int x, int y);

//void drawA(int x, int y);

//calculate and setting glNormal3f
GLvoid Normal3f(GLfloat fVert1[], GLfloat fVert2[],GLfloat fVert3[]);

//for font
extern TTF_Font* font;

// for light
/*light0 position
[0]=my x position
[1]=my y position
[2]=my z position
[3]=1.0  never change*/
extern GLfloat lightpos[4];
extern GLfloat DifLight[];
extern GLfloat GrayMaterial[];
extern GLfloat WhiteMaterial[];
extern GLfloat SpecularLight[];
extern GLfloat GrayLight[];
extern GLfloat WhiteLight[];
extern GLfloat FogColor[];
extern GLuint *texHandle[10];
#endif            
