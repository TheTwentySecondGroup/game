#ifndef _3DSTRUCT_H_
#define _3DSTRUCT_H_


#include <iostream>
#include <vector>
#include <string>
//#include <unistd.h>



using namespace std;

class vec3f{
public:
	float x,y,z;
	vec3f(){
		x=0;y=0;z=0;
	}
};

class vec4f{
public:
	float x,y,z,w;
	vec4f(){
		x=0;y=0;z=0;w=0;
	}
};


class col4f{
public:
    float r,g,b,a;
    col4f(){
    	r=0;g=0;b=0;a=0;
    }
};

class reflect{
public:
    col4f diffuse;
    col4f ambient;
    col4f emission;
    col4f specular;
};


class UV{
public:
	float u;
    float v;
    UV(){
    	u=0;v=0;
    }
};


class tri{
    vec3f vec;
    vec3f normal;
    UV uv;
};


class material{

   // std::string MaterialName;//マテリアル名
    Ref MaterialColor;//反射
    float Shininess;//shininess
   // string TextureName;//テクスチャ名
    int TexNo;//テクスチャNO.

};
#endif
