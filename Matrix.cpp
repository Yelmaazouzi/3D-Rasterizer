#include <iostream>
#include <math.h>
#include "Matrix.h"

using namespace std;

Matrix4::Matrix4(){
    ix = 1.0,jx = 0.0,kx = 0.0,ox = 0.0;
    iy = 0.0,jy = 1.0,ky = 0.0,oy = 0.0;
    iz = 0.0,jz = 0.0,kz = 1.0,oz = 0.0;
    iw = 0.0,jw = 0.0,kw = 0.0,ow = 1.0;
}

Matrix4::Matrix4(float pix,float pjx,float pkx, float pox,
                 float piy,float pjy,float pky, float poy,
                 float piz,float pjz,float pkz, float poz,
                 float piw,float pjw,float pkw, float pow){

    ix = pix,jx = pjx,kx = pkx,ox = pox;
    iy = piy,jy = pjy,ky = pky,oy = poy;
    iz = piz,jz = pjz,kz = pkz,oz = poz;
    iw = piw,jw = pjw,kw = pkw,ow = pow;
}

Vector4 Matrix4::operator *(Vector4 vector){
    Vector4 v;
    v.x = ix * vector.x + jx * vector.y + kx * vector.z + ox * vector.w;
    v.y = iy * vector.x + jy * vector.y + ky * vector.z + oy * vector.w;
    v.z = iz * vector.x + jz * vector.y + kz * vector.z + oz * vector.w;
    v.w = iw * vector.x + jw * vector.y + kw * vector.z + ow * vector.w;
    return v;
}

Matrix4 Matrix4::operator * (Matrix4 b){
    Matrix4 a;
    a.ix = (b.ix)*ix + (b.iy)*jx + (b.iz)*kx + (b.iw)*ox;
    a.iy = (b.ix)*iy + (b.iy)*jy + (b.iz)*ky + (b.iw)*oy;
    a.iz = (b.ix)*iz + (b.iy)*jz + (b.iz)*kz + (b.iw)*oz;
    a.iw = (b.ix)*iw + (b.iy)*jw + (b.iz)*kw + (b.iw)*ow;

    a.jx = (b.jx)*ix + (b.jy)*jx + (b.jz)*kx + (b.jw)*ox;
    a.jy = (b.jx)*iy + (b.jy)*jy + (b.jz)*ky + (b.jw)*oy;
    a.jz = (b.jx)*iz + (b.jy)*jz + (b.jz)*kz + (b.jw)*oz;
    a.jw = (b.jx)*iw + (b.jy)*jw + (b.jz)*kw + (b.jw)*ow;

    a.kx = (b.kx)*ix + (b.ky)*jx + (b.kz)*kx + (b.kw)*ox;
    a.ky = (b.kx)*iy + (b.ky)*jy + (b.kz)*ky + (b.kw)*oy;
    a.kz = (b.kx)*iz + (b.ky)*jz + (b.kz)*kz + (b.kw)*oz;
    a.kw = (b.kx)*iw + (b.ky)*jw + (b.kz)*kw + (b.kw)*ow;

    a.ox = (b.ox)*ix + (b.oy)*jx + (b.oz)*kx + (b.ow)*ox;
    a.oy = (b.ox)*iy + (b.oy)*jy + (b.oz)*ky + (b.ow)*oy;
    a.oz = (b.ox)*iz + (b.oy)*jz + (b.oz)*kz + (b.ow)*oz;
    a.ow = (b.ox)*iw + (b.oy)*jw + (b.oz)*kw + (b.ow)*ow;   
    return a;
}

void Matrix4::print(){
    cout <<ix<<" "<<jx<<" "<<kx<<" "<<ox<< endl;
    cout <<iy<<" "<<jy<<" "<<ky<<" "<<oy<< endl;
    cout <<iz<<" "<<jz<<" "<<kz<<" "<<oz<< endl;
    cout <<iw<<" "<<jw<<" "<<kw<<" "<<ow<< endl;
    
}

Matrix4 Translate3D(float tX, float tY,float tZ){
    Matrix4 m(1,0,0,tX,0,1,0,tY,0,0,1,tZ,0,0,0,1);
    return m;
}

Matrix4 Scale3D(float sX, float sY, float sZ) {
	Matrix4 m(sX,0,0,0,0,sY,0,0,0,0,sZ,0,0,0,0,1);
    return m;
}

Matrix4 RotateX3D(float degrees){
    float rad = degrees * M_PI / 180.0;
    Matrix4 m(1,0,0,0,0,cos(rad),sin(rad), 0,0,-sin(rad),cos(rad),0,0,0,0,1);
    return m;
}

Matrix4 RotateY3D(float degrees){
    float rad = degrees * M_PI / 180.0;
    Matrix4 m(cos(rad),0,-sin(rad),0,0,1, 0, 0,sin(rad), 0,cos(rad),0,0,0,0,1);
    return m;
}

Matrix4 RotateZ3D(float degrees){
    float rad = degrees * M_PI / 180.0;
    Matrix4 m(cos(rad),sin(rad),0, 0,-sin(rad),cos(rad),0, 0, 0,0, 1,0,0,0,0,1);
    return m;
}

Matrix4 Rotate3D (float degreesX,float degreesY,float degreesZ){
    return RotateX3D(degreesX)*RotateY3D(degreesY)*RotateZ3D(degreesZ);
}

Matrix4 Rotate3D(float degrees, Vector4 vec){
    Matrix4 m;
    float rad = degrees * M_PI / 180.0;
    float alpha = atanf(vec.x/vec.z);
    float beta = acos(vec.y/vec.magnitude());
    return RotateY3D(-alpha)*RotateX3D(-beta)*RotateY3D(degrees)*RotateX3D(beta)*RotateY3D(alpha);
}

Matrix4 LookAt(Vector4 eye, Vector4 spot, Vector4 up)
{
    Matrix4 m;

    Vector4 look = (spot - eye);
    look.normalize();
    Vector4 right = look.cross(up);
    right.normalize();
    up = right.cross(look);
    up.normalize();

    
    m.ix = right.x;
    m.jx = right.y;
    m.kx = right.z;

    m.iy = up.x;
    m.jy = up.y;
    m.ky = up.z;

    m.iz = -look.x;
    m.jz = -look.y;
    m.kz = -look.z;

    Matrix4 matrix = m * Translate3D(-eye.x,-eye.y,-eye.z);
    return matrix;
}

Matrix4 Orthographic(float minX, float maxX, float minY, float maxY,float minZ, float maxZ)
{
    Matrix4 m = Scale3D(2/(maxX - minX), 2/(maxY - minY), 2/(maxZ - minZ))*Translate3D(-((minX + maxX) / 2), -((minY + maxY) / 2), -((minZ + maxZ) / 2));

    return m;
}

Matrix4 Perspective(float fovY, float aspect, float nearZ, float farZ)
{
    Matrix4 m;
    float y = tanf(fovY/2);
    float F = 1 / y;
    m.ix = F / aspect;
    m.jy = F;
    m.kz = (farZ + nearZ) / (nearZ - farZ);
    m.kw = -1;
    m.oz = (2 * nearZ * farZ) / (nearZ - farZ);
    m.ow = 0;
    return m;
}

Matrix4 Viewport(float x, float y, float width, float height)
{
    return Translate3D(x,y,0) * Scale3D(width, height, 1) * Scale3D(0.5,0.5,0.5) * Translate3D(1,1,-1);
}







