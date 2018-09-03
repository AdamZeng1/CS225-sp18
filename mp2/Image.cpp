#include "Image.h"

using namespace cs225;

//Lighten an Image by increasing the luminance of every pixel by 0.1.
//This function ensures that the luminance remains in the range [0, 1].
void Image::lighten(){
	for (unsigned x = 0; x < this->width(); x++) {
	for (unsigned y = 0; y < this->height(); y++) {
		HSLAPixel & pixel = this->getPixel(x, y);
		//HSLAPixel * pixel1 = image1.getPixel(image2.width()-1-x, image2.height()-1-y);
		//pixel2->s = pixel1->s;
		//pixel2->h = pixel1->h;
		pixel.l = pixel.l + 0.1;
		if (pixel.l > 1)
		{
			pixel.l = 1.0;
		}
		//pixel2->a = pixel1->a;
	}
	}
}


//Lighten an Image by increasing the luminance of every pixel by amount.
//This function ensures that the luminance remains in the range [0, 1].
//Parameters
//amount	The desired increase in luminance.
void Image::lighten(double amount){
	for (unsigned x = 0; x < this->width(); x++) {
	for (unsigned y = 0; y < this->height(); y++) {
		HSLAPixel & pixel = this->getPixel(x, y);
		pixel.l = pixel.l + amount;
		if (pixel.l > 1)
		{
			pixel.l = 1.0;
		}
	}
	}
}


//Darken an Image by decreasing the luminance of every pixel by 0.1.
//This function ensures that the luminance remains in the range [0, 1].
void Image::darken(){
	for (unsigned x = 0; x < this->width(); x++) {
	for (unsigned y = 0; y < this->height(); y++) {
		HSLAPixel & pixel = this->getPixel(x, y);
		pixel.l = pixel.l - 0.1;
		if (pixel.l < 0)
		{
			pixel.l = 0.0;
		}
	}
	}
}


//Darkens an Image by decreasing the luminance of every pixel by amount.
//This function ensures that the luminance remains in the range [0, 1].
//Parameters
//amount	The desired decrease in luminance.
void Image::darken(double amount){
	for (unsigned x = 0; x < this->width(); x++) {
	for (unsigned y = 0; y < this->height(); y++) {
		HSLAPixel & pixel = this->getPixel(x, y);
		pixel.l = pixel.l - amount;
		if (pixel.l < 0)
		{
			pixel.l = 0.0;
		}
	}
	}
}


//Saturates an Image by increasing the saturation of every pixel by 0.1.
//This function ensures that the saturation remains in the range [0, 1].
void Image::saturate(){
	for (unsigned x = 0; x < this->width(); x++) {
	for (unsigned y = 0; y < this->height(); y++) {
		HSLAPixel & pixel = this->getPixel(x, y);
		pixel.s = pixel.s + 0.1;
		if (pixel.s > 1)
		{
			pixel.s = 1.0;
		}
	}
	}
}


//Saturates an Image by increasing the saturation of every pixel by amount.
//This function ensures that the saturation remains in the range [0, 1].
//Parameters
//amount	The desired increase in saturation.
void Image::saturate(double amount){
	for (unsigned x = 0; x < this->width(); x++) {
	for (unsigned y = 0; y < this->height(); y++) {
		HSLAPixel & pixel = this->getPixel(x, y);
		pixel.s = pixel.s + amount;
		if (pixel.s > 1)
		{
			pixel.s = 1.0;
		}
	}
	}
}


//Desaturates an Image by decreasing the saturation of every pixel by 0.1.
//This function ensures that the saturation remains in the range [0, 1].
void Image::desaturate(){
	for (unsigned x = 0; x < this->width(); x++) {
	for (unsigned y = 0; y < this->height(); y++) {
		HSLAPixel & pixel = this->getPixel(x, y);
		pixel.s = pixel.s - 0.1;
		if (pixel.s < 0)
		{
			pixel.s = 0.0;
		}
	}
	}
}


//Desaturates an Image by decreasing the saturation of every pixel by amount.
//This function ensures that the saturation remains in the range [0, 1].
//Parameters
//amount	The desired decrease in saturation.
void Image::desaturate(double amount){
	for (unsigned x = 0; x < this->width(); x++) {
	for (unsigned y = 0; y < this->height(); y++) {
		HSLAPixel & pixel = this->getPixel(x, y);
		pixel.s = pixel.s - amount;
		if (pixel.s < 0)
		{
			pixel.s = 0.0;
		}
	}
	}
}


//Turns the image grayscale.
void Image::grayscale(){
}


//Rotates the color wheel by degrees.
//This function ensures that the hue remains in the range [0, 360].
//Parameters
//degrees	The desired amount of rotation.
void Image::rotateColor(double degrees){
	for (unsigned x = 0; x < this->width(); x++) {
	for (unsigned y = 0; y < this->height(); y++) {
		HSLAPixel & pixel = this->getPixel(x, y);
		pixel.h = pixel.h + degrees;
		if (pixel.h > 360)
		{
			pixel.h = pixel.h - 360;
		}
		else if (pixel.h < 0)
		{
			pixel.h = pixel.h + 360;
		}
	}
	}
}


//Illinify the image.
void Image::illinify(){
}


//Scale the Image by a given factor.
//For example:
//A factor of 1.0 does not change the iamge.
//A factor of 0.5 results in an image with half the width and half the height.
//A factor of 2 results in an image with twice the width and twice the height.
//This function both resizes the Image and scales the contents.
//Parameters
//factor	Scale factor.
void Image::scale(double factor){
	int newWidth = factor*width();
	int newHeight = factor*height();
	PNG* image2 = new PNG(*this);
	resize(newWidth,newHeight);
	for (unsigned x = 0; x < this->width(); x++) {
	for (unsigned y = 0; y < this->height(); y++) {
		unsigned x2 = (1.0*x)/factor;
		unsigned y2 = (1.0*y)/factor;		
		HSLAPixel & pixel = this->getPixel(x, y);
		HSLAPixel & pixel2 = image2->getPixel(x2, y2);
		pixel = pixel2;
	}
	}
}


//Scales the image to fit within the size (w x h).
//This function preserves the aspect ratio of the image, so the result will always be an image of width w or of height h (not necessarily both).
//This function both resizes the Image and scales the contents.
//Parameters
//w	Desired width of the scaled Iamge
//h	Desired height of the scaled Image
void Image::scale(unsigned w, unsigned h){
	double factor_w = (1.0*w)/this->width();
	double factor_h = (1.0*h)/this->height();
	PNG* image2 = new PNG(*this);
	resize(w,h);
	for (unsigned x = 0; x < this->width(); x++) {
	for (unsigned y = 0; y < this->height(); y++) {
		unsigned x2 = (1.0*x)/factor_w;
		unsigned y2 = (1.0*y)/factor_h;		
		HSLAPixel & pixel = this->getPixel(x, y);
		HSLAPixel & pixel2 = image2->getPixel(x2, y2);
		pixel = pixel2;
	}
	}
}