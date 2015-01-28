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

class material;

//3Dモデル管理用クラス
class Model {
public:
	Model(const char* filename);
	~Model();

	FbxNode* rootnode;
	int getMesh(FbxNode* node,FbxAMatrix&); //情報所得

	void GetAnimation(const char*);

	vector<string> split(const string &str, char delim);

	void getWeight(FbxMesh* mesh, material *mattemp,FbxAMatrix&);
	FbxAMatrix GetGeometry(FbxNode* node);
	void ComputeClusterDeformation(FbxAMatrix& pGlobalPosition, FbxMesh* pMesh, FbxCluster* pCluster,
			FbxAMatrix& pVertexTransformMatrix, FbxTime pTime, FbxPose* pPose);
	void MatrixScale(FbxAMatrix& pMatrix, double pValue);
	FbxAMatrix GetGlobalPosition(FbxNode* pNode, const FbxTime& pTime, FbxPose* pPose,
			FbxAMatrix* pParentGlobalPosition);
	FbxAMatrix GetPoseMatrix(FbxPose* pPose, int pNodeIndex);
	void MatrixAddToDiagonal(FbxAMatrix& pMatrix, double pValue);
	void MatrixAdd(FbxAMatrix& pDstMatrix, FbxAMatrix& pSrcMatrix);


	FbxTime animationStartFrame;
	FbxTime animationEndFrame;
	FbxTime importOffset;
	FbxTime startTime;
	FbxTime stopTime;
	int poseNum;
	FbxPose *pPose;
	int myTime;


	void Draw(double x, double y, double z, double dir); //描写
	char Name[256]; //モデル名
	vector<material> mat; //モデルの情報
	vector<TEXTURE> texture; //テクスチャデータ

	FbxScene *animScene;

};

#endif
