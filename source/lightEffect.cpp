/*
 * lightEffect.cpp
 *
 *  last update 2015/02/12
 *      Author: Takeda
 */

#include "global.h"
#include "lightEffect.h"
#include "draw.h"
#include "Map.h"
#include "Title.h"
#include "system.h"

lightEffect::lightEffect() {
	//srand(time(NULL));
	f = 0;
	for (int i = 0; i < MAX_LIGHT_EFFECT; i++) {
		count[i] = 0;
		x[i] = -1.0;
		y[i] = -1.0;
		z[i] = -1.0;
		dx[i] = ((double) (100 - rand() % 200)) / 20000.0;
		dy[i] = ((double) (rand() % 100 + 40)) / 5000.0;
		dz[i] = ((double) (100 - rand() % 200)) / 20000.0;

	}
}

void lightEffect::routine() {

	for (int i = 0; i < MAX_LIGHT_EFFECT; i++) {

		if (count[i] >= LIGHT_COUNT || y[i] < 0) {
			count[i] = 0;
			x[i] = z[i] = 0;
			y[i] = 0;
			dx[i] = ((double) (100 - rand() % 200)) / 20000.0;
			dy[i] = ((double) (rand() % 100 + 40)) / 5000.0;
			dz[i] = ((double) (100 - rand() % 200)) / 20000.0;
		} else {
			static float g = 0.0005;
			//static float g = 0.0;
			x[i] += dx[i];
			dy[i] -=  g;
			y[i] +=  dy[i];
			z[i] +=  dz[i];
			count[i]++;
		}

	}
}

void lightEffect::draw() {

	glEnable(GL_BLEND);
	glDisable(GL_FOG);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, sys->draw->WhiteMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, sys->draw->GrayMaterial);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, sys->draw->WhiteMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, sys->draw->WhiteMaterial);
	glMaterialf(GL_FRONT, GL_SHININESS, 60);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	for (int i = 0; i < MAX_LIGHT_EFFECT; i++) {
		glPushMatrix();
		glTranslatef(x[i] + posX, y[i], z[i] + posY);
		glBegin(GL_POLYGON);
		glutSolidSphere(0.01, 4, 4);
		//cout <<i<<" "<<x[i] + posX<<" "<<y[i]<<" "<< z[i] + posY<<endl;
		glEnd();
		glPopMatrix();
	}
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, sys->draw->FogColor);
	glDisable(GL_BLEND);

	glEnable(GL_FOG);
}
