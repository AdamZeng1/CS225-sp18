#ifndef STICKERSHEET_H_
#define STICKERSHEET_H_

#include "Image.h"
#include "cs225/PNG.h"
#include <iostream>

class StickerSheet
{
	public:
	StickerSheet(const Image & picture, unsigned max);
	~StickerSheet();
	StickerSheet(const StickerSheet & other);
	const StickerSheet & operator=(const StickerSheet & other);
	void changeMaxStickers(unsigned max);
	int addSticker(Image & sticker, unsigned x, unsigned y);
	bool translate(unsigned index, unsigned x, unsigned y);
	void removeSticker(unsigned index);
	Image * getSticker(unsigned index) const;
	Image render() const;

	private:
	Image * picture_;
	Image ** stickers_;
	unsigned * x_;
	unsigned * y_;
	bool * empty_; // whether the sticker is empty.
	unsigned max_;
	unsigned num_;
    void _copy(const StickerSheet &);
    void _destroy_picture();
    void _destroy_sticker();
};

#endif
 