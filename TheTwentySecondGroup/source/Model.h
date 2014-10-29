#ifndef _MODEL_H
#define _MODEL_H
//#define FBXSDK_NEW_API

#define MAX_VERTICES 80000
#define MAX_POLIGONS 80000


#include <fbxsdk.h>
#include "3dModelStruct.h"
#include <iostream>
#include <GL/glut.h>
using namespace std;

class Model
{

    public:

        Model();
        ~Model();

        void ShowDetails();

        char* GetModelName();
        void  SetModelName( char* );
        void  GetFbxInfo( FbxNode* );
        int  getMesh(FbxNode* node);
        void getPos(FbxMesh* mesh);
        void  Draw();
        void  InitializeVertexBuffer( vertex* );
    //private:

        char Name[256];

        vec3f *vertices;
        //vertex vertices[MAX_VERTICES];
        poligon poligons[MAX_POLIGONS];

        int numPoligons;
        int *poligonsSize;
        int *indexes;
        int numIndices;

        int numVertices;
        int numIndexes;  


};

#endif
