#include"Vector2.h"

Vector2::Vector2(){
    x =0.0;
    y = 0.0;
}

Vector2::Vector2(float pX,float pY){
    x = pX;
    y = pY;
}

Vector2 Vector2::operator * (float s){
    Vector2 v;
    v.x = x*s;
    v.y = y*s;
    return v;
}

Vector2 Vector2 ::operator + (Vector2& other){
    Vector2 v;
    v.x = x + other.x;
    v.y = y + other.y;
    return v;
}

Vector2 Vector2::operator - (Vector2& other){
    Vector2 v;
    v.x = x - other.x;
    v.y = y - other.y;
    return v;
}

float Vector2::magnitude(){
    return sqrt(pow(x,2.0)+pow(y,2.0));
}

float Vector2::dot(Vector2 other){
    return x*other.x+y*other.y;
}

Vector2 Vector2::normalize(){
    float factor = magnitude();
    x = (1 / factor) * x;
    y = (1 / factor) * y;
    return Vector2(x,y);
}

Vector2 Vector2::perpendicular(){
    return Vector2(-y,x);
}

Vector4::Vector4(){
    x = 0.0;
    y = 0.0;
    z = 0.0;
    w = 0.0;
}
Vector4::Vector4(float pX, float pY, float pZ, float pW){
    x = pX;
    y = pY;
    z = pZ;
    w = pW;
}
Vector4 Vector4::operator * (float s){
    Vector4 v;
    v.x = x*s;
    v.y = y*s;
    v.z = z*s;
    v.w = w*s;
    return v;
}

Vector4 Vector4::operator + (Vector4& other){
    Vector4 v;
    v.x = x + other.x;
    v.y = y + other.y;
    v.z = z + other.z;
    v.w = w + other.w;
    return v;
}

Vector4 Vector4::operator - (Vector4& other){
    Vector4 v;
    v.x = x - other.x;
    v.y = y - other.y;
    v.z = z - other.z;
    v.w = w - other.w;
    return v;
}

float Vector4::magnitude(){
    return sqrt(pow(x,2.0)+pow(y,2.0)+pow(z,2.0)+pow(w,2.0));
}

void Vector4::normalize(){
    float factor = magnitude();
    x = (1 / factor) * x;
    y = (1 / factor) * y;
    z = (1/ factor) * z;
}

float Vector4::dot(Vector4 other){
    return x*other.x+y*other.y+z*other.z+w*other.w;
}

Vector4 Vector4::cross(Vector4 other){
    Vector4 vec;
    vec.x = y * other.z - z * other.y;
    vec.y = z * other.x - x * other.z;
    vec.z = x * other.y - y * other.x;
    return  vec;
}


















