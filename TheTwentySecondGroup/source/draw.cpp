#include "global.h"


GLfloat lightpos[4];
GLfloat DifLight[] = {0.5,0.5,0.5,1.0};
GLfloat GrayMaterial[] = {0.3,0.3,0.3,1};
GLfloat WhiteMaterial[] = {0.8,0.8,0.8,1};
GLfloat SpecularLight[] = {1,1,1,1.0};
GLfloat GrayLight[] = {0.3,0.3,0.3,1.0};
GLfloat FogColor[] = {0,0,0,1.0};




void drawCube(int x,int y);

void Normal3f(GLfloat fVert1[],GLfloat fVert2[],GLfloat fVert3[]);

void init2D(){
    glDisable(GL_DEPTH_TEST);
    //glDisable(GL_CULL_FACE);
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
    glLoadIdentity();
    gluPerspective(30.0, (GLdouble) WINDOW_X / (GLdouble) WINDOW_Y, 0.01, 1000.0);
    //gluPerspective(30.0, (GLdouble) WINDOW_X / (GLdouble) WINDOW_Y, 0.01, 15.0);


    //fog
    // glFogi(GL_FOG_MODE,GL_LINEAR);
    // glFogfv(GL_FOG_COLOR,FogColor);
    //glFogf(GL_FOG_DENSITY,0.5);
    //glHint(GL_FOG_HINT,GL_DONT_CARE);
    //glFogf(GL_FOG_START,2);
    //glFogf(GL_FOG_END,8);
    //glEnable(GL_FOG);

    //z buffer
    glEnable(GL_DEPTH_TEST);

    //CULLING
    //glEnable(GL_CULL_FACE);

    //to smooth
    glShadeModel(GL_SMOOTH);
}




void draw()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    init3D();
    {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        double xd= sin(myPos.dir);
        double zd=   cos(myPos.dir) ;
        gluLookAt(myPos.x - xd/20 ,myPos.y,myPos.z- zd/20, // position of camera
                myPos.x  , myPos.y ,myPos.z, //look-at point
                0.0f,1.0f,0.0f);

        //Light
        lightpos[0]=myPos.x;
        lightpos[1]=myPos.y;
        lightpos[2]=myPos.z;
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
        model[0].Draw();



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















void drawCube(int x,int y){
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,WhiteMaterial);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,WhiteMaterial);
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,WhiteMaterial);
    glMaterialf(GL_FRONT,GL_SHININESS,60.0);

    //glBindTexture( GL_TEXTURE_2D, *texHandle[0] );


    GLfloat vertices [8][3]={
        {0+x, 0+y,  1.0},
        { 1+x, 0+y,  1.0},
        { 1+x,  1+y,  1.0},
        {0+x,  1+y,  1.0},
        { 1+x, 0+y, 0.0},
        {0+x, 0+y, 0.0},
        {0+x,  1+y, 0.0},
        { 1+x,  1+y, 0.0}
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








