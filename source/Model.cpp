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

		cout << "lahgsf" << endl;
		vector<vec3f> transVec;
		cout<<"size ="<< mat[i].flame.size() <<endl;
		for (int j = 0; j < mat[i].ver.size(); j++) {
			//cout<<j<<endl;;
			FbxVector4 vertex(mat[i].ver[j].x, mat[i].ver[j].y, mat[i].ver[j].z);
			FbxVector4 transVertex = vertex;
			double lWeight = mat[i].weight[j];
			if (lWeight != 0.0) {
				if(mat[i].flame[j].bone.size()>=j)
				transVertex = mat[i].flame[0].bone[0].MultT(vertex);
				transVertex += vertex * (1.0 - lWeight);
			}
			vec3f tmp;
			tmp.x = transVertex[0];
			tmp.y = transVertex[1];
			tmp.z = transVertex[2];

			transVec.push_back(tmp);
		}

		cout<<"asgfsrfg"<<endl;
		glVertexPointer(3, GL_FLOAT, sizeof(vec3f), &transVec[0].x);

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
			mattemp.model = this;
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
			mattemp->invBaseposeMatrix  = cluster->GetLink()->EvaluateGlobalTransform().Inverse();
			for (FbxTime t = mattemp->model->animationStartFrame; t < mattemp->model->animationEndFrame; t +=
					FbxTime::GetOneFrameValue(FbxTime::eFrames60)) {
				FbxAMatrix matrix = mattemp->invBaseposeMatrix * cluster->GetLink()->EvaluateGlobalTransform(t);

				Flame flametmp;
				flametmp.bone.push_back(matrix);
				mattemp->flame.push_back(flametmp);
			}



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
