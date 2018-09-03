#include "cs225/PNG.h"

#ifndef IMAGE_H_
#define IMAGE_H_

class Image : public cs225::PNG
{
	public:
	void lighten();
	void lighten(double amount);
	void darken();
	void darken(double amount);
	void saturate();
	void saturate(double amount);
	void desaturate();
	void desaturate(double amount);
	void grayscale();
	void rotateColor(double degrees);
	void illinify();
	void scale(double factor);
	void scale(unsigned w, unsigned h);
};

#endif
 