#include "global.h"
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
	//cout<<"--Model """<<x<<y<<z<<dir<<endl;

	//int i,j;
	//cout<<"numIndices="<< numIndices<<"\n";
	//cout<<mat.size()<<"\n";

	glEnableClientState(GL_VERTEX_ARRAY);

	glEnableClientState(GL_NORMAL_ARRAY);

	for (int i = 0; i < mat.size(); i++) {
		glPushMatrix();

		glTranslatef(x, 0, z);
		glScalef(0.003f, 0.003f, 0.003f);
		glRotatef(dir * 360 / 6.28, 0.0f, 1.0f, 0.0f);

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

			cout << "a" << endl;
			//テクスチャー座標読み込み

			for (int n = 0; n < mesh->GetLayerCount(); n++) {

				FbxLayerElementUV* pUV = mesh->GetLayer(n)->GetUVs();

				cout << "a" << endl;
				int uvsize =
						pUV->GetDirectArray().GetCount() > pUV->GetIndexArray().GetCount() ?
								pUV->GetDirectArray().GetCount() : pUV->GetIndexArray().GetCount();

				cout << "as" << endl;
				if (pUV->GetMappingMode() == FbxLayerElement::eByPolygonVertex) {

					cout << "asd" << endl;
					if (pUV->GetReferenceMode() == FbxLayerElement::eDirect) {

						cout << "a" << endl;
						// 直接取得
						for (int i = 0; i < uvsize; ++i) {
							UV uvtemp;
							uvtemp.u = (float) pUV->GetDirectArray().GetAt(i)[0];
							uvtemp.v = 1.0f - (float) pUV->GetDirectArray().GetAt(i)[1];
							mattemp.uv.push_back(uvtemp);
						}
					} else if (pUV->GetReferenceMode() == FbxLayerElement::eIndexToDirect) {

						cout << "c" << endl;
						// インデックスから取得
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

			//マテリアル読み込み
			FbxNode* pNode = mesh->GetNode();
			cout << "--====--------=====================" << pNode->GetMaterialCount() << endl;
			for (int i = 0; i < pNode->GetMaterialCount(); i++) {

				//フォンモデルを想定
				FbxSurfaceMaterial* pMaterial = pNode->GetMaterial(i);
				FbxClassId classid = pMaterial->GetClassId();
				if (classid.Is(FbxSurfacePhong::ClassId)) {
					FbxSurfacePhong* pPhong = (FbxSurfacePhong*) pMaterial;
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
					FbxSurfaceLambert * lambert = static_cast<FbxSurfaceLambert *>(pMaterial);
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
			}
			/*
			 //テクスチャ
			 FbxProperty lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);
			 FbxTexture* ktex = FbxCast <FbxTexture> (lProperty.GetSrcObject(FbxTexture::ClassId, 0));
			 if (ktex) {
			 cout<<"texture name is "<<ktex->GetFileName();
			 //テクスチャを作成
			 TexData.push_back(tex);
			 TexData[TexData.size() - 1] = new TEXTURE(
			 mtl.TextureName.c_str());
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
			 glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
			 TexData[TexData.size() - 1]->Width,
			 TexData[TexData.size() - 1]->Height, 0, GL_RGBA,
			 GL_UNSIGNED_BYTE,
			 TexData[TexData.size() - 1]->image);
			 glDisable(GL_TEXTURE_2D);
			 }
			 Material.push_back(mtl);
			 }
			 */

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

// アニメーションフレーム数取得
	int animStackCount = importer->GetAnimStackCount();
//assert(animStackCount == 1);
	FbxTakeInfo* takeInfo = importer->GetTakeInfo(0);

	FbxTime importOffset = takeInfo->mImportOffset;
	FbxTime startTime = takeInfo->mLocalTimeSpan.GetStart();
	FbxTime stopTime = takeInfo->mLocalTimeSpan.GetStop();

	animationStartFrame = (importOffset.Get() + startTime.Get()) / FbxTime::GetOneFrameValue(FbxTime::eFrames60);
	animationEndFrame = (importOffset.Get() + stopTime.Get()) / FbxTime::GetOneFrameValue(FbxTime::eFrames60);
	importer->Destroy();
//EvaluateGlobalTransform()

	FbxAnimEvaluator* mySceneEvaluator = scene->GetEvaluator();

}
