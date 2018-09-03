/**
 * @file DFS.h
 */

#ifndef DFS_H
#define DFS_H

#include <iterator>
#include <cmath>
#include <list>
#include <stack>
#include <vector>
#include <list>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A depth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class DFS : public ImageTraversal {
public:
	DFS(const PNG & png, const Point & start, double tolerance);  
	//Initializes a depth-first ImageTraversal on a given png image, starting at start, and with a given tolerance.
  
	ImageTraversal::Iterator begin();
	//Returns an iterator for the traversal starting at the first point.
	ImageTraversal::Iterator end();
	//Returns an iterator for the traversal one past the end of the traversal.

	void add(const Point & point);
	//Adds a Point for the traversal to visit at some point in the future.
	Point pop();
	//Removes and returns the current Point in the traversal.
	Point peek() const;    
	// Returns the current Point in the traversal.
	bool empty() const;
	//Returns true if the traversal is empty.

private:
	/** @todo [Part 1] */
	/** add private members here*/
	PNG image_;
	Point start_;
	double tolerance_;
    list<Point> list_;  // a list to function as the stack
	//vector<Point> vector_;
	vector<vector<bool>> vec2D;
	bool find_vector(Point point);
	void delete_list(Point point);
};

#endif
