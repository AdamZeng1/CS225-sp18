#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <cstdlib>
#include <string>

using namespace cs225;


void rotate(std::string inputFile, std::string outputFile) {
  // Part 2
  PNG image1;
  image1.readFromFile(inputFile);
  unsigned int W = image1.width();
  unsigned int H = image1.height();
  PNG image2(W,H);

  for (unsigned x = 0; x < image2.width(); x++) {
    for (unsigned y = 0; y < image2.height(); y++) {
      HSLAPixel * pixel2 = image2.getPixel(x, y);
      HSLAPixel * pixel1 = image1.getPixel(image2.width()-1-x, image2.height()-1-y);
      pixel2->s = pixel1->s;
      pixel2->h = pixel1->h;
      pixel2->l = pixel1->l;
      pixel2->a = pixel1->a;
    }
  }

  image2.writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  // Part 3
 /* 
  for (unsigned x = 0; x < png.width(); x++) {
    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel * pixel = png.getPixel(x, y);
      pixel->s = 1;  // Saturation of the pixel, [0,1]
      pixel->h = 360-360.0*y/png.height();  // Hue of the pixel, in degree [0,360)
      pixel->l = 0.1;  // Luminance of the pixel, [0,1]
      pixel->a = 1;  // Alpha of the pixel, [0,1]
    }
  }*/
  
  double a[5][6] = {  
   {0.195, -0.488, 0.344, 0.433, 0.4431, 0.2452} ,  
   {0.462, 0.414, -0.252, 0.361, 0.2511, 0.5692} , 
   {-0.058, -0.07, 0.453, -0.111, 0.5976, 0.0969},  
   {-0.035, 0.07, -0.469, -0.022, 0.4884, 0.5069},  
   {-0.637, 0, 0, 0.501, 0.8562, 0.2513} 
  };
  double x0,x1,y0,y1 = 0;
  for (int i=0; i<20000000; i++)
  {
	double r = ((double) rand() / (RAND_MAX)) ;
	if (r<=0.25)
	{
        x1=a[0][0]*x0+a[0][1]*y0+a[0][4];
        y1=a[0][2]*x0+a[0][3]*y0+a[0][5];
	}
	if (r>0.25 && r<=0.5)
	{
        x1=a[1][0]*x0+a[1][1]*y0+a[1][4];
        y1=a[1][2]*x0+a[1][3]*y0+a[1][5];
	}
	if (r>0.5 && r<=0.75)
	{
        x1=a[2][0]*x0+a[2][1]*y0+a[2][4];
        y1=a[2][2]*x0+a[2][3]*y0+a[2][5];
	}
	if (r>0.75 & r<=0.95)
	{
        x1=a[3][0]*x0+a[3][1]*y0+a[3][4];
        y1=a[3][2]*x0+a[3][3]*y0+a[3][5];
	}
	if (r>0.95 && r<=1)
	{
        x1=a[4][0]*x0+a[4][1]*y0+a[4][4];
        y1=a[4][2]*x0+a[4][3]*y0+a[4][5];
	}
    x0=x1;y0=y1;
//cout << int((x1+1)*400) << int(y1*400) << endl;
      int W = png.width()-int((x1+0.1)*png.width()/1.15);
	  int H = png.height()-int(y1*png.height());
      HSLAPixel * pixel = png.getPixel(W, H);
      pixel->s = 1;  // Saturation of the pixel, [0,1]
      pixel->h = 360.0*H/png.height();  // Hue of the pixel, in degree [0,360)
      pixel->l = 0.5;  // Luminance of the pixel, [0,1]
      pixel->a = 1;  // Alpha of the pixel, [0,1]
//cout << pixel->h << endl;
  }

  return png;
}
