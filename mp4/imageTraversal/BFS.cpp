#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {  
	/** @todo [Part 1] */
    image_ = png;
	start_ = start;
	tolerance_ = tolerance;
	list_.push_back(start);
	vec2D.resize(image_.height(), vector<bool>(image_.width(), false));
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
	/** @todo [Part 1] */
	BFS* bfs = new BFS(image_,start_,tolerance_);
	return ImageTraversal::Iterator(*bfs, start_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
	/** @todo [Part 1] */
	unsigned x_coord = point.x;
	unsigned y_coord = point.y;
	HSLAPixel & p1 = image_.getPixel(start_.x, start_.y);
	if (x_coord+1<image_.width() && calculateDelta(p1, image_.getPixel(x_coord+1, y_coord))<tolerance_ && !find_vector(Point(x_coord+1, y_coord))){
		//if (!find_list(Point(x_coord+1, y_coord)))
			list_.push_back(Point(x_coord+1, y_coord));
	}
	if (y_coord+1<image_.height() && calculateDelta(p1, image_.getPixel(x_coord, y_coord+1))<tolerance_ && !find_vector(Point(x_coord, y_coord+1))){
		//if (!find_list(Point(x_coord, y_coord+1)))
			list_.push_back(Point(x_coord, y_coord+1));
	}
	if ((int)(x_coord-1)>=0 && calculateDelta(p1, image_.getPixel(x_coord-1, y_coord))<tolerance_ && !find_vector(Point(x_coord-1, y_coord))){
		//if (!find_list(Point(x_coord-1, y_coord)))
			list_.push_back(Point(x_coord-1, y_coord));
	}
	if ((int)(y_coord-1)>=0 && calculateDelta(p1, image_.getPixel(x_coord, y_coord-1))<tolerance_ && !find_vector(Point(x_coord, y_coord-1))){
		//if (!find_list(Point(x_coord, y_coord-1)))
			list_.push_back(Point(x_coord, y_coord-1));
	}
}

bool BFS::find_vector(Point point) {
	unsigned x_coord = point.x;
	unsigned y_coord = point.y;
	if (vec2D[y_coord][x_coord] == true) return true;
	//for (unsigned i=0 ; i<vector_.size() ; i++)
	//{
	//	if (point == vector_[i]) return true;
	//}
	return false;
}

bool BFS::find_list(Point point) {
	std::list<Point>::iterator it;
	for (it = list_.begin(); it != list_.end(); ++it)
	{
		if (point == *(it)) return true;
	}
	return false;
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
	/** @todo [Part 1] */
	Point out = list_.front();
	unsigned x_coord = out.x;
	unsigned y_coord = out.y;
	vec2D[y_coord][x_coord] = true;
	//vector_.push_back(out);
	list_.pop_front();
	Point out2 = list_.front();
	while (find_vector(out2) && !list_.empty())
	{
		list_.pop_front();
		out2 = list_.front();
	}
	return out;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
	/** @todo [Part 1] */
	return list_.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
	/** @todo [Part 1] */
	return list_.empty();
}
