/*
 * 3dModelStruct.h
 *
 *  last update 2015/02/12
 *      Author: Murokawa,Takeda
 */

#ifndef _3DSTRUCT_H_
#define _3DSTRUCT_H_


#include <iostream>
#include <vector>
#include <string>
#include "Model.h"

using namespace std;

class Model;
//3軸ベクトル
class vec3f{
    public:
        float x,y,z;
        vec3f(){
            x=0;y=0;z=0;
        }
};

//4軸ベクトル
class vec4f{
    public:
        float x,y,z,w;
        vec4f(){
            x=0;y=0;z=0;w=0;
        }
};

//色情報
class col4f{
    public:
        float r,g,b,a;
        col4f(){
            r=0.5;g=0.5;b=0.5;a=1;
        }
};

//光の反射
class reflect{
    public:
        col4f diffuse;
        col4f ambient;
        col4f emission;
        col4f specular;
};

//UV座標
class UV{
    public:
        float u;
        float v;
        UV(){
            u=0;v=0;
        }
};
/*
class TEXTURE{
    public:
        TEXTURE(const char* FileName,char* dataType);
        char* image;//イメージポインタ
        int x,y;//size
};
*/
/*
class Flame{
public:
	vector <vec3f> ver;
	vector <double> weight;
	vector <FbxAMatrix> bone;
};
*/
class material{
    public:
		string textureName;
        reflect color;//反射
        vector <vec3f> ver;//頂点座標
        vector <vec3f> nor;//法線座標
        vector <UV> uv;//UV座標
        vector <int> index;//インデックスバッファ
        double shininess;
        GLuint *texture;//テクスチャハンドル
/*
        vector <string> weightName;
        vector <int>weightIndex;
        vector <float>weight;
        FbxAMatrix invBaseposeMatrix;


        vector <Flame> flame;
        FbxTime myTime,startTime,endTime;
*/
        Model* model;//元モデルのポインタ
        material(){
        	texture=NULL;

        	shininess = 128;
        }
};

#endif
