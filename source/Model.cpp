#include "global.h"
#include "system.h"
#include "Model.h"

Model::Model(const char* filename) {
	bzero(Name, '\0');
	strcpy(Name, filename);
	cout << "A model \"" << filename << "\" is loading\n";

	FbxManager *manager = FbxManager::Create();

	FbxIOSettings *ioSettings = FbxIOSettings::Create(manager, IOSROOT);
	manager->SetIOSettings(ioSettings);

	FbxImporter *importer = FbxImporter::Create(manager, "");
	importer->Initialize(Name, -1, manager->GetIOSettings());

	FbxScene *scene = FbxScene::Create(manager, "tempName");

	importer->Import(scene);

	//三角化
	FbxGeometryConverter geometryConverter(manager);
	geometryConverter.Triangulate(scene, true);
	geometryConverter.SplitMeshesPerMaterial(scene, true);

	importer->Destroy();

	//scene->SetEvaluator();

	rootnode = scene->GetRootNode();

	if (rootnode) {
		this->getMesh(rootnode);

	}

}

Model::~Model() {
	cout << "A model has been destroied!\n";
}

void Model::Draw(double x, double y, double z, double dir) {

	glEnableClientState(GL_VERTEX_ARRAY);

	glEnableClientState(GL_NORMAL_ARRAY);

	for (int i = 0; i < mat.size(); i++) {
		glPushMatrix();

		glTranslatef(x, 0, z);
		glScalef(0.3f, 0.3f, 0.3f);
		glRotatef(dir * 360 / 6.28, 0.0f, 1.0f, 0.0f);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

		//glRotatef();
		//material
		GLfloat WhiteMaterial[] = { 0.8, 0.8, 0.8, 1 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (const GLfloat *) &mat[i].color.ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (const GLfloat *) &mat[i].color.diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (const GLfloat *) &mat[i].color.specular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat[i].shininess);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, WhiteMaterial);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, WhiteMaterial);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, WhiteMaterial);
		//glMaterialf(GL_FRONT, GL_SHININESS, 60.0);

		//texture
		if (mat[i].texture) {
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, *(mat[i].texture));
			glTexCoordPointer(2, GL_FLOAT, 0, &mat[i].uv[0].u);
		} else {
			glDisable(GL_TEXTURE_2D);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		}

		glNormalPointer(GL_FLOAT, sizeof(vec3f), &mat[i].nor[0].x);
		glVertexPointer(3, GL_FLOAT, sizeof(vec3f), &mat[i].ver[0].x);

		glDrawArrays(GL_TRIANGLES, 0, mat[i].ver.size());

		glPopMatrix();

	}
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	/*
	 glEnableClientState(GL_VERTEX_ARRAY);
	 glEnableClientState(GL_NORMAL_ARRAY);
	 for(int i=0;i<(signed)Material.size();i++){
	 glPushMatrix();
	 glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(const GLfloat *)&Material[i].MaterialColor.ambient);
	 glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(const GLfloat *)&Material[i].MaterialColor.diffuse);
	 glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(const GLfloat *)&Material[i].MaterialColor.specular);
	 glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,Material[i].Shininess);
	 if(Material[i].TexNo>0){
	 glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	 glEnable(GL_TEXTURE_2D);
	 glBindTexture(GL_TEXTURE_2D, TexID[Material[i].TexNo-1]);
	 }else{
	 glDisable(GL_TEXTURE_2D);
	 glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	 }
	 if(Material[i].Tridata.size()>1){
	 glVertexPointer(3, GL_FLOAT,sizeof(Tri) , &Material[i].Tridata[0].TriVer.x);
	 glNormalPointer(GL_FLOAT,sizeof(Tri),&Material[i].Tridata[0].TriNor.x);
	 if(Material[i].TexNo>0)glTexCoordPointer(2, GL_FLOAT, sizeof(Tri), &Material[i].Tridata[0].TriUV.u);
	 glDrawArrays(GL_TRIANGLES,0,Material[i].Tridata.size());
	 }
	 if(Material[i].Quaddata.size()>1){
	 glVertexPointer(3, GL_FLOAT,sizeof(Quad) , &Material[i].Quaddata[0].QuadVer.x);
	 glNormalPointer(GL_FLOAT,sizeof(Quad),&Material[i].Quaddata[0].QuadNor.x);
	 if(Material[i].TexNo>0)glTexCoordPointer(2, GL_FLOAT, sizeof(Quad), &Material[i].Quaddata[0].QuadUV.u);
	 glDrawArrays(GL_QUADS,0,Material[i].Quaddata.size());
	 }
	 glPopMatrix();
	 }
	 glDisableClientState(GL_VERTEX_ARRAY);
	 glDisableClientState(GL_NORMAL_ARRAY);
	 glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	 glDisable(GL_TEXTURE_2D);

	 */

}

int Model::getMesh(FbxNode* node) {
	FbxNodeAttribute* attr = node->GetNodeAttribute();
	if (attr != NULL) {
		if (attr->GetAttributeType() == FbxNodeAttribute::eMesh) {
			//syori
			FbxMesh *mesh = node->GetMesh();

			material mattemp;

			//頂点情報

			int* indexes = mesh->GetPolygonVertices();
			int indexcounttmp = mesh->GetPolygonVertexCount();
			int VerticesCount = mesh->GetControlPointsCount();

			//cout << VerticesCount << "\n";
			FbxVector4* vec = mesh->GetControlPoints();
			//cout << indexcounttmp << endl;
			for (int i = 0; i < indexcounttmp; i++) {
				//位置情報格納
				vec3f temp;
				temp.x = (float) vec[indexes[i]].mData[0];
				temp.y = (float) vec[indexes[i]].mData[1];
				temp.z = (float) vec[indexes[i]].mData[2];
				mattemp.ver.push_back(temp);
				//cout <<"temp.x="<<(float)temp.x<< " 	temp.y="<<(float)temp.y<< "	temp.z="<<(float)temp.z<<"\n";
			}

			//法線情報
			FbxGeometryElementNormal* element = mesh->GetElementNormal();
			int normalCount = mesh->GetElementNormalCount();
			cout << "normal " << normalCount << endl;
			if (normalCount == 1) {
				if ((element->GetReferenceMode() == FbxGeometryElement::eDirect)) {
					if (element->GetMappingMode() == FbxGeometryElement::eByControlPoint) {
						cout << "controlpoint" << endl;
						vector<vec3f> vectemp;
						for (int i = 0; i < element->GetDirectArray().GetCount(); ++i) {
							vec3f nor;
							nor.x = (float) element->GetDirectArray().GetAt(i)[0];
							nor.y = (float) element->GetDirectArray().GetAt(i)[1];
							nor.z = (float) element->GetDirectArray().GetAt(i)[2];
							vectemp.push_back(nor);
						}
						for (int i = 0; i < indexcounttmp; i++) {
							mattemp.nor.push_back(vectemp[indexes[i]]);
						}
					} else if (element->GetMappingMode() == FbxGeometryElement::eByPolygonVertex) {
						cout << "Polygon" << endl;

						for (int i = 0; i < element->GetDirectArray().GetCount(); ++i) {
							vec3f nor;
							nor.x = (float) element->GetDirectArray().GetAt(i)[0];
							nor.y = (float) element->GetDirectArray().GetAt(i)[1];
							nor.z = (float) element->GetDirectArray().GetAt(i)[2];
							mattemp.nor.push_back(nor);
						}
					}

				} else {
					cout << "not eDirect\n";
					if (element->GetMappingMode() == FbxGeometryElement::eByControlPoint) {
						cout << "controlpoint" << endl;
						vector<vec3f> vectemp;
						for (int i = 0; i < element->GetDirectArray().GetCount(); ++i) {

							int index = element->GetIndexArray().GetAt(i);
							vec3f nor;
							nor.x = (float) element->GetDirectArray().GetAt(index)[0];
							nor.y = (float) element->GetDirectArray().GetAt(index)[1];
							nor.z = (float) element->GetDirectArray().GetAt(index)[2];
							mattemp.nor.push_back(nor);
						}
					} else if (element->GetMappingMode() == FbxGeometryElement::eByPolygonVertex) {
						cout << "Polygon" << endl;

						for (int i = 0; i < element->GetDirectArray().GetCount(); ++i) {

							int index = element->GetIndexArray().GetAt(i);
							vec3f nor;
							nor.x = (float) element->GetDirectArray().GetAt(index)[0];
							nor.y = (float) element->GetDirectArray().GetAt(index)[1];
							nor.z = (float) element->GetDirectArray().GetAt(index)[2];
							mattemp.nor.push_back(nor);
						}
					}

				}

			}

			//UV読み込み

			for (int n = 0; n < mesh->GetLayerCount(); n++) {

				FbxLayerElementUV* pUV = mesh->GetLayer(n)->GetUVs();
				if (pUV) {

					int uvsize =
							pUV->GetDirectArray().GetCount() > pUV->GetIndexArray().GetCount() ?
									pUV->GetDirectArray().GetCount() : pUV->GetIndexArray().GetCount();

					if (pUV->GetMappingMode() == FbxLayerElement::eByPolygonVertex) {

						cout << "a" << endl;
						if (pUV->GetReferenceMode() == FbxLayerElement::eDirect) {
							// 直接取得

							cout << "b" << endl;
							for (int i = 0; i < uvsize; ++i) {
								UV uvtemp;
								uvtemp.u = (float) pUV->GetDirectArray().GetAt(i)[0];
								uvtemp.v = 1.0f - (float) pUV->GetDirectArray().GetAt(i)[1];
								mattemp.uv.push_back(uvtemp);
							}
						} else if (pUV->GetReferenceMode() == FbxLayerElement::eIndexToDirect) {
							// インデックスから取得

							cout << "c" << endl;
							for (int i = 0; i < uvsize; ++i) {
								UV uvtemp;
								int index = pUV->GetIndexArray().GetAt(i);
								uvtemp.u = (float) pUV->GetDirectArray().GetAt(index)[0];
								uvtemp.v = 1.0f - (float) pUV->GetDirectArray().GetAt(index)[1];
								mattemp.uv.push_back(uvtemp);
							}
						}
					}
				}
			}

			//マテリアル読み込み
			FbxNode* pNode = mesh->GetNode();
			cout << "--====--------=====================" << pNode->GetMaterialCount() << endl;
			for (int i = 0; i < pNode->GetMaterialCount(); i++) {

				//フォンモデルを想定
				FbxSurfaceMaterial* material = pNode->GetMaterial(i);
				FbxClassId classid = material->GetClassId();
				if (classid.Is(FbxSurfacePhong::ClassId)) {
					FbxSurfacePhong* pPhong = (FbxSurfacePhong*) material;
					if (!pPhong) {
						cout << "pPhongisnull\n";
						continue;
					}
					//環境光
					mattemp.color.ambient.r = (float) pPhong->Ambient.Get()[0];
					mattemp.color.ambient.g = (float) pPhong->Ambient.Get()[1];
					mattemp.color.ambient.b = (float) pPhong->Ambient.Get()[2];
					mattemp.color.ambient.a = 1.0f;
					cout << "amb [" << mattemp.color.ambient.r << "][" << mattemp.color.ambient.g << "]["
							<< mattemp.color.ambient.b << "]";
					//拡散反射光
					mattemp.color.diffuse.r = (float) pPhong->Diffuse.Get()[0];
					mattemp.color.diffuse.g = (float) pPhong->Diffuse.Get()[1];
					mattemp.color.diffuse.b = (float) pPhong->Diffuse.Get()[2];
					mattemp.color.diffuse.a = 1.0f;
					cout << "diff [" << mattemp.color.diffuse.r << "][" << mattemp.color.diffuse.g << "]["
							<< mattemp.color.diffuse.b << "]";
					//emissive
					mattemp.color.emission.r = (float) pPhong->Emissive.Get()[0];
					mattemp.color.emission.g = (float) pPhong->Emissive.Get()[1];
					mattemp.color.emission.b = (float) pPhong->Emissive.Get()[2];
					mattemp.color.emission.a = 1.0f;
					cout << "emi [" << mattemp.color.emission.r << "][" << mattemp.color.emission.g << "]["
							<< mattemp.color.emission.b << "]";

					//鏡面反射光
					mattemp.color.specular.r = (float) pPhong->Specular.Get()[0];
					mattemp.color.specular.g = (float) pPhong->Specular.Get()[1];
					mattemp.color.specular.b = (float) pPhong->Specular.Get()[2];
					mattemp.color.specular.a = 1.0f;

					cout << "spe [" << mattemp.color.specular.r << "][" << mattemp.color.specular.g << "]["
							<< mattemp.color.specular.b << "]";
					mattemp.shininess = (float) pPhong->Shininess;
					cout << "shininess" << mattemp.shininess << endl;
				} else if (classid.Is(FbxSurfaceLambert::ClassId)) {
					FbxSurfaceLambert * lambert = static_cast<FbxSurfaceLambert *>(material);
					if (!lambert) {
						cout << "lambert is null\n";
						continue;
					}
					mattemp.color.ambient.r = (float) lambert->Ambient.Get()[0];
					mattemp.color.ambient.g = (float) lambert->Ambient.Get()[1];
					mattemp.color.ambient.b = (float) lambert->Ambient.Get()[2];
					mattemp.color.ambient.a = 1.0f;
					cout << "amb [" << mattemp.color.ambient.r << "][" << mattemp.color.ambient.g << "]["
							<< mattemp.color.ambient.b << "]";
					//拡散反射光
					mattemp.color.diffuse.r = (float) lambert->Diffuse.Get()[0];
					mattemp.color.diffuse.g = (float) lambert->Diffuse.Get()[1];
					mattemp.color.diffuse.b = (float) lambert->Diffuse.Get()[2];
					mattemp.color.diffuse.a = 1.0f;
					cout << "diff [" << mattemp.color.diffuse.r << "][" << mattemp.color.diffuse.g << "]["
							<< mattemp.color.diffuse.b << "]";
					//emissive
					mattemp.color.emission.r = (float) lambert->Emissive.Get()[0];
					mattemp.color.emission.g = (float) lambert->Emissive.Get()[1];
					mattemp.color.emission.b = (float) lambert->Emissive.Get()[2];
					mattemp.color.emission.a = 1.0f;
					cout << "emi [" << mattemp.color.emission.r << "][" << mattemp.color.emission.g << "]["
							<< mattemp.color.emission.b << "]" << endl;
				} else {
					cout << "unknownclassid" << endl;
				}

				//テクスチャ
				FbxProperty lProperty = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
				FbxTexture* ktex = FbxCast<FbxTexture>(lProperty.GetSrcObject(FbxTexture::ClassId, 0));
				if (ktex) {
					string tmp = FbxCast<FbxFileTexture>(ktex)->GetFileName();
					vector<string> temp = split(tmp, '\\');
					mattemp.textureName = "data/fbx/" + temp[temp.size() - 1];
					cout << "texture name is " << mattemp.textureName << endl;
					if (FILE * file = fopen(mattemp.textureName.c_str(), "r")) {
						fclose(file);

						mattemp.texture = sys->draw->pngTexture(mattemp.textureName);
					}

					/*
					 //テクスチャを作成
					 TexData.push_back(tex);
					 TexData[TexData.size() - 1] = new TEXTURE(mtl.TextureName.c_str());
					 ;
					 mtl.TexNo = TexData.size();
					 TexID.push_back(TexID2);
					 glGenTextures(1, (GLuint *) &TexID[TexData.size() - 1]);
					 glBindTexture(GL_TEXTURE_2D, TexID[TexData.size() - 1]);
					 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
					 GL_NEAREST);
					 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
					 GL_NEAREST);
					 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
					 GL_REPEAT);
					 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
					 GL_REPEAT);

					 glEnable(GL_TEXTURE_2D);
					 glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TexData[TexData.size() - 1]->Width,
					 TexData[TexData.size() - 1]->Height, 0, GL_RGBA,
					 GL_UNSIGNED_BYTE, TexData[TexData.size() - 1]->image);
					 glDisable(GL_TEXTURE_2D);
					 */
				} else {
					cout << "no texture\n";
				}
			}

			getWeight(node->GetMesh(), &mattemp);
			mat.push_back(mattemp);

			cout << "mat.push_back complated\n";
		} else {
			cout << attr->GetAttributeType() << endl;
		}
	}

	int childCount = node->GetChildCount();
	for (int i = 0; childCount > i; i++) {
		this->getMesh(node->GetChild(i));
		//if(this->getMesh(node->GetChild(i))==1);//return 1;
	}
	GetAnimation("data/fbx/n.fbx");

	return 1;
}

void Model::GetAnimation(const char* filename) {
	FbxManager *manager = FbxManager::Create();

	FbxIOSettings *ioSettings = FbxIOSettings::Create(manager, IOSROOT);
	manager->SetIOSettings(ioSettings);

	FbxImporter *importer = FbxImporter::Create(manager, "");
	importer->Initialize(filename, -1, manager->GetIOSettings());

	FbxScene *scene = FbxScene::Create(manager, "tempName");

	importer->Import(scene);

	FbxNode* rootnode = scene->GetRootNode();
	FbxMesh* mesh = rootnode->GetMesh();

// アニメーションフレーム数取得
	int animStackCount = importer->GetAnimStackCount();
	cout << "=============================animStackCount =" << animStackCount << endl;
//assert(animStackCount == 1);
	FbxTakeInfo* takeInfo = importer->GetTakeInfo(0);

	FbxTime importOffset = takeInfo->mImportOffset;
	FbxTime startTime = takeInfo->mLocalTimeSpan.GetStart();
	FbxTime stopTime = takeInfo->mLocalTimeSpan.GetStop();

	animationStartFrame = (importOffset.Get() + startTime.Get()) / FbxTime::GetOneFrameValue(FbxTime::eFrames60);
	animationEndFrame = (importOffset.Get() + stopTime.Get()) / FbxTime::GetOneFrameValue(FbxTime::eFrames60);
	importer->Destroy();

	int stackCount = scene->GetSrcObjectCount<FbxAnimStack>();
	if (stackCount <= 0)
		return;

	// num of animation
	cout << "stackCount====" << stackCount << endl;
	for (int i = 0; i < stackCount; i++) {
		FbxAnimEvaluator *animEvaluator = scene->GetEvaluator();
		FbxAnimStack* stack = scene->GetSrcObject<FbxAnimStack>(i);
		int layerCount = stack->GetMemberCount<FbxAnimLayer>();
		cout << "layercount====================" << layerCount << endl;
		for (int j = 0; j < layerCount; j++) {
			FbxAnimLayer* layer = stack->GetMember(FBX_TYPE(FbxAnimLayer), j);
			FbxAnimCurve* transCurve = scene->GetRootNode()->LclTranslation.GetCurve(layer);
			FbxAnimCurve* rotateCurve = scene->GetRootNode()->LclRotation.GetCurve(layer);
			FbxAnimCurve* scaleCurve = scene->GetRootNode()->LclScaling.GetCurve(layer);
			if (scaleCurve != 0) {
				int numKeys = scaleCurve->KeyGetCount();
				for (int keyIndex = 0; keyIndex < numKeys; keyIndex++) {
					FbxTime frameTime = scaleCurve->KeyGetTime(keyIndex);
					//FbxDouble3 scalingVector = scene->GetRootNode()->LclScaling();

					//scene->EvaluateLocalScaling(frameTime);
					//	float x = (float) scalingVector[0];
					//float y = (float) scalingVector[1];
					//float z = (float) scalingVector[2];
					//float frameSeconds = (float) frameTime.GetSecondDouble();
				}
			} else {
				// If this animation layer has no scaling curve, then use the default one, if needed
				//FbxDouble3 scalingVector = scene->GetRootNode()->LclScaling.Get();
				//float x = (float) scalingVector[0];
				//float y = (float) scalingVector[1];
				//float z = (float) scalingVector[2];
			}

		}

		/*
		 *
		 *
		 *
		 *
		 *
		 *
		 // If it has some defomer connection, update the vertices position
		 const bool lHasVertexCache = lMesh->GetDeformerCount(FbxDeformer::eVertexCache) &&
		 (static_cast<FbxVertexCacheDeformer*>(lMesh->GetDeformer(0, FbxDeformer::eVertexCache)))->IsActive();
		 const bool lHasShape = lMesh->GetShapeCount() > 0;
		 const bool lHasSkin = lMesh->GetDeformerCount(FbxDeformer::eSkin) > 0;
		 const bool lHasDeformation = lHasVertexCache || lHasShape || lHasSkin;

		 FbxVector4* lVertexArray = NULL;
		 if (!lMeshCache || lHasDeformation)
		 {
		 lVertexArray = new FbxVector4[lVertexCount];
		 memcpy(lVertexArray, lMesh->GetControlPoints(), lVertexCount * sizeof(FbxVector4));
		 }

		 if (lHasDeformation)
		 {
		 // Active vertex cache deformer will overwrite any other deformer
		 if (lHasVertexCache)
		 {
		 ReadVertexCacheData(lMesh, pTime, lVertexArray);
		 }
		 else
		 {
		 if (lHasShape)
		 {
		 // Deform the vertex array with the shapes.
		 ComputeShapeDeformation(lMesh, pTime, pAnimLayer, lVertexArray);
		 }

		 //we need to get the number of clusters
		 const int lSkinCount = lMesh->GetDeformerCount(FbxDeformer::eSkin);
		 int lClusterCount = 0;
		 for (int lSkinIndex = 0; lSkinIndex < lSkinCount; ++lSkinIndex)
		 {
		 lClusterCount += ((FbxSkin *)(lMesh->GetDeformer(lSkinIndex, FbxDeformer::eSkin)))->GetClusterCount();
		 }
		 if (lClusterCount)
		 {
		 // Deform the vertex array with the skin deformer.
		 ComputeSkinDeformation(pGlobalPosition, lMesh, pTime, lVertexArray, pPose);
		 }
		 }


		 if (lMeshCache)
		 lMeshCache->UpdateVertexPosition(lMesh, lVertexArray);
		 }
		 *
		 *
		 *
		 *
		 *
		 *
		 *
		 void ComputeSkinDeformation(FbxAMatrix& pGlobalPosition,
		 FbxMesh* pMesh,
		 FbxTime& pTime,
		 */
		FbxVector4* vertexArray;
		/*
		 FbxPose* pPose)
		 {
		 FbxSkin * lSkinDeformer = (FbxSkin *)pMesh->GetDeformer(0, FbxDeformer::eSkin);
		 FbxSkin::EType lSkinningType = lSkinDeformer->GetSkinningType();

		 if(lSkinningType == FbxSkin::eLinear || lSkinningType == FbxSkin::eRigid)
		 {
		 ComputeLinearDeformation(pGlobalPosition, pMesh, pTime, pVertexArray, pPose);
		 }
		 *
		 *
		 *
		 *
		 *
		 *
		 *
		 void ComputeLinearDeformation(FbxAMatrix& pGlobalPosition,
		 FbxMesh* pMesh,
		 FbxTime& pTime,
		 FbxVector4* pVertexArray,
		 FbxPose* pPose)
		 {
		 */
		// All the links must have the same link mode.
		cout << "aaaaaaaaafsfgasdgasdf" << endl;

		FbxSkin* skin = static_cast<FbxSkin*>(mesh->GetDeformer(0, FbxDeformer::eSkin));
		int clusterCount = skin->GetClusterCount();

		for (int i = 0; i < clusterCount; ++i) {
			FbxCluster* cluster = skin->GetCluster(i);
			int vertexCount = mesh->GetControlPointsCount();
			FbxAMatrix* clusterDeformation = new FbxAMatrix[vertexCount];
			memset(clusterDeformation, 0, vertexCount * sizeof(FbxAMatrix));

			double* clusterWeight = new double[vertexCount];
			memset(clusterWeight, 0, vertexCount * sizeof(double));

			if (cluster->GetLinkMode() == FbxCluster::eAdditive) {
				for (int i = 0; i < vertexCount; ++i) {
					clusterDeformation[i].SetIdentity();
				}
			} else if (cluster->GetLinkMode() == FbxCluster::eNormalize) {
				;
			}

			// For all skins and all clusters, accumulate their deformation and weight
			// on each vertices and store them in lClusterDeformation and lClusterWeight.
			int skinCount = mesh->GetDeformerCount(FbxDeformer::eSkin);
			for (int k = 0; k < skinCount; k++) {
				FbxSkin * skinDeformer = (FbxSkin *) mesh->GetDeformer(k, FbxDeformer::eSkin);

				int clusterCount = skinDeformer->GetClusterCount();
				for (int l = 0; l < clusterCount; l++) {
					FbxCluster* cluster = skinDeformer->GetCluster(l);
					if (!cluster->GetLink())continue;

					FbxAMatrix vertexTransformMatrix;
					//ComputeClusterDeformation(pGlobalPosition, pMesh, lCluster, lVertexTransformMatrix, pTime, pPose);

					int vertexIndexCount = cluster->GetControlPointIndicesCount();
					for (int m = 0; m < vertexIndexCount; ++m) {
						int lIndex = cluster->GetControlPointIndices()[m];

						// Sometimes, the mesh can have less points than at the time of the skinning
						// because a smooth operator was active when skinning but has been deactivated during export.
						if (lIndex >= vertexCount)
							continue;

						double lWeight = cluster->GetControlPointWeights()[m];

						if (lWeight == 0.0) {
							continue;
						}

						// Compute the influence of the link on the vertex.
						FbxAMatrix influence = vertexTransformMatrix;
						//MatrixScale(influence, lWeight);

						if (clusterMode == FbxCluster::eAdditive) {
							// Multiply with the product of the deformations on the vertex.
							//MatrixAddToDiagonal(influence, 1.0 - lWeight);
							//clusterDeformation[lIndex] = influence * clusterDeformation[lIndex];

							// Set the link to 1.0 just to know this vertex is influenced by a link.
							clusterWeight[lIndex] = 1.0;
						} else // lLinkMode == FbxCluster::eNormalize || lLinkMode == FbxCluster::eTotalOne
						{
							// Add to the sum of the deformations on the vertex.
							//MatrixAdd(clusterDeformation[lIndex], influence);

							// Add to the sum of weights to either normalize or complete the vertex.
							clusterWeight[lIndex] += lWeight;
						}
					} //For each vertex
				} //lClusterCount
			}

			//Actually deform each vertices here by information stored in lClusterDeformation and lClusterWeight
			for (int i = 0; i < vertexCount; i++) {
				FbxVector4 srcVertex = vertexArray[i];
				FbxVector4& dstVertex = vertexArray[i];
				double lWeight = clusterWeight[i];

				// Deform the vertex if there was at least a link with an influence on the vertex,
				if (lWeight != 0.0) {
					dstVertex = clusterDeformation[i].MultT(srcVertex);
					if (clusterMode == FbxCluster::eNormalize) {
						// In the normalized link mode, a vertex is always totally influenced by the links.
						dstVertex /= lWeight;
					} else if (clusterMode == FbxCluster::eTotalOne) {
						// In the total 1 link mode, a vertex can be partially influenced by the links.
						srcVertex *= (1.0 - lWeight);
						dstVertex += srcVertex;
					}
				}
			}

			delete[] clusterDeformation;
			delete[] clusterWeight;
		}
		//}
		/*
		 *
		 *
		 *
		 *
		 *
		 *
		 *
		 *
		 *
		 *
		 *
		 *
		 *
		 *
		 *
		 *
		 *
		 *
		 *
		 *
		 *
		 *
		 *
		 *
		 *
		 *
		 *
		 *
		 */

//FinalVector = TranslationMat * RotationMat * ScaleMat * vector
// Analogically, process rotationa and translation
		/*
		 scene->GetEvaluator()->SetContext(stack);


		 if(layerCount>0){
		 const char* animeName = stack->GetName();
		 const S32 clipIndex = a.AddClip();

		 //  追加したクリップを貰う
		 AnimationBuild::Clip& clip = a.GetClip( clipIndex );

		 //  パラメーター初期化
		 clip.InitParam( clipIndex );

		 //  クリップ名がすでにあるかどうか調べる
		 if( a.isClipName( animeName ) ) {
		 //  ある場合はインデックス名で生成
		 std::stringstream str;
		 str<<"motion"<<clipIndex;
		 clip.SetClipName( str.str().c_str() );
		 } else {
		 //  ないので普通に名前を設定
		 clip.SetClipName( animeName );
		 }

		 //  開始と終了の時間を貰う
		 FbxTime startTime = pStack->LocalStart;
		 FbxTime endTime   = pStack->LocalStop;

		 //  フレームに直す
		 const S32 startFrame = GetFrameValue( startTime );
		 const S32 endFrame   = GetFrameValue( endTime );

		 ASSERT( startFrame < endFrame );

		 //  差をフレーム数にします
		 clip.SetFrame( endFrame - startFrame );

		 //  開始フレームオフセットを設定
		 clip.SetStartFrameOffset( startFrame );
















		 }*/

	}
	animScene = scene;

//scene->setContext();
//FbxAnimEvaluator* mySceneEvaluator = scene->GetEvaluator();

}

vector<string> Model::split(const string &str, char delim) {
	vector<string> res;
	size_t current = 0, found;
	while ((found = str.find_first_of(delim, current)) != string::npos) {
		res.push_back(string(str, current, found - current));
		current = found + 1;
	}
	res.push_back(string(str, current, str.size() - current));
	return res;
}

void Model::getWeight(FbxMesh* mesh, material *mattemp) {

	int skinCount = mesh->GetDeformerCount(FbxDeformer::eSkin);

//no skin
	if (skinCount == 0) {
		return;
	}

	cout << skinCount << endl;
	int controlPointsCount = mesh->GetControlPointsCount();

	FbxSkin* skin = static_cast<FbxSkin*>(mesh->GetDeformer(0, FbxDeformer::eSkin));
	int clusterCount = skin->GetClusterCount();

	for (int i = 0; i < clusterCount; ++i) {
		FbxCluster* cluster = skin->GetCluster(i);

// eNormalize
		if (cluster->GetLinkMode() == FbxCluster::eNormalize) {

			int indicesCount = cluster->GetControlPointIndicesCount();
			int* indices = cluster->GetControlPointIndices();
			double* weightarray = cluster->GetControlPointWeights();

			//get weight
			for (int i = 0; i < indicesCount; ++i) {
				int index = indices[i];
				mattemp->weightIndex.push_back(index);
				mattemp->weight.push_back((float) weightarray[i]);
				cout << "index=" << index << " weight[" << i << "]" << (float) weightarray[i] << endl;
			}
			//get weight's name
			mattemp->weightName.push_back(cluster->GetLink()->GetName());
			cout << " name:" << cluster->GetLink()->GetName() << endl;
			// ペースポーズの逆行列を作成しておく
			//GLKMatrix4 invBaseposeMatrix;
			GLfloat invBaseposeMatrix[16];
			FbxAMatrix baseposeMatrix = cluster->GetLink()->EvaluateGlobalTransform().Inverse();
			double* baseposeMatrixPtr = (double*) baseposeMatrix;
			for (int j = 0; j < 16; ++j) {
				cout << "matrix[" << j << "] " << (float) baseposeMatrixPtr[j] << endl;
				invBaseposeMatrix[j] = (float) baseposeMatrixPtr[j];

				mattemp->invBaseposeMatrix.push_back(invBaseposeMatrix[j]);
			}

			cout << "aa" << endl;
			//invBaseposeMatrixList.push_back(invBaseposeMatrix);
		}
	}

	/*
	 // コントロールポイントに対応したウェイトを作成
	 std::vector<ModelBoneWeight> boneWeightListControlPoints;
	 for (auto& tmpBoneWeight : tmpBoneWeightList) {
	 // ウェイトの大きさでソート
	 std::sort(tmpBoneWeight.begin(), tmpBoneWeight.end(),
	 [](const TmpWeight& weightA, const TmpWeight& weightB) {return weightA.second > weightB.second;}
	 //[](const TmpWeight& weightA, const TmpWeight& weightB){ return weightA.second < weightB.second; }
	 );

	 // 1頂点に4つより多くウェイトが割り振られているなら影響が少ないものは無視する
	 while (tmpBoneWeight.size() > 4) {
	 tmpBoneWeight.pop_back();
	 }

	 // 4つに満たない場合はダミーを挿入
	 while (tmpBoneWeight.size() < 4) {
	 tmpBoneWeight.push_back( { 0, 0.0f });
	 }

	 ModelBoneWeight weight;
	 float total = 0.0f;
	 for (int i = 0; i < 4; ++i) {
	 weight.boneIndex[i] = tmpBoneWeight[i].first;
	 weight.boneWeight.v[i] = tmpBoneWeight[i].second;

	 total += tmpBoneWeight[i].second;
	 }

	 // ウェイトの正規化
	 for (int i = 0; i < 4; ++i) {
	 weight.boneWeight.v[i] /= total;
	 }

	 boneWeightListControlPoints.push_back(weight);
	 }

	 // インデックスで展開
	 for (auto index : indexList) {
	 boneWeightList.push_back(boneWeightListControlPoints[index]);
	 }
	 */
}
