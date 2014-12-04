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

//3Dモデル管理用クラス
class Model
{
    public:
        Model(const char* filename);
        ~Model();

        FbxNode* rootnode;
        int  getMesh(FbxNode* node);//情報所得

        void GetAnimation(const char*);


        FbxTime animationStartFrame;
		FbxTime animationEndFrame;

        void  Draw(double x ,double y,double z,double dir);//描写
        char Name[256];//モデル名
        vector <material> mat;//モデルの情報
        vector <TEXTURE> texture;//テクスチャデータ

};

#endif
