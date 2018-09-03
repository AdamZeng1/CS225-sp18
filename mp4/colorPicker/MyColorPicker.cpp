#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
	HSLAPixel pixel;
	pixel.s = 1;  // Saturation of the pixel, [0,1]
	pixel.h = 360-360.0*y/400;  // Hue of the pixel, in degree [0,360)
	pixel.l = 0.1;  // Luminance of the pixel, [0,1]
	pixel.a = 1;  // Alpha of the pixel, [0,1]
  return pixel;
}
