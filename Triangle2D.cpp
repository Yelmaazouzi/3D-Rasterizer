#include"Triangle2D.h"
#include <iostream>

using namespace std;

Triangle2D::Triangle2D(){
    Vector2 v1(0.0,0.0);
    Vector2 v2(0.0,0.0);
    Vector2 v3(0.0,0.0);

    c1=Black;
    c2=Black;
    c3=Black;
}

Triangle2D::Triangle2D(Vector2 p1, Vector2 p2, Vector2 p3, Color b1, Color b2, Color b3){
    v1=p1;
    v2=p2;
    v3=p3;

    c1=b1;
    c2=b2;
    c3=b3;
}

Triangle2D::Triangle2D(Triangle3D t){
    v1 = Vector2(t.v1.x,t.v1.y);
	v2 = Vector2(t.v2.x,t.v2.y);
	v3 = Vector2(t.v3.x,t.v3.y);
    c1 = t.c1;
    c2 = t.c2;
    c3 = t.c3;
}

void Triangle2D::calculateBarycentricCoordinates(Vector2 P,float& lambda1,float& lambda2,float& lambda3){
    float area = determinant(v2 - v3, v1 - v3);
    lambda1 = determinant(v2 - v3, P - v3) / area;
    lambda2 = determinant(P - v3, v1 - v3) / area;
    lambda3 = 1.0 - lambda1 - lambda2;

}

Triangle3D::Triangle3D(){
    v1 = Vector4(0.0 ,0.0, 0.0, 1.0);
    v2 = Vector4(0.0 ,0.0, 0.0, 1.0);
    v3 = Vector4(0.0 ,0.0, 0.0, 1.0);
    c1 = White, c2 = White, c3 = White;
    shouldDraw = true;
}

Triangle3D::Triangle3D(Vector4 pV1, Vector4 pV2, Vector4 pV3, Color pC1, Color pC2, Color pC3){
    v1 = pV1, v2 = pV2, v3 = pV3;
    c1 = pC1, c2 = pC2, c3 = pC3;
}

void Triangle3D::transform(Matrix4 matrix){
    v1 = matrix * v1;
    v2 = matrix * v2;
    v3 = matrix * v3;
}










