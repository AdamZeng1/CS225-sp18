#include "StickerSheet.h"
#include <algorithm>    // std::max
#include <iostream>

using namespace std;
using namespace cs225;

//Initializes this StickerSheet with a base picture and the ability to hold a max number of stickers (Images) with indices 0 through max-1.
//Parameters
//picture	The base picture to use in the StickerSheet
//max	The maximum number of stickers (Images) on this StickerSheet
StickerSheet::StickerSheet(const Image & picture, unsigned 	max){
	picture_ = new Image();
	*picture_ = picture;
	max_ = max;
	num_ = 0;
	stickers_ = new Image*[max];
	x_ = new unsigned[max_];
	y_ = new unsigned[max_];
	empty_ = new bool[max_];
	for (unsigned i=0; i<max ; i++)
	{
		stickers_[i] = new Image();
		x_[i] = 0;
		y_[i] = 0;
		empty_[i] = false;
	}
}

//Frees all space that was dynamically allocated by this StickerSheet.
StickerSheet::~StickerSheet(){
    _destroy_picture();
    _destroy_sticker();
}

//The copy constructor makes this StickerSheet an independent copy of the source.
//Hint: Code is likely shared between all of the "Rule of Three" functions. Would a helper function (or two) make your life easier?
//Parameters
//other	The other StickerSheet object to copy data from
//Member Function Documentation
StickerSheet::StickerSheet(const StickerSheet & other){
	_copy(other);
}

//The assignment operator for the StickerSheet class.
//Hint: Code is likely shared between all of the "Rule of Three" functions. Would a helper function (or two) make your life easier?
//Parameters
//other	The other Scene object to copy data from
//Returns
//a constant Scene reference
const StickerSheet& StickerSheet::operator=(const StickerSheet & other){
    _destroy_picture();
    _destroy_sticker();
	_copy(other);
	return *this;
}

//Modifies the maximum number of stickers that can be stored on this StickerSheet without changing existing stickers' indices.
//If the new maximum number of stickers is smaller than the current number number of stickers, the stickers with indices above max - 1 will be lost.
//Parameters
//max	The new value for the maximum number of Images in the StickerSheet.
void StickerSheet::changeMaxStickers(unsigned max){
	Image ** stickers2 = new Image*[max];
	unsigned * x2 = new unsigned[max];
	unsigned * y2 = new unsigned[max];
	bool * empty2 = new bool[max];
	for (unsigned i=0; i<max ; i++)
	{
		stickers2[i] = new Image();
		x2[i] = 0;
		y2[i] = 0;
		empty2[i] = false;
	}
	if (max < max_)
	{
		for (unsigned i=0; i<max ; i++)
		{
			*(stickers2[i]) = *(stickers_[i]);
			x2[i] = x_[i];
			y2[i] = y_[i];
			empty2[i] = empty_[i];
		}
		num_ = max; // other stickers are deleted.
	}
	else if (max >= max_)
	{
		for (unsigned i=0; i<max_ ; i++)
		{
			*(stickers2[i]) = *(stickers_[i]);
			x2[i] = x_[i];
			y2[i] = y_[i];
			empty2[i] = empty_[i];
		}
	}
    _destroy_sticker();
	stickers_ = stickers2;
	x_ = x2;
	y_ = y2;
	empty_ = empty2;
	max_ = max;
}

//Adds a sticker to the StickerSheet, so that the top-left of the sticker's Image is at (x, y) on the StickerSheet.
//The sticker must be added to the lowest possible layer available.
//Parameters
//sticker	The Image of the sticker.
//x	The x location of the sticker on the StickerSheet
//y	The y location of the sticker on the StickerSheet
//Returns
//The zero-based layer index the sticker was added to, or -1 if the sticker cannot be added.
int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y){
	if (num_ == max_)
	{
		return -1;
	}
	*(stickers_[num_]) = sticker;
	x_[num_] = x;
	y_[num_] = y;
	empty_[num_] = true;
	num_ += 1;
	return num_ - 1 ;
}

//Changes the x and y coordinates of the Image in the specified layer.
//If the layer is invalid or does not contain a sticker, this function must return false. Otherwise, this function returns true.
//Parameters
//index	Zero-based layer index of the sticker.
//x	The new x location of the sticker on the StickerSheet
//y	The new y location of the sticker on the StickerSheet
//Returns
//true if the translate was successful; otherwise false.
bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
	if ( index >= num_ )
	{
		return false;
	}
	x_[index] = x;
	y_[index] = y;
	return true;
}

//Removes the sticker at the given zero-based layer index.
//Parameters
//index	The layer in which to delete the png
void StickerSheet::removeSticker(unsigned index){
	if ( index >= max_ )
	{
		return;
	}
	x_[index] = 0;
	y_[index] = 0;
	delete stickers_[index];
	stickers_[index] = new Image();
	empty_[index] = false;
}

//Returns a pointer to the sticker at the specified index, not a copy of it.
//That way, the user can modify the Image.
//If the index is invalid, return NULL.
//Parameters
//index	The layer in which to get the sticker.
//Returns
//A pointer to a specific Image in the StickerSheet
Image* StickerSheet::getSticker(unsigned index)	const{
	if ( index >= num_ || empty_[index]==false )
	{
		return NULL;
	}
	return stickers_[index];
}


//Renders the whole StickerSheet on one Image and returns that Image.
//The base picture is drawn first and then each sticker is drawn in order starting with layer zero (0), then layer one (1), and so on.
//If a pixel's alpha channel in a sticker is zero (0), no pixel is drawn for that sticker at that pixel. If the alpha channel is non-zero, a pixel is drawn. (Alpha blending is awesome, but not required.)
//The returned Image always includes the full contents of the picture and all stickers. This means that the size of the result image may be larger than the base picture if some stickers go beyond the edge of the picture.
//Returns
//an Image object representing the drawn scene
Image StickerSheet::render() const{
	unsigned width_max, height_max;
	width_max = picture_->width();
	height_max = picture_->height();
	for (unsigned i=0 ; i<num_ ; i++)
	{
		width_max = max(width_max, x_[i]+stickers_[i]->width());
		height_max = max(height_max, y_[i]+stickers_[i]->height());
	}
	Image output;
	output.resize(width_max, height_max);
	//copy the images
	for (unsigned x = 0; x < picture_->width(); x++) 
	for (unsigned y = 0; y < picture_->height(); y++) {		
		HSLAPixel & pixel = picture_->getPixel(x, y);
		HSLAPixel & pixel_out = output.getPixel(x, y);
		pixel_out = pixel;
	}
	for (unsigned i=0; i<num_ ; i++)
	{
		for (unsigned x = x_[i]; x < x_[i] + stickers_[i]->width() ; x++) 
		for (unsigned y = y_[i]; y < y_[i] + stickers_[i]->height() ; y++) {		
			HSLAPixel & pixel = stickers_[i]->getPixel(x-x_[i], y-y_[i]);
			HSLAPixel & pixel_out = output.getPixel(x, y);
			if (pixel.a != 0)
			{
				pixel_out = pixel;
			}
		}
	}
	return output;
}


//destroy function
void StickerSheet::_destroy_picture(){
	if (picture_ != NULL)
	{
		delete picture_;
		picture_ = NULL;
	}
}

//destroy function
void StickerSheet::_destroy_sticker(){
	if (stickers_ != NULL)
	{
		for (unsigned i=0; i<max_ ; i++)
		{
			if (stickers_[i] != NULL)
			{
				delete stickers_[i];
				stickers_[i] = NULL;
			}
		}
		delete[] stickers_;
		stickers_ = NULL;
	}
	if (x_ != NULL && y_ != NULL && empty_ != NULL)
	{
		delete[] x_;
		delete[] y_;
		delete[] empty_;
		x_ = NULL;
		y_ = NULL;
		empty_ = NULL;
	}
}

//copy function
void StickerSheet::_copy(const StickerSheet & other){
	//picture
	this->picture_ = new Image();
	*(this->picture_) = *(other.picture_);
	//max
	this->max_ = other.max_;
	//num
	this->num_ = other.num_;
	//stickers
	this->stickers_ = new Image*[max_];
	for (unsigned i=0; i<max_ ; i++)
	{
		stickers_[i] = new Image();
		*(stickers_[i]) = *(other.stickers_[i]);
	}
	//x_ and y_
	this->x_ = new unsigned[max_];
	this->y_ = new unsigned[max_];
	for (unsigned i=0; i<max_ ; i++)
	{
		x_[i] = other.x_[i];
		y_[i] = other.y_[i];
	}
	//empty_
	this->empty_ = new bool[max_];
	for (unsigned i=0; i<max_ ; i++)
	{
		empty_[i] = other.empty_[i];
	}
}