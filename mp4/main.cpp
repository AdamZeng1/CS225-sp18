
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

	// @todo [Part 3]
	// - The code below assumes you have an Animation called `animation`
	// - The code provided below produces the `myFloodFill.png` file you must
	//   submit Part 3 of this assignment -- uncomment it when you're ready.
	PNG png;       png.readFromFile("art.png");
	  
	FloodFilledImage image(png);
	DFS dfs(png, Point(40, 40), 0.05);
	BFS bfs(png, Point(40, 40), 0.05);
	MyColorPicker mycolor;
	HSLAPixel pixel1(100, 1, 0.5);
	HSLAPixel pixel2(10, 1, 0.5);
	Point center(0,0);
	GradientColorPicker gradient(pixel1,pixel2,center,250);
	image.addFloodFill( bfs, gradient );
	image.addFloodFill( dfs, mycolor );
	Animation animation = image.animate(1000);
	PNG secondFrame = animation.getFrame(1);
	PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );

	lastFrame.writeToFile("myFloodFill.png");
	animation.write("myFloodFill.gif");

	/*
	PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
	lastFrame.writeToFile("myFloodFill.png");
	animation.write("myFloodFill.gif");
	*/


  return 0;
}
