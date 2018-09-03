/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>
#include <stack>
#include <algorithm>    // std::max
using std::stack;
using std::max;
/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
	//your code here
	mirror(root);
}

template <typename T>
void BinaryTree<T>::mirror(Node* subRoot)
{
	if (subRoot == NULL)
	{
		return;
	}
	//your code here
	Node * middle = subRoot->left;
	subRoot->left = subRoot->right;
	subRoot->right = middle;
	mirror(subRoot->left);
	mirror(subRoot->right);
}

/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
	stack<T> s;
	int larger_value;
	InorderTraversal<int> iot(this->getRoot());
	for (TreeTraversal<int>::Iterator it = iot.begin(); it != iot.end(); ++it) {
		s.push((*it)->elem);
	}
	if (!s.empty()){ 
		larger_value = s.top();
		s.pop();
	}
	while (!s.empty())
	{
		if (larger_value < s.top())
		{
			return false;
		}
		larger_value = s.top();
		s.pop();
	}
    return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    return isOrderedRecursive(root);
}

template <typename T>
bool BinaryTree<T>::isOrderedRecursive(Node* subRoot) const
{
	if (subRoot==NULL) return true;
	if (subRoot->left==NULL && subRoot->right==NULL) return true;
	bool out = isOrderedRecursive(subRoot->left) && isOrderedRecursive(subRoot->right);
	if (out == false) return out;
	if (subRoot->left==NULL)
	{
		if (subRoot->elem < MaxValue(subRoot->right)) return true;
		else return false;
	}
	if (subRoot->right==NULL)
	{
		if (subRoot->elem > MaxValue(subRoot->left)) return true;
		else return false;
	}
	if (subRoot->elem > MaxValue(subRoot->left) && subRoot->elem < MaxValue(subRoot->right))
	{
		return true;
	}
    else return false;
}

template <typename T>
int BinaryTree<T>::MaxValue(Node* subRoot) const
{
	InorderTraversal<int> iot(subRoot);
	int max = 0;
	for (TreeTraversal<int>::Iterator it = iot.begin(); it != iot.end(); ++it) {
		if ((*it)->elem > max)
			max = (*it)->elem;
	}
	return max;
}
/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::printPaths(vector<vector<T> > &paths) const
{
	T patharray[200];
	int array_index = 0;
	printPathHelper(root, paths, patharray, array_index);
}

template <typename T>
void BinaryTree<T>::printPathHelper(Node *subRoot, vector<vector<T> > &paths, T patharray[], int array_index) const{
	if (subRoot==NULL) return;
	patharray[array_index] = subRoot->elem;
	array_index = array_index+1;
	if (subRoot->left==NULL && subRoot->right==NULL)   //record this path
	{
		vector<T> v;
		for (int i=0; i<array_index ; i++)
			v.push_back(patharray[i]);
		paths.push_back(v);
	}
	else 
	{
		printPathHelper(subRoot->left, paths, patharray, array_index);
		printPathHelper(subRoot->right, paths, patharray, array_index);
	}
	array_index = array_index-1;
}

/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
	if (root==NULL)
	{
		return -1;
	}
	return sumDistances(root, 0);
}

template <typename T>
int BinaryTree<T>::sumDistances(Node *subRoot, int level) const
{
	if (subRoot->left==NULL && subRoot->right==NULL) return level;
	if (subRoot->left==NULL) 
		return level+sumDistances(subRoot->right, level+1);
	if (subRoot->right==NULL) 
		return level+sumDistances(subRoot->left, level+1);
	else
		return level+sumDistances(subRoot->left, level+1)+sumDistances(subRoot->right, level+1);
}