#include <iostream>
#include "Raster.h"
#include <math.h>
#include <fstream>
#include <limits>


Raster::Raster(){
    width = 0;
    height = 0;
    pixels = NULL;
    depthPixels = NULL; 
}

Raster::Raster(int pWidth, int pHeight,Color pFillColor){
    width = pWidth;
    height = pHeight;
    pixels = new Color[pWidth*pHeight];
    
    for(int i = 0; i < (pWidth*pHeight); i++)
        pixels[i] = pFillColor;

    depthPixels = new float[pWidth*pHeight];

	for(int i = 0; i < (pWidth*pHeight); i ++){
        depthPixels[i] = numeric_limits<float>::max();
    }
}

Raster::~Raster(){
    delete[] pixels;
    delete[] depthPixels;
}

int Raster::getWidth(){
    return width;
}

int Raster::getHeight(){
    return height;
}

Color Raster::getColorPixel(int x,int y){
    if(x < 0 || x > width - 1|| y < 0 || y > height - 1){
        return White; 
    }
    int temp = height - y - 1;
    int pixel = temp * width + x;
    return pixels[pixel];
}

float Raster::getDepthPixel(int x, int y)
{
    if(x < 0 || x > width - 1|| y < 0 || y > height - 1){
        return 0; 
    }
    int temp = height - y - 1;
    int myPixel = temp * width + x;
    return depthPixels[myPixel];
}

void Raster::setColorPixel(int x, int y, Color pFillColor){
    if(x < 0 || x > width - 1|| y < 0 || y > height - 1){
        return;
    }
    int temp = height - y - 1;
    int pixel = temp * width + x;
    pixels[pixel] = pFillColor;
}

void Raster::setDepthPixel(int x, int y, float depth)
{
    if(x < 0 || x > width - 1|| y < 0 || y > height - 1){
        return;
    }
    int temp = height - y - 1;
    int myPixel = temp * width + x;
    depthPixels[myPixel] = depth;
}

void Raster::clear(Color pFillColor){
    for(int i = 0; i < (width*height); i++)
        pixels[i] = pFillColor;
}

void Raster::clear(float pDepth)
{
    for(int i = 0;i < width * height; i ++)
    {
        depthPixels[i] = pDepth;
    }
}

void Raster::writeToPPM(){
     ofstream myfile;
  myfile.open("FRAME_BUFFER.ppm");
  myfile << "P3\n";
  myfile << width << " " << height << "\n";
  myfile << "255\n";
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int index = i * width + j;
      Color c = pixels[index];
      myfile << (int)(c.red * 255) << " " << (int)(c.green * 255) << " " << (int)(c.blue * 255) << " ";
    }
    myfile << "\n";
  }
  myfile.close();
}

void Raster::drawLine_DDA(float x1, float y1, float x2, float y2, Color fillColor){
    int dx = x2 - x1;
    int dy = y2 - y1;
 
    int s = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
 
    float Xi = dx /(float) s;
    float Yi = dy /(float) s;
 
    float X = x1;
    float Y = y1;
    for (int i = 0; i <= s; i++)
    {   setColorPixel(round(X),round(Y),fillColor);  
        X += Xi;          
        Y += Yi;  
    }
}
void Raster::drawLine_DDA_Interpolated(float x1, float y1, float x2, float y2, Color color1,Color color2){
    Vector2 v1(x1,y1);
    Vector2 v2(x2,y2);
    Color pColor;
    float ratio;
    float dist;
    float length = (v2-v1).magnitude(); 

    int dx = x2 - x1;
    int dy = y2 - y1;

    int s = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
 
    float Xi = dx /(float) s;
    float Yi = dy /(float) s;
 
    float X = x1;
    float Y = y1;

    for (int i = 0; i <= s; i++)
    {   Vector2 Vi(X,Y);
        dist = (Vi-v1).magnitude(); 
        ratio = dist/length;
        pColor = (color2 * ratio) + (color1 * (1.0 - ratio));

        setColorPixel(X,Y,pColor);  
        X += Xi;          
        Y += Yi;  
    }

}

void Raster::drawTriangle2D_DotProduct(Triangle2D triangle){
    int xmin=round(fmin(triangle.v1.x,fmin(triangle.v2.x,triangle.v3.x)));
    int ymin=round(fmin(triangle.v1.y,fmin(triangle.v2.y,triangle.v3.y)));

    int xmax=round(fmax(triangle.v1.x,fmax(triangle.v2.x,triangle.v3.x)));
    int ymax=round(fmax(triangle.v1.y,fmax(triangle.v2.y,triangle.v3.y)));

    xmin = fmax(0, xmin);
	xmax = fmin(width, xmax);
	ymin = fmax(0,ymin);
	ymax = fmin(height, ymax); 

    for(int x=xmin;x<= xmax;x++){
        for(int y=ymin;y<= ymax;y++){
            Vector2 p(x,y);

            Vector2 edge1 = triangle.v2-triangle.v1;
            Vector2 edgeperp1 = edge1.perpendicular();
            Vector2 g1 = p-triangle.v1;
            float result1 = edgeperp1.dot(g1);  

            Vector2 edge2 = triangle.v3-triangle.v2;
            Vector2 edgeperp2 = edge2.perpendicular();
            Vector2 g2 = p-triangle.v2;
            float result2 = edgeperp2.dot(g2); 

            Vector2 edge3 = triangle.v1-triangle.v3;
            Vector2 edgeperp3 = edge3.perpendicular();
            Vector2 g3 = p-triangle.v3;
            float result3 = edgeperp3.dot(g3); 

            if (result1 >= 0 && result2 >= 0 && result3 >= 0){ 
                 setColorPixel(x,y,triangle.c1);
            }

        }
    }
    
}

void Raster::drawTriangle3D_Barycentric(Triangle3D t){
    if (t.shouldDraw == false){
		return;
    }
	int xMin = fmax(0, fmin(fmin(floor(t.v1.x), floor(t.v2.x)), floor(t.v3.x)));
	int xMax = fmin(getWidth(), fmax(fmax(ceil(t.v1.x), ceil(t.v2.x)), ceil(t.v3.x)));
	int yMin = fmax(0, fmin(fmin(floor(t.v1.y), floor(t.v2.y)), floor(t.v3.y)));
	int yMax = fmin(getHeight(), fmax(fmax(ceil(t.v1.y), ceil(t.v2.y)), ceil(t.v3.y)));
    
	Triangle2D myTri(t);

	for (int x = xMin; x < xMax; x++){
		for (int y = yMin; y < yMax; y++){
			
			float lambda1 = 0.0;
			float lambda2 = 0.0;
			float lambda3 = 0.0;

			myTri.calculateBarycentricCoordinates(Vector2(float(x) + 0.5, float(y) + 0.5), lambda1, lambda2, lambda3);

			if (lambda1 >= 0.0 && lambda2 >= 0.0 && lambda3 >= 0.0){
				float setDepth = t.v1.z*lambda1+ t.v2.z*lambda2+ t.v3.z*lambda3;
				if (setDepth < getDepthPixel(x,y)){
					setDepthPixel(x, y, setDepth);
					setColorPixel(x, y, t.c1*lambda1 + t.c2*lambda2 + t.c3*lambda3);
				}
			}
		}
	}
}

void Raster::drawModel(Model model){
    for(int i = 0; i<model.numTriangles();i++){
        Triangle3D t = model[i];
		drawTriangle3D_Barycentric(t);
    }
}








