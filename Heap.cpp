#include"Heap.h"

/* *~*~*
 The private member function _reHeapUp rearranges the heap after insert by moving the
 last item up to the correct location in the heap
 *~**/
template<class ItemType>
void Heap<ItemType>::_reHeapUp(int lastndx, int comp(ItemType&, ItemType&))
{
	ItemType temp;
	int parentIndex;
	if (lastndx) // means lastndx != 0, i.e. newElement is not heap's root
	{
		while (lastndx > 0) {
			parentIndex = (lastndx - 1) / 2;
			if (comp(heapAry[lastndx], heapAry[parentIndex]) == 1)
				return;
			else {
				temp = heapAry[lastndx];
				heapAry[lastndx] = heapAry[parentIndex];
				heapAry[parentIndex] = temp;
				lastndx = parentIndex;
			}
		}
	}
	return;
}

/* *~*~*
 The private member function _reHeapDown rearranges the heap after delete by moving the
 data in the root down to the correct location in the heap
 *~**/
template<class ItemType>
void Heap<ItemType>::_reHeapDown(int rootdex, int comp(ItemType&, ItemType&))
{
	ItemType temp;
	ItemType empty;
	int left = _findLeftChild(rootdex);
	int right = _findRightChild(rootdex);
	int parent = rootdex;

	if (left != -1) // if there's a left child
	{
		while (left < heapSize && left != -1) {


			// Find the min among the node and all the node's children
			if (right != -1 &&heapAry[right] != empty && comp(heapAry[left], heapAry[right]) == 1) {

				if (comp(heapAry[parent], heapAry[right]) == 1) {
					temp = heapAry[parent];
					heapAry[parent] = heapAry[right];
					heapAry[right] = temp;
					parent = right;
				}
				else {
					return;
				}
			}
			else if (heapAry[left] != empty && comp(heapAry[parent], heapAry[left]) == 1) {
				temp = heapAry[parent];
				heapAry[parent] = heapAry[left];
				heapAry[left] = temp;
				parent = left;
			}
			else {
				return;
			}

			left = _findLeftChild(parent);
			right = _findRightChild(parent);
		}
	}

}
/* *~*~*
 The public member function insertHeap inserts a new item into a heap.
 It calls _reheapUp.
 *~**/
template<class ItemType>
bool Heap<ItemType>::insertHeap(ItemType& newItem, int compare(ItemType&, ItemType&))
{
	if (isFull())
		return false;

	heapAry[count] = newItem;
	_reHeapUp(count, compare);
	/*for (int i = 0; i < count; i++) {
		std::cout << heapAry[i].getName() << " ";
	}
	std::cout << std::endl;*/
	count++;

	return true;
}

/* *~*~*
 The public member function deleteHeap deletes the root of the heap and
 passes back the root's data. It calls _reheapDown.
 *~**/
template<class ItemType>
bool Heap<ItemType>::deleteHeap(ItemType& returnItem, int compare(ItemType&, ItemType&))
{
	ItemType empty;
	if (isEmpty())
		return false;

	returnItem = heapAry[0];
	/*for (int i = 0; i < count; i++) {
		std::cout << heapAry[i].getName() << " ";
	}
	std::cout << std::endl;*/
	heapAry[0] = heapAry[count - 1];
	heapAry[count - 1] = empty;
	count--;
	_reHeapDown(0, compare);

	return true;
}