#ifndef _MODEL_H
#define _MODEL_H
//#define FBXSDK_NEW_API

#define MAX_VERTICES 80000
#define MAX_POLIGONS 80000


#include <fbxsdk.h>
#include "3dModelStruct.h"
#include <iostream>
#include <vector>
#include <GL/glut.h>
using namespace std;

class Model
{

    public:

        Model();
        ~Model();

       // void ShowDetails();

       // void  GetFbxInfo( FbxNode* );
        int  getMesh(FbxNode* node);
        void  Draw();
        //void  InitializeVertexBuffer( vertex* );

        char Name[256];
        vector <material> mat;

/*
        int numPoligons;
        //int *poligonsSize;
        int *indexes;
        int numIndices;

        int numVertices;
        int numIndexes;
*/

};

#endif
