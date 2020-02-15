#pragma warning(disable :4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <iostream>
#include "puzzle.h"
#include "PIDA.h"

#define boardSIZE        25                 // board size
#define inverseSIZE      277                // inversion max size : 1+2+...+23
#define maxNODE      9000000           // �ִ� Ž�� ������ ��� ��
#define minNODE      9000000            // �ߺ� üũ�� �ִ� Ž�� ������ ��� ��

// declaring global variables
char virtualBoard[boardSIZE];                      // ���� ����
int boardState[500][boardSIZE];              // ���� ���� ����
int bsSTART, bSEND;                        // ���� ������ ���¸� ������ ť ������
char inverseTABLE[inverseSIZE];                  // �̵�Ƚ�� ��� ���̺�
int CUTOFF;                                // ���� ����ġ
char change[] = {                          // ��� ���� ���� �ٲٱ� ����
   0,
   1, 6,11,16,21,
   2, 7,12,17,22,
   3, 8,13,18,23,
   4, 9,14,19,24,
   5,10,15,20,25
};
int direct[] = { -SIZE, 1, SIZE, -1 };
direction SOLUTION[200];                   // �ּ� �̵� ������ ����
// �ٻ�Ž���� ���Ǵ� ������
int middle_bound, temp_solve, temp_bound;  // �߰� ��ǥ inversion ��
int middle_dir, temp_dir;                  // �߰� ��ǥ ����
int middle_depth, temp_depth;              // �߰� ��ǥ ����
int middle_cutoff, temp_cutoff;            // �߰� ��ǥ ���� ����
int mode;                                  // ����,�߰� ��ǥ Ž�� ��� ����
int node_count;                            // Ž���� �� ��� ��
int search_cutoff;                         // ���� ����ġ

int state_check;                           // �ߺ�üũ ����,���� ����
int next_cutoff;                           // ���� Ž���� ���� ���� ����ġ

// define sub-functions
void virtual_board(int** puzzle);
int heuristic();
int Search(int inv_rowo, int inv_colo, int iBlank, int iPrev, int depth);
void puzzleSolution(void);
int argc1;
char** argv1;

//ȯ������迭
int puzzle111[5][5] = { 0 };

///////////////////////////////////////////////////////////////
// Main Function
///////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
	argc1 = argc; argv1 = argv;

	puzzleSolution();

	return 0;
}
void puzzleSolution() {
	int t = -1;
	printf(">>T �Է� : ");
	scanf("%d", &t);


	for (int i = 0; i < t; i++) {

		int** puzzle, iLoop, iLoop2, iLoop3;

		printf("\n>>5*5 ���� �Է�\n");
		puzzle = initialize(argc1, argv1);

		int arr[5][5];
		for (int j = 0; j < SIZE; j++) {
			for (int k = 0; k < SIZE; k++) {
				arr[j][k] = _np[j][k];
			}
		}
		// real ida
		SSS55::ida55(arr, i);

		// ������
		if (SSS55::pass == false && SSS55::canSolve == true) {
		//if (true) {
			T = i;
			// �������� �̿��Ͽ� �̵� Ƚ���� ���ϱ� ���� ���̺� �غ�
			for (iLoop = 0; iLoop < inverseSIZE; iLoop++)
				inverseTABLE[iLoop] = (char)((iLoop / 4) + (iLoop % 4));

			search_cutoff = maxNODE;
			bsSTART = bSEND = state_check = 0;
			// main loop
			while (1) {

				puzzle = get_status();  // ���� ������ ������
				virtual_board(puzzle);  // ���� ������ ���� ���忡 ����
				// �߰� ��ǥ�� ã�ư��� ���� ������ �ʱ�ȭ
				middle_bound = temp_bound = temp_solve = middle_cutoff = temp_cutoff = 1000000;
				node_count = temp_depth = middle_depth = mode = 0;
				temp_dir = 4;

				if (heuristic()) {  // ���� ��ǥ�� ����
				   // �ϼ��� ���·� ������ ����
					for (iLoop = 0; iLoop < CUTOFF; iLoop++) move(SOLUTION[iLoop]);
					break;
				}
				else {
					// ���� �ð����� ���� ��ǥ�� �������� ���ߴٸ�, ��ǥ��
					// ���� ������ �߰� ��ǥ ���·� ������ ����
					mode = 1;
					middle_depth = temp_depth;
					middle_bound = temp_bound;
					middle_dir = temp_dir;
					middle_cutoff = temp_cutoff;
					heuristic();  // �ٻ� Ž��
					// �߰� ��ǥ ���·� ������ ����
					for (iLoop = 0; iLoop < CUTOFF; iLoop++) move(SOLUTION[iLoop]);
					// Cycle�� ������ ��� �ִ� 2�� ������ ������ ���¹ۿ��� ã���� ���Ѵ�.
					// Normal search ��� 2�� ������ �̵� Ƚ�� �������� ���� Cycle�� ����
					// �Ѵٰ� �����Ѵ�.
					if (CUTOFF <= 2) {  // Ž�� �׷����� cycle ������ ��� �ߺ� üũ�� ����
						state_check = 1; search_cutoff = minNODE;
					}
					else {  // Cycle �� ���ٸ� �ߺ�üũ ���� ����
						state_check = 0; search_cutoff = maxNODE;
					}
				}
			}
		}


		// ȯ�� �߰�

		for (int j = 0; j < SIZE; j++) {
			for (int k = 0; k < SIZE; k++) {
				_np[j][k] = arr[j][k];
			}
		}

		puzzle = initialize1(argc1, argv1);

		// real ida
		//SSS55::ida55(arr, i);

		// ������2
		//if (SSS55::pass == false && SSS55::canSolve == true) {
		if (true) {
			T = i;
			// �������� �̿��Ͽ� �̵� Ƚ���� ���ϱ� ���� ���̺� �غ�
			for (iLoop = 0; iLoop < inverseSIZE; iLoop++)
				inverseTABLE[iLoop] = (char)((iLoop / 2) + (iLoop % 2));

			search_cutoff = maxNODE;
			bsSTART = bSEND = state_check = 0;
			// main loop
			while (1) {

				puzzle = get_status();  // ���� ������ ������
				virtual_board(puzzle);  // ���� ������ ���� ���忡 ����
				// �߰� ��ǥ�� ã�ư��� ���� ������ �ʱ�ȭ
				middle_bound = temp_bound = temp_solve = middle_cutoff = temp_cutoff = 1000000;
				node_count = temp_depth = middle_depth = mode = 0;
				temp_dir = 4;

				if (heuristic()) {  // ���� ��ǥ�� ����
				   // �ϼ��� ���·� ������ ����
					for (iLoop = 0; iLoop < CUTOFF; iLoop++) move1(SOLUTION[iLoop]);
					break;
				}
				else {
					// ���� �ð����� ���� ��ǥ�� �������� ���ߴٸ�, ��ǥ��
					// ���� ������ �߰� ��ǥ ���·� ������ ����
					mode = 1;
					middle_depth = temp_depth;
					middle_bound = temp_bound;
					middle_dir = temp_dir;
					middle_cutoff = temp_cutoff;
					heuristic();  // �ٻ� Ž��
					// �߰� ��ǥ ���·� ������ ����
					for (iLoop = 0; iLoop < CUTOFF; iLoop++) move1(SOLUTION[iLoop]);
					// Cycle�� ������ ��� �ִ� 2�� ������ ������ ���¹ۿ��� ã���� ���Ѵ�.
					// Normal search ��� 2�� ������ �̵� Ƚ�� �������� ���� Cycle�� ����
					// �Ѵٰ� �����Ѵ�.
					if (CUTOFF <= 2) {  // Ž�� �׷����� cycle ������ ��� �ߺ� üũ�� ����
						state_check = 1; search_cutoff = minNODE;
					}
					else {  // Cycle �� ���ٸ� �ߺ�üũ ���� ����
						state_check = 0; search_cutoff = maxNODE;
					}
				}
			}
		}
	}
}


///////////////////////////////////////////////////////////////
// �̵������ �̸� ���ϱ� ���� ���� ���带 ����
///////////////////////////////////////////////////////////////
void virtual_board(int** puzzle)
{
	int iLoop, iLoop2;

	for (iLoop = 0; iLoop < SIZE; iLoop++)
		for (iLoop2 = 0; iLoop2 < SIZE; iLoop2++)
			virtualBoard[iLoop * SIZE + iLoop2] = (char)(puzzle[iLoop][iLoop2]);
}

///////////////////////////////////////////////////////////////
// Heuristic Search : IDA*
///////////////////////////////////////////////////////////////
int heuristic()
{
	// ������ �����ǿ��� ������ ������ �������� ���´� �� 4�����̴�.
	// ������ �߽����� ��, �Ʒ�, ����, ������ ���ڸ� �ű�� ��찡 �װ��ε�,
	// �̿� ���� ������ �ڽĳ�尡 2 - 4 ���� Tree ������ ���� �� �ִ�.
	// �� Tree�� leaf node �߿� �츮�� ���ϴ� ���� ��ǥ�� ���� ���̰�, �� ����
	// ��ǥ�� ã�´ٸ� �ش� �������� �ϼ��� �� �ִ� ��θ� �� �� �ִ�.

	// ���� �켱 Ž��, �ʺ� �켱 Ž���� ��ǥ�� �� �����ϰ� �ִ��� �� �� ���� �͸�
	// ���� Ž�� ����̾, Ž���ð��� ���� �ɸ���. Ž�� �ð��� ���� ��Ű�� ����
	// �� �Լ��� ���� ������ �̿��Ͽ� Ž���� �ϴ� iteratice deepening A* �˰�����
	// ����Ͽ���.

	// �� �Լ��� inversion �� ����Ͽ���.

	// IDA* �˰����� �̿��Ͽ� ���� ��ǥ ��带 ã�´ٸ� ȿ������ ��θ� ã�� �� �ְ�
	// ����, Ž���ؾ� �� Tree�� ���̰� ��� ���ٸ� �� ���� �ð��� ��û �ɸ��� �ȴ�.
	// (���� �Լ� ��ŭ ��� ���� ���� �ϹǷ�...)

	// �׷��� ���� ������ ��带 Ž���ߴٸ� Ž���� ���� �ϰ�, Ž���� ��� �� ���� ��ǥ��
	// ������ ���� �������� �����ϰ�, �ٽ� Ž���� �����Ѵ�. �ִ� ��δ� �ƴ����� Ž��
	// �ð��� ���̴µ� ����� ȿ���� ���� �� �־���.

	// Ž���׷����� Ʈ�� ����� �ƴ� cycle �� ���Ե� ��쵵 �ִ�.
	// �� ��� ���α׷��� ���� ������ ������ ���µ� �̸� �ذ��ϱ� ���� ���� ������ ���¸�
	// �����Ͽ� �Ȱ��� �������� ������ �ʵ��� �ߺ�üũ�� �Ͽ���.

	int iBlank, inv_row = 0, inv_col = 0, iTemp, iLoop, iLoop2, lower_bound = 0;
	int md_row = 0, md_col = 0;
	char Trans[boardSIZE];

	// ###### ����� ������ ���� ######
	for (iLoop = 0; iLoop < boardSIZE; iLoop++)
	{
		if (virtualBoard[iLoop] == BLANK) {  // get the blank point
			iBlank = iLoop;
			continue;
		}
		iTemp = virtualBoard[iLoop];
		// calculate invertion of row
		for (iLoop2 = iLoop + 1; iLoop2 < boardSIZE; iLoop2++)
			if (iTemp > virtualBoard[iLoop2]) inv_row++;
	}

	// ###### ������ ������ ���� ######
	// create transpose matrix & conversion
	for (iLoop = 0; iLoop < SIZE; iLoop++)
		for (iLoop2 = 0; iLoop2 < SIZE; iLoop2++)
			Trans[iLoop2 * SIZE + iLoop] = change[virtualBoard[iLoop * SIZE + iLoop2]];
	// calculate inversion of colum
	for (iLoop = 0; iLoop < boardSIZE; iLoop++)
	{
		if (Trans[iLoop] == BLANK) continue;
		iTemp = Trans[iLoop];
		for (iLoop2 = iLoop + 1; iLoop2 < boardSIZE; iLoop2++)
			if (iTemp > Trans[iLoop2]) inv_col++;
	}

	//�ʱ� lower bound ����
	lower_bound = inverseTABLE[inv_row] + inverseTABLE[inv_col];

	if (mode == 0) {  // �ٻ�Ž���� �ƴ϶��
	   // ������ ���¸� ����
		for (iLoop = 0; iLoop < boardSIZE; iLoop++)
			boardState[bSEND][iLoop] = virtualBoard[iLoop];
		bSEND++;
		if (bSEND >= 6) bsSTART++;
	}

	// ###### IDA* ���� ######
	if (mode == 0) CUTOFF = lower_bound;  // if Normal search mode
	else CUTOFF = middle_cutoff;  // if Approximate search mode
	while (1) {
		next_cutoff = 1000000;
		node_count = 0;
		// ���� ��ǥ�� ã�Ҵٸ� Ž�� �ߴ�
		if (Search(inv_row, inv_col, iBlank, -1, 0)) break;
		else {
			if (mode == 0 && node_count > search_cutoff) return FALSE;
			else CUTOFF = next_cutoff;  // Ž���� �����Ͽ��ٸ� lower bound �� ����
		}
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////
// Iteratice Deepening A*
///////////////////////////////////////////////////////////////
int Search(int inv_rowo, int inv_colo, int iBlank, int iPrev, int depth)
{
	int iTemp, iLoop, iLoop2, iLoop3, iLoop4, NextMove, n, n2, lower_bound, distant;
	int inv_row, inv_col, equal;
	direction course;

	// Ž�� �ð��� ����� ��� Ž���� �ߴ�
	if (mode == 0 && node_count > search_cutoff) return FALSE;

	depth++; // increase tree depth

	for (iLoop = 0; iLoop < 4; iLoop++)  // 4����(��,�Ʒ�,����,������)�� ���ؼ�
	{
		NextMove = iBlank + direct[iLoop];
		// ������ ���� �ڸ����� �˻�
		if (NextMove < 0 || NextMove > boardSIZE - 1 || direct[iLoop] == 1
			&& NextMove % SIZE == 0 || direct[iLoop] == -1
			&& NextMove % SIZE == SIZE - 1) continue;
		if (NextMove == iPrev) continue;  // ��� ������ ��ȣ��� �״�� �� �д�.
		n = virtualBoard[NextMove];  // �̵��� ��ȣ�� ������

		inv_row = inv_rowo;
		inv_col = inv_colo;

		// ���� �̵��� ���� ������ ��ȭ�� ���

		// ������ ���ڸ� ���Ϸ� �̵��� ��� ����� �������� ���Ѵ�.
		// ������ ������ �������� ������ �ʴ´�. ������ ��ȭ�� ���ؼ� ����
		// ������ �׸��� 4���� ���� �κи� ����ϸ� ��.
		// ������
		// ������

		// ������ ���������� �¿�� �����̴� ��쵵 ������ �������� ���Ѵ�.
		// ������ �̶��� ���� �簢���� 4�� ���ڿ� ���ؼ��� ����� ��.
		// �ࢹ�����
		// ������
		// ������
		switch (iLoop) {  // ���ڸ� �Ʒ��� �̵�
		case 0:
			course = DOWN;
			for (iLoop2 = NextMove + 1; iLoop2 < iBlank; iLoop2++)
				if (virtualBoard[iLoop2] > n) inv_row++; else inv_row--;
			break;
		case 1:  // ���ڸ� �������� �̵�
			course = LEFT;
			n2 = change[n];
			for (iLoop2 = iBlank + SIZE; iLoop2 < boardSIZE; iLoop2 += SIZE)
				if (change[virtualBoard[iLoop2]] > n2) inv_col--; else inv_col++;
			for (iLoop2 = NextMove - SIZE; iLoop2 >= 0; iLoop2 -= SIZE)
				if (change[virtualBoard[iLoop2]] > n2) inv_col--; else inv_col++;
			break;
		case 2:  // ���ڸ� ���� �̵�
			course = UP;
			for (iLoop2 = iBlank + 1; iLoop2 < NextMove; iLoop2++)
				if (virtualBoard[iLoop2] > n) inv_row--; else inv_row++;
			break;
		case 3:  // ���ڸ� ���������� �̵�
			course = RIGHT;
			n2 = change[n];
			for (iLoop2 = NextMove + SIZE; iLoop2 < boardSIZE; iLoop2 += SIZE)
				if (change[virtualBoard[iLoop2]] > n2) inv_col++; else inv_col--;
			for (iLoop2 = iBlank - SIZE; iLoop2 >= 0; iLoop2 -= SIZE)
				if (change[virtualBoard[iLoop2]] > n2) inv_col++; else inv_col--;
		}

		// �ڽ� ����� lower bound ����
		lower_bound = inverseTABLE[inv_row] + inverseTABLE[inv_col];

		if (!mode) node_count++;  // Ž���� ��� ���� ����
		if (state_check) {
			// ���� �������� ���� ���Դ� �������� üũ
			virtualBoard[NextMove] = BLANK;
			virtualBoard[iBlank] = n;
			for (iLoop3 = bsSTART; iLoop3 < bSEND; iLoop3++)
			{
				equal = 0;
				for (iLoop4 = 0; iLoop4 < boardSIZE; iLoop4++)
				{
					if (boardState[iLoop3][iLoop4] == virtualBoard[iLoop4]) equal++;
				}
				if (equal == 25) break;
			}
			virtualBoard[NextMove] = n;
			virtualBoard[iBlank] = BLANK;
			if (equal == 25) continue;  // �ߺ��̸� �� ���� ���� ����
		}

		// ���� �ð��ȿ� ��ǥ�� ã�� �������� �ٻ�Ž���� �ϱ� ���� �߰� ��ǥ ������ ����
		if (mode == 0 && (temp_bound > lower_bound)) {
			temp_bound = lower_bound;  // inversion �� ����
			temp_depth = depth;  // ���� ����
			temp_cutoff = CUTOFF;  // ���� ���� ����
			temp_dir = iLoop;  // ���� ����
		}

		// �߰� ��ǥ ����, ���� ��ǥ ����
		if (lower_bound == 0 || mode == 1 && middle_bound == lower_bound &&
			middle_depth == depth && middle_dir == iLoop && middle_cutoff == CUTOFF) {
			CUTOFF = depth;
			SOLUTION[depth - 1] = course;  // �̵� ���� ���
			return TRUE;
		}
		else if (depth + lower_bound <= CUTOFF) {  // ���� ���� ���� ���ų� �۴ٸ�
		// ���� �����ǿ��� ���� �̵�
			virtualBoard[NextMove] = BLANK;
			virtualBoard[iBlank] = n;
			if (Search(inv_row, inv_col, NextMove, iBlank, depth)) {
				SOLUTION[depth - 1] = course;  // �̵� ���� ���
				return TRUE;
			}
			// ���� �������� �����·� �ǵ��� ����
			virtualBoard[NextMove] = n;
			virtualBoard[iBlank] = BLANK;
		}
		else {
			// ���� ���� ������ ����
			if (next_cutoff > depth + lower_bound) next_cutoff = depth + lower_bound;
		}
	}
	return FALSE;
	getchar();
}