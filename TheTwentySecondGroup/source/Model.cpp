#include "global.h"
#include "Model.h"


Model::Model()
{
    char filename[256] = "UnityChan/Models/unitychan.fbx";
    cout<<"A model has been built!\n";

    numVertices=0;
    numIndices=0;

    FbxManager *manager = FbxManager::Create();

    FbxIOSettings *ioSettings = FbxIOSettings::Create(manager, IOSROOT);
    manager->SetIOSettings(ioSettings);

    FbxImporter *importer=FbxImporter::Create(manager,"");
    importer->Initialize(filename,-1,manager->GetIOSettings());

    FbxScene *scene = FbxScene::Create(manager,"tempName");

    importer->Import(scene);
    importer->Destroy();

    FbxNode* rootNode = scene->GetRootNode();
    this->SetModelName(filename);
    if(rootNode) { 
        //this->GetFbxInfo(rootNode); 
        this->getMesh(rootNode); 

    }

}

Model::~Model()
{
    cout<<"A model has been destroied!\n";
}


void Model::ShowDetails()
{
    cout<<"Name:"<<Name<<"\n";
    cout<<"Vertices Number:"<<numVertices<<"\n";
    //cout<<"Indices which i never get:"<<indices<<"\n";

}

char* Model::GetModelName()
{
    return Name;
}

void Model::SetModelName(char *x)
{
    strcpy(Name,x);
}

void Model::GetFbxInfo( FbxNode* Node )
{

    int numKids = Node->GetChildCount();
    FbxNode *childNode = 0;

    for ( int i=0 ; i<numKids ; i++)
    {
        childNode = Node->GetChild(i);
        FbxMesh *mesh = childNode->GetMesh();

        if ( mesh != NULL)
        {
            //Get Vertices
            int numVerts = mesh->GetControlPointsCount();

            for ( int j=0; j<numVerts; j++)
            {
                FbxVector4 vert = mesh->GetControlPointAt(j);
                vertices[numVertices].x = (float)vert.mData[0];
                vertices[numVertices].y = (float)vert.mData[1];
                vertices[numVertices++].z=(float)vert.mData[2];
                cout<<vertices[numVertices-1].x<<" "<<vertices[numVertices-    1].y<<" "<<vertices[numVertices-1].z<<"\n";
                this->InitializeVertexBuffer(vertices);
            }
            //Get Indices
            int *indices = mesh->GetPolygonVertices();
            numIndices+=mesh->GetPolygonVertexCount();
        }
        this->GetFbxInfo(childNode);
    }
}

void Model::Draw()
{ 

    GLfloat WhiteMaterial[] = {0.8,0.8,0.8,1};
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,WhiteMaterial);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,WhiteMaterial);
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,WhiteMaterial);
    glMaterialf(GL_FRONT,GL_SHININESS,60.0);



    int i,j;
    cout<<"numIndices="<< numIndices<<"\n";
    for(i=0;i<numIndices-3;i++){
        glBegin(GL_TRIANGLES);
        //glNormal3f(normals[i*3+0],normals[i*3+1],normals[i*3+2]); 
        for(j=i;j<=i+2;j++) {
            //cout<<"ver  x ";cout<<vertices[indexes[j]].x <<"\n";
            //cout<<"     y ";cout<<vertices[indexes[j]].y<< "\n" ;
            //cout<<"     Z ";cout<<vertices[indexes[j]].z<<"\n";
            glVertex3f(vertices[indexes[j]].x,vertices[indexes[j]].y,vertices[indexes[j]].z);
        }   
        glEnd();
    }
    cout<<"----------------------------------------------------------------------------------------\n";


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
void Model::InitializeVertexBuffer(vertex *vertices)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,0,vertices);
    //glDrawArrays(GL_TRIANGLES,0,36);
}

int Model::getMesh(FbxNode* node){
    FbxNodeAttribute* attr = node->GetNodeAttribute();
    if(attr != NULL){
        if(attr->GetAttributeType()==FbxNodeAttribute::eMesh){
            //syori
            FbxMesh *mesh = node->GetMesh();

            numPoligons=mesh->GetPolygonCount();
            cout<<"numPoligons="<< numPoligons<<"\n";
            numVertices= mesh->GetControlPointsCount();
            cout<<"numVertices="<< numVertices<<"\n";
            numIndexes=mesh->GetPolygonVertexCount();
            cout<<"numIndexes="<< numIndexes<<"\n";
            numIndices+=mesh->GetPolygonVertexCount();


            //
            FbxVector4* vec = mesh->GetControlPoints();
            int* index = mesh->GetPolygonVertices();
            vertices = new vertex[numVertices] ;
            for(int i=0; i<numVertices;i++){
                vertices[i].x=(float)vec[i][0];
                vertices[i].y=(float)vec[i][1];
                vertices[i].z=(float)vec[i][2];
            } 
            indexes = new int[numIndexes] ;
            for(int i=0; i<numIndexes;i++){
                indexes[i]=index[i];
            }
            poligonsSize = new int[numPoligons];
            for (int i=0;i<numPoligons;i++){
                poligonsSize[i]=mesh->GetPolygonSize(i);
            }

            // this->getPos(FbxMesh *mesh);
            return 1;
        }
    }

    int childCount = node->GetChildCount();
    for(int i = 0; childCount > i; i++) {
        if(this->getMesh(node->GetChild(i))==1)return 1;
    }
}

void Model::getPos(FbxMesh* mesh){
    numPoligons=mesh->GetPolygonCount();

    numVertices= mesh->GetControlPointsCount();


}



