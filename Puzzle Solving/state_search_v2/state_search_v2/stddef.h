#pragma once

#ifndef STDDEF_H
#define STDDEF_H

#include <string>
#include <iostream>
#include <stdio.h>
#include <chrono>


using namespace std;

#ifndef BLACK_TILE
#define BLANK_TILE (0)
#endif

#ifndef ROW
#define ROW (4)
#endif

#ifndef COL
#define COL (4)
#endif

#ifndef DEFAULT_SIZE
#define DEFAULT_SIZE (100)
#endif

#ifndef BUF_SIZE
#define BUF_SIZE 128
#endif // !BUF_SIZE

typedef unsigned int uint;

enum legal_moves { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3, START = 4, INVALID = 5 };

struct node {
	int **state;
	int **parent;
	int heuristic;
	int depth;
	int parent_heuristic;
	void operator= (const node *rhs) {
		this->state = rhs->state;
		this->parent = rhs->parent;
		this->heuristic = rhs->heuristic;
		this->depth = rhs->depth;
	}
	legal_moves move;
};

struct tile {
	int row;
	int col;
	void operator= (const tile *rhs) {
		this->row = rhs->row;
		this->col = rhs->col;
	}
};


extern void print_state(string, int**);
extern void print_state_to_file(legal_moves, int**, bool);

template <int r, int c>
extern int **interpret_array(int(&arr)[r][c]);


#endif