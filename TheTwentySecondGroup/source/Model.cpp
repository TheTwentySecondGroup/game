#include "global.h"
#include "Model.h"


Model::Model()
{
	bzero(Name,'\0');
	strcpy(Name,"UnityChan/Models/unitychan.fbx");
	//strcpy(Name,"UnityChan/Models/BoxUnityChan.fbx");

	//Name="UnityChan/Models/unitychan.fbx";
    cout<<"A model has been built!\n";


    FbxManager *manager = FbxManager::Create();

    FbxIOSettings *ioSettings = FbxIOSettings::Create(manager, IOSROOT);
    manager->SetIOSettings(ioSettings);

    FbxImporter *importer=FbxImporter::Create(manager,"");
    importer->Initialize(Name,-1,manager->GetIOSettings());

    FbxScene *scene = FbxScene::Create(manager,"tempName");

    importer->Import(scene);

    //三角化
    FbxGeometryConverter geometryConverter(manager);
    geometryConverter.Triangulate(scene, true);
    geometryConverter.SplitMeshesPerMaterial(scene,true);
    importer->Destroy();


    FbxNode* rootNode = scene->GetRootNode();

    if(rootNode) {
        this->getMesh(rootNode);

    }

}

Model::~Model()
{
    cout<<"A model has been destroied!\n";
}




void Model::Draw()
{


    //int i,j;
    //cout<<"numIndices="<< numIndices<<"\n";
    //cout<<mat.size()<<"\n";


	glEnableClientState(GL_VERTEX_ARRAY);

	//glEnableClientState(GL_NORMAL_ARRAY);

	for(int i=0;i<mat.size();i++){
    	//cout<<mat[i].ver.size()<<"\n";
    	//for(int j=0;j<mat[i].ver.size();j++){
		glPushMatrix();
    		//material
    		GLfloat WhiteMaterial[] = {0.8,0.8,0.8,1};
    		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,WhiteMaterial);
    		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,WhiteMaterial);
    		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,WhiteMaterial);
    		glMaterialf(GL_FRONT,GL_SHININESS,60.0);


    		//texture

    		glVertexPointer(3,GL_FLOAT,sizeof(vec3f),&mat[i].ver[0].x);
    		glScalef(0.01f,0.01f,0.01f);
    		glDrawArrays(GL_TRIANGLES, 0, mat[i].ver.size());
    		cout<< mat[i].ver.size()<<"\n";

    		glPopMatrix();

    	//}

    }
	glDisableClientState(GL_VERTEX_ARRAY);


	//glDisableClientState(GL_NORMAL_ARRAY);




    /*
       for(int i=0;i<
       glBegin(GL_POLYGON);
       glTexCoord2i(0,0);
       glVertex3fv(vertices[1]);
       glTexCoord2i(0,1);
       glVertex3fv(vertices[4]);
       glTe+0xCoord2i(1,1);
       glVertex3fv(vertices[7]);
       glTexCoord2i(1,0);
       glVertex3fv(vertices[2]);
       glEnd();

     */



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








    // glDrawElements(GL_TRIANGLES,36,GL_INT,indices);
}
/*
void Model::InitializeVertexBuffer(vertex *vertices)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,0,vertices);
    //glDrawArrays(GL_TRIANGLES,0,36);
}*/

int Model::getMesh(FbxNode* node){
    FbxNodeAttribute* attr = node->GetNodeAttribute();
    if(attr != NULL){
        if(attr->GetAttributeType()==FbxNodeAttribute::eMesh){
            //syori
            FbxMesh *mesh = node->GetMesh();


            /*
            numPoligons=mesh->GetPolygonCount();
            cout<<"numPoligons="<< numPoligons<<"\n";

            cout<<"numVertices="<< numVertices<<"\n";

            cout<<"numIndexes="<< numIndexes<<"\n";
            numIndices+=mesh->GetPolygonVertexCount();
            */



           material mattemp;

           int* indexes = mesh->GetPolygonVertices();
           int indexcounttmp = mesh->GetPolygonVertexCount();
           //for(int i=0;i<indexcounttmp;i++){
        	   //cout<<indexcounttmp<<"\n";
              // mattemp.index.push_back(indexes[i]);
           //}


            int VerticesCount= mesh->GetControlPointsCount();
            cout<<VerticesCount<<"\n";
            FbxVector4* vec = mesh->GetControlPoints();
            for(int i=0; i<indexcounttmp;i++){
            	//cout<<VerticesCount<<"\n";
            	//位置情報格納

           //FbxVector4* vec = mesh->GetControlPoints();
           //
            	vec3f temp;

            	temp.x=(float)vec[indexes[i]].mData[0];
            	temp.y=(float)vec[indexes[i]].mData[1];
            	temp.z=(float)vec[indexes[i]].mData[2];

            	mattemp.ver.push_back(temp);
            	//mattemp.ver.push_back(temp.y);
            	//mattemp.ver.push_back(temp.z);

            	cout <<"temp.x="<<(float)temp.x<< " 	temp.y="<<(float)temp.y<< "	temp.z="<<(float)temp.z<<"\n";

				//mattemp.ver.push_back(temp);

            }




			mat.push_back(mattemp);

			cout<<"mat.push_back complated\n";
            /*
            numIndexes=mesh->GetPolygonVertexCount();
            int* index = mesh->GetPolygonVertices();
            indexes = new int[numIndexes] ;
            for(int i=0; i<numIndexes;i++){
                indexes[i]=index[i];
            }
            poligonsSize = new int[numPoligons];
            for (int i=0;i<numPoligons;i++){
                poligonsSize[i]=mesh->GetPolygonSize(i);
            }*/

            // this->getPos(FbxMesh *mesh);
            //return 1;
        }
    }

    int childCount = node->GetChildCount();
    //cout<<"childCOunt"<<childCount;
    for(int i = 0; childCount > i; i++) {
        if(this->getMesh(node->GetChild(i))==1);//return 1;
    }
    return 1;
}

