#include "Model.h"
#include <fstream>
#include <sstream>

Model::Model(){
    vector<unsigned char> triangles;
}

int Model::numTriangles(){
    return triangles.size();
}

Triangle3D Model::operator[ ](int i){
    return triangles[i];
}

void Model::transform(Matrix4 m){
    for(int i= 0; i<numTriangles();i++){
        if(triangles[i].shouldDraw == true){
            triangles[i].transform(m);
        }
    }
}

void Model::readFromOBJFile(string filepath, Color pFillColor){
	ifstream ifile(filepath.c_str());
	string line;
	vector<string> words;
	vector<Vector4> vertices;
	vector<Triangle3D> vectriangles;

	if (ifile.is_open())
	{
		while (getline(ifile, line)){

			istringstream s(line);

			std::string sub;
			while (s >> sub){
				words.push_back(sub);
			}
			if (words.size() > 0){
				if (words[0] == "v"){
					// Vertex
					vertices.push_back(Vector4(atof(words[1].c_str()), atof(words[2].c_str()), atof(words[3].c_str()),1.0));
				}
				else if (words[0] == "f"){
					// Face
					triangles.push_back(Triangle3D(vertices[atoi(words[1].c_str()) - 1], vertices[atoi(words[2].c_str()) - 1], vertices[atoi(words[3].c_str()) - 1], pFillColor, pFillColor, pFillColor));
				}
				words.clear();
			}
		}
	}
	ifile.close();
}

void Model::homogenize()
{
    for(int i = 0; i < numTriangles();i++){
        float t1 = triangles[i].v1.w;
        triangles[i].v1.x /= t1;
        triangles[i].v1.y /= t1;
        triangles[i].v1.z /= t1;
        triangles[i].v1.w /= t1;
        
        float t2 = triangles[i].v2.w;
        triangles[i].v2.x /= t2;
        triangles[i].v2.y /= t2;
        triangles[i].v2.z /= t2;
        triangles[i].v2.w /= t2;

        float t3 = triangles[i].v3.w;
        triangles[i].v3.x /= t3;
        triangles[i].v3.y /= t3;
        triangles[i].v3.z /= t3;
        triangles[i].v3.w /= t3;
    }
    return;
}

void Model::performBackfaceCulling(Vector4 eye, Vector4 spot)
{  
    Vector4 look =  spot - eye;
    look.normalize();
    for(int i = 0; i < numTriangles();i++){
        Vector4 p1 = triangles[i].v3 - triangles[i].v2;
        Vector4 p2 = triangles[i].v1 - triangles[i].v2;
        Vector4 normal = p1.cross(p2);
        normal.normalize();
        if(look.dot(normal) < 0.0){
            triangles[i].shouldDraw = false;
        }
        else{
            triangles[i].shouldDraw = true;
        }
    }
}

