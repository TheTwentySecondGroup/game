#include "global.h"
#include "Model.h"


Model::Model(const char* filename)
{
    bzero(Name,'\0');
    strcpy(Name,filename);
    cout<<"A model \""<<filename<<"\" is loading\n";


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

    glEnableClientState(GL_NORMAL_ARRAY);


    for(int i=0;i<mat.size();i++){
        glPushMatrix();
        //material
        GLfloat WhiteMaterial[] = {0.8,0.8,0.8,1};
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,WhiteMaterial);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,WhiteMaterial);
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,WhiteMaterial);
        glMaterialf(GL_FRONT,GL_SHININESS,60.0);


        //texture


        glNormalPointer(GL_FLOAT,sizeof(vec3f),&mat[i].nor[0].x);
        glVertexPointer(3,GL_FLOAT,sizeof(vec3f),&mat[i].ver[0].x);
        glScalef(0.01f,0.01f,0.01f);
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







int Model::getMesh(FbxNode* node){
    FbxNodeAttribute* attr = node->GetNodeAttribute();
    if(attr != NULL){
        if(attr->GetAttributeType()==FbxNodeAttribute::eMesh){
            //syori
            FbxMesh *mesh = node->GetMesh();



            material mattemp;

            int* indexes = mesh->GetPolygonVertices();
            int indexcounttmp = mesh->GetPolygonVertexCount();


            int VerticesCount= mesh->GetControlPointsCount();
            cout<<VerticesCount<<"\n";
            FbxVector4* vec = mesh->GetControlPoints();


            for(int i=0; i<indexcounttmp;i++){
                //位置情報格納
                vec3f temp;
                temp.x=(float)vec[indexes[i]].mData[0];
                temp.y=(float)vec[indexes[i]].mData[1];
                temp.z=(float)vec[indexes[i]].mData[2];
                mattemp.ver.push_back(temp);

                //cout <<"temp.x="<<(float)temp.x<< " 	temp.y="<<(float)temp.y<< "	temp.z="<<(float)temp.z<<"\n";

            }



            //mesh->GetPolygonVertexNormal()

            //mesh->GetPolygonVertexNormal(nor);


            FbxGeometryElementNormal* element = mesh->GetElementNormal();
            int normalCount = mesh->GetElementNormalCount();
            cout<<"normal "<<normalCount<<endl;
            if(normalCount==1){
                if((element->GetReferenceMode() == FbxGeometryElement::eDirect)){
                    if(element->GetMappingMode()==FbxGeometryElement::eByControlPoint){
                        cout<<"controlpoint"<<endl;
                        vector <vec3f>vectemp;
                        for ( int i = 0; i < element->GetDirectArray().GetCount(); ++i ) {
                            vec3f nor;
                            nor.x = (float)element->GetDirectArray().GetAt( i )[ 0 ];
                            nor.y = (float)element->GetDirectArray().GetAt( i )[ 1 ];
                            nor.z = (float)element->GetDirectArray().GetAt( i )[ 2 ];
                            vectemp.push_back(nor);
                        }
                        for(int i=0; i<indexcounttmp;i++){
                            mattemp.nor.push_back(vectemp[indexes[i]]);
                        }
                    }else if(element->GetMappingMode()==FbxGeometryElement::eByPolygonVertex){
                        cout<<"Polygon"<<endl;

                        for ( int i = 0; i < element->GetDirectArray().GetCount(); ++i ) {
                            vec3f nor;
                            nor.x = (float)element->GetDirectArray().GetAt( i )[ 0 ];
                            nor.y = (float)element->GetDirectArray().GetAt( i )[ 1 ];
                            nor.z = (float)element->GetDirectArray().GetAt( i )[ 2 ];
                            mattemp.nor.push_back(nor);
                        }
                    }


                    /*
                       int polygonCount = mesh->GetPolygonCount();
                       vector <FbxVector4>vectemp;
                       for(int i=0;i<polygonCount;i++){
                       int polygonSize=mesh->GetPolygonSize(i);
                       for(int j=0;j<polygonSize;j++){
                       FbxVector4 nor;
                       mesh->GetPolygonVertexNormal(i,j,nor);
                       vectemp.push_back(nor);

                       }
                       }
                       for(int i=0; i<indexcounttmp;i++){
                       vec3f temp;
                       temp.x=(float)vectemp[indexes[i]].mData[0];
                       temp.y=(float)vectemp[indexes[i]].mData[1];
                       temp.z=(float)vectemp[indexes[i]].mData[2];
                       mattemp.nor.push_back(temp);
                       }*/






                }


            }




            mat.push_back(mattemp);

            cout<<"mat.push_back complated\n";
        }
    }

    int childCount = node->GetChildCount();
    for(int i = 0; childCount > i; i++) {
        this->getMesh(node->GetChild(i));
        //if(this->getMesh(node->GetChild(i))==1);//return 1;
    }
    return 1;
}
