/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <stack>
#include <iostream>
#include <cmath>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
	//@todo Implement this function!
	if (first[curDim]!=second[curDim]) return (first[curDim]<second[curDim]);
	return (first<second);
}

template<int Dim>
double KDTree<Dim>::distance(const Point<Dim> & point1, const Point<Dim> & point2) const
{
    double d = 0;
	for(int i = 0; i < Dim; i++){
		d+=(point1[i]-point2[i])*(point1[i]-point2[i]);
	}
	return d;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
	//@todo Implement this function!
	if (distance(target,potential)<distance(target,currentBest)) return true;
	if (distance(target,potential)>distance(target,currentBest)) return false;
	return (potential<currentBest);
}

template<int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>> & Points, int left, int right, int pivotIndex, int d){
	Point<Dim> pivotValue = Points[pivotIndex];
	Point<Dim> temp = Points[right];
	Points[right] = Points[pivotIndex];
	Points[pivotIndex] = temp;  //swap Points[pivotIndex] and Points[right]  
	int storeIndex = left;
	for (int i=left; i<right; i++) {
		if (smallerDimVal(Points[i], pivotValue, d)) {
			temp = Points[i];
			Points[i] = Points[storeIndex];
			Points[storeIndex] = temp;  //swap Points[storeIndex] and Points[i]  
			storeIndex++;
		}
	}
	temp = Points[storeIndex];
	Points[storeIndex] = Points[right];
	Points[right] = temp;  //swap Points[right] and Points[storeIndex]  
	return storeIndex;
}

// Returns the k-th smallest element of the vector within left..right inclusive
// (i.e. left <= k <= right).
// The search space within the array is changing for each round - but the list
// is still the same size. Thus, k does not need to be updated with each round.
// d is the splitting dimension
template<int Dim>
void KDTree<Dim>::select(vector<Point<Dim>> & Points, int left, int right, int k, int d){
	if (left==right) return;
	int pivotIndex = (left+right)/2;  // select a pivotIndex between left and right, can be random
	pivotIndex = partition(Points, left, right, pivotIndex, d);
	// The pivot is in its final sorted position
	if (k == pivotIndex) return;
	else if (k < pivotIndex) return select(Points, left, pivotIndex-1, k, d);
	else return select(Points, pivotIndex+1, right, k, d);
	return;
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::createtree(vector<Point<Dim>>& Points, int left, int right, int d)
{

	if (right < left) return NULL;
	KDTreeNode * node = new KDTreeNode();
	int middle = (left+right)/2;
	select(Points, left, right, middle, d%Dim);
	node->point = Points[middle];
	node->left = createtree(Points, left, middle-1, (d+1)%Dim);
	node->right = createtree(Points, middle+1, right, (d+1)%Dim);
	return node;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
	//@todo Implement this function!
	vector<Point<Dim>> Points(newPoints);
	size = Points.size();
	root = createtree(Points, 0, Points.size()-1, 0);
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree& other) 
	: root(copy(other.root))
{
	//@todo Implement this function!
	size = other.size();
}

template <int Dim>
void KDTree<Dim>::clear()
{
    clear(root);
    root = NULL;
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::copy(const KDTreeNode* subRoot)
{
    if (subRoot == NULL)
        return NULL;

    // Copy this node and it's children
    KDTreeNode* newNode = new KDTreeNode(subRoot->point);
    newNode->left = copy(subRoot->left);
    newNode->right = copy(subRoot->right);
    return newNode;
}

template <int Dim>
void KDTree<Dim>::clear(KDTree<Dim>::KDTreeNode* subRoot)
{
    if (subRoot == NULL)
        return;

    clear(subRoot->left);
    clear(subRoot->right);
    delete subRoot;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree& rhs) {
	//@todo Implement this function!
    if (this != &rhs) {
        clear(root);
        root = copy(rhs.root);
		size = rhs.size();
    }
	return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
	//@todo Implement this function!
	clear(root);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::forwardtraversal(const Point<Dim>& query, KDTreeNode* subRoot, 
																int d, int & bottom_d, double & Dist, stack<KDTreeNode*> & parents, 
																stack<bool> & direction) const{
	if (query == subRoot->point)
	{
		parents.push(subRoot);
		direction.push(true);
		Dist = 0;
		bottom_d = d;
		return subRoot;
	}
	//go left
	if (smallerDimVal(query, subRoot->point, d)){
		//update the stacks
		parents.push(subRoot);
		direction.push(true);
		if (subRoot->left != NULL)
			return forwardtraversal(query, subRoot->left, (d+1)%Dim, bottom_d, Dist, parents, direction);
		else{
			Dist = distance(query, subRoot->point);     // The optimum distance
			bottom_d = d;              // The partition used in the leaf nodes
			return subRoot;
		}
	}
	//go right
	else{
		parents.push(subRoot);
		direction.push(false);
		if (subRoot->right != NULL)
			return forwardtraversal(query, subRoot->right, (d+1)%Dim, bottom_d, Dist, parents, direction);
		else{
			Dist = distance(query, subRoot->point);
			bottom_d = d;
			return subRoot;
		}
	}
	return subRoot;
}

// check if hypersphere exists across the boundary
template <int Dim>
bool KDTree<Dim>::hypersphere_check(const Point<Dim>& query, const Point<Dim>& target, 
									int d, double & Dist) const{
	Point<Dim> boundary = query;
	boundary.set(d, target[d]);
	if (distance(query,boundary)<=Dist) return true;
	return false;
}

template <int Dim>
void KDTree<Dim>::backwardtraversal(const Point<Dim>& query, KDTreeNode* subRoot, KDTreeNode* & nearnode, 
									int d, double & Dist, stack<KDTreeNode*> & parents, stack<bool> & direction) const{
	// current node near query point
	if (distance(query, subRoot->point)<Dist){
		Dist = distance(query, subRoot->point);
		nearnode = subRoot;
	}
	else if (distance(query, subRoot->point)==Dist){
		if (subRoot->point < nearnode->point)
			nearnode = subRoot;
	}
	// update the stacks
	bool direction_top = direction.top();
	parents.pop();
	direction.pop();
	// check the child 
	if (hypersphere_check(query, subRoot->point, d, Dist)){
		if (direction_top==true && subRoot->right!=NULL){
			KDTreeNode* subnearnode = subRoot;//new KDTreeNode();
			double subDist = NearestNeighbor(query, subRoot->right, subnearnode, (d+1)%Dim);
			if ((subDist<Dist) || (subDist==Dist && subnearnode->point<nearnode->point)){
				nearnode = subnearnode;
				Dist = subDist;
			}
		}
		else if (direction_top==false && subRoot->left!=NULL){
			KDTreeNode* subnearnode = subRoot;//new KDTreeNode();
			double subDist = NearestNeighbor(query, subRoot->left, subnearnode, (d+1)%Dim);
			if ((subDist<Dist) || (subDist==Dist && subnearnode->point<nearnode->point)){
				nearnode = subnearnode;
				Dist = subDist;
			}
		}
	}
	// check the parent
	if (!parents.empty()){
		KDTreeNode* parent = parents.top();
		//if (hypersphere_check(query, parent->point, (d-1+Dim)%Dim, Dist))
			backwardtraversal(query, parent, nearnode, (d-1+Dim)%Dim, Dist, parents, direction);
	}
	return;
}

template <int Dim>
double KDTree<Dim>::NearestNeighbor(const Point<Dim>& query, KDTreeNode* subRoot,
									KDTreeNode* & nearnode, int d) const{
	stack<KDTreeNode*> * parents = new stack<KDTreeNode*>();
	stack<bool> * direction = new stack<bool>();
	int *bottom_d = new int();
	double *Dist = new double();
	//forward search
	KDTreeNode* node = forwardtraversal(query, subRoot, d, *bottom_d, *Dist, *parents, *direction);
	nearnode = node; // set the nearest node
	//backward search
	backwardtraversal(query, node, nearnode, *bottom_d, *Dist, *parents, *direction);
	double dist = *Dist;
	delete parents;
	delete direction;
	delete bottom_d;
	delete Dist;
	return dist;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
	//@todo Implement this function!
	KDTreeNode* nearnode = root;//new KDTreeNode();
	double Dist = NearestNeighbor(query, root, nearnode, 0);
	KDTreeNode* node = nearnode;
	return nearnode->point;
}