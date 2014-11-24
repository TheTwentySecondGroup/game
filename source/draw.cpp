#include "global.h"
//#include "draw.h"
//#include "Effect.h"
//#include "mode.h"
//#include "Map.h"
#include "system.h"



//GLuint *texHandle[10];

//TTF_Font* font;



void Draw::routine(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    init3D();

    {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        double xd= sin(sys->player[sys->myID].dir);
        double zd=   cos(sys->player[sys->myID].dir) ;
        gluLookAt(sys->player[sys->myID].x - xd/20 ,sys->player[sys->myID].y,sys->player[sys->myID].z- zd/20, // position of camera
        		sys->player[sys->myID].x  , sys->player[sys->myID].y ,sys->player[sys->myID].z, //look-at point
                0.0f,1.0f,0.0f);

        //Light
        sys->draw->lightpos[0]=sys->player[sys->myID].x;
        lightpos[1]=sys->player[sys->myID].y;
        lightpos[2]=sys->player[sys->myID].z;
        lightpos[3]=1;

        glLightfv(GL_LIGHT0,GL_POSITION,lightpos); // position of light0
        GLfloat Light0Dir[]={xd,0,zd};
        glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,Light0Dir);
        glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 30.0f );
        glLightf( GL_LIGHT0, GL_SPOT_EXPONENT, 2.0f );
        glLightfv(GL_LIGHT0,GL_AMBIENT,GrayLight);
        glLightfv(GL_LIGHT0,GL_DIFFUSE,DifLight);
        glLightfv(GL_LIGHT0,GL_SPECULAR,SpecularLight);
        glEnable(GL_LIGHTING);
        glEnable(GL_NORMALIZE);

        glEnable(GL_LIGHT0);

        //drawCube(1,1);
        //model[0].Draw();

        sys->map->drawMap();//
        //if(sys->player[sys->myID].attflag == 1)
        //drawA(sys->player[sys->myID].x,sys->player[sys->myID].y+5);
        //hp(sys->player[sys->myID].x, sys->player[sys->myID].y);



    }

    init2D();
    {
        //drawTime(WINDOW_X-150,100,150,100);
        //procEffect();
        //drawItemStatus();

    }
    glFlush();
    SDL_GL_SwapBuffers();//reflect swap


}




Draw::Draw(){

	//system

	charaImage[0] = initTexture("data/image/chara1.bmp");
	charaImage[1] = initTexture("data/image/chara2.bmp");
	charaImage[2] = initTexture("data/image/chara3.bmp");
	charaImage[3] = initTexture("data/image/chara4.bmp");
	charaImage[4] = initTexture("data/image/chara1g.bmp");
	charaImage[5] = initTexture("data/image/chara2g.bmp");
	charaImage[6] = initTexture("data/image/chara3g.bmp");
	charaImage[7] = initTexture("data/image/chara4g.bmp");



    //initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB|GLUT_DEPTH);

    //format to black
    glClearColor(0.0, 0.0, 0.0, 0.0);

    //LoadTexture
    texHandle[0] = initTexture("data/image/glass1.bmp");
    texHandle[1] = initTexture("data/image/sky.bmp");
    texHandle[2] = initTexture("data/image/block.bmp");
    texHandle[3] = initTexture("data/image/glass2.bmp");
    texHandle[4] = initTexture("data/image/star.bmp");
    texHandle[5] = initTexture("data/image/mist.bmp");
    //texHandle[6] = initTexture("data/image/HP.bmp");
    //texHandle[7] = initTexture("data/image/MP.bmp");
	//Initialize ttf
    //TTF_Init();
    //font = TTF_OpenFont("data/Koruri-20140524/Koruri-Regular.ttf",200);


	lightpos[0] = 0;
	lightpos[1] = 0;
	lightpos[2] = 0;
	lightpos[3] = 0;

	DifLight[0] = 0.5;
	DifLight[1] = 0.5;
	DifLight[2] = 0.5;
	DifLight[3] = 1.0;

	GrayMaterial[0] = 0.3;
	GrayMaterial[1] = 0.3;
	GrayMaterial[2] = 0.3;
	GrayMaterial[3] = 1;

	WhiteMaterial[0] = 0.8;
	WhiteMaterial[1] = 0.8;
	WhiteMaterial[2] = 0.8;
	WhiteMaterial[3] = 1;

	SpecularLight[0] = 1;
	SpecularLight[1] = 1;
	SpecularLight[2] = 1;
	SpecularLight[3] = 1;

	GrayLight[0] = 0.3;
	GrayLight[1] = 0.3;
	GrayLight[2] = 0.3;
	GrayLight[3] = 1;



	FogColor[0] = 0;
	FogColor[1] = 0;
	FogColor[2] = 0;
	FogColor[3] = 1;

}

Draw::~Draw(){
    TTF_CloseFont(font);
    TTF_Quit();
}

GLuint *Draw::pngTexture(string name){
    SDL_Surface *surface;
    SDL_RWops *rw;
    rw = SDL_RWFromFile(name.c_str(), "rb");
    surface = IMG_LoadPNG_RW(rw);
    glEnable( GL_TEXTURE_2D );
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    GLuint *Handle;
    Handle = (GLuint *)malloc(sizeof(GLuint));
    glGenTextures(1, Handle);
    glBindTexture(GL_TEXTURE_2D, *Handle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    gluBuild2DMipmaps( GL_TEXTURE_2D, 4, surface->w, surface->h, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
    if(surface){
        SDL_FreeSurface(surface);
    }
    return Handle;

}

GLuint *Draw::timeTexture(SDL_Surface *surface){
    if(surface == NULL){
        printf("timeTexture receice null surface\n");
        exit(-1);
    }
    glEnable( GL_TEXTURE_2D );
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    GLint texColor;
    GLenum texFormat;
    GLuint *Handle;
    Handle = (GLuint *)malloc(sizeof(GLuint));
    texColor = surface->format->BytesPerPixel;
    if(texColor ==4){
        if(surface->format->Rmask == 0x000000ff){
            texFormat = GL_RGBA;
        }else {
            texFormat = GL_BGRA;
        }
    }else if(texColor== 3){
        if (surface->format->Rmask == 0x000000ff) {
            texFormat = GL_RGB;
        }else{
            texFormat = GL_BGR;
        }
    }
    glGenTextures(1, Handle);
    glBindTexture(GL_TEXTURE_2D, *Handle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D( GL_TEXTURE_2D, 0, texColor, surface->w, surface->h, 0, texFormat, GL_UNSIGNED_BYTE, surface->pixels);
    if(surface){
        SDL_FreeSurface(surface);
    }
    return Handle;
}

GLuint *Draw::initTexture(string name){
    glEnable( GL_TEXTURE_2D );
    SDL_Surface *surface;
    GLint texColor;
    GLenum texFormat;
    GLuint *Handle;
    Handle = (GLuint *)malloc(sizeof(GLuint));
    surface = SDL_LoadBMP(name.c_str());

    if(surface == NULL){
    	cout<<"can't open "<<name<<endl;
        //printf("can't open %s \n",name);
        exit(-1);

    }
    texColor = surface->format->BytesPerPixel;
    if(texColor ==4){
        if(surface->format->Rmask == 0x000000ff){
            texFormat = GL_RGBA;
        }else {
            texFormat = GL_BGRA;
        }
    }else if(texColor== 3){
        if (surface->format->Rmask == 0x000000ff) {
            texFormat = GL_RGB;
        }else{
            texFormat = GL_BGR;
        }
    }
    glGenTextures(1, Handle);
    glBindTexture(GL_TEXTURE_2D, *Handle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D( GL_TEXTURE_2D, 0, texColor, surface->w, surface->h, 0, texFormat, GL_UNSIGNED_BYTE, surface->pixels);
    if(surface){
        SDL_FreeSurface(surface);
    }
    return Handle;
}

void Draw::drawCharaSelect(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	init3D();
	{
	}
	init2D();
	{
		//character1
		cout <<"selChara"<<sys->selChara<<endl;
		for (int i = 0; i < 4; i++) {
			if (sys->selChara == i+1)
				glBindTexture( GL_TEXTURE_2D, *charaImage[i]);
			else
				glBindTexture( GL_TEXTURE_2D, *charaImage[i + 4]);
			glBegin( GL_QUADS);
			glTexCoord2i(0, 0);
			glVertex3f(200 * (i), 0, 0);
			glTexCoord2i(1, 0);
			glVertex3f(200 * (i+1), 0, 0);
			glTexCoord2i(1, 1);
			glVertex3f(200 * (i+1), 200, 0);
			glTexCoord2i(0, 1);
			glVertex3f(200 * (i), 200, 0);
			glEnd();

		/*
		 strcpy(buf, "ニブルヘイム");
		 TextImage=TTF_RenderUTF8_Blended(font,buf,white);
		 GLuint *texText;
		 texText = timeTexture(TextImage);
		 glBindTexture( GL_TEXTURE_2D, *texText);
		 glBegin( GL_QUADS );
		 glTexCoord2i( 0, 0 );
		 glVertex3f( 0, 300, 0 );
		 glTexCoord2i( 1, 0 );
		 glVertex3f( 150, 300, 0 );
		 glTexCoord2i( 1, 1 );
		 glVertex3f( 150, 350, 0 );
		 glTexCoord2i( 0, 1 );
		 glVertex3f( 0, 350, 0 );
		 glEnd();
		 glDeleteTextures(1,texText);
		 */
		}
	}
	glFlush();
	SDL_GL_SwapBuffers();


}



















void Draw::drawCube(int x,int y){
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,WhiteMaterial);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,WhiteMaterial);
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,WhiteMaterial);
    glMaterialf(GL_FRONT,GL_SHININESS,60.0);

    //glBindTexture( GL_TEXTURE_2D, *texHandle[0] );


    GLfloat vertices [8][3]={
        {0+x, 1.0 ,0+y},
        { 1+x,  1.0, 0+y},
        { 1+x,  1.0,  1+y},
        {0+x,  1.0,  1+y},
        { 1+x, 0.0, 0+y},
        {0+x, 0.0, 0+y},
        {0+x, 0.0,  1+y},
        { 1+x, 0.0,  1+y}
    };
    /*
       glBegin(GL_POLYGON);
       glNormal3f(myPos.xd , myPos.yd , 0);
       glTexCoord2i(0,0);
       glVertex3fv(vertices[0]);
       glTexCoord2i(0,1);
       glVertex3fv(vertices[1]);
       glTexCoord2i(1,1);
       glVertex3fv(vertices[2]);
       glTexCoord2i(1,0);
       glVertex3fv(vertices[3]);
       glEnd();
    //
    glBegin(GL_POLYGON);
    glNormal3f(myPos.xd , myPos.yd , 0);
    glTexCoord2i(0,0);
    glVertex3fv(vertices[4]);
    glTexCoord2i(0,1);
    glVertex3fv(vertices[5]);
    glTexCoord2i(1,1);
    glVertex3fv(vertices[6]);
    glTexCoord2i(1,0);
    glVertex3fv(vertices[7]);
    glEnd();
     */
    // 右
    glBegin(GL_POLYGON);

	Normal3f(vertices[1] , vertices[4] , vertices[7]);
    glTexCoord2i(0,0);
    glVertex3fv(vertices[1]);
    glTexCoord2i(0,1);
    glVertex3fv(vertices[4]);
    glTexCoord2i(1,1);
    glVertex3fv(vertices[7]);
    glTexCoord2i(1,0);
    glVertex3fv(vertices[2]);
    glEnd();
    // 左
    glBegin(GL_POLYGON);
    Normal3f(vertices[5] , vertices[0] , vertices[3]);
    glTexCoord2i(0,0);
    glVertex3fv(vertices[5]);
    glTexCoord2i(0,1);
    glVertex3fv(vertices[0]);
    glTexCoord2i(1,1);
    glVertex3fv(vertices[3]);
    glTexCoord2i(1,0);
    glVertex3fv(vertices[6]);
    glEnd();
    // 上
    glBegin(GL_POLYGON);
    Normal3f(vertices[3], vertices[2], vertices[7]);
    glTexCoord2i(1,0);
    glVertex3fv(vertices[3]);
    glTexCoord2i(0,0);
    glVertex3fv(vertices[2]);
    glTexCoord2i(0,1);
    glVertex3fv(vertices[7]);
    glTexCoord2i(1,1);
    glVertex3fv(vertices[6]);
    glEnd();
    // 下
    glBegin(GL_POLYGON);
    Normal3f(vertices[1] , vertices[0] , vertices[5]);
    glTexCoord2i(1,0);
    glVertex3fv(vertices[1]);
    glTexCoord2i(0,0);
    glVertex3fv(vertices[0]);
    glTexCoord2i(0,1);
    glVertex3fv(vertices[5]);
    glTexCoord2i(1,1);
    glVertex3fv(vertices[4]);
    glEnd();
}
void Draw::Normal3f(GLfloat fVert1[],GLfloat fVert2[],GLfloat fVert3[]){
    GLfloat Qx, Qy, Qz, Px, Py, Pz;

    Qx = fVert2[0]-fVert1[0];
    Qy = fVert2[1]-fVert1[1];
    Qz = fVert2[2]-fVert1[2];
    Px = fVert3[0]-fVert1[0];
    Py = fVert3[1]-fVert1[1];
    Pz = fVert3[2]-fVert1[2];

    glNormal3f(Py*Qz - Pz*Qy, Pz*Qx - Px*Qz , Px*Qy - Py*Qx);
}

void Draw::init2D(){
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glViewport(0,0,WINDOW_X,WINDOW_Y);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0,WINDOW_X,WINDOW_Y,0,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}
void Draw::init3D(){
    glViewport(0, 0, WINDOW_X, WINDOW_Y);
    //perspective
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	//変換行列に単位行列を設定

	/*変換行列に透視変換の行列を乗じる*/
    gluPerspective(30.0, (GLdouble) WINDOW_X / (GLdouble) WINDOW_Y, 0.01, 15.0);

    //fog
   // glFogi(GL_FOG_MODE, GL_LINEAR);
   // glFogfv(GL_FOG_COLOR, FogColor);
    //glFogf(GL_FOG_DENSITY,0.5);
    glHint(GL_FOG_HINT, GL_DONT_CARE);
    glFogf(GL_FOG_START, 10);
    glFogf(GL_FOG_END,15);
    glEnable(GL_FOG);

    //z buffer
    glEnable(GL_DEPTH_TEST);

    //CULLING
    glEnable(GL_CULL_FACE);

    //to smooth
    glShadeModel(GL_SMOOTH);
}


void Draw::drawFloor(int x, int y){
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,GrayMaterial);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,GrayMaterial);
	glMaterialf(GL_FRONT,GL_SHININESS,60.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glBindTexture(GL_TEXTURE_2D,*texHandle[0]);

	GLfloat vertices[4][3]={
		{1+x, 0.0, 1+y},
		{0+x, 0.0, 1+y},
		{0+x, 0.0, 0+y},
		{1+x, 0.0, 0+y},
	};
	glBegin(GL_POLYGON);
	glNormal3f(sys->player[sys->myID].xd, sys->player[sys->myID].yd, 0);
	glTexCoord2i(0,0);
	glVertex3fv(vertices[0]);
	glTexCoord2i(0,1);
	glVertex3fv(vertices[1]);
	glTexCoord2i(1,1);
	glVertex3fv(vertices[2]);
	glTexCoord2i(1,0);
	glVertex3fv(vertices[3]);
	glEnd();
	glDisable(GL_CULL_FACE);
}

void Draw::drawSky(int x, int y){
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,GrayMaterial);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,GrayMaterial);
	glMaterialf(GL_FRONT,GL_SHININESS,60.0);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glBindTexture(GL_TEXTURE_2D,*texHandle[1]);
	glNormal3f(sys->player[sys->myID].xd, sys->player[sys->myID].yd, 0);
	GLfloat vertices[4][3]={
		{26, 2.0, 80},
		{-5, 2.0 , 80},
		{-5, 2.0 , 0},
		{26, 2.0, 0},
	};
	glBegin(GL_POLYGON);
	glNormal3f(sys->player[sys->myID].xd, sys->player[sys->myID].yd, 0);
	glTexCoord2i(0,0);
	glVertex3fv(vertices[0]);
	glTexCoord2i(0,1);
	glVertex3fv(vertices[1]);
	glTexCoord2i(1,1);
	glVertex3fv(vertices[2]);
	glTexCoord2i(1,0);
	glVertex3fv(vertices[3]);
	glEnd();
	glDisable(GL_CULL_FACE);
}



void Draw::drawFloor2(int x, int y){
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,GrayMaterial);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,GrayMaterial);
	glMaterialf(GL_FRONT,GL_SHININESS,60.0);

	glBindTexture(GL_TEXTURE_2D,*texHandle[3]);

	GLfloat vertices[4][3]={
		{1+x,  0.0,1+y},
		{0+x, 0.0, 1+y},
		{0+x, 0.0, 0+y},
		{1+x, 0.0, 0+y},
	};
	glBegin(GL_POLYGON);
	glNormal3f(sys->player[sys->myID].xd, sys->player[sys->myID].yd, 0);
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

void Draw::drawWall(int x, int y){
int i;
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,GrayMaterial);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,GrayMaterial);
	glMaterialf(GL_FRONT,GL_SHININESS,60.0);

	glDisable(GL_CULL_FACE);
	//前
	glBindTexture(GL_TEXTURE_2D,*texHandle[2]);
	GLfloat vertices1[4][3]={
		{1+x, y, 1.5},
		{0+x, y, 1.5},
		{0+x, y, 0},
		{1+x, y, 0},
	};
	glBegin(GL_POLYGON);
	glNormal3f(sys->player[sys->myID].xd, sys->player[sys->myID].yd, 0);
	glTexCoord2i(0,0);
	glVertex3fv(vertices1[0]);
	glTexCoord2i(0,1);
	glVertex3fv(vertices1[1]);
	glTexCoord2i(1,1);
	glVertex3fv(vertices1[2]);
	glTexCoord2i(1,0);
	glVertex3fv(vertices1[3]);
	glEnd();

	//後ろ
	glBindTexture(GL_TEXTURE_2D,*texHandle[2]);
	GLfloat vertices2[4][3]={
		{1+x, y+1, 1.5},
		{0+x, y+1, 1.5},
		{0+x, y+1, 0},
		{1+x, y+1, 0},
	};
	glBegin(GL_POLYGON);
	glNormal3f(sys->player[sys->myID].xd, sys->player[sys->myID].yd, 0);
	glTexCoord2i(0,0);
	glVertex3fv(vertices2[0]);
	glTexCoord2i(0,1);
	glVertex3fv(vertices2[1]);
	glTexCoord2i(1,1);
	glVertex3fv(vertices2[2]);
	glTexCoord2i(1,0);
	glVertex3fv(vertices2[3]);
	glEnd();

	//左
	glBindTexture(GL_TEXTURE_2D,*texHandle[2]);
	GLfloat vertices3[4][3]={
		{x, 1+y, 1.5},
		{x, 0+y, 1.5},
		{x, 0+y, 0},
		{x, 1+y, 0},
	};
	glBegin(GL_POLYGON);
	glNormal3f(sys->player[sys->myID].xd, sys->player[sys->myID].yd, 0);
	glTexCoord2i(0,0);
	glVertex3fv(vertices3[0]);
	glTexCoord2i(0,1);
	glVertex3fv(vertices3[1]);
	glTexCoord2i(1,1);
	glVertex3fv(vertices3[2]);
	glTexCoord2i(1,0);
	glVertex3fv(vertices3[3]);
	glEnd();

	//右
	glBindTexture(GL_TEXTURE_2D,*texHandle[2]);
	GLfloat vertices4[4][3]={
		{1+x, 1+y, 1.5},
		{1+x, 0+y, 1.5},
		{1+x, 0+y, 0},
		{1+x, 1+y, 0},
	};
	glBegin(GL_POLYGON);
	glNormal3f(sys->player[sys->myID].xd, sys->player[sys->myID].yd, 0);
	glTexCoord2i(0,0);
	glVertex3fv(vertices4[0]);
	glTexCoord2i(0,1);
	glVertex3fv(vertices4[1]);
	glTexCoord2i(1,1);
	glVertex3fv(vertices4[2]);
	glTexCoord2i(1,0);
	glVertex3fv(vertices4[3]);
	glEnd();
}







