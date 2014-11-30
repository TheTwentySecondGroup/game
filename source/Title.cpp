#include "global.h"
#include "draw.h"
#include "Title.h"
#include "Tutorial.h"
#include "system.h"
#include "io.h"
using namespace std;

Title::Title(){

	sel = 1;
	KeyFlag=0;

	sys->player[sys->myID].x=2.5;
    sys->player[sys->myID].y=0;
    //sys->player[sys->myID].z = 1.5;
    sys->player[sys->myID].dir=0;

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0,GL_AMBIENT,sys->draw->GrayLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,sys->draw->DifLight);
    glLightfv(GL_LIGHT0,GL_SPECULAR,sys->draw->SpecularLight);



    SDL_Color color1 = {255, 255, 0};
    SDL_Color color2 = {255, 255, 255};
	titleImage[0] = sys->draw->initTexture("data/image/sam.bmp");

	SDL_Surface *tmp1,*tmp2,*tmp3,*tmp4,*tmp5,*tmp6,*tmp7;
	tmp1 = TTF_RenderUTF8_Blended(sys->font,"1 VS 1",color1);
	titleImage[1] = sys->draw->timeTexture(tmp1);
	tmp2 = TTF_RenderUTF8_Blended(sys->font,"2 VS 2",color1);
	titleImage[2] = sys->draw->timeTexture(tmp2);
    tmp3 = TTF_RenderUTF8_Blended(sys->font,"BATTLE ROYAL",color1);
    titleImage[3] = sys->draw->timeTexture(tmp3);
    tmp4 = TTF_RenderUTF8_Blended(sys->font,"1 VS 1",color2);
    titleImage[4] = sys->draw->timeTexture(tmp4);
    tmp5 = TTF_RenderUTF8_Blended(sys->font,"2 VS 2",color2);
	titleImage[5] = sys->draw->timeTexture(tmp5);
	tmp6 = TTF_RenderUTF8_Blended(sys->font,"BATTLE ROYAL",color2);
	titleImage[6] = sys->draw->timeTexture(tmp6);

}

Title::~Title(){
    glDeleteTextures(6,*titleImage);

}

void Title::drawMenuCube(int x,int y,GLuint *texture,double sw){
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,sys->draw->WhiteMaterial);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,sys->draw->WhiteMaterial);
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,sys->draw->WhiteMaterial);
    glMaterialf(GL_FRONT,GL_SHININESS,60.0);

    glBindTexture( GL_TEXTURE_2D, *texture );

    GLfloat vertices [4][3]={
        {1, 2.5-x, sw+y},
        {1, 1.5-x, sw+y},
        {2, 1.5-x, sw+y},
        {2, 2.5-x, sw+y},
    };
    glBegin(GL_POLYGON);
    glNormal3f(sys->player[0].xd , sys->player[0].yd , 0);
    glTexCoord2i(0,0);
    glVertex3fv(vertices[0]);
    glTexCoord2i(0,1);
    glVertex3fv(vertices[1]);
    glTexCoord2i(1,1);
    glVertex3fv(vertices[2]);
    glTexCoord2i(1,0);
    glVertex3fv(vertices[3]);
    glEnd();
}


void Title::routine(){

	cout<<"execute title routine()"<<endl;
	if((sys->io->key[KEY_UP] == 1)){
        if(sel>CHOICE_MIN)sel -=1;
    }
	if((sys->io->key[KEY_DOWN] == 1)){
        if(sel<CHOICE_MAX)sel +=1;
    }
	//cout<<sys->io->key[KEY_A]<<"----------------------------------------------------------------------"<<endl;
    if(sys->io->key[KEY_A] >= 1){
    	//Tutorial();
		sys->Stage = -2;
	}
	cout<<"execute title routine() 1"<<endl;


    drawTitle();
    SDL_Delay(1000/60);

	cout<<"execute title routine()  2"<<endl;

}

void Title::drawTitle(){
	cout<<"execute title drawTitle()"<<endl;

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    sys->draw->init3D();
    {
        //glDisable(GL_LIGHTING);
        glDisable(GL_FOG);
        //init
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        double xd= sin(sys->player[0].dir);
        double yd=   cos(sys->player[0].dir) ;
        gluLookAt(sys->player[0].x - xd/20 ,sys->player[0].y - yd/20,sys->player[0].z, // position of camera
        		sys->player[0].x  , sys->player[0].y ,sys->player[0].z, //look-at point
                0.0,0.0,1.0);
    	cout<<"execute title drawTitle() 1"<<endl;


        //Light
        sys->draw->lightpos[0]=sys->player[0].x-5*xd;
        sys->draw->lightpos[1]=sys->player[0].y-5*yd;
        sys->draw->lightpos[2]=sys->player[0].z;
        sys->draw->lightpos[3]=1;
        glLightfv(GL_LIGHT0,GL_POSITION,sys->draw->lightpos); // position of light0
        GLfloat Light0Dir[]={xd,yd,0};
        glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,Light0Dir);
        glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 30.0f );
        glLightf( GL_LIGHT0, GL_SPOT_EXPONENT, 2.0f );
        glLightfv(GL_LIGHT0,GL_AMBIENT,sys->draw->GrayLight);
        glLightfv(GL_LIGHT0,GL_DIFFUSE,sys->draw->DifLight);
        glLightfv(GL_LIGHT0,GL_SPECULAR,sys->draw->SpecularLight);
        glEnable(GL_LIGHTING);
        glEnable(GL_NORMALIZE); 

    	cout<<"execute title drawTitle() 2"<<endl;

        //draw wall
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,sys->draw->WhiteMaterial);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,sys->draw->WhiteMaterial);
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,sys->draw->WhiteMaterial);
        glMaterialf(GL_FRONT,GL_SHININESS,60.0);
        glBindTexture( GL_TEXTURE_2D, *titleImage[0] );
        GLfloat vertices [4][3]={
            {2, 8,  3.0},
            {2, 8, -1.5},
            { 8, 8, -1.5},
            { 8, 8,  3.0},
        };
        glBegin(GL_POLYGON);
        glNormal3f(sys->player[0].xd , sys->player[0].yd , 0);
        glTexCoord2i(0,0);
        glVertex3fv(vertices[0]);
        glTexCoord2i(0,1);
        glVertex3fv(vertices[1]);
        glTexCoord2i(1,1);
        glVertex3fv(vertices[2]);
        glTexCoord2i(1,0);
        glVertex3fv(vertices[3]);
		glEnd();
		
		cout<<"execute title drawTitle() 3"<<endl;

		//draw menu
		int c;
		for(c=1;c<=CHOICE_MAX;c++){
			//draw on button
			if(sel == c)drawMenuCube(c, 7,  titleImage[c],0);
			//draw off button
			else drawMenuCube(c, 7,  titleImage[c+3],1.5);
		}
	}
	//init2D();
	cout<<"execute title drawTitle() 4"<<endl;

	glFlush();
	SDL_GL_SwapBuffers();

	cout<<"execute title drawTitle() 5"<<endl;

}

