#include "Color.h"
#include "Model.h"
#include "Raster.h"
#include "Triangle2D.h"
#include "Vector2.h"
#include "Matrix.h"
#include "Color.cpp"
#include "Model.cpp"
#include "Raster.cpp"
#include "Triangle2D.cpp"
#include "Vector2.cpp"
#include "Matrix.cpp"

#include <iostream>
using namespace std;

#define WIDTH 100
#define HEIGHT 100


int main(){
    Raster myRaster(WIDTH,HEIGHT,White);

    Model teapot;
    teapot.readFromOBJFile("./teapot.obj",Red);
    

    Matrix4 modelMatrixTeapot = Translate3D(50,50,-60)*RotateZ3D(45.0)*Scale3D(0.5,0.5,0.5);


    Vector4 eye(50,50,30,1);
    Vector4 spot(50,50,-40,1);
    teapot.performBackfaceCulling(eye,spot);
    

    Matrix4 viewMatrix = LookAt(eye,spot,Vector4(0,1,0,0));

    Matrix4 perspectiveMatrix = Perspective(70.0,myRaster.getWidth()/ myRaster.getHeight(), 0.01, 1000.0);

    Matrix4 viewportMatrix = Viewport(0,0,myRaster.getWidth(), myRaster.getHeight());

    teapot.transform(perspectiveMatrix*viewMatrix*modelMatrixTeapot);
    


    teapot.homogenize();
  

    teapot.transform(viewportMatrix);
   
  
    myRaster.drawModel(teapot);
    

    myRaster.writeToPPM();


} 
