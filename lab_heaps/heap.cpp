
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
	// @TODO Update to return the index you are choosing to be your root.
	return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
	// @TODO Update to return the index of the left child.
	return 2*currentIdx;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
	// @TODO Update to return the index of the right child.
	return 2*currentIdx+1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
	// @TODO Update to return the index of the parent.
	return currentIdx/2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
	// @TODO Update to return whether the given node has a child
	if (_elems.size()>leftChild(currentIdx))
		return true;
	return false;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
	// @TODO Update to return the index of the child with highest priority
	///   as defined by higherPriority()
	if (_elems.size() == leftChild(currentIdx)+1)
		return leftChild(currentIdx);
	if (higherPriority(_elems[leftChild(currentIdx)], _elems[rightChild(currentIdx)]))
		return leftChild(currentIdx);
    return rightChild(currentIdx);
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
	// @TODO Implement the heapifyDown algorithm.
	if (hasAChild(currentIdx))
	{
		size_t minChildIndex = maxPriorityChild(currentIdx);
		if (_elems[currentIdx] > _elems[minChildIndex])
		{
			std::swap(_elems[currentIdx], _elems[minChildIndex]);
			heapifyDown(minChildIndex);
		}
	}
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
	// @TODO Depending on your implementation, this function may or may
	///   not need modifying
	_elems.push_back(0);
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
	// @TODO Construct a heap using the buildHeap algorithm
	_elems.push_back(0);
	_elems.resize(elems.size()+1);
	for (int i=elems.size()-1; i>=0; i--)
	{
		_elems[i+1] = elems[i];
		heapifyDown(i+1);
	}
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
	// @TODO Remove, and return, the element with highest priority
	T elem = peek();
	_elems[root()] = _elems[_elems.size()-1];
	_elems.pop_back();
	heapifyDown(root());
    return elem;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
	// @TODO Return, but do not remove, the element with highest priority
    return _elems[root()];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
	// @TODO Add elem to the heap
	_elems.push_back(elem);
	heapifyUp(_elems.size()-1);
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
	// @TODO Determine if the heap is empty
	if (_elems.size()==1)
		return true;
	return false;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}