#include "stdafx.h"
#include "priority_queue.h"


priority_queue::priority_queue(int Size) : heapSize(Size)
{
	if (heapSize < DEFAULT_SIZE)
		heapSize = DEFAULT_SIZE;

	myHeap = new heapNode[heapSize];

	for (int i = 0; i<heapSize; i++)
		myHeap[i].priority = 0;
	count = 0;
}


priority_queue::~priority_queue()
{
	free_resources();
}


const int priority_queue::entries()
{
	return count;
}


void priority_queue::insert(node* newItem, int keyValue)
{
	if (count + 1 >= heapSize)
		resize();
	count++;
	myHeap[count].priority = keyValue;
	myHeap[count].name = newItem;
	reheapUp(count);
}


int priority_queue::search(node* item, int key)
{
	for (int i = 1; i < count; i++) {
		/*if (myHeap[i].name->heuristic == key) */{
			int match = 0;
			for (int j = 0; j < ROW; j++) {
				for (int k = 0; k < COL; k++) {
					if (myHeap[i].name->state[j][k] == item->state[j][k]) {
						match++;
					}
				}
			}
			if (match == ROW * COL) {
				return i;
			}
		}
	}
	return -1;
}

void priority_queue::print_list()
{
	for (int i = 0; i < count; i++) {
		print_state("", myHeap[i].name->state);
	}
} 


bool priority_queue::deleteMin(node*& deletedItem, int& keyValue)
{
	if (isEmpty())
		return false;
	keyValue = myHeap[1].priority;
	deletedItem = myHeap[1].name;
	swap(myHeap[1], myHeap[count]);
	count--;
	reheapDown(1);
	return true;

}




const bool priority_queue::isEmpty()
{
	return (count == 0);
}



const void priority_queue::printHeap()
{
	for (int i = 1; i <= count; i++)
	{
		cout << myHeap[i].priority << " ";
		cout << myHeap[i].name << endl;
	}
}


void priority_queue::reheapUp(int index)
{
	if (index > 0)
	{
		int parent;
		parent = index / 2;
		if (myHeap[parent].priority > myHeap[index].priority)
		{
			swap(myHeap[parent], myHeap[index]);
			reheapUp(parent);
		}
	}
}


void priority_queue::reheapDown(int index)
{
	int childLeft, childRight;
	childLeft = index * 2;
	childRight = (index * 2) + 1;
	if ((childLeft <= count) || (childRight <= count))
	{
		if (childRight <= count)
		{
			if ((myHeap[index].priority > myHeap[childLeft].priority) || (myHeap[index].priority > myHeap[childRight].priority))
			{
				if (myHeap[childLeft].priority > myHeap[childRight].priority)
				{
					swap(myHeap[index], myHeap[childRight]);
					reheapDown(childRight);
				}
				else
				{
					swap(myHeap[index], myHeap[childLeft]);
					reheapDown(childLeft);
				}
			}
		}
		else
			if (myHeap[index].priority > myHeap[childLeft].priority)
				swap(myHeap[index], myHeap[childLeft]);
	}
}


void priority_queue::buildHeap()
{
	if (isEmpty())
		return;
	int parent = count / 2;
	while (parent > 0)
	{
		reheapDown(parent);
		parent--;
	}
}

void priority_queue::resize()
{
	int oldSize = heapSize;
	heapSize = heapSize * 2;
	heapNode *currHeap;
	currHeap = myHeap;
	myHeap = new heapNode[heapSize];
	for (int i = 1; i<oldSize; i++)
		myHeap[i] = currHeap[i];
	delete[] currHeap;
	currHeap = NULL;
}


void priority_queue::swap(heapNode &first, heapNode &second)
{
	heapNode temp;
	temp.priority = first.priority;
	temp.name = first.name;

	first.priority = second.priority;
	first.name = second.name;

	second.priority = temp.priority;
	second.name = temp.name;
}

void priority_queue::free_resources()
{

}
