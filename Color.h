#ifndef COLOR_H
#define COLOR_H
#define Red Color(1.0,0.0,0.0,1.0)
#define Blue Color(0.0,0.0,1.0,1.0)
#define Green Color(0.0,1.0,0.0,1.0)
#define Black Color(0.0,0.0,0.0,1.0)
#define White Color(1.0,1.0,1.0,1.0)


struct Color
{
	public:
    	float red;
		float green;
        float blue;
        float alpha;
	
		Color();	// Default Constructor
        Color(float pRed, float pGreen, float pBlue,float pAlpha);
        void clamp();
        Color operator + (const Color& other);
        Color operator - (const Color& other);
        Color operator * (float x);
};

#endif