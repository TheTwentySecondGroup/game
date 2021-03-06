/*
 * Title.cpp
 *
 *  last update 2015/02/12
 *      Author: Murokawa,Takeda
 */
#include "global.h"
#include "draw.h"
#include "Title.h"
#include "Tutorial.h"
#include "system.h"
#include "io.h"
using namespace std;

Title::Title() {

	menuString[0] = "START";

	menuString[1] = "CONFIG";

	menuString[2] = "EXIT";

	sel = 1;
	KeyFlag = 0;



	SDL_Color color1 = { 255, 255, 0 };
	SDL_Color color2 = { 255, 255, 255 };
	//titleImage[0] = sys->draw->pngTexture("data/image/title.png");

	SDL_Surface *tmp1, *tmp2, *tmp3, *tmp4, *tmp5, *tmp6, *tmp7;
	tmp1 = TTF_RenderUTF8_Blended(sys->font, "1 VS 1", color1);
	titleImage[1] = sys->draw->timeTexture(tmp1);
	tmp2 = TTF_RenderUTF8_Blended(sys->font, "2 VS 2", color1);
	titleImage[2] = sys->draw->timeTexture(tmp2);
	tmp3 = TTF_RenderUTF8_Blended(sys->font, "BATTLE ROYAL", color1);
	titleImage[3] = sys->draw->timeTexture(tmp3);
	tmp4 = TTF_RenderUTF8_Blended(sys->font, "1 VS 1", color2);
	titleImage[4] = sys->draw->timeTexture(tmp4);
	tmp5 = TTF_RenderUTF8_Blended(sys->font, "2 VS 2", color2);
	titleImage[5] = sys->draw->timeTexture(tmp5);
	tmp6 = TTF_RenderUTF8_Blended(sys->font, "BATTLE ROYAL", color2);
	titleImage[6] = sys->draw->timeTexture(tmp6);
}

Title::~Title() {
	glDeleteTextures(6, *titleImage);

}

/*メニューの表示*/
void Title::drawMenu(int x, int y, int w, int h, string mes) {
	SDL_Color color = { 0, 0, 0 };
	SDL_Surface *tmp;
	tmp = TTF_RenderUTF8_Blended(sys->font, mes.c_str(), color);

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
/*
void Title::drawMenuCube(int x, int y, GLuint *texture, double sw) {
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, sys->draw->WhiteMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, sys->draw->WhiteMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, sys->draw->WhiteMaterial);
	glMaterialf(GL_FRONT, GL_SHININESS, 60.0);

	glBindTexture( GL_TEXTURE_2D, *texture);

	GLfloat vertices[4][3] = { { 1, 2.5 - x, sw + y }, { 1, 1.5 - x, sw + y }, { 2, 1.5 - x, sw + y }, { 2, 2.5 - x, sw
			+ y }, };
	glBegin(GL_POLYGON);
	glNormal3f(sys->player[0].xd, sys->player[0].yd, 0);
	glTexCoord2i(0, 0);
	glVertex3fv(vertices[0]);
	glTexCoord2i(0, 1);
	glVertex3fv(vertices[1]);
	glTexCoord2i(1, 1);
	glVertex3fv(vertices[2]);
	glTexCoord2i(1, 0);
	glVertex3fv(vertices[3]);
	glEnd();
}
*/
void Title::routine() {

	if ((sys->io->key[KEY_UP] == 1)) {
		if (sel > CHOICE_MIN)
			sel -= 1;
	}
	if ((sys->io->key[KEY_DOWN] == 1)) {
		if (sel < CHOICE_MAX)
			sel += 1;
	}
	if (sys->io->key[KEY_A] > 1) {
		if (sel == 3) {
			exit(EXIT_FAILURE);
		} else if (sel == 1) {
			sys->Stage = -2;
		} else if (sel == 2) {
			sys->Stage = 5;
		}
	}

	drawTitle();
	SDL_Delay(1000 / 60);
}

/*タイトル画面の描画*/
void Title::drawTitle() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	sys->draw->init3D();
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		double xd = sin(0);
		double zd = cos(0);

		gluLookAt(sys->lighteffect[0].posX - xd * 2,   1,
				sys->lighteffect[0].posY - zd * 2, // position of camera
				sys->lighteffect[0].posX,   0, sys->lighteffect[0].posY, //look-at point
				0, 1.0f, 0);

		//Light
		glEnable(GL_LIGHTING);
		glEnable(GL_NORMALIZE);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT1);

		//light1
		sys->draw->lightpos[0] = sys->lighteffect[0].posX;
		sys->draw->lightpos[1] = 5;
		sys->draw->lightpos[2] = sys->lighteffect[0].posY;
		sys->draw->lightpos[3] = 1;

		glLightfv(GL_LIGHT1, GL_POSITION, sys->draw->lightpos);
		GLfloat Light1Dir[] = { 0, -1, 0 };
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Light1Dir);
		glLightf( GL_LIGHT1, GL_SPOT_CUTOFF, 80.0f);
		glLightf( GL_LIGHT1, GL_SPOT_EXPONENT, 10.0f);
		glLightfv(GL_LIGHT1, GL_AMBIENT, sys->draw->WhiteLight);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, sys->draw->DifLight);
		glLightfv(GL_LIGHT1, GL_SPECULAR, sys->draw->SpecularLight);

		sys->map->drawMap();

		for (int i = 0; i < NUM_LIGHT_EFFECT; i++) {
			if (sys->lighteffect[i].f > 0) {
				sys->lighteffect[i].draw();
			}
		}
	}
	sys->draw->init2D();
	{

		drawMenu(100, 200, 600, 200, "Calamity");

		int c;
		for (c = 1; c <= CHOICE_MAX; c++) {
			//draw on button
			string tmp;
			if (sel == c)
				tmp += "->";
			else
				tmp += "    ";

			tmp += menuString[c - 1];

			drawMenu(700, 300 + c * 100, 200, 80, tmp);
		}

	}

	glFlush();
	SDL_GL_SwapBuffers();

}

