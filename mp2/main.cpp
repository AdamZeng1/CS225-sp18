#include "Image.h"
#include "StickerSheet.h"

int main() {

	using namespace cs225;
	
	Image photo; 
	photo.readFromFile("harden.png");
	Image hat;    
	hat.readFromFile("hat.png");
	hat.scale(100,50);
	Image food;
	food.readFromFile("chuan.png");
	food.scale(100,100);
	Image mvp;
	mvp.readFromFile("mvp.png");
	mvp.scale(1.5);
	
	StickerSheet sheet(photo, 5);
	sheet.addSticker(hat, 290, 150);
	sheet.addSticker(food, 195, 90);
	sheet.addSticker(mvp, 20, 20);
	sheet.render().writeToFile("myImage.png");

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  return 0;
}
