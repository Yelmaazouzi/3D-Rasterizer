#ifndef MODEL_H
#define MODEL_H
#include <vector>
#include "Triangle2D.h"
#include <string>

using namespace std;

class Model{
    public:
    vector<Triangle3D> triangles;

    Model();
    int numTriangles();
    Triangle3D operator[ ](int i);
    void transform(Matrix4 m);
    void readFromOBJFile(string filepath, Color pFillColor);
    void homogenize();
    void performBackfaceCulling(Vector4 eye, Vector4 spot);

};



#endif