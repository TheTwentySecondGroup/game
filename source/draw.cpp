/*
 * draw.cpp
 *
 *  last update 2015/02/12
 *      Author: Murokawa,Takeda
 */

#include "global.h"
#include "system.h"

GLuint *texHandle[10];

void Draw::routine() {
	glClearColor(0, 0, 0, 1.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	init3D();

	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		double xd = sin(sys->player[sys->myID].dir);
		double zd = cos(sys->player[sys->myID].dir);
		double cameraPosZ = 1;
		if (sys->map->data[(int) (sys->player[sys->myID].x - xd * 2)][(int) (sys->player[sys->myID].z - zd * 2)] != 0)
			cameraPosZ += 4;
		gluLookAt(sys->player[sys->myID].x - xd * 2, sys->player[sys->myID].y + cameraPosZ,
				sys->player[sys->myID].z - zd * 2, // position of camera
				sys->player[sys->myID].x, sys->player[sys->myID].y + 0.5, sys->player[sys->myID].z, //look-at point
				0, 1.0f, 0);

		//Light
		glEnable(GL_LIGHTING);
		glEnable(GL_NORMALIZE);

		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);

		lightpos[0] = sys->player[sys->myID].x - 2 * sin(sys->player[sys->myID].dir);
		lightpos[1] = sys->player[sys->myID].y + 0.5;
		lightpos[2] = sys->player[sys->myID].z - 2 * cos(sys->player[sys->myID].dir);

		lightpos[3] = 1;

		glLightfv(GL_LIGHT0, GL_POSITION, lightpos); // position of light0
		GLfloat Light0Dir[] = { sin(sys->player[sys->myID].dir), 0, cos(sys->player[sys->myID].dir) };
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Light0Dir);
		glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 40.0f);
		glLightf( GL_LIGHT0, GL_SPOT_EXPONENT, 80.0f);
		glLightfv(GL_LIGHT0, GL_AMBIENT, WhiteLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, DifLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);

		//light1
		lightpos[0] = sys->lighteffect[0].posX;
		lightpos[1] = 5;
		lightpos[2] = sys->lighteffect[0].posY;
		lightpos[3] = 1;

		glDisable(GL_FOG);

		glLightfv(GL_LIGHT1, GL_POSITION, lightpos);
		GLfloat Light1Dir[] = { 0, -1, 0 };
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Light1Dir);
		glLightf( GL_LIGHT1, GL_SPOT_CUTOFF, 80.0f);
		glLightf( GL_LIGHT1, GL_SPOT_EXPONENT, 10.0f);
		glLightfv(GL_LIGHT1, GL_AMBIENT, WhiteLight);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, DifLight);
		glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight);

		glEnable(GL_FOG);

		sys->map->drawMap();
		for (int i = 0; i < 4; i++) {
			if (sys->player[i].hp > 0 && sys->player[i].chara != -1 && i != sys->myID) {
				drawHP3D(i);
			}
		}

		//draw character
		for (int i = 0; i < 4; i++) {
			if (sys->player[i].hp > 0) {
				if (sys->player[i].chara <= 3 && sys->player[i].chara > 0) {
					sys->model[sys->player[i].chara - 1].Draw(sys->player[i].x, sys->player[i].y, sys->player[i].z,
							sys->player[i].dir);

					if (sys->player[i].chara == 3) {
						glPushMatrix();
						glEnable(GL_TEXTURE_2D);
						glDisable(GL_BLEND);

						glDisable(GL_CULL_FACE);
						glTranslatef(sys->player[i].x, 0, sys->player[i].z);
						glRotatef(sys->player[i].dir * 360 / 6.28, 0.0f, 1.0f, 0.0f);
						glTranslatef(-sys->player[i].x, 0, -sys->player[i].z);
						glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, WhiteMaterial);
						glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, GrayMaterial);
						glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, WhiteMaterial);
						glMaterialf(GL_FRONT, GL_SHININESS, 60.0);

						GLfloat vertices[4][3] =
								{{sys->player[i].x - 0.15 ,0.85, sys->player[i].z },
								{ sys->player[i].x + 0.15 ,0.85  , sys->player[i].z },
								{ sys->player[i].x + 0.15 ,0.55  , sys->player[i].z },
								{ sys->player[i].x - 0.15 ,0.55, sys->player[i].z }, };
						glBindTexture(GL_TEXTURE_2D, *sys->faceImage[i]);
						glBegin(GL_POLYGON);
						//Normal3f(vertices[1], vertices[4], vertices[7]);
						glTexCoord2i(0, 0);
						glVertex3fv(vertices[0]);
						glTexCoord2i(0, 1);
						glVertex3fv(vertices[1]);
						glTexCoord2i(1, 1);
						glVertex3fv(vertices[2]);
						glTexCoord2i(1, 0);
						glVertex3fv(vertices[3]);
						glEnd();

						glEnable(GL_CULL_FACE);
						glPopMatrix();

					}
				}
			}
		}

		drawIndicator();

		for (int i = 0; i < MAX_EFFECT; i++) {
			if (sys->effect[i].f > 0) {
				sys->effect[i].draw();
			}
		}
		for (int i = 0; i < NUM_LIGHT_EFFECT; i++) {
			if (sys->lighteffect[i].f > 0) {
				sys->lighteffect[i].draw();
			}
		}
	}

	init2D();
	{
		drawHP(WINDOW_X - 150, 100, 100, 50);
		if (sys->player[sys->myID].hp <= 0)
			drawGameOver(100, 100, 800, 300);

		int judgeWin = 0;
		for (int i = 0; i < 4; i++) {
			if (i == sys->myID)
				continue;
			if (sys->player[i].chara != -1 && sys->player[i].hp > 0)
				judgeWin++;
		}
		if (judgeWin == 0) {
			int count = 0;
			for (int i = 0; i < 4; i++) {
				if (sys->player[i].chara == -1)
					count++;
			}
			if (count != 3)
				drawWin(100, 100, 800, 300);

		}
	}
	glFlush();
	SDL_GL_SwapBuffers();        //reflect swap
}

/*ゲームオーバーになった時の描画*/
void Draw::drawGameOver(int x, int y, int w, int h) {
	SDL_Color color = { 0, 0, 0 };
	SDL_Surface *tmp;
	string tmpstring = "GAME OVER";
	tmp = TTF_RenderUTF8_Blended(sys->font, tmpstring.c_str(), color);

	GLuint *tmpimage = sys->draw->timeTexture(tmp);
	glBindTexture( GL_TEXTURE_2D, *tmpimage);
	glBegin( GL_QUADS);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glTexCoord2i(0, 0);
	glVertex3f(x, y, 0);
	glTexCoord2i(1, 0);
	glVertex3f(x + w, y, 0);
	glTexCoord2i(1, 1);
	glVertex3f(x + w, y + h, 0);
	glTexCoord2i(0, 1);
	glVertex3f(x, y + h, 0);
	glEnd();
	glDeleteTextures(1, tmpimage);
}

/*勝利画面の描画*/
void Draw::drawWin(int x, int y, int w, int h) {
	SDL_Color color = { 0, 0, 0 };
	SDL_Surface *tmp;
	string tmpstring = "YOU WIN!";
	tmp = TTF_RenderUTF8_Blended(sys->font, tmpstring.c_str(), color);

	GLuint *tmpimage = sys->draw->timeTexture(tmp);
	glBindTexture( GL_TEXTURE_2D, *tmpimage);
	glBegin( GL_QUADS);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glTexCoord2i(0, 0);
	glVertex3f(x, y, 0);
	glTexCoord2i(1, 0);
	glVertex3f(x + w, y, 0);
	glTexCoord2i(1, 1);
	glVertex3f(x + w, y + h, 0);
	glTexCoord2i(0, 1);
	glVertex3f(x, y + h, 0);
	glEnd();
	glDeleteTextures(1, tmpimage);
}

/*HPバーの描画*/
void Draw::drawHP(int x, int y, int w, int h) {
	SDL_Color color = { 0, 0, 0 };
	SDL_Surface *tmp;
	if (sys->player[sys->myID].hp >= 60) {
		glBindTexture(GL_TEXTURE_2D, *texHandle[3]);
	} else if (sys->player[sys->myID].hp < 60 && sys->player[sys->myID].hp >= 30) {
		glBindTexture(GL_TEXTURE_2D, *texHandle[4]);
	} else if (sys->player[sys->myID].hp < 30) {
		glBindTexture(GL_TEXTURE_2D, *texHandle[5]);
	}

	glBegin(GL_QUADS);

	glTexCoord2i(0,0);
	glVertex3f(10,10,0);
	glTexCoord2i(1,0);
	glVertex3f(10+sys->player[sys->myID].hp*3,10,0);
	glTexCoord2i(1,1);
	glVertex3f(10+sys->player[sys->myID].hp*3,30,0);
	glTexCoord2i(0,1);
	glVertex3f(10,30,0);
	glEnd();

}

/*敵HPの描画*/
void Draw::drawHP3D(int i) {
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, WhiteMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, GrayMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, WhiteMaterial);
	glMaterialf(GL_FRONT, GL_SHININESS, 60.0);

	glTranslated(sys->player[i].x, 0, sys->player[i].z);
	glRotatef(sys->player[sys->myID].dir * 56.5, 0, 1, 0);
	glTranslated(-sys->player[i].x, 0, -sys->player[i].z);

	glTranslated(0.25, 0, 0);
	if (sys->player[i].hp >= 60) {
		glBindTexture(GL_TEXTURE_2D, *texHandle[3]);
	} else if (sys->player[i].hp < 60 && sys->player[i].hp >= 30) {
		glBindTexture(GL_TEXTURE_2D, *texHandle[4]);
	} else if (sys->player[i].hp < 30) {
		glBindTexture(GL_TEXTURE_2D, *texHandle[5]);
	}

	GLfloat vertices[4][3] = { { sys->player[i].x - sys->player[i].hp * 0.005, 0.8, sys->player[i].z }, {
			sys->player[i].x, 0.8, sys->player[i].z }, { sys->player[i].x, 0.75, sys->player[i].z }, { sys->player[i].x
			- sys->player[i].hp * 0.005, 0.75, sys->player[i].z }, };

	glBegin(GL_POLYGON);
	glTexCoord2i(0, 0);
	glVertex3fv(vertices[0]);
	glTexCoord2i(0, 1);
	glVertex3fv(vertices[1]);
	glTexCoord2i(1, 1);
	glVertex3fv(vertices[2]);
	glTexCoord2i(1, 0);
	glVertex3fv(vertices[3]);
	glEnd();

	glPopMatrix();
}

Draw::Draw() {

	sys->faceImage[0] = initTexture("data/image/dummy.bmp");
	sys->faceImage[1] = initTexture("data/image/dummy.bmp");
	sys->faceImage[2] = initTexture("data/image/dummy.bmp");
	sys->faceImage[3] = initTexture("data/image/dummy.bmp");

//system

	charaImage[0] = initTexture("data/image/chara1.bmp");
	charaImage[1] = initTexture("data/image/chara2.bmp");
	charaImage[2] = initTexture("data/image/chara3.bmp");
	charaImage[3] = initTexture("data/image/chara1g.bmp");
	charaImage[4] = initTexture("data/image/chara2g.bmp");
	charaImage[5] = initTexture("data/image/chara3g.bmp");

//initialize GLUT

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

//format to white
	glClearColor(1.0, 1.0, 1.0, 1.0);

//LoadTexture
	texHandle[0] = pngTexture("data/image/zimen.png");
	//texHandle[1] = initTexture("data/image/sky2.bmp");
	texHandle[2] = pngTexture("data/image/block.png");
	texHandle[3] = initTexture("data/image/hp.bmp");
	texHandle[4] = initTexture("data/image/hp2.bmp");
	texHandle[5] = initTexture("data/image/hp3.bmp");

	lightpos[0] = 0;
	lightpos[1] = 0;
	lightpos[2] = 0;
	lightpos[3] = 0;

	DifLight[0] = 0.4;
	DifLight[1] = 0.4;
	DifLight[2] = 0.4;
	DifLight[3] = 1.0;

	GrayMaterial[0] = 0.3;
	GrayMaterial[1] = 0.3;
	GrayMaterial[2] = 0.3;
	GrayMaterial[3] = 1;

	WhiteMaterial[0] = 0.8;
	WhiteMaterial[1] = 0.8;
	WhiteMaterial[2] = 0.8;
	WhiteMaterial[3] = 0.5;

	SpecularLight[0] = 1;
	SpecularLight[1] = 1;
	SpecularLight[2] = 1;
	SpecularLight[3] = 1;

	GrayLight[0] = 0.6;
	GrayLight[1] = 0.6;
	GrayLight[2] = 0.6;
	GrayLight[3] = 1;

	WhiteLight[0] = 1;
	WhiteLight[1] = 1;
	WhiteLight[2] = 1;
	WhiteLight[3] = 1.0;

	FogColor[0] = 0;
	FogColor[1] = 0;
	FogColor[2] = 0;
	FogColor[3] = 1;

}

Draw::~Draw() {
	TTF_CloseFont(font);
	TTF_Quit();
}

/*pngファイルの読み込み*/
GLuint *Draw::pngTexture(string name) {
	SDL_Surface *surface;
	SDL_RWops *rw;
	rw = SDL_RWFromFile(name.c_str(), "rb");
	surface = IMG_LoadPNG_RW(rw);
	glEnable( GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	GLuint *Handle;
	Handle = (GLuint *) malloc(sizeof(GLuint));
	glGenTextures(1, Handle);
	glBindTexture(GL_TEXTURE_2D, *Handle);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	gluBuild2DMipmaps( GL_TEXTURE_2D, 4, surface->w, surface->h, GL_RGBA,
	GL_UNSIGNED_BYTE, surface->pixels);
	if (surface) {
		SDL_FreeSurface(surface);
	}
	return Handle;
}

/*文字列の読み込み*/
GLuint * Draw::timeTexture(SDL_Surface * surface) {
	if (surface == NULL) {
		printf("timeTexture receice null surface\n");
		exit(-1);
	}
	glEnable( GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	GLint texColor;
	GLenum texFormat;
	GLuint *Handle;
	Handle = (GLuint *) malloc(sizeof(GLuint));
	texColor = surface->format->BytesPerPixel;
	if (texColor == 4) {
		if (surface->format->Rmask == 0x000000ff) {
			texFormat = GL_RGBA;
		} else {
			texFormat = GL_BGRA;
		}
	} else if (texColor == 3) {
		if (surface->format->Rmask == 0x000000ff) {
			texFormat = GL_RGB;
		} else {
			texFormat = GL_BGR;
		}
	}
	glGenTextures(1, Handle);
	glBindTexture(GL_TEXTURE_2D, *Handle);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D( GL_TEXTURE_2D, 0, texColor, surface->w, surface->h, 0, texFormat,
	GL_UNSIGNED_BYTE, surface->pixels);
	if (surface) {
		SDL_FreeSurface(surface);
	}
	return Handle;
}

/*bmpファイルの読み込み*/
GLuint *Draw::initTexture(string name) {
	glEnable( GL_TEXTURE_2D);
	SDL_Surface *surface;
	GLint texColor;
	GLenum texFormat;
	GLuint *Handle;
	Handle = (GLuint *) malloc(sizeof(GLuint));
	surface = SDL_LoadBMP(name.c_str());

	if (surface == NULL) {
		cout << "can't open " << name << endl;
		exit(-1);
	}
	texColor = surface->format->BytesPerPixel;
	if (texColor == 4) {
		if (surface->format->Rmask == 0x000000ff) {
			texFormat = GL_RGBA;
		} else {
			texFormat = GL_BGRA;
		}
	} else if (texColor == 3) {
		if (surface->format->Rmask == 0x000000ff) {
			texFormat = GL_RGB;
		} else {
			texFormat = GL_BGR;
		}
	}
	glGenTextures(1, Handle);
	glBindTexture(GL_TEXTURE_2D, *Handle);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D( GL_TEXTURE_2D, 0, texColor, surface->w, surface->h, 0, texFormat,
	GL_UNSIGNED_BYTE, surface->pixels);
	if (surface) {
		SDL_FreeSurface(surface);
	}
	return Handle;
}

/*キャラクター選択画面の描画*/
void Draw::drawCharaSelect() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	init3D();
	{
	}
	init2D();
	{
		//character1
		for (int i = 0; i < 3; i++) {
			if (sys->selChara == i + 1)
				glBindTexture( GL_TEXTURE_2D, *charaImage[i]);
			else
				glBindTexture( GL_TEXTURE_2D, *charaImage[i + 3]);
			
			glBegin( GL_QUADS);
			glTexCoord2i(0, 0);
			glVertex3f(200 * (i) + 120, 200, 0);
			glTexCoord2i(1, 0);
			glVertex3f(200 * (i + 1) + 100, 200, 0);
			glTexCoord2i(1, 1);
			glVertex3f(200 * (i + 1) + 100, 400, 0);
			glTexCoord2i(0, 1);
			glVertex3f(200 * (i) + 120, 400, 0);
			glEnd();
		}
	}
	glFlush();
	SDL_GL_SwapBuffers();
}

void Draw::drawCube(int x, int y) {
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, WhiteMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, GrayMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, WhiteMaterial);
	glMaterialf(GL_FRONT, GL_SHININESS, 60.0);

	GLfloat vertices[8][3] = { 
		{ 0 + x, 1.0, 0 + y }, 
		{ 1 + x, 1.0, 0 + y }, 
		{ 1 + x, 1.0, 1 + y },
		{ 0 + x, 1.0, 1 + y }, 
		{ 1 + x, 0.0, 0 + y }, 
		{ 0 + x, 0.0, 0 + y }, 
		{ 0 + x, 0.0, 1 + y }, 
		{ 1 + x, 0.0, 1 + y } 
	};

// 右
	glBegin(GL_POLYGON);
	Normal3f(vertices[1], vertices[4], vertices[7]);
	glTexCoord2i(0, 0);
	glVertex3fv(vertices[1]);
	glTexCoord2i(0, 1);
	glVertex3fv(vertices[4]);
	glTexCoord2i(1, 1);
	glVertex3fv(vertices[7]);
	glTexCoord2i(1, 0);
	glVertex3fv(vertices[2]);
	glEnd();
// 左
	glBegin(GL_POLYGON);
	Normal3f(vertices[5], vertices[0], vertices[3]);
	glTexCoord2i(0, 0);
	glVertex3fv(vertices[5]);
	glTexCoord2i(0, 1);
	glVertex3fv(vertices[0]);
	glTexCoord2i(1, 1);
	glVertex3fv(vertices[3]);
	glTexCoord2i(1, 0);
	glVertex3fv(vertices[6]);
	glEnd();
// 上
	glBegin(GL_POLYGON);
	Normal3f(vertices[3], vertices[2], vertices[7]);
	glTexCoord2i(1, 0);
	glVertex3fv(vertices[3]);
	glTexCoord2i(0, 0);
	glVertex3fv(vertices[2]);
	glTexCoord2i(0, 1);
	glVertex3fv(vertices[7]);
	glTexCoord2i(1, 1);
	glVertex3fv(vertices[6]);
	glEnd();
// 下
	glBegin(GL_POLYGON);
	Normal3f(vertices[1], vertices[0], vertices[5]);
	glTexCoord2i(1, 0);
	glVertex3fv(vertices[1]);
	glTexCoord2i(0, 0);
	glVertex3fv(vertices[0]);
	glTexCoord2i(0, 1);
	glVertex3fv(vertices[5]);
	glTexCoord2i(1, 1);
	glVertex3fv(vertices[4]);
	glEnd();
}
void Draw::Normal3f(GLfloat fVert1[], GLfloat fVert2[], GLfloat fVert3[]) {
	GLfloat Qx, Qy, Qz, Px, Py, Pz;

	Qx = fVert2[0] - fVert1[0];
	Qy = fVert2[1] - fVert1[1];
	Qz = fVert2[2] - fVert1[2];
	Px = fVert3[0] - fVert1[0];
	Py = fVert3[1] - fVert1[1];
	Pz = fVert3[2] - fVert1[2];

	glNormal3f(Py * Qz - Pz * Qy, Pz * Qx - Px * Qz, Px * Qy - Py * Qx);
}

/*2Dテクスチャの初期化*/
void Draw::init2D() {
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glViewport(0, 0, WINDOW_X, WINDOW_Y);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, WINDOW_X, WINDOW_Y, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

/*3D表示の初期化*/
void Draw::init3D() {
	glViewport(0, 0, WINDOW_X, WINDOW_Y);
//perspective
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(30.0, (GLdouble) WINDOW_X / (GLdouble) WINDOW_Y, 0.01, 210.0);

//fog
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogfv(GL_FOG_COLOR, FogColor);
	glFogf(GL_FOG_DENSITY, 0.5);
	glHint(GL_FOG_HINT, GL_DONT_CARE);
	glFogf(GL_FOG_START, 6);
	glFogf(GL_FOG_END, 22);
	glEnable(GL_FOG);

//z buffer
	glEnable(GL_DEPTH_TEST);

//CULLING
	glEnable(GL_CULL_FACE);

//to smooth
	glShadeModel(GL_SMOOTH);
}

/*地面の描画*/
void Draw::drawFloor(int x, int y) {
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, GrayMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, GrayMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, WhiteMaterial);
	glMaterialf(GL_FRONT, GL_SHININESS, 60.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glBindTexture(GL_TEXTURE_2D, *texHandle[0]);

	GLfloat vertices[4][3] = { { 1 + x, 0.0, 1 + y }, { 0 + x, 0.0, 1 + y }, { 0 + x, 0.0, 0 + y },
			{ 1 + x, 0.0, 0 + y }, };

	glBegin(GL_POLYGON);
	//glNormal3f(vertices[0][0], vertices[0][1], vertices[0][2]);
	glTexCoord2i(0, 0);
	glVertex3fv(vertices[0]);

	//glNormal3f(vertices[1][0], vertices[1][1], vertices[1][2]);
	glTexCoord2i(0, 1);
	glVertex3fv(vertices[1]);

	//glNormal3f(vertices[2][0], vertices[2][1], vertices[2][2]);
	glTexCoord2i(1, 1);
	glVertex3fv(vertices[2]);

	//glNormal3f(vertices[3][0], vertices[3][1], vertices[3][2]);
	glTexCoord2i(1, 0);
	glVertex3fv(vertices[3]);
	glEnd();
	glDisable(GL_CULL_FACE);
	glEnable(GL_FOG);
}

/*壁の描画*/
void Draw::drawWall(int x, int y) {
	int i;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, GrayMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, GrayMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, WhiteMaterial);
	glMaterialf(GL_FRONT, GL_SHININESS, 60.0);

	glDisable(GL_CULL_FACE);
//前
	glBindTexture(GL_TEXTURE_2D, *texHandle[2]);
	GLfloat vertices1[4][3] = { { 1 + x, 1.5, y }, { 0 + x, 1.5, y }, { 0 + x, 0, y }, { 1 + x, 0, y }, };
	glBegin(GL_POLYGON);
	//glNormal3f(vertices1[0][0], vertices1[0][1], vertices1[0][2]);
	glTexCoord2i(0, 0);
	glVertex3fv(vertices1[0]);

	//glNormal3f(vertices1[1][0], vertices1[1][1], vertices1[1][2]);
	glTexCoord2i(1, 0);
	glVertex3fv(vertices1[1]);

	//glNormal3f(vertices1[2][0], vertices1[2][1], vertices1[2][2]);
	glTexCoord2i(1, 1);
	glVertex3fv(vertices1[2]);

	//glNormal3f(vertices1[3][0], vertices1[3][1], vertices1[3][2]);
	glTexCoord2i(0, 1);
	glVertex3fv(vertices1[3]);
	glEnd();

//後ろ
	glBindTexture(GL_TEXTURE_2D, *texHandle[2]);
	GLfloat vertices2[4][3] =
			{ { 1 + x, 1.5, y + 1 }, { 0 + x, 1.5, y + 1 }, { 0 + x, 0, y + 1 }, { 1 + x, 0, y + 1 }, };
	glBegin(GL_POLYGON);
	//glNormal3f(vertices2[0][0], vertices2[0][1], vertices2[0][2]);
	glTexCoord2i(0, 0);
	glVertex3fv(vertices2[0]);

	//glNormal3f(vertices2[1][0], vertices2[1][1], vertices2[1][2]);
	glTexCoord2i(1, 0);
	glVertex3fv(vertices2[1]);

	//glNormal3f(vertices2[2][0], vertices2[2][1], vertices2[2][2]);
	glTexCoord2i(1, 1);
	glVertex3fv(vertices2[2]);

	//glNormal3f(vertices2[3][0], vertices2[3][1], vertices2[3][2]);
	glTexCoord2i(0, 1);
	glVertex3fv(vertices2[3]);
	glEnd();

//左
	glBindTexture(GL_TEXTURE_2D, *texHandle[2]);
	GLfloat vertices3[4][3] = { { x, 1.5, y + 1 }, { x, 1.5, 0 + y }, { x, 0, 0 + y }, { x, 0, 1 + y }, };
	glBegin(GL_POLYGON);
	//glNormal3f(vertices3[0][0], vertices3[0][1], vertices3[0][2]);
	glTexCoord2i(0, 0);
	glVertex3fv(vertices3[0]);

	//glNormal3f(vertices3[1][0], vertices3[1][1], vertices3[1][2]);
	glTexCoord2i(1, 0);
	glVertex3fv(vertices3[1]);

	//glNormal3f(vertices3[2][0], vertices3[2][1], vertices3[2][2]);
	glTexCoord2i(1, 1);
	glVertex3fv(vertices3[2]);

	//glNormal3f(vertices3[3][0], vertices3[3][1], vertices3[3][2]);
	glTexCoord2i(0, 1);
	glVertex3fv(vertices3[3]);
	glEnd();

//右
	glBindTexture(GL_TEXTURE_2D, *texHandle[2]);
	GLfloat vertices4[4][3] =
			{ { 1 + x, 1.5, 1 + y }, { 1 + x, 1.5, 0 + y }, { 1 + x, 0, 0 + y }, { 1 + x, 0, 1 + y }, };
	glBegin(GL_POLYGON);
	glNormal3f(vertices4[0][0], vertices4[0][1], vertices4[0][2]);
	glTexCoord2i(0, 0);
	glVertex3fv(vertices4[0]);

	//glNormal3f(vertices4[1][0], vertices4[1][1], vertices4[1][2]);
	glTexCoord2i(1, 0);
	glVertex3fv(vertices4[1]);

	//glNormal3f(vertices4[2][0], vertices4[2][1], vertices4[2][2]);
	glTexCoord2i(1, 1);
	glVertex3fv(vertices4[2]);

	//glNormal3f(vertices4[3][0], vertices4[3][1], vertices4[3][2]);
	glTexCoord2i(0, 1);
	glVertex3fv(vertices4[3]);
	glEnd();

	//上
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glBindTexture(GL_TEXTURE_2D, *texHandle[2]);
	GLfloat vertices5[4][3] = { { 0 + x, 1.5, 1 + y }, { 1 + x, 1.5, 1 + y }, { 1 + x, 1.5, 0 + y },
			{ 0 + x, 1.5, 0 + y }, };
	glBegin(GL_POLYGON);
	glTexCoord2i(0, 0);
	glVertex3fv(vertices5[0]);

	glTexCoord2i(1, 0);
	glVertex3fv(vertices5[1]);

	glTexCoord2i(1, 1);
	glVertex3fv(vertices5[2]);

	glTexCoord2i(0, 1);
	glVertex3fv(vertices5[3]);
	glEnd();

}

void Draw::drawCylinder(int div, float r, float h) {
	int i;
	double degree;
	float x, z;

	degree = 360 / div;
	for (i = 0; i < div; i++) {
		glBegin(GL_QUADS);
		{
			double temp = degree * i / 180.0 * PI;
			x = r * sin(temp);
			z = r * cos(temp);
			glTexCoord2i(0, 0);
			glVertex3f(x, h, z);
			glTexCoord2i(0, 1);
			glVertex3f(x, 0.0f, z);

			temp = degree * (i + 1) / 180.0 * PI;
			x = r * sin(temp);
			z = r * cos(temp);
			glTexCoord2i(1, 1);
			glVertex3f(x, 0.0f, z);
			glTexCoord2i(1, 0);
			glVertex3f(x, h, z);
		}
		glEnd();
	}
}

void Draw::drawIndicator() {
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_BLEND);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, sys->draw->WhiteMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, sys->draw->GrayMaterial);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, sys->draw->WhiteMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, sys->draw->WhiteMaterial);
	glMaterialf(GL_FRONT, GL_SHININESS, 60);
	for (int i = 0; i < 4; i++) {
		if (i == sys->myID || sys->player[i].chara <= 0)
			continue;

		double dis = 4
				* sqrt(
						(sys->player[i].x - sys->player[sys->myID].x) * (sys->player[i].x - sys->player[sys->myID].x)
								+ (sys->player[i].z - sys->player[sys->myID].z)
										* (sys->player[i].z - sys->player[sys->myID].z));

		glPushMatrix();
		glTranslatef((sys->player[i].x - sys->player[sys->myID].x) / dis + sys->player[sys->myID].x, 0.5,
				(sys->player[i].z - sys->player[sys->myID].z) / dis + sys->player[sys->myID].z);
		//cout<<dis<<"  "<<sys->player[i].x/dis + sys->player[i].x <<"  "<< sys->player[i].z/dis + sys->player[i].z<<endl;

		glBegin(GL_POLYGON);
		glutSolidSphere(0.01, 4, 4);
		glEnd();
		glPopMatrix();

	}

}

