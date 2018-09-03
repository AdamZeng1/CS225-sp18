#include <iostream>
/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List() {
	/// @todo Graded in MP3.1
	clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
	/// @todo Graded in MP3.1
	ListNode* pointer = tail_;
	while (pointer != NULL)
	{
		if (pointer->prev != NULL)
		{
			pointer = pointer->prev;
			delete pointer->next;
		}
		else{ 
			delete pointer;
			pointer = NULL;
		}

	}
	head_ = NULL;
	tail_ = NULL;
	length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata) {
	/// @todo Graded in MP3.1
	ListNode* node = new ListNode(ndata);
	if (head_ != NULL)
	{
		node->next = head_;
		head_->prev = node;
		head_ = node;
	}
	else
	{
		head_ = node;
		tail_ = head_;
	}
	length_=length_+1;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T & ndata) {
	/// @todo Graded in MP3.1
	ListNode* node = new ListNode(ndata);
	if (tail_ != NULL)
	{
		tail_->next = node;
		node->prev = tail_;
		tail_ = node;
	}
	else
	{
		head_ = node;
		tail_ = head_;
	}
	length_=length_+1;
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
	/// @todo Graded in MP3.1
	
	if (startPoint==NULL || startPoint->next==NULL)
	{
		return;
	}
	// define 2 pointers
	ListNode * pointer1 = startPoint;
	ListNode * pointer2 = startPoint->next;
	// change the middle points 
	while (pointer1 != endPoint)
	{
		pointer1->next = pointer1->prev;
		pointer1->prev = pointer2;
		pointer1 = pointer2;
		pointer2 = pointer2->next;
	}
	pointer1->next = pointer1->prev;
	pointer1->prev = pointer2;
	//change startpoint and endpoint
	ListNode * start_next_ori = startPoint->next;
	ListNode * end_prev_ori = endPoint->prev;
	if (start_next_ori != NULL && end_prev_ori != NULL)
	{
		start_next_ori->next = endPoint;
		endPoint->prev = start_next_ori;
		end_prev_ori->prev = startPoint;
		startPoint->next = end_prev_ori;
	}
	else if (start_next_ori != NULL && end_prev_ori == NULL)
	{
		start_next_ori->next = endPoint;
		endPoint->prev = start_next_ori;
		startPoint->next = NULL;
	}
	else if (start_next_ori == NULL && end_prev_ori != NULL)
	{
		end_prev_ori->prev = startPoint;
		startPoint->next = end_prev_ori;
		endPoint->prev = NULL;
	}
	pointer1 = startPoint;
	startPoint = endPoint;
	endPoint = pointer1;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
	/// @todo Graded in MP3.1
	int num_block = length_/n + 1;
	ListNode * pointer1 = head_;
	ListNode * pointer2 = head_;
	for (int i=0; i<num_block ; i++)
	{
		if (i<num_block-1)
		{
			pointer2 = pointer1;
			for (int j=0; j<n-1 ; j++)
				pointer2 = pointer2->next;
		}
		else 
			pointer2 = tail_;
		reverse(pointer1, pointer2);
		if (i==0)
			head_ = pointer1;
		if (i==num_block-1)
			tail_ = pointer2;
		pointer1 = pointer2->next;
	}
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
	/// @todo Graded in MP3.1
	ListNode * curr = head_;
	if (curr==NULL || curr==tail_ || curr->next==tail_)
		return;
	ListNode * middle = curr->next;
	while (curr->next!=tail_)
	{
		curr->next = middle->next;
		middle->next->prev = curr;
		middle->prev = tail_;
		middle->next = NULL;
		tail_->next = middle;
		tail_ = middle;
		curr = curr->next;
		middle = curr->next;
	}

}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
	/// @todo Graded in MP3.2
	ListNode * pointer = start;
	for (int i=0; i<splitPoint ; i++)
	{
		pointer = pointer->next;
		if (pointer == NULL)
		{
			return NULL;
		}
	}
	pointer->prev->next = NULL;
	pointer->prev = NULL;
	return pointer;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
	/// @todo Graded in MP3.2
	ListNode * curr1 = first;
	ListNode * curr2 = second;
	if (first == NULL)
	{
		return second;
	}
	if (second == NULL)
	{
		return first;
	}
	if (curr2->data < curr1->data)
	{
		curr1->prev = curr2;
		second = curr2->next;
		if (second != NULL)
			second->prev = NULL;
		curr2->next = curr1;
		first = curr2;
		curr2 = second;
	}
	while (second != NULL)
	{
		if (curr2->data < curr1->data)
		{
			second = curr2->next;
			curr1->prev->next = curr2;
			curr2->prev = curr1->prev;
			curr2->next = curr1;
			curr1->prev = curr2;
			curr2 = second;
		}
		else if (curr1->next != NULL)
		{
			curr1 = curr1->next;
		}
		else
		{
			curr1->next = curr2;
			curr2->prev = curr1;
			second = NULL;
		}
	}
	return first;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
	/// @todo Graded in MP3.2
	//base case
	if (chainLength == 1 || chainLength == 0)
	{
		return start;
	}
	//recursive case
	int length1 = chainLength/2;
	int length2 = chainLength-length1;
	ListNode * middle = split(start, length1);
	return merge(mergesort(start,length1), mergesort(middle,length2));
}
