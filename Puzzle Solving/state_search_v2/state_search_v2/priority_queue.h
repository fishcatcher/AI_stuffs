#pragma once

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "stddef.h"
#include "array_list.h"

#include <iostream>
using namespace std;



class priority_queue
{
public:
	priority_queue(int = DEFAULT_SIZE);
	~priority_queue();
	const int entries();
	void insert(node*, int);
	bool deleteMin(node*&, int&);
	const bool isEmpty();
	const void printHeap();
	int search(node*, int);
	void print_list();

private:
	void reheapUp(int);
	void reheapDown(int);
	void buildHeap();
	void resize();

	struct heapNode
	{
		int priority;
		node* name;
	};
	void swap(heapNode&, heapNode&);
	int count;
	int heapSize;
	void free_resources();

protected:
	heapNode * myHeap;

};


#endif // PRIORITY_QUEUE_H

