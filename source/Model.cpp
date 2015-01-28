#include "global.h"
#include "system.h"
#include "Model.h"

Model::Model(const char* filename) {
	myTime = 0;
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

	//animation
	FbxTakeInfo* takeInfo = importer->GetTakeInfo(0);
	if (takeInfo != NULL) {
		importOffset = takeInfo->mImportOffset;
		startTime = takeInfo->mLocalTimeSpan.GetStart();
		stopTime = takeInfo->mLocalTimeSpan.GetStop();
	}

	importer->Destroy();

	poseNum = scene->GetPoseCount();
	cout << "scene->GetPoseCount() ==" << scene->GetPoseCount() << endl;
	pPose = NULL; //scene->GetPose(0);

	rootnode = scene->GetRootNode();

	if (rootnode) {
		FbxAMatrix dummy;
		this->getMesh(rootnode,dummy);

	}else{
		cout<<"rootnode is NULL"<<endl;
	}

	//GetAnimation("data/fbx/n.fbx");

}

Model::~Model() {
	cout << "A model has been destroied!\n";
}

void Model::Draw(double x, double y, double z, double dir) {

	if (myTime++ && myTime >= mat[0].flame.size()) {
		myTime = 1;
	}
	cout << "myTime=" << myTime << endl;
	//cout << "Model::Draw start" << endl;
	glEnableClientState(GL_VERTEX_ARRAY);

	glEnableClientState(GL_NORMAL_ARRAY);

	glPushMatrix();

	glTranslatef(x, 0.3, z);
	glScalef(0.3f, 0.3f, 0.3f);
	glRotatef(dir * 360 / 6.28, 0.0f, 1.0f, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

	for (int i = 0; i < mat.size(); i++) {

		//glRotatef();
		//material
		GLfloat WhiteMaterial[] = { 0.8, 0.8, 0.8, 1 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (const GLfloat *) &mat[i].color.ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (const GLfloat *) &mat[i].color.diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (const GLfloat *) &mat[i].color.specular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat[i].shininess);

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
		/*
		 cout << "lahgsf" << endl;
		 vector<vec3f> transVec;
		 cout << "size =" << mat[i].flame.size() << endl;
		 for (int j = 0; j < mat[i].ver.size(); j++) {
		 //cout<<j<<endl;;
		 FbxVector4 vertex(mat[i].ver[j].x, mat[i].ver[j].y, mat[i].ver[j].z);
		 FbxVector4 transVertex = vertex;
		 double lWeight = mat[i].weight[j];
		 if (lWeight != 0.0) {
		 if (mat[i].flame[j].bone.size() >= j)
		 transVertex = mat[i].flame[myTime].bone[0].MultT(vertex);
		 transVertex += vertex * (1.0 - lWeight);
		 }
		 vec3f tmp;
		 tmp.x = transVertex[0];
		 tmp.y = transVertex[1];
		 tmp.z = transVertex[2];

		 transVec.push_back(tmp);
		 }

		 cout << "asgfsrfg" << endl;
		 glVertexPointer(3, GL_FLOAT, sizeof(vec3f), &transVec[0].x);
		 */

		if (mat[i].flame.size() == 0)
			glVertexPointer(3, GL_FLOAT, sizeof(vec3f), &mat[i].ver[0].x);
		else
			glVertexPointer(3, GL_FLOAT, sizeof(vec3f), &mat[i].flame[myTime].ver[0].x);

		glDrawArrays(GL_TRIANGLES, 0, mat[i].ver.size());

		//cout << "Model::Draw mat" <<i<<"end"<< endl;

	}

	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

}

int Model::getMesh(FbxNode* node ,FbxAMatrix& globalPosition) {
	FbxNodeAttribute* attr = node->GetNodeAttribute();
	//FbxAMatrix lGlobalOffPosition;
	if (attr != NULL) {
		FbxAMatrix lGeometryOffset = GetGeometry(node);
		FbxAMatrix lGlobalOffPosition = globalPosition * lGeometryOffset;

		if (attr->GetAttributeType() == FbxNodeAttribute::eMesh) {
			//syori
			FbxMesh *mesh = node->GetMesh();

			material mattemp;
			mattemp.model = this;
			//頂点情報

			int* indexes = mesh->GetPolygonVertices();
			int indexcounttmp = mesh->GetPolygonVertexCount();
			//int VerticesCount = mesh->GetControlPointsCount();

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
				cout <<"temp.x="<<(float)temp.x<< " 	temp.y="<<(float)temp.y<< "	temp.z="<<(float)temp.z<<"\n";
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
				} else {
					cout << "no texture\n";
				}
			}

			getWeight(node->GetMesh(), &mattemp,lGlobalOffPosition);
			mat.push_back(mattemp);

			cout << "mat.push_back complated\n";
		} else {
			cout << attr->GetAttributeType() << endl;
		}
	}else{
		cout<<"attr is NULL"<<endl;
	}

	int childCount = node->GetChildCount();
	cout<<"childCount="<<childCount<<endl;
	for (int i = 0; childCount > i; i++) {
		this->getMesh(node->GetChild(i),globalPosition);
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

	animationStartFrame = (importOffset.Get() + startTime.Get()) / FbxTime::GetOneFrameValue(FbxTime::eFrames24);
	animationEndFrame = (importOffset.Get() + stopTime.Get()) / FbxTime::GetOneFrameValue(FbxTime::eFrames24);
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

void Model::getWeight(FbxMesh* mesh, material *mattemp,FbxAMatrix &globalPosition) {

	int skinCount = mesh->GetDeformerCount(FbxDeformer::eSkin);

//no skin
	cout << "skinCount" << skinCount << endl;
	if (skinCount == 0) {
		return;
	}

	FbxCluster::ELinkMode clusterMode =
			((FbxSkin*) mesh->GetDeformer(0, FbxDeformer::eSkin))->GetCluster(0)->GetLinkMode();

	int vertexCount = mesh->GetControlPointsCount();
	FbxAMatrix* clusterDeformation = new FbxAMatrix[vertexCount];
	memset(clusterDeformation, 0, vertexCount * sizeof(FbxAMatrix));

	double* clusterWeight = new double[vertexCount];
	memset(clusterWeight, 0, vertexCount * sizeof(double));

	for (FbxTime t = startTime; t < stopTime; t += FbxTime::GetOneFrameValue(FbxTime::eFrames24) * 30) {
		if (clusterMode == FbxCluster::eAdditive) {
			for (int i = 0; i < vertexCount; ++i) {
				clusterDeformation[i].SetIdentity();
			}
		}

		FbxSkin* skin = static_cast<FbxSkin*>(mesh->GetDeformer(0, FbxDeformer::eSkin));
		int clusterCount = skin->GetClusterCount();
		cout << "cluster num =" << clusterCount << endl;

		for (int i = 0; i < clusterCount; ++i) {

			FbxCluster* cluster = skin->GetCluster(i);
			if (!cluster->GetLink())
				continue;

			FbxAMatrix vertexTransformMatrix;
			FbxAMatrix dummy;
			ComputeClusterDeformation(dummy, mesh, cluster, vertexTransformMatrix, t, pPose);

			int vertexIndexCount = cluster->GetControlPointIndicesCount();
			for (int k = 0; k < vertexIndexCount; ++k) {
				int index = cluster->GetControlPointIndices()[k];

				// Sometimes, the mesh can have less points than at the time of the skinning
				// because a smooth operator was active when skinning but has been deactivated during export.
				if (index >= mesh->GetControlPointsCount())
					continue;

				double weight = cluster->GetControlPointWeights()[k];

				if (weight == 0.0) {
					continue;
				}

				// Compute the influence of the link on the vertex.
				FbxAMatrix influence = vertexTransformMatrix;
				MatrixScale(influence, weight);

				if (clusterMode == FbxCluster::eAdditive) {
					// Multiply with the product of the deformations on the vertex.
					MatrixAddToDiagonal(influence, 1.0 - weight);
					clusterDeformation[index] = influence * clusterDeformation[index];

					// Set the link to 1.0 just to know this vertex is influenced by a link.
					clusterWeight[index] = 1.0;
				} else // lLinkMode == FbxCluster::eNormalize || lLinkMode == FbxCluster::eTotalOne
				{
					// Add to the sum of the deformations on the vertex.
					MatrixAdd(clusterDeformation[index], influence);

					// Add to the sum of weights to either normalize or complete the vertex.
					clusterWeight[index] += weight;
				}
			} //For each vertex
		} //lClusterCount

		FbxVector4 tmpControlPoint[vertexCount];
		FbxVector4 *vertexArray = mesh->GetControlPoints();
//Actually deform each vertices here by information stored in lClusterDeformation and lClusterWeight
		for (int i = 0; i < vertexCount; i++) {
			FbxVector4 srcVertex = vertexArray[i];
			FbxVector4& dstVertex = vertexArray[i];
			double weight = clusterWeight[i];

			// Deform the vertex if there was at least a link with an influence on the vertex,
			if (weight != 0.0) {
				dstVertex = clusterDeformation[i].MultT(srcVertex);
				if (clusterMode == FbxCluster::eNormalize) {
					// In the normalized link mode, a vertex is always totally influenced by the links.
					dstVertex /= weight;
				} else if (clusterMode == FbxCluster::eTotalOne) {
					// In the total 1 link mode, a vertex can be partially influenced by the links.
					srcVertex *= (1.0 - weight);
					dstVertex += srcVertex;
				}
			}
			tmpControlPoint[i] = dstVertex;
		}

		int* indexes = mesh->GetPolygonVertices();
		int indexcounttmp = mesh->GetPolygonVertexCount();
		//cout << tmpControlPoint.size() << "  " << indexcounttmp << endl;

		cout << ((stopTime - startTime) / (FbxTime::GetOneFrameValue(FbxTime::eFrames24) * 20)).Get() << endl;
		;
		Flame flame;
		for (int i = 0; i < indexcounttmp; i++) {
			//位置情報格納
			vec3f temp;
			temp.x = (float) tmpControlPoint[indexes[i]].mData[0];
			temp.y = (float) tmpControlPoint[indexes[i]].mData[1];
			temp.z = (float) tmpControlPoint[indexes[i]].mData[2];

			flame.ver.push_back(temp);

			//cout <<"temp.x="<<(float)temp.x<< " 	temp.y="<<(float)temp.y<< "	temp.z="<<(float)temp.z<<"\n";
		}
		mattemp->flame.push_back(flame);

	}

	delete[] clusterDeformation;
	delete[] clusterWeight;
}

FbxAMatrix Model::GetGeometry(FbxNode* node) {
	FbxVector4 lT = node->GetGeometricTranslation(FbxNode::eSourcePivot);
	FbxVector4 lR = node->GetGeometricRotation(FbxNode::eSourcePivot);
	FbxVector4 lS = node->GetGeometricScaling(FbxNode::eSourcePivot);
	return FbxAMatrix(lT, lR, lS);
}

void Model::ComputeClusterDeformation(FbxAMatrix& pGlobalPosition, FbxMesh* pMesh, FbxCluster* pCluster,
		FbxAMatrix& pVertexTransformMatrix, FbxTime pTime, FbxPose* pPose) {
	FbxCluster::ELinkMode lClusterMode = pCluster->GetLinkMode();

	FbxAMatrix lReferenceGlobalInitPosition;
	FbxAMatrix lReferenceGlobalCurrentPosition;
	FbxAMatrix lAssociateGlobalInitPosition;
	FbxAMatrix lAssociateGlobalCurrentPosition;
	FbxAMatrix lClusterGlobalInitPosition;
	FbxAMatrix lClusterGlobalCurrentPosition;

	FbxAMatrix lReferenceGeometry;
	FbxAMatrix lAssociateGeometry;
	FbxAMatrix lClusterGeometry;

	FbxAMatrix lClusterRelativeInitPosition;
	FbxAMatrix lClusterRelativeCurrentPositionInverse;

	if (lClusterMode == FbxCluster::eAdditive && pCluster->GetAssociateModel()) {
		pCluster->GetTransformAssociateModelMatrix(lAssociateGlobalInitPosition);
		// Geometric transform of the model
		lAssociateGeometry = GetGeometry(pCluster->GetAssociateModel());
		lAssociateGlobalInitPosition *= lAssociateGeometry;
		lAssociateGlobalCurrentPosition = GetGlobalPosition(pCluster->GetAssociateModel(), pTime, pPose, NULL);

		pCluster->GetTransformMatrix(lReferenceGlobalInitPosition);
		// Multiply lReferenceGlobalInitPosition by Geometric Transformation
		lReferenceGeometry = GetGeometry(pMesh->GetNode());
		lReferenceGlobalInitPosition *= lReferenceGeometry;
		lReferenceGlobalCurrentPosition = pGlobalPosition;

		// Get the link initial global position and the link current global position.
		pCluster->GetTransformLinkMatrix(lClusterGlobalInitPosition);
		// Multiply lClusterGlobalInitPosition by Geometric Transformation
		lClusterGeometry = GetGeometry(pCluster->GetLink());
		lClusterGlobalInitPosition *= lClusterGeometry;
		lClusterGlobalCurrentPosition = GetGlobalPosition(pCluster->GetLink(), pTime, pPose, NULL);

		// Compute the shift of the link relative to the reference.
		//ModelM-1 * AssoM * AssoGX-1 * LinkGX * LinkM-1*ModelM
		pVertexTransformMatrix = lReferenceGlobalInitPosition.Inverse() * lAssociateGlobalInitPosition
				* lAssociateGlobalCurrentPosition.Inverse() * lClusterGlobalCurrentPosition
				* lClusterGlobalInitPosition.Inverse() * lReferenceGlobalInitPosition;
	} else {
		pCluster->GetTransformMatrix(lReferenceGlobalInitPosition);
		lReferenceGlobalCurrentPosition = pGlobalPosition;
		// Multiply lReferenceGlobalInitPosition by Geometric Transformation
		lReferenceGeometry = GetGeometry(pMesh->GetNode());
		lReferenceGlobalInitPosition *= lReferenceGeometry;

		// Get the link initial global position and the link current global position.
		pCluster->GetTransformLinkMatrix(lClusterGlobalInitPosition);
		lClusterGlobalCurrentPosition = GetGlobalPosition(pCluster->GetLink(), pTime, pPose, NULL);

		// Compute the initial position of the link relative to the reference.
		lClusterRelativeInitPosition = lClusterGlobalInitPosition.Inverse() * lReferenceGlobalInitPosition;

		// Compute the current position of the link relative to the reference.
		lClusterRelativeCurrentPositionInverse = lReferenceGlobalCurrentPosition.Inverse()
				* lClusterGlobalCurrentPosition;

		// Compute the shift of the link relative to the reference.
		pVertexTransformMatrix = lClusterRelativeCurrentPositionInverse * lClusterRelativeInitPosition;
	}
}
// Scale all the elements of a matrix.
void Model::MatrixScale(FbxAMatrix& pMatrix, double pValue) {
	int i, j;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			pMatrix[i][j] *= pValue;
		}
	}
}
FbxAMatrix Model::GetGlobalPosition(FbxNode* pNode, const FbxTime& pTime, FbxPose* pPose,
		FbxAMatrix* pParentGlobalPosition) {
	FbxAMatrix lGlobalPosition;
	bool lPositionFound = false;
	/*
	 if (pPose) {
	 int lNodeIndex = pPose->Find(pNode);

	 if (lNodeIndex > -1) {
	 // The bind pose is always a global matrix.
	 // If we have a rest pose, we need to check if it is
	 // stored in global or local space.
	 if (pPose->IsBindPose() || !pPose->IsLocalMatrix(lNodeIndex)) {
	 lGlobalPosition = GetPoseMatrix(pPose, lNodeIndex);
	 } else {
	 // We have a local matrix, we need to convert it to
	 // a global space matrix.
	 FbxAMatrix lParentGlobalPosition;

	 if (pParentGlobalPosition) {
	 lParentGlobalPosition = *pParentGlobalPosition;
	 } else {
	 if (pNode->GetParent()) {
	 lParentGlobalPosition = GetGlobalPosition(pNode->GetParent(), pTime, pPose, NULL);
	 }
	 }

	 FbxAMatrix lLocalPosition = GetPoseMatrix(pPose, lNodeIndex);
	 lGlobalPosition = lParentGlobalPosition * lLocalPosition;
	 }

	 lPositionFound = true;
	 }
	 }
	 */
	if (!lPositionFound) {
		// There is no pose entry for that node, get the current global position instead.

		// Ideally this would use parent global position and local position to compute the global position.
		// Unfortunately the equation
		//    lGlobalPosition = pParentGlobalPosition * lLocalPosition
		// does not hold when inheritance type is other than "Parent" (RSrs).
		// To compute the parent rotation and scaling is tricky in the RrSs and Rrs cases.
		lGlobalPosition = pNode->EvaluateGlobalTransform(pTime);
	}

	return lGlobalPosition;
}

FbxAMatrix Model::GetPoseMatrix(FbxPose* pPose, int pNodeIndex) {
	FbxAMatrix lPoseMatrix;
	FbxMatrix lMatrix = pPose->GetMatrix(pNodeIndex);

	memcpy((double*) lPoseMatrix, (double*) lMatrix, sizeof(lMatrix.mData));

	return lPoseMatrix;
}

// Add a value to all the elements in the diagonal of the matrix.
void Model::MatrixAddToDiagonal(FbxAMatrix& pMatrix, double pValue) {
	pMatrix[0][0] += pValue;
	pMatrix[1][1] += pValue;
	pMatrix[2][2] += pValue;
	pMatrix[3][3] += pValue;
}
// Sum two matrices element by element.
void Model::MatrixAdd(FbxAMatrix& pDstMatrix, FbxAMatrix& pSrcMatrix) {
	int i, j;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			pDstMatrix[i][j] += pSrcMatrix[i][j];
		}
	}
}
