#include "global.h"
#include "Effect.h"
#include "draw.h"
#include "Map.h"
#include "Title.h"
#include "system.h"

Effect::Effect() {
	count = 0;
	f = 0;
	x = -1.0;
	y = -1.0;
	z = -1.0;
	dx = 0;
	dz = 0;
	r = 0;
	fromPlayerID = 0;

	effectImage[0] = sys->draw->initTexture("data/image/beam.bmp");
	effectImage[1] = sys->draw->initTexture("data/image/star1.bmp");
	effectImage[2] = sys->draw->initTexture("data/image/mist.bmp");
	effectImage[3] = sys->draw->initTexture("data/image/fire.bmp");
	effectImage[4] = sys->draw->initTexture("data/image/thunder.bmp");
	effectImage[5] = sys->draw->initTexture("data/image/star2.bmp");
	effectImage[6] = sys->draw->initTexture("data/image/star3.bmp");
	effectImage[7] = sys->draw->initTexture("data/image/ice.bmp");
	effectImage[8] = sys->draw->initTexture("data/image/star4.bmp");
	effectImage[9] = sys->draw->initTexture("data/image/sword.bmp");
}

void Effect::routine() {
	//if(fromPlayerID == sys->myID)

	if (f > 0) {
		//dir+=0.1;
		count++;
		if (count >= 500) {
			cout << sys->player[sys->myID].x << endl;
			cout << sys->player[sys->myID].z << endl;
			cout << x << endl;
			cout << z << endl;
			cout << dir*56.5 << endl;
			sys->player[sys->myID].attflag = 0;
			count = 0;
			f = 0;
			x = -1;
			y = -1;
			z = -1;
			dir=0;
			return;
		}
	}
}

void Effect::draw(){
	if(f==1)drawAttack();
	else if(f==2)drawAttack2();
	else if(f==3)drawAttack3();
	else if(f==4)drawAttack4();
	else if(f==5)drawAttack5();
	else if(f==6)drawAttack6();
	else if(f==7)drawAttack7();

}

void Effect::drawAttack() {
	glMaterialf(GL_FRONT, GL_SHININESS, 60.0);

	glBindTexture(GL_TEXTURE_2D, *effectImage[1]);

	glTranslatef(x, 0, z);
	glRotated(r, 0.0, 1.0, 0.0);
	glTranslatef(-x, 0, -z);

	GLfloat vertices[4][3] = {
	    { x + 2, 0.1, z + 2 },
        { x - 2, 0.1, z + 2 },
        { x - 2, 0.1, z - 2},
        { x + 2, 0.1, z - 2},
    };
	glBegin(GL_POLYGON);
	glNormal3f(sys->player[sys->myID].xd, sys->player[sys->myID].yd, 0);
	glTexCoord2i(0, 0);
	glVertex3fv(vertices[0]);
	glTexCoord2i(0, 1);
	glVertex3fv(vertices[1]);
	glTexCoord2i(1, 1);
	glVertex3fv(vertices[2]);
	glTexCoord2i(1, 0);
	glVertex3fv(vertices[3]);
	glEnd();

    glBindTexture(GL_TEXTURE_2D, *effectImage[2]);
	{
        GLfloat vertices2[4][3] = {
            { x + 2, 1.5, z + 2 },
            { x - 2, 1.5, z + 2 },
            { x - 2, 0.3, z + 2 },
            { x + 2, 0.3, z + 2 },
        };
        glBegin(GL_POLYGON);
        glNormal3f(sys->player[sys->myID].xd, sys->player[sys->myID].yd, 0);
        glTexCoord2i(0, 0);
        glVertex3fv(vertices2[0]);
        glTexCoord2i(0, 1);
        glVertex3fv(vertices2[1]);
        glTexCoord2i(1, 1);
        glVertex3fv(vertices2[2]);
        glTexCoord2i(1, 0);
        glVertex3fv(vertices2[3]);
        glEnd();
	}

	glBindTexture(GL_TEXTURE_2D, *effectImage[2]);
	{
        GLfloat vertices3[4][3] = {
            { x + 2, 1.5, z - 2 },
            { x - 2, 1.5, z - 2 },
            { x - 2, 0.3, z - 2 },
            { x + 2, 0.3, z - 2 },
        };
        glBegin(GL_POLYGON);
        glNormal3f(sys->player[sys->myID].xd, sys->player[sys->myID].yd, 0);
        glTexCoord2i(0, 0);
        glVertex3fv(vertices3[0]);
        glTexCoord2i(0, 1);
        glVertex3fv(vertices3[1]);
        glTexCoord2i(1, 1);
        glVertex3fv(vertices3[2]);
        glTexCoord2i(1, 0);
        glVertex3fv(vertices3[3]);
        glEnd();
	}

	glBindTexture(GL_TEXTURE_2D, *effectImage[2]);
	GLfloat vertices4[4][3] = {
	    { x - 2, 1.5, z + 2 },
	    { x - 2, 1.5, z - 2 },
	    { x - 2, 0.3, z - 2},
	    { x - 2, 0.3, z + 2 },
    };
	glBegin(GL_POLYGON);
	glNormal3f(sys->player[sys->myID].xd, sys->player[sys->myID].yd, 0);
	glTexCoord2i(0, 0);
	glVertex3fv(vertices4[0]);
	glTexCoord2i(0, 1);
	glVertex3fv(vertices4[1]);
	glTexCoord2i(1, 1);
	glVertex3fv(vertices4[2]);
	glTexCoord2i(1, 0);
	glVertex3fv(vertices4[3]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, *effectImage[2]);
	GLfloat vertices5[4][3] = {
	    { x + 2, 1.5, z + 2 },
	    { x + 2, 1.5, z - 2 },
        { x + 2, 0.3, z - 2},
        { x + 2, 0.3, z + 2 },
    };
	glBegin(GL_POLYGON);
	glNormal3f(sys->player[sys->myID].xd, sys->player[sys->myID].yd, 0);
	glTexCoord2i(0, 0);
	glVertex3fv(vertices5[0]);
	glTexCoord2i(0, 1);
	glVertex3fv(vertices5[1]);
	glTexCoord2i(1, 1);
	glVertex3fv(vertices5[2]);
	glTexCoord2i(1, 0);
	glVertex3fv(vertices5[3]);
	glEnd();

	if ((r += 20) >= 360)   r = 0;
}

void Effect::drawAttack2() {

	glMaterialf(GL_FRONT, GL_SHININESS, 60.0);

	glDisable(GL_CULL_FACE);

	glTranslatef(x , 0.0, z );
	glRotated(dir*56.5, 0.0, 1.0, 0.0);
	glTranslatef(-x, 0.0, -z);
	if(count >= 20){
		glBindTexture(GL_TEXTURE_2D, *effectImage[3]);
		{
			glPushMatrix();
			glTranslatef(x, 0.5, z+2.5);
			glRotated(90, 0.0, 1.0, 0.0);
			glutSolidSphere(0.1, 20, 10);
			glPopMatrix();
		}
	}
	if(count >= 30){
		glBindTexture(GL_TEXTURE_2D, *effectImage[3]);
		{
			glPushMatrix();
			glTranslatef(x-0.5, 0.5, z+2.5);
			glRotated(90, 1.0, 0.0, 0.0);
			glutSolidSphere(0.1, 20, 10);
			glPopMatrix();
		}
	}
	if(count >= 40){
		glBindTexture(GL_TEXTURE_2D, *effectImage[3]);
		{
			glPushMatrix();
			glTranslatef(x+0.5, 0.5, z+2.5);
			glRotated(90, 1.0, 0.0, 0.0);
			glutSolidSphere(0.1, 20, 10);
			glPopMatrix();
		}
	}	
	if(count <= 50){
		glBindTexture(GL_TEXTURE_2D, *effectImage[8]);
		{
			GLfloat vertices1[4][3] = {
			    { x + 0.5, 1.0, z },
			    { x - 0.5, 1.0, z },
			    { x - 0.5, 0.0, z },
			    { x + 0.5, 0.0, z },
			};
    
			glBegin(GL_POLYGON);
			glNormal3f(vertices1[0][0], vertices1[0][1], vertices1[0][2]);
			glTexCoord2i(0, 0);
			glVertex3fv(vertices1[0]);

			glNormal3f(vertices1[1][0], vertices1[1][1], vertices1[1][2]);
			glTexCoord2i(0, 1);
			glVertex3fv(vertices1[1]);

			glNormal3f(vertices1[2][0], vertices1[2][1], vertices1[2][2]);
			glTexCoord2i(1, 1);
			glVertex3fv(vertices1[2]);

			glNormal3f(vertices1[3][0], vertices1[3][1], vertices1[3][2]);
			glTexCoord2i(1, 0);
			glVertex3fv(vertices1[3]);
			glEnd();
		}
	}
	if(count >= 50){
		z+=cos(dir)/3;
		x+=sin(dir)/3;
	}

}

void Effect::drawAttack3() {
	glEnable(GL_BLEND);
	glMaterialf(GL_FRONT, GL_SHININESS, 60.0);

	glDisable(GL_CULL_FACE);
	
	glTranslatef(x , 0.0, z );
	glRotated(dir*56.5, 0.0, 1.0, 0.0);
	glTranslatef(-x, 0.0, -z);

    if(count >= 200){
        glBindTexture(GL_TEXTURE_2D, *effectImage[0]);
        {
            GLfloat vertices2[4][3] = {
                { x, 1.1, z + 15 },
                { x + 0.6, 0.5, z + 15 },
                { x + 0.6, 0.5, z + 2 },
                { x, 1.1, z + 2 },
            };

            glBegin(GL_POLYGON);
            glTexCoord2i(0, 0);
            glVertex3fv(vertices2[0]);
            glTexCoord2i(0, 1);
            glVertex3fv(vertices2[1]);
            glTexCoord2i(1, 1);
            glVertex3fv(vertices2[2]);
            glTexCoord2i(1, 0);
            glVertex3fv(vertices2[3]);
            glEnd();
        }

        glBindTexture(GL_TEXTURE_2D, *effectImage[0]);
        {
            GLfloat vertices3[4][3] = {
                { x, 1.1, z + 15 },
                { x - 0.6, 0.5, z + 15 },
                { x - 0.6, 0.5, z + 2 },
                { x, 1.1, z + 2 },
            };

            glBegin(GL_POLYGON);
            glTexCoord2i(0, 0);
            glVertex3fv(vertices3[0]);
            glTexCoord2i(0, 1);
            glVertex3fv(vertices3[1]);
            glTexCoord2i(1, 1);
            glVertex3fv(vertices3[2]);
            glTexCoord2i(1, 0);
            glVertex3fv(vertices3[3]);
            glEnd();
        }

        glBindTexture(GL_TEXTURE_2D, *effectImage[0]);
        {
            GLfloat vertices4[4][3] = {
                { x + 0.6, 0.5, z + 15 },
                { x, 0, z + 15 },
                { x, 0, z + 2 },
                { x + 0.6, 0.5, z + 2 },
            };

            glBegin(GL_POLYGON);
            glTexCoord2i(0, 0);
            glVertex3fv(vertices4[0]);
            glTexCoord2i(0, 1);
            glVertex3fv(vertices4[1]);
            glTexCoord2i(1, 1);
            glVertex3fv(vertices4[2]);
            glTexCoord2i(1, 0);
            glVertex3fv(vertices4[3]);
            glEnd();
        }

        glBindTexture(GL_TEXTURE_2D, *effectImage[0]);
        {
            GLfloat vertices5[4][3] = {
                { x - 0.6, 0.5, z + 15 },
                { x, 0, z + 15 },
                { x, 0, z + 2 },
                { x - 0.6, 0.5, z + 2 },
            };

            glBegin(GL_POLYGON);
            glTexCoord2i(0, 0);
            glVertex3fv(vertices5[0]);
            glTexCoord2i(0, 1);
            glVertex3fv(vertices5[1]);
            glTexCoord2i(1, 1);
            glVertex3fv(vertices5[2]);
            glTexCoord2i(1, 0);
            glVertex3fv(vertices5[3]);
            glEnd();
        }
    }
   	glTranslatef(x, 0.5, 0);
	glRotated(r, 0.0, 0.0, 1.0);
	glTranslatef(-x, -0.5, 0);

	glBindTexture(GL_TEXTURE_2D, *effectImage[1]);
	{
		GLfloat vertices1[4][3] = {
		    { x + 0.5, 1, z },
            { x - 0.5, 1, z },
            { x - 0.5, 0, z },
            { x + 0.5, 0, z },
        };
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        glColor4f(1.0, 1.0, 1.0, 0.5);
		glBegin(GL_POLYGON);
		glTexCoord2i(0, 0);
		glVertex3fv(vertices1[0]);
		glTexCoord2i(0, 1);
		glVertex3fv(vertices1[1]);
		glTexCoord2i(1, 1);
		glVertex3fv(vertices1[2]);
		glTexCoord2i(1, 0);
		glVertex3fv(vertices1[3]);
		glEnd();
	}

	glDisable(GL_BLEND);
//r=0;
	if ((r+=15) >= 360) r = 0;

}

void Effect::drawAttack4(){
    glTranslatef(x, 0, z);
	glRotated(r, 0.0, 1.0, 0.0);
	glTranslatef(-x, 0, -z);

       if(count >= 200 && count%2 == 0){
        glBindTexture(GL_TEXTURE_2D, *effectImage[4]);
        {
            GLfloat vertices1[4][3] = {
				{ x + 2, 1.5, z + 2 },
				{ x - 2, 1.5, z + 2 },
                { x - 2, 0.3, z + 2 },
                { x + 2, 0.3, z + 2 },
            };

            glBegin(GL_POLYGON);
            glTexCoord2i(0, 0);
            glVertex3fv(vertices1[0]);
            glTexCoord2i(0, 1);
            glVertex3fv(vertices1[1]);
            glTexCoord2i(1, 1);
            glVertex3fv(vertices1[2]);
            glTexCoord2i(1, 0);
            glVertex3fv(vertices1[3]);
            glEnd();
        }

        glBindTexture(GL_TEXTURE_2D,*effectImage[4]);
        {
            GLfloat vertices1[4][3] = {
                { x + 2, 1.5, z - 2 },
                { x - 2, 1.5, z - 2  },
                { x - 2, 0.3, z - 2 },
                { x + 2, 0.3, z - 2 },
            };
            glBegin(GL_POLYGON);
            glTexCoord2i(0, 0);
            glVertex3fv(vertices1[0]);
            glTexCoord2i(0, 1);
            glVertex3fv(vertices1[1]);
            glTexCoord2i(1, 1);
            glVertex3fv(vertices1[2]);
            glTexCoord2i(1, 0);
            glVertex3fv(vertices1[3]);
            glEnd();
        }

        glBindTexture(GL_TEXTURE_2D,*effectImage[4]);
        {
            GLfloat vertices1[4][3] = {
                { x - 2, 1.5, z + 2 },
                { x - 2, 1.5, z - 2 },
                { x - 2, 0.3, z - 2},
                { x - 2, 0.3, z + 2 },
            };
            glBegin(GL_POLYGON);
            glTexCoord2i(0, 0);
            glVertex3fv(vertices1[0]);
            glTexCoord2i(0, 1);
            glVertex3fv(vertices1[1]);
            glTexCoord2i(1, 1);
            glVertex3fv(vertices1[2]);
            glTexCoord2i(1, 0);
            glVertex3fv(vertices1[3]);
            glEnd();
        }

        glBindTexture(GL_TEXTURE_2D,*effectImage[4]);
        {
            GLfloat vertices1[4][3] = {
                { x + 2, 1.5, z + 2 },
                { x + 2, 1.5, z - 2 },
                { x + 2, 0.3, z - 2 },
                { x + 2, 0.3, z + 2 },
            };
            glBegin(GL_POLYGON);
            glTexCoord2i(0, 0);
            glVertex3fv(vertices1[0]);
            glTexCoord2i(0, 1);
            glVertex3fv(vertices1[1]);
            glTexCoord2i(1, 1);
            glVertex3fv(vertices1[2]);
            glTexCoord2i(1, 0);
            glVertex3fv(vertices1[3]);
            glEnd();
        }
    }

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);


	 glBindTexture(GL_TEXTURE_2D, *effectImage[5]);
	{
		GLfloat vertices1[4][3] = {
		    { x + 2, 0.1, z + 2 },
            { x - 2, 0.1, z + 2 },
            { x - 2, 0.1, z - 2},
            { x + 2, 0.1, z - 2},
        };
		 glBlendFunc(GL_SRC_ALPHA, GL_ONE);

		glBegin(GL_POLYGON);
		glTexCoord2i(0, 0);
		glVertex3fv(vertices1[0]);
		glTexCoord2i(0, 1);
		glVertex3fv(vertices1[1]);
		glTexCoord2i(1, 1);
		glVertex3fv(vertices1[2]);
		glTexCoord2i(1, 0);
		glVertex3fv(vertices1[3]);
		glEnd();
	}
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);


    if((r += 15) >= 360)   r = 0;
}

void Effect::drawAttack5(){
/*
    if(x == -1 && z == -1){
           // x = px;
            //z = pz;
            //r = dir*60;
    }
*/
    glTranslatef(x, 0, z);
	glRotated(r, 0.0, 1.0, 0.0);
	glTranslatef(-x, 0, -z);

    glBindTexture(GL_TEXTURE_2D, *effectImage[6]);
	{
		GLfloat vertices1[4][3] = {
		    { x + 2, 0.1, z + 2 },
			{ x - 2, 0.1, z + 2 },
            { x - 2, 0.1, z - 2},
            { x + 2, 0.1, z - 2},
        };

		glBegin(GL_POLYGON);
		glTexCoord2i(0, 0);
		glVertex3fv(vertices1[0]);
		glTexCoord2i(0, 1);
		glVertex3fv(vertices1[1]);
		glTexCoord2i(1, 1);
		glVertex3fv(vertices1[2]);
		glTexCoord2i(1, 0);
		glVertex3fv(vertices1[3]);
		glEnd();
	}

	glBindTexture(GL_TEXTURE_2D, *effectImage[7]);
	{
	    GLfloat vertices2[4][3] = {
	        { x + 2, 1.5, z + 3 },
            { x - 2, 1.5, z + 3 },
            { x - 2, 0.3, z + 1 },
            { x + 2, 0.3, z + 1 },
        };
        glBegin(GL_POLYGON);
		glTexCoord2i(0, 0);
		glVertex3fv(vertices2[0]);
		glTexCoord2i(0, 1);
		glVertex3fv(vertices2[1]);
		glTexCoord2i(1, 1);
		glVertex3fv(vertices2[2]);
		glTexCoord2i(1, 0);
		glVertex3fv(vertices2[3]);
		glEnd();
	}

	glBindTexture(GL_TEXTURE_2D, *effectImage[7]);
	{
	    GLfloat vertices3[4][3] = {
            { x + 2, 1.5, z - 3 },
            { x - 2, 1.5, z - 3 },
            { x - 2, 0.3, z - 1 },
            { x + 2, 0.3, z - 1 },
        };
        glBegin(GL_POLYGON);
		glTexCoord2i(0, 0);
		glVertex3fv(vertices3[0]);
		glTexCoord2i(0, 1);
		glVertex3fv(vertices3[1]);
		glTexCoord2i(1, 1);
		glVertex3fv(vertices3[2]);
		glTexCoord2i(1, 0);
		glVertex3fv(vertices3[3]);
		glEnd();
	}

	glBindTexture(GL_TEXTURE_2D, *effectImage[7]);
	{
	    GLfloat vertices4[4][3] = {
	        { x - 3, 1.5, z + 2 },
            { x - 3, 1.5, z - 2 },
            { x - 1, 0.3, z - 2},
            { x - 1, 0.3, z + 2 },
        };
        glBegin(GL_POLYGON);
		glTexCoord2i(0, 0);
		glVertex3fv(vertices4[0]);
		glTexCoord2i(0, 1);
		glVertex3fv(vertices4[1]);
		glTexCoord2i(1, 1);
		glVertex3fv(vertices4[2]);
		glTexCoord2i(1, 0);
		glVertex3fv(vertices4[3]);
		glEnd();
	}

	glBindTexture(GL_TEXTURE_2D, *effectImage[7]);
	{
	    GLfloat vertices5[4][3] = {
            { x + 3, 1.5, z + 2 },
            { x + 3, 1.5, z - 2 },
            { x + 1, 0.3, z - 2 },
            { x + 1, 0.3, z + 2 },
        };
        glBegin(GL_POLYGON);
		glTexCoord2i(0, 0);
		glVertex3fv(vertices5[0]);
		glTexCoord2i(0, 1);
		glVertex3fv(vertices5[1]);
		glTexCoord2i(1, 1);
		glVertex3fv(vertices5[2]);
		glTexCoord2i(1, 0);
		glVertex3fv(vertices5[3]);
		glEnd();
	}

	if((r += 10) >= 360)   r = 0;

}

void Effect::drawAttack6(){
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glMaterialf(GL_FRONT, GL_SHININESS, 60.0);

	glDisable(GL_CULL_FACE);

	glTranslatef(x , 0.0, z );
	glRotated(dir*56.5, 0.0, 1.0, 0.0);
	glTranslatef(-x, 0.0, -z);

/*
	glTranslatef(x, 0.6, 0);
	glRotated(r, 0.0, 0.0, 1.0);
	glTranslatef(-x, -0.6, 0);	
*/	
	glDisable(GL_DEPTH_TEST);

	glBindTexture(GL_TEXTURE_2D, *effectImage[6]);
	{
		GLfloat vertices2[4][3] = {
			{ x + 0.5, 1.1, z + 1 },
           	{ x - 0.5, 1.1, z + 1 },
        	{ x - 0.5, 0.1, z + 1 },
          	{ x + 0.5, 0.1, z + 1 },
    	};
		glColor4f(0.8, 0.5, 0.7, 0.5);
		glBegin(GL_POLYGON);
		glTexCoord2i(0,0);
		glVertex3fv(vertices2[0]);
		glTexCoord2i(0, 1);
		glVertex3fv(vertices2[1]);
		glTexCoord2i(1, 1);
		glVertex3fv(vertices2[2]);
		glTexCoord2i(1, 0);
		glVertex3fv(vertices2[3]);
		glEnd();
	}

	glBindTexture(GL_TEXTURE_2D, *effectImage[8]);
	{
		GLfloat vertices[4][3] = {
			{ x + 0.5, 1.1, z },
            { x - 0.5, 1.1, z },
            { x - 0.5, 0.1, z },
            { x + 0.5, 0.1, z },
        };
		glColor4f(1.0, 0.8, 0.8, 0.7);
		glBegin(GL_POLYGON);
		glTexCoord2i(0,0);
		glVertex3fv(vertices[0]);
		glTexCoord2i(0, 1);
		glVertex3fv(vertices[1]);
		glTexCoord2i(1, 1);
		glVertex3fv(vertices[2]);
		glTexCoord2i(1, 0);
		glVertex3fv(vertices[3]);
		glEnd();
	}
	if((r+=10) >= 360)	r = 0; 
	glEnable(GL_DEPTH_TEST);
}

void Effect::drawAttack7(){
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glMaterialf(GL_FRONT, GL_SHININESS, 60.0);

	glDisable(GL_CULL_FACE);
		
	glTranslatef(x , 0.0, z );
	glRotated(dir*56.5, 0.0, 1.0, 0.0);
	glTranslatef(-x, 0.0, -z);

	glTranslatef(x , 0.6, 0 );
	glRotated(r, 0.0, 0.0, 1.0);
	glTranslatef(-x, -0.6, 0);

	glBindTexture(GL_TEXTURE_2D, *effectImage[9]);
	{
		GLfloat vertices[4][3] = {
			{ x, 0.8, z + 0.8 },
            { x, 0.8, z - 0.8 },
            { x, 0.4, z - 0.8 },
            { x, 0.4, z + 0.8 },
        };
		glBegin(GL_POLYGON);
		glTexCoord2i(0,0);
		glVertex3fv(vertices[0]);
		glTexCoord2i(0, 1);
		glVertex3fv(vertices[1]);
		glTexCoord2i(1, 1);
		glVertex3fv(vertices[2]);
		glTexCoord2i(1, 0);
		glVertex3fv(vertices[3]);
		glEnd();
	}


	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	if((r+=25) >= 360)	r = 0;

	if(count >= 20){
		z+=cos(dir)/2;
		x+=sin(dir)/2;
	}

	if(x<0 || x>STAGE_X || z<0 || z>STAGE_Y)	count = 500;
}














