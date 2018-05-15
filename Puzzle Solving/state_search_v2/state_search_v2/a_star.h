#pragma once

#include "stddef.h"
#include "priority_queue.h"
#include "array_list.h"

class a_star
{
public:
	a_star(int=DEFAULT_SIZE, bool=false);
	~a_star();
	void set_initial(int**);
	void set_goal(int**);
	void begin(int*, int*);
	int heuristic(int**, int**);
	

private:
	int **initial_state;
	int **goal_state;
	array_list *close_list_head, *close_list_tail;
	priority_queue *open_list_head, *open_list_tail;

	tile search_tile(int**, int);
	int search_value(int**, tile);
	bool compare_for_solution(node*, node*);
	int **make_move(legal_moves, int**);
	bool check_move(legal_moves, int**);
	bool is_optimal;

	static const int MAX_NODES_STAGED = 5;
	static const int MAX_DURATION_MINUTE = 30;

};


