#include "global.h"
#include "draw.h"
#include "Effect.h"
#include "mode.h"
#include "Map.h"

GLfloat lightpos[4];
GLfloat DifLight[] = {0.5,0.5,0.5,1.0};
GLfloat GrayMaterial[] = {0.3,0.3,0.3,1};
GLfloat WhiteMaterial[] = {0.8,0.8,0.8,1};
GLfloat SpecularLight[] = {1,1,1,1.0};
GLfloat GrayLight[] = {1.0,1.0,1.0,1.0};
GLfloat WhiteLight[] = {1.0, 1.0, 1.0, 1.0};
GLfloat FogColor[] = {0,0,0,1.0};

GLuint *texHandle[10];

TTF_Font* font;

void init2D(){
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
void init3D(){
    glViewport(0, 0, WINDOW_X, WINDOW_Y);
    //perspective
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	//変換行列に単位行列を設定
	
	/*変換行列に透視変換の行列を乗じる*/
    gluPerspective(30.0, (GLdouble) WINDOW_X / (GLdouble) WINDOW_Y, 0.01, 15.0);

    //fog
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogfv(GL_FOG_COLOR, FogColor);
    //glFogf(GL_FOG_DENSITY,0.5);
    glHint(GL_FOG_HINT, GL_DONT_CARE);
    glFogf(GL_FOG_START, 2);
    glFogf(GL_FOG_END, 8);
    glEnable(GL_FOG);

    //z buffer
    glEnable(GL_DEPTH_TEST);

    //CULLING
    glEnable(GL_CULL_FACE);

    //to smooth
    glShadeModel(GL_SMOOTH);
}

void initDraw(){

    //initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB|GLUT_DEPTH);

    //format to black
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    //LoadTexture
    texHandle[0] = initTexture("data/image/glass1.bmp");
    texHandle[1] = initTexture("data/image/sky.bmp");
    texHandle[2] = initTexture("data/image/block.bmp");

	//Initialize ttf
    TTF_Init();
    font = TTF_OpenFont("data/Koruri-20140524/Koruri-Regular.ttf",200);
}

void delDraw(){
    TTF_CloseFont(font);
    TTF_Quit();
}

GLuint *pngTexture(char name[]){
    SDL_Surface *surface;
    SDL_RWops *rw;
    rw = SDL_RWFromFile(name, "rb");
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

GLuint *timeTexture(SDL_Surface *surface){
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

GLuint *initTexture(char name[]){
    glEnable( GL_TEXTURE_2D );
    SDL_Surface *surface;
    GLint texColor;
    GLenum texFormat;
    GLuint *Handle;
    Handle = (GLuint *)malloc(sizeof(GLuint));
    surface = SDL_LoadBMP(name);
    
    if(surface == NULL){
        printf("can't open %s \n",name);
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

void draw(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    init3D();
    {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        double xd= sin(player[0].dir);
        double yd=   cos(player[0].dir) ;
        gluLookAt(player[0].x - xd/20 ,player[0].y - yd/20,player[0].z, // position of camera
                player[0].x  , player[0].y ,player[0].z, //look-at point
                0.0,0.0,1.0);

        //Light
        lightpos[0]=player[0].x-5*xd;
        lightpos[1]=player[0].y-5*yd;
        lightpos[2]=player[0].z;
        lightpos[3]=1;
        
        glLightfv(GL_LIGHT0,GL_POSITION,lightpos); // position of light0
        GLfloat Light0Dir[]={xd,yd,0};
        glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,Light0Dir);
        glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 30.0f );
        glLightf( GL_LIGHT0, GL_SPOT_EXPONENT, 2.0f );
        glLightfv(GL_LIGHT0,GL_AMBIENT,GrayLight);
        glLightfv(GL_LIGHT0,GL_DIFFUSE,DifLight);
        glLightfv(GL_LIGHT0,GL_SPECULAR,SpecularLight);
        
        glEnable(GL_LIGHTING);
        glEnable(GL_NORMALIZE); 
		glEnable(GL_LIGHT0);

        drawMap();//
    }

    init2D();
}


void drawSky(int x, int y){
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,GrayMaterial);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,GrayMaterial);
	glMaterialf(GL_FRONT,GL_SHININESS,60.0);
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glBindTexture(GL_TEXTURE_2D,*texHandle[1]);
	glNormal3f(player[0].xd, player[0].yd, 0);
	GLfloat vertices[4][3]={
		{1+x, 1+y, 1.5},
		{0+x, 1+y, 1.5},
		{0+x, 0+y, 1.5},
		{1+x, 0+y, 1.5},
	};
	glBegin(GL_POLYGON);
	glNormal3f(player[0].xd, player[0].yd, 0);
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

void drawFloor(int x, int y){
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,GrayMaterial);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,GrayMaterial);
	glMaterialf(GL_FRONT,GL_SHININESS,60.0);
	
	glBindTexture(GL_TEXTURE_2D,*texHandle[0]);
	
	GLfloat vertices[4][3]={
		{1+x, 1+y, 0.0},
		{0+x, 1+y, 0.0},
		{0+x, 0+y, 0.0},
		{1+x, 0+y, 0.0},
	};
	glBegin(GL_POLYGON);
	glNormal3f(player[0].xd, player[0].yd, 0);
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

void drawWall(int x, int y){
int i;
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,GrayMaterial);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,GrayMaterial);
	glMaterialf(GL_FRONT,GL_SHININESS,60.0);
	
	//前
	glBindTexture(GL_TEXTURE_2D,*texHandle[2]);
	GLfloat vertices1[4][3]={
		{1+x, y, 1},
		{0+x, y, 1},
		{0+x, y, 0},
		{1+x, y, 0},
	};
	glBegin(GL_POLYGON);
	glNormal3f(player[0].xd, player[0].yd, 0);
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
		{1+x, y+1, 1},
		{0+x, y+1, 1},
		{0+x, y+1, 0},
		{1+x, y+1, 0},
	};
	glBegin(GL_POLYGON);
	glNormal3f(player[0].xd, player[0].yd, 0);
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
		{x, 1+y, 1},
		{x, 0+y, 1},
		{x, 0+y, 0},
		{x, 1+y, 0},
	};
	glBegin(GL_POLYGON);
	glNormal3f(player[0].xd, player[0].yd, 0);
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
		{1+x, 1+y, 1},
		{1+x, 0+y, 1},
		{1+x, 0+y, 0},
		{1+x, 1+y, 0},
	};
	glBegin(GL_POLYGON);
	glNormal3f(player[0].xd, player[0].yd, 0);
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

void Normal3f(GLfloat fVert1[],GLfloat fVert2[],GLfloat fVert3[]){
    GLfloat Qx, Qy, Qz, Px, Py, Pz;

    Qx = fVert2[0]-fVert1[0];
    Qy = fVert2[1]-fVert1[1];
    Qz = fVert2[2]-fVert1[2];
    Px = fVert3[0]-fVert1[0];
    Py = fVert3[1]-fVert1[1];
    Pz = fVert3[2]-fVert1[2];

    glNormal3f(Py*Qz - Pz*Qy, Pz*Qx - Px*Qz , Px*Qy - Py*Qx);
}
