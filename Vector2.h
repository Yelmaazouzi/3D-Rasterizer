#ifndef VECTOR2_H
#define VECTOR2_H
#include <math.h>

struct Vector2
{
	public:
    	float x;
		float y;
	
		Vector2();
        Vector2(float pX, float pY);
        Vector2 operator * (float s);
        Vector2 operator + (Vector2& other);
        Vector2 operator - (Vector2& other);
        float magnitude();
        float dot(Vector2 other);
        Vector2 normalize();
        Vector2 perpendicular();
};

struct Vector4
{
	public:
    	float x;
		float y;
        float z;
        float w;
	
		Vector4();
        Vector4(float pX, float pY, float pZ, float pW);
        Vector4 operator * (float s);
        Vector4 operator + (Vector4& other);
        Vector4 operator - (Vector4& other);
        float magnitude();
        float dot(Vector4 other);
        void normalize();
        Vector4 cross(Vector4 other);
};

float determinant(Vector2 a, Vector2 b){
    return b.x*a.y - a.x*b.y;
};

#endif
