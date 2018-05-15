#include "stdafx.h"
#include "array_list.h"


array_list::array_list(int s)
	: arr_size(s)
{
	arr = new array_node[arr_size];
	count = 0;
}


array_list::~array_list()
{
	free_resources();
}

int array_list::search(node *item, int key)
{
	for (int i = 0; i < count; i++) {
		/*if (arr[i].key == key)*/ {
			int match = 0;
			for (int j = 0; j < ROW; j++) {
				for (int k = 0; k < COL; k++) {
					if (arr[i].name->state[j][k] == item->state[j][k]) {
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

void array_list::insert(node *item, int key)
{
	if (count >= arr_size)
		resize();
	arr[count].key = key;
	arr[count].name = item;
	count++;
}

int array_list::entries()
{
	return count;
}


node * array_list::get_item(int index)
{
	return arr[index].name;
}

void array_list::reverse()
{
	array_node *curr_arr = arr;
	int pos = 0;

	arr = new array_node[count];

	for (int i = count - 1; i >= 0; i--) {
		arr[pos] = curr_arr[i];
		pos++;
	}

	delete[] curr_arr;

}

void array_list::print_list(int index, bool print_to_file, bool rev)
{
	for (int i = index; i < count; i++) {
		(print_to_file) ? print_state_to_file(arr[i].name->move, arr[i].name->state, rev) : print_state("", arr[i].name->state);
	}
}

void array_list::append(array_list *rhs)
{
	for (int i = 0; i < rhs->entries(); i++) {
		insert(rhs->get_item(i), 0);
	}
}

void array_list::resize()
{
	int old_size = arr_size;
	arr_size = arr_size * 2;
	array_node *curr_list;
	curr_list = arr;
	arr = new array_node[arr_size];
	for (int i = 0; i<old_size; i++)
		arr[i] = curr_list[i];
	delete[] curr_list;
	curr_list = NULL;
}

array_list * array_list::reconstruct_path(array_list* list, node *child, int& length)
{
	array_list *arry = new array_list();

	parent_seeker(list, child, length);

	return arry;

}

void array_list::parent_seeker(array_list *list, node *child, int &length)
{
	list->insert(child, 0);

	if (child->parent == NULL) {
		return;
	}

	node *parent = new node;
	parent->state = child->parent;
	parent->heuristic = child->parent_heuristic;

	length++;
	int pos = search(parent, parent->heuristic);

	if (pos != -1) {
		parent_seeker(list, arr[pos].name, length);
	}

	delete parent;
}

void array_list::free_resources()
{
	for (int i = 0; i < count-1; i++) {
		//printf("i: %d\n", i);
		if (arr[i].name != nullptr) {
			if (arr[i].name->state != nullptr) {
				for (int j = 0; j < ROW; j++) {
					if (arr[i].name->state[j] != nullptr) {
						delete[] arr[i].name->state[j];
						arr[i].name->state[j] = nullptr;
					}
				}
				delete[] arr[i].name->state;
				arr[i].name->state = nullptr;
			}
			delete arr[i].name;
			arr[i].name = nullptr;
		}
	}

	delete arr;
	arr = nullptr;


}
