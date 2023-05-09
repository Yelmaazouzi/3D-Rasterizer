#include "Color.h"
#include <cmath>
#include <iostream>

using namespace std;

Color::Color(){
        red = 0.0;
        green = 0.0;
        blue = 0.0;
        alpha = 0.0;
}
Color::Color(float pRed, float pGreen, float pBlue,float pAlpha){ 
        red = pRed;
        green = pGreen;
        blue = pBlue;
        alpha = pAlpha;
        clamp();
}

void Color::clamp(){
            red = fmax(0.0, fmin(red, 1.0));
            blue = fmax(0.0, fmin(blue, 1.0));
            green = fmax(0.0, fmin(green, 1.0));
            alpha = fmax(0.0, fmin(alpha, 1.0));
}

Color Color::operator + (const Color& other){
        Color color;
        color.red = red + other.red;
        color.green = green + other.green;
        color.blue = blue +other.blue;
        color.alpha = alpha +other.alpha;
        
        color.clamp();        
        return color;
}

Color Color::operator-(const Color& other){
        Color color;
        color.red = red - other.red;
        color.green = green - other.green;
        color.blue = blue - other.blue;
        color.alpha = alpha - other.alpha;
        
        color.clamp();        
        return color;
}

Color Color::operator * (float x){
        Color color;   
        color.red = red * x;
        color.green = green * x;
        color.blue = blue * x;
        color.alpha = alpha * x;
        color.clamp();
        return color;
}
 

