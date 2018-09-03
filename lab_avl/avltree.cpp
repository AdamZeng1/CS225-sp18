/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
 #include <algorithm>
 #include <iostream>
 using namespace std;

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
	Node * t2 = t->right;   // don't pass by reference
	t->right = t2->left;
	t2->left = t;
    t->height = max(heightOrNeg1(t->left), heightOrNeg1(t->right))+1;
    t2->height = max(heightOrNeg1(t2->left), heightOrNeg1(t2->right))+1; 
	t = t2;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
	Node * t2 = t->left;
	t->left = t2->right;
	t2->right = t;
    t->height = max(heightOrNeg1(t->left), heightOrNeg1(t->right))+1;
    t2->height = max(heightOrNeg1(t2->left), heightOrNeg1(t2->right))+1; 
	t = t2;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);

}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
	int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
	if (subtree->left != NULL)
	{
		int leftbalance = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
		if (balance == -2)
		{
			if (leftbalance == 1) rotateLeftRight(subtree);
			else rotateRight(subtree);
		}
	}
	if (subtree->right != NULL)
	{
		int rightbalance = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
		if (balance == 2)
		{
			if (rightbalance == -1) rotateRightLeft(subtree);
			else rotateLeft(subtree);
		}
	}
	return;
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
	if (subtree==NULL) {
		subtree = new Node(key,value);
		return;
	}
	else if (key < subtree->key) insert(subtree->left, key, value);
	else if (key > subtree->key) insert(subtree->right, key, value);
	subtree->height = 1+max(heightOrNeg1(subtree->left),heightOrNeg1(subtree->right));
	rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL) return;
    if (key < subtree->key) {
		// your code here
		remove(subtree->left,key);
    } else if (key > subtree->key) {
		// your code here
		remove(subtree->right,key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
			/* no-child remove */
			delete subtree;
			subtree = NULL;
			return;
        } else if (subtree->left != NULL && subtree->right != NULL) {
			/* two-child remove */
			// your code here
			Node* temp = subtree->left;
			while (temp->right!=NULL) temp = temp->right;
			K key_temp = temp->key;
			V value_temp = temp->value;
			remove(subtree, key_temp);
			subtree->key = key_temp;
			subtree->value = value_temp;
        } else {
			// one-child remove 
			if (subtree->left == NULL)
			{
				Node * node2 = subtree;
				subtree = subtree->right;
				delete node2;
				node2 = NULL;
			}
			else if (subtree->right == NULL)
			{
				Node * node2 = subtree;
				subtree = subtree->left;
				delete node2;
				node2 = NULL;
			}
        }
		// your code here
    }
	subtree->height = 1+max(heightOrNeg1(subtree->left),heightOrNeg1(subtree->right));
	rebalance(subtree);

}
