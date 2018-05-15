#include "stdafx.h"
#include "a_star.h"

a_star::a_star(int init, bool opt)
//constructor
//initialize variables
//initialize open lists + close lists
//Parameter:	int init:	prefered size of objects (DEFAULT=100)
//				bool opt:	optimal search (DEFAULT=false)
//Return:		none
{
	initial_state = goal_state = NULL;
	close_list_head = new array_list(init);
	close_list_tail = new array_list(init);
	open_list_head = new priority_queue(init);
	open_list_tail = new priority_queue(init);
	is_optimal = opt;
}


a_star::~a_star()
//dtor
{
	delete close_list_head;
	delete close_list_tail;
	delete open_list_head;
	delete open_list_tail;
}

void a_star::set_initial(int **ini)
//function to set initial state
//Parameter:	int **ini:	pointer to a state
//Return:		none
{
	initial_state = ini;
}

void a_star::set_goal(int **goal)
//function to set goal state
//Parameter:	int **goal:	pointer to a state
//Return:		none
{
	goal_state = goal;
}

void a_star::begin(int *length, int *count)
//function to start the search
//Parameter:	none
//Return:		int: solution path length
{
	if (!initial_state) {
		printf("Initial state is not set\n");
		return;
	}

	if (!goal_state) {
		printf("Goal state is not set\n");
		return;
	}

	print_state("INITIAL", initial_state);	//print initial state to stdin
	print_state("GOAL", goal_state);		//print goal state to stdin

	printf("OPTIMAL=%s\n", (is_optimal) ? "TRUE" : "FALSE");	//print optimal option
	
	system("pause");	//wait for user's respond (not safe function)


	//timming stuffs
	auto t1 = chrono::high_resolution_clock::now();
	auto t2 = chrono::high_resolution_clock::now();
	//end timming stuffs
	

	bool flag = false;	//variable to exit while loop
	bool is_solution = false;	//variable to indicate if solution has been found
	int solution_path_length = -1;	//varible to return to caller

	//
	printf("**********************************\n");

	/*step 1*/
	//add IS to open_list_head
	node *initial_node = new node;
	initial_node->state = initial_state;
	initial_node->parent = NULL;
	initial_node->heuristic = heuristic(initial_state, goal_state);
	initial_node->parent_heuristic = 0;
	initial_node->depth = 0;
	initial_node->move = START;

	open_list_head->insert(initial_node, initial_node->heuristic);

	//add IS to open_list_tail
	node *goal_node = new node;
	goal_node->state = goal_state;
	goal_node->parent = NULL;
	goal_node->heuristic = heuristic(goal_state, initial_state);
	goal_node->parent_heuristic = 0;
	goal_node->depth = 0;
	goal_node->move = START;

	open_list_tail->insert(goal_node, goal_node->heuristic);

	node *intermidiate_goal_head = goal_node;	//intermidiate nodes (aiding bidirectional search)
	node *intermidiate_goal_tail = initial_node;	// ""

	/*step 2*/
	do {

		//check if both open lists are empty
		//only process if they are both not empty
		//otherwise return with no solution
		if (!open_list_head->isEmpty() && !open_list_tail->isEmpty()) {

			node *best_node_head;
			node *best_node_tail;
			node *succesor_node_head;
			node *succesor_node_tail;
			int **succesor_state_head;
			int **succesor_state_tail;
			int key_head;
			int key_tail;
			int pos = -1;
			int depth;

			//remove best node from open list head
			open_list_head->deleteMin(best_node_head, key_head);

			printf("[HEAD]Node generated: %d depth: %d\n", open_list_head->entries() + close_list_head->entries(), best_node_head->depth);

			//insert best node head to close list head
			close_list_head->insert(best_node_head, best_node_head->heuristic);

			//check if solution is found
			if (compare_for_solution(best_node_head, intermidiate_goal_head) || (pos = close_list_tail->search(best_node_head, best_node_head->heuristic)) != -1) {
				//found solution
				printf("FIRST\n");
				printf("POS: %d\n", pos);

				
				int length_head;
				int length_tail;

				pos = (pos == -1) ? close_list_tail->search(intermidiate_goal_head, intermidiate_goal_head->heuristic) : pos;

				//construct solution paths
				array_list *solution_path_head = new array_list;
				close_list_head->reconstruct_path(solution_path_head, best_node_head, length_head);

				array_list *solution_path_tail = new array_list;
				close_list_tail->reconstruct_path(solution_path_tail, close_list_tail->get_item(pos), length_head);

				solution_path_head->reverse();

				solution_path_head->print_list(0, true);
				solution_path_tail->print_list(1, true, true);

				solution_path_length = solution_path_head->entries() + solution_path_tail->entries() - 2;
				printf("Solution Path: %d\n", solution_path_length);

				is_solution = true;
				flag = !flag;
				break;
			}

			

			//expand best node head
			for (int i = 0; i < 4; i++) {
				succesor_state_head = make_move((legal_moves)i, best_node_head->state);
				if (succesor_state_head) {
					succesor_node_head = new node;
					succesor_node_head->state = succesor_state_head;
					succesor_node_head->heuristic = heuristic(succesor_state_head, intermidiate_goal_head->state);
					succesor_node_head->depth = best_node_head->depth + 1;
					succesor_node_head->parent = best_node_head->state;
					succesor_node_head->parent_heuristic = best_node_head->heuristic;
					succesor_node_head->move = (legal_moves)i;

					depth = (is_optimal) ? succesor_node_head->depth : 0;

					//add to open list
					if (open_list_head->search(succesor_node_head, succesor_node_head->heuristic) == -1) {
						if (close_list_head->search(succesor_node_head, succesor_node_head->heuristic) == -1) {
							open_list_head->insert(succesor_node_head, succesor_node_head->heuristic + depth);
						}
					}
				}
			}

			intermidiate_goal_tail = best_node_head;

			//remove best node from open list tail
			open_list_tail->deleteMin(best_node_tail, key_tail);

			printf("[TAIL]Node generated: %d depth: %d\n", open_list_tail->entries() + close_list_tail->entries(), best_node_tail->depth);

			//add best node tail to close list tail
			close_list_tail->insert(best_node_tail, best_node_tail->heuristic);

			//check for solution
			if (compare_for_solution(best_node_tail, intermidiate_goal_tail) || (pos = close_list_head->search(best_node_tail, best_node_tail->heuristic)) != -1) {
				//found solution
				printf("SECOND\n");
				printf("POS: %d\n", pos);

				int length_head;
				int length_tail;

				pos = (pos == -1) ? close_list_head->search(intermidiate_goal_tail, intermidiate_goal_tail->heuristic) : pos;


				//construct solution paths
				array_list *solution_path_head = new array_list;
				close_list_head->reconstruct_path(solution_path_head, close_list_head->get_item(pos), length_head);
				array_list *solution_path_tail = new array_list;
				close_list_tail->reconstruct_path(solution_path_tail, best_node_tail, length_tail);

				solution_path_head->reverse();

				solution_path_head->print_list(0, true);
				solution_path_tail->print_list(1, true, true);

				solution_path_length = solution_path_head->entries() + solution_path_tail->entries() - 2;
				printf("Solution Path: %d\n", solution_path_length);

				is_solution = true;
				flag = !flag;
				break;
			}

			

			//expand best node tail
			for (int i = 0; i < 4; i++) {
				succesor_state_tail = make_move((legal_moves)i, best_node_tail->state);
				if (succesor_state_tail) {
					succesor_node_tail = new node;
					succesor_node_tail->state = succesor_state_tail;
					succesor_node_tail->heuristic = heuristic(succesor_state_tail, intermidiate_goal_tail->state);
					succesor_node_tail->depth = best_node_tail->depth + 1;
					succesor_node_tail->parent = best_node_tail->state;
					succesor_node_tail->parent_heuristic = best_node_tail->heuristic;
					succesor_node_tail->move = (legal_moves)i;

					depth = (is_optimal) ? succesor_node_tail->depth : 0;

					//add to open list
					if (open_list_tail->search(succesor_node_tail, succesor_node_tail->heuristic) == -1) {
						if (close_list_tail->search(succesor_node_tail, succesor_node_tail->heuristic) == -1) {
							open_list_tail->insert(succesor_node_tail, succesor_node_tail->heuristic + depth);
						}
					}
				}
			}

			intermidiate_goal_head = best_node_tail;


			//optinal implementation for staging search
			//is currently not implemented
			t2 = chrono::high_resolution_clock::now();
			if (std::chrono::duration_cast<std::chrono::minutes>(t2 - t1).count() >= MAX_DURATION_MINUTE) {
				//staging here


				//get new timmer
				t1 = chrono::high_resolution_clock::now();
			}

		}
		else {
			flag = !flag;
		}

	} while (!flag);


	if (is_solution) {
		printf("SOLUTION IS FOUND\n");
	}
	else {
		printf("SOLUTION IS NOT FOUND\n");
	}

	*length = solution_path_length;
	*count = open_list_head->entries() + open_list_tail->entries() + close_list_head->entries() + close_list_tail->entries() - 2;

	//this stuffs are for time keeping
	t2 = chrono::high_resolution_clock::now();
	cout << "\nElapsed time: " << endl;
	cout << "\t" << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << " milisecond(s)" << endl;
	cout << "\t" << std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count() << " second(s)" << endl;

	//return solution path
	//-1 will be return if no solution is found
	return;

}

int a_star::heuristic(int **init, int **goal)
//function to realize the heuristic
//Parameters:	int **init: the from-state
//				int **goal: the to-state
//Return:		int: the heuristic score
{
	//Manhattan distance
	int sum = 0;
	for (int i = 1; i < ROW*COL; i++) {
		tile t = search_tile(init, i);
		tile g = search_tile(goal, i);
		sum += abs(t.row - g.row) + abs(t.col - g.col);
	}

	return sum;
}



tile a_star::search_tile(int **state, int t)
//function to find the position of a value in a state
//Paremeters:	int **state: the current state
//				int t: the value to search
//Return:		tile: a struct which contains the row and column values of t in state
{
	if (state == NULL)
		return { -1, -1 };

	int pos;

	for (int i = 0; i<ROW; i++) {
		for (int j = 0; j<COL; j++) {
			if (state[i][j] == t)
				return { i, j };
		}
	}
	return { -1, -1 };
}

int a_star::search_value(int **state , tile t)
//function to find the value of a position in a state
//reverse of search_tile()
//Parameters:	int **state: the current state
//				tile t: the tile position
//Return:		int: the value at the t position of the state
{
	return state[t.row][t.col];
}

bool a_star::compare_for_solution(node *lhs, node *rhs)
//function to compare between two nodes
//two nodes are equal if their contained states are equal
//Parameters:	node *lhs: first node to compare
//				node *rhs: second node to compare
//Return:		bool: the truth value of the comparison
{
	if (lhs == NULL || rhs == NULL)
		return false;


	int match = 0;
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (lhs->state[i][j] == rhs->state[i][j])
				match++;
		}
	}
	if (match == ROW * COL)
		return true;
	return false;
}

int ** a_star::make_move(legal_moves move, int **state)
//function to expands a state to possible position
//Parameters:	legal_moves move: the legal move (UP, DOWN, LEFT, RIGHT)
//				int **state: current state to expand
//Return:		int **: a new state after applied the move
{
	if (state == NULL)
		return NULL;

	int **s_state = NULL;
	int temp;
	tile blank = search_tile(state, BLANK_TILE);

	if (check_move(move, state)) {

		s_state = new int*[ROW];
		for (int i = 0; i < ROW; i++) {
			s_state[i] = new int[COL];
		}

		for (int i = 0; i < ROW; i++) {
			for (int j = 0; j < COL; j++) {
				s_state[i][j] = state[i][j];
			}
		}

		//make move
		switch (move) {
		case UP: {
			temp = s_state[blank.row - 1][blank.col];
			s_state[blank.row - 1][blank.col] = BLANK_TILE;
			s_state[blank.row][blank.col] = temp;
			break;
		}
		case DOWN: {
			temp = s_state[blank.row + 1][blank.col];
			s_state[blank.row + 1][blank.col] = BLANK_TILE;
			s_state[blank.row][blank.col] = temp;
			break;
		}
		case LEFT: {
			temp = s_state[blank.row][blank.col - 1];
			s_state[blank.row][blank.col - 1] = BLANK_TILE;
			s_state[blank.row][blank.col] = temp;
			break;
		}
		case RIGHT: {
			temp = s_state[blank.row][blank.col + 1];
			s_state[blank.row][blank.col + 1] = BLANK_TILE;
			s_state[blank.row][blank.col] = temp;
			break;
		}
		}
	}

	return s_state;


}

bool a_star::check_move(legal_moves move, int **state)
//function to check the constraint of a move
//Parameters:	legal_moves move: the move to apply
//				int **state: current state
//Return:		bool: true if the current move can be applied to the current state
//					  false otherwise
{

	tile blank = search_tile(state, BLANK_TILE);

	switch (move) {
	case UP: {
		if (blank.row - 1 >= 0) {
			return true;
		}
		else return false;
	}
	case DOWN: {
		if (blank.row + 1 < ROW) {
			return true;
		}
		else return false;
	}
	case LEFT: {
		if (blank.col - 1 >= 0) {
			return true;
		}
		else return false;
	}
	case RIGHT: {
		if (blank.col + 1 < COL) {
			return true;
		}
		else return false;
	}
	default:
		return false;
	}

}