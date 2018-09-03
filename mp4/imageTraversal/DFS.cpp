#include <iterator>
#include <cmath>
#include <list>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {  
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
ImageTraversal::Iterator DFS::begin() {
	/** @todo [Part 1] */
	DFS* dfs = new DFS(image_,start_,tolerance_);
	return ImageTraversal::Iterator(*dfs, start_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
	/** @todo [Part 1] */
	unsigned x_coord = point.x;
	unsigned y_coord = point.y;
	HSLAPixel & p1 = image_.getPixel(start_.x, start_.y);
	if (x_coord+1<image_.width() && calculateDelta(p1, image_.getPixel(x_coord+1, y_coord))<tolerance_ && !find_vector(Point(x_coord+1, y_coord))){
		//delete_list(Point(x_coord+1, y_coord));
		list_.push_back(Point(x_coord+1, y_coord));
	}
	if (y_coord+1<image_.height() && calculateDelta(p1, image_.getPixel(x_coord, y_coord+1))<tolerance_ && !find_vector(Point(x_coord, y_coord+1))){
		//delete_list(Point(x_coord, y_coord+1));
		list_.push_back(Point(x_coord, y_coord+1));
	}
	if ((int)(x_coord-1)>=0 && calculateDelta(p1, image_.getPixel(x_coord-1, y_coord))<tolerance_ && !find_vector(Point(x_coord-1, y_coord))){
		//delete_list(Point(x_coord-1, y_coord));
		list_.push_back(Point(x_coord-1, y_coord));	
	}
	if ((int)(y_coord-1)>=0 && calculateDelta(p1, image_.getPixel(x_coord, y_coord-1))<tolerance_ && !find_vector(Point(x_coord, y_coord-1))){
		//delete_list(Point(x_coord, y_coord-1));
		list_.push_back(Point(x_coord, y_coord-1));
	}
}

bool DFS::find_vector(Point point) {
	unsigned x_coord = point.x;
	unsigned y_coord = point.y;
	if (vec2D[y_coord][x_coord] == true) return true;
	//for (unsigned i=0 ; i<vector_.size() ; i++)
	//{
	//	if (point == vector_[i]) return true;
	//}
	return false;
}

void DFS::delete_list(Point point) {
	std::list<Point>::iterator it;
	for (it = list_.begin(); it != list_.end(); ++it)
	{
		if (point == *(it)) list_.erase(it);
	}
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
	/** @todo [Part 1] */
	Point out = list_.back();
	unsigned x_coord = out.x;
	unsigned y_coord = out.y;
	vec2D[y_coord][x_coord] = true;
	//vector_.push_back(out);
	list_.pop_back();
	Point out2 = list_.back();
	while (find_vector(out2) && !list_.empty())
	{
		list_.pop_back();
		out2 = list_.back();
	}
	return out;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
	/** @todo [Part 1] */
	return list_.back();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
	/** @todo [Part 1] */
	return list_.empty();
}
