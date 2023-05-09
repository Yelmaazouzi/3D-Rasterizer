#ifndef MATRIX_H
#define MATRIX_H
#include "Vector2.h"

struct Matrix4
{
    public:
    float ix,jx,kx,ox;
    float iy,jy,ky,oy;
    float iz,jz,kz,oz;
    float iw,jw,kw,ow;


    Matrix4();
    Matrix4(float pix,float pjx,float pkx, float pox,
            float piy,float pjy,float pky, float poy,
            float piz,float pjz,float pkz, float poz,
            float piw,float pjw,float pkw, float pow);
    Vector4 operator * (Vector4 v);
    Matrix4 operator * (Matrix4 b);
    void print();

};

Matrix4 Translate3D(float tX, float tY,float tZ);
Matrix4 Scale3D(float sX, float sY, float sZ);
Matrix4 RotateX3D(float degrees);
Matrix4 RotateY3D(float degrees);
Matrix4 RotateZ3D(float degrees);
Matrix4 Rotate3D (float degreesX,float degreesY,float degreesZ);
Matrix4 Rotate3D(float degrees, Vector4 vec);
Matrix4 LookAt(Vector4 eye,Vector4 spot,Vector4 up);
Matrix4 Orthographic(float minX, float maxX, float minY, float maxY,float minZ, float maxZ);
Matrix4 Perspective(float fovY, float aspect, float nearZ, float farZ);
Matrix4 Viewport(float x, float y, float width, float height);


#endif