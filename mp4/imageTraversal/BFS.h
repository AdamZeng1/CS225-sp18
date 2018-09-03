/**
 * @file BFS.h
 */

#ifndef BFS_H
#define BFS_H

#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A breadth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class BFS : public ImageTraversal {
public:
  BFS(const PNG & png, const Point & start, double tolerance);

  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();
  
  void add(const Point & point);
  Point pop();
  Point peek() const;
  bool empty() const;

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
	bool find_list(Point point);
};

#endif
