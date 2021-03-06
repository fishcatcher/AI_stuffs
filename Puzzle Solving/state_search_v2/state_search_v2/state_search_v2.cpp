// state_search_v2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stddef.h"
#include "a_star.h"

template <int r, int c>
int **interpret_array(int(&arr)[r][c]);
void print_state(string msg, int**state);

FILE *infp;
FILE *outfp;
int opt = 0;

int main()
{
	//
	char inf[BUF_SIZE];
	char outf[BUF_SIZE];
	char dummy[BUF_SIZE];
	int input_count = 1;
	//


	int goal_state0[4][4] =
	{ { 1, 2, 3, 4 },
	{ 5, 6, 7, 8 },
	{ 9, 10, 11, 12 },
	{ 13, 14 ,15, 0 } };

	int goal_state1[4][4] =
	{ { 0, 1, 2, 3 },
	{ 4, 5, 6, 7 },
	{ 8, 9, 10, 11 },
	{ 12, 13 ,14, 15 } };

	int initial_state0[4][4] =
	{ { 1, 2, 0, 3 },
	{ 6, 7, 11, 4 },
	{ 5, 9, 12, 8 },
	{ 13, 10, 14, 15 } };

	int initial_state1[4][4] =
	{ { 1, 2, 3, 4 },
	{ 12, 13, 14, 5 },
	{ 11, 0, 15, 6 },
	{ 10, 9, 8, 7 } };

	int initial_state2[4][4] =
	{ { 0, 15, 14, 13 },
	{ 12, 11, 10, 9 },
	{ 8, 7, 6, 5 },
	{ 4, 3, 2, 1 } };

	int initial_state5[4][4] =
	{ { 7, 14, 0, 5 },
	{ 6, 1, 11, 13 },
	{ 3, 9, 12, 8 },
	{ 4, 10, 2, 15 } };


	printf("Enter Input file: ");
	scanf_s("%s", inf, BUF_SIZE - 1);

	printf("\nEnter Output file: ");
	scanf_s("%s", outf, BUF_SIZE - 1);

	printf("\nFind optimal solution?\n(NO=0 YES=otherwise): ");
	scanf_s("%d", &opt, sizeof(opt));

	sprintf_s(inf, BUF_SIZE-1, "%s.txt", inf);
	sprintf_s(outf, BUF_SIZE - 1, "%s.txt", outf);

	//open to read
	fopen_s(&infp, inf, "r");

	//open to write
	fopen_s(&outfp, outf, "w");

	if (!infp) {
		printf("Error, cannot open file: %s\n", inf);
		system("pause");
		return 1;
	}

	do {
		int **initial_state = NULL;
		initial_state = new int*[ROW];
		for (int i = 0; i<ROW; i++) {
			initial_state[i] = new int[COL];
		}

		for (int i = 0; i < ROW; i++) {
			for (int j = 0; j < COL; j++) {
				if (feof(infp)) {
					printf("PROGRAM TERMINATES\n");
					system("pause");
					return 0;
				}
				fscanf_s(infp, "%d", &initial_state[i][j]);

			}
		}

		sprintf_s(dummy, BUF_SIZE - 1, "Input %d", input_count);
		fprintf(outfp, "**************\n");
		fprintf(outfp, "%s\n", dummy);
		fprintf(outfp, "**************\n");
		input_count++;

		int **goal_state = interpret_array(goal_state1);
		int length;
		int nodes;
		a_star *as = new a_star(DEFAULT_SIZE, bool(opt));
		as->set_initial(initial_state);
		as->set_goal(goal_state);
		as->begin(&length, &nodes);

		fprintf(outfp, "Number of nodes generated: %d\n", nodes);
		fprintf(outfp, "Length of solution path: %d\n", length);
		
		//free pointers
		delete as;

	} while (true);


	//noreach
    return 0;
}

template <int r, int c>
int **interpret_array(int(&arr)[r][c])
{
	int **ptr;
	//initialize ptr
	ptr = new int*[r];
	for (int i = 0; i<r; i++) {
		ptr[i] = new int[c];
	}

	//copy values
	for (int i = 0; i<r; i++) {
		for (int j = 0; j<c; j++) {
			ptr[i][j] = arr[i][j];
		}
	}

	return ptr;
}

void print_state(string msg, int **state)
{
	cout << "-----\n";
	cout << msg << endl;

	if (state == NULL) {
		cout << "state is empty\n";
		return;
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << state[i][j] << "\t";
		}
		cout << "\n";
	}
	cout << "-----\n";
}

void print_state_to_file(legal_moves move, int **state, bool rev)
{

	string m = "";

	switch(move) {
	case UP: {
		m = (!rev) ? "UP" : "DOWN";
		break;
	}
	case DOWN: {
		m = (!rev) ? "DOWN" : "UP";
		break;
	}
	case LEFT: {
		m = (!rev) ? "LEFT" : "RIGHT";
		break;
	}
	case RIGHT: {
		m = (!rev) ? "RIGHT" : "LEFT";
		break;
	}
	case START: {
		m = (!rev) ? "START" : "END";
		break;
	}
	}

	(rev) ? fprintf(outfp, "") : fprintf(outfp, "%s\n", m.c_str());

	fprintf(outfp, "-----\n");
	if (state) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				fprintf(outfp, "%d\t", state[i][j]);
			}
			fprintf(outfp, "\n");
		}
	}
	fprintf(outfp, "-----\n");
	(rev) ? fprintf(outfp, "%s\n", m.c_str()) : fprintf(outfp, "");
}