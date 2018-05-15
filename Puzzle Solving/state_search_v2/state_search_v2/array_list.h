#pragma once

#include "stddef.h"

#ifndef DEFAULT_SIZE
#define DEFAULT_SIZE (100)
#endif

class array_list
{
public:
	array_list(int=DEFAULT_SIZE);
	~array_list();
	int search(node*, int);
	void insert(node*, int);
	int entries();
	array_list* reconstruct_path(array_list*, node*, int&);
	node *get_item(int);
	void reverse();
	void print_list(int=0, bool=false, bool=false);
	void append(array_list*);

private:
	struct array_node {
		int key;
		node* name;
	};
	int count;
	int arr_size;
	array_node *arr;
	void resize();
	void parent_seeker(array_list*, node*, int&);
	void free_resources();
};

