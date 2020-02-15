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
#define maxNODE      80000000           // �ִ� Ž�� ������ ��� ��
#define minNODE      8000000            // �ߺ� üũ�� �ִ� Ž�� ������ ��� ��


// ��������
char virtualPuzzle[boardSIZE];                      // ���� ����
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
int middleBound, tempSolve, tempBound;  // �߰� ��ǥ inversion ��
int middleDir, tempDir;                  // �߰� ��ǥ ����
int midDepth, tempDepth;              // �߰� ��ǥ ����
int midCutOfff, tempCutOff;            // �߰� ��ǥ ���� ����
int mode;                                  // ����,�߰� ��ǥ Ž�� ��� ����
int NodeCount;                            // Ž���� �� ��� ��
int searchCutOff;                         // ���� ����ġ

int sameCheck;                           // �ߺ�üũ ����,���� ����
int nextCutOff;                           // ���� Ž���� ���� ���� ����ġ
int argc1;
char** argv1;


// �Լ�
void VirtualPuzzle(int** puzzle);
int heuristic();
int Search(int inv_rowo, int inv_colo, int iBlank, int iPrev, int depth);


// ���ξ˰���
void puzzleSolution(void);
void step2(int** puzzle, int& iLoop, int& iLoop2, int& iLoop3);

//////////////////////////////// MAIN//////////////////////////////////////////
int main(int argc, char* argv[])
{
	argc1 = argc; argv1 = argv;

	puzzleSolution();

	return 0;
}
void step2(int** puzzle, int& iLoop, int& iLoop2, int& iLoop3) {
	searchCutOff = maxNODE;
	bsSTART = bSEND = sameCheck = 0;
	
	while (1) {
		puzzle = getPuzzleStatus();  // ���� ������ ������
		VirtualPuzzle(puzzle);  // ���� ������ ���� ���忡 ����
		// �߰� ��ǥ�� ã�ư��� ���� ������ �ʱ�ȭ
		middleBound = tempBound = tempSolve = midCutOfff = tempCutOff = 1000000;
		NodeCount = tempDepth = midDepth = mode = 0;
		tempDir = 4;
		int ret;
		if ((ret = heuristic()) == TRUE) {  // ���� ��ǥ�� ����
		   // �ϼ��� ���·� ������ ����
			for (iLoop = 0; iLoop < CUTOFF; iLoop++) move(SOLUTION[iLoop]);
			break;
		}
		else {
			mode = 1;
			midDepth = tempDepth;
			middleBound = tempBound;
			middleDir = tempDir;
			midCutOfff = tempCutOff;
			int ret1;
			ret1 = heuristic();  // �ٻ� Ž��
			// �߰� ��ǥ ���·� ������ ����
			for (iLoop = 0; iLoop < CUTOFF; iLoop++) move(SOLUTION[iLoop]);
			// Cycle�� ������ ��� �ִ� 2�� ������ ������ ���¹ۿ��� ã���� ���Ѵ�.
			// Normal search ��� 2�� ������ �̵� Ƚ�� �������� ���� Cycle�� ����
			// �Ѵٰ� �����Ѵ�.
			if (CUTOFF <= 2) {  // Ž�� �׷����� cycle ������ ��� �ߺ� üũ�� ����
				sameCheck = 1; searchCutOff = minNODE;
			}
			else {  // Cycle �� ���ٸ� �ߺ�üũ ���� ����
				sameCheck = 0; searchCutOff = maxNODE;
			}
		}
	}

}

void puzzleSolution() {
	int t = -1;
	printf(">>T �Է� : ");
	scanf("%d", &t);


	for (int i = 0; i < t; i++) {

		int** puzzle, iLoop, iLoop2, iLoop3;

		printf("\n>>5*5 ���� �Է�\n");
		puzzle = initialize(argc1, argv1);

		 // ���� ��� ���纻�� �ϳ� �������� ���߿� ����
		int arr[5][5];
		for (int j = 0; j < SIZE; j++) {
			for (int k = 0; k < SIZE; k++) {
				arr[j][k] = _startPuzzle[j][k];
			}
		}


		// real ida, ���⼭ ������ ������ ã�´ٰ� �����Ѵ�
		SSS55::ida55(arr, i);
		// �� �Լ����� ��ã�� ��� �Ʒ� �Լ����� �̿��� ������ ã�´�

		if (SSS55::pass == false && SSS55::canSolve == true) {

			T = i;



			// /4 ���
			arrMode = 0;
			for (iLoop = 0; iLoop < inverseSIZE; iLoop++) {
				inverseTABLE[iLoop] = (char)((iLoop / 4) + (iLoop % 4));
			}
			step2(puzzle, iLoop, iLoop2, iLoop3);




			// /3 ���
			// ����� ��̷� ������ �ʱ�ȭ
			for (int j = 0; j < SIZE; j++) {
				for (int k = 0; k < SIZE; k++) {
					_startPuzzle[j][k] = arr[j][k];
				}
			}
			re_initialize(argc1, argv1);
			arrMode = 1;
			arr2Count = 9999999;
			//step2LimitReal = step2Limit = 0;
			for (iLoop = 0; iLoop < inverseSIZE; iLoop++) {
				inverseTABLE[iLoop] = (char)((iLoop / 3) + (iLoop % 3));
			}
			step2(puzzle, iLoop, iLoop2, iLoop3);




			// /2 ���
			// ����� ��̷� ������ �ʱ�ȭ
			for (int j = 0; j < SIZE; j++) {
				for (int k = 0; k < SIZE; k++) {
					_startPuzzle[j][k] = arr[j][k];
				}
			}
			re_initialize(argc1, argv1);
			arrMode = 2;
			arr3Count = 9999999;
			//step2LimitReal = step2Limit = 0;
			for (iLoop = 0; iLoop < inverseSIZE; iLoop++) {
				inverseTABLE[iLoop] = (char)((iLoop / 2) + (iLoop % 2));
			}
			step2(puzzle, iLoop, iLoop2, iLoop3);




			// /3 %4 ���
			// ����� ��̷� ������ �ʱ�ȭ
			for (int j = 0; j < SIZE; j++) {
				for (int k = 0; k < SIZE; k++) {
					_startPuzzle[j][k] = arr[j][k];
				}
			}
			re_initialize(argc1, argv1);
			arrMode = 3;
			arr4Count = 9999999;
			//step2LimitReal = step2Limit = 0;
			for (iLoop = 0; iLoop < inverseSIZE; iLoop++) {
				inverseTABLE[iLoop] = (char)((iLoop / 3) + (iLoop % 4));
			}
			step2(puzzle, iLoop, iLoop2, iLoop3);




			// ��� ��� �κ�, /2, /3, /4 �� ���� ���� ���� ����Ѵ�
			if (arr1Count <= arr2Count && arr1Count <= arr3Count && arr1Count<=arr4Count)
			{
				printf("#%d %d ", i + 1, arr1Count);
				for (int k = 0; k < arr1Count; k++)
					printf("%c ", arr1[k]);
				printf("\n");
			}
			else if(arr2Count <= arr1Count && arr2Count <= arr3Count && arr2Count <= arr4Count){
				printf("#%d %d ", i + 1, arr2Count);
				for (int k = 0; k < arr2Count; k++)
					printf("%c ", arr2[k]);
				printf("\n");
			}
			else if(arr3Count <= arr1Count &&  arr3Count <= arr2Count && arr3Count <= arr4Count){
				printf("#%d %d ", i + 1, arr3Count);
				for (int k = 0; k < arr3Count; k++)
					printf("%c ", arr3[k]);
				printf("\n");
			}
			else {
				printf("#%d %d ", i + 1, arr4Count);
				for (int k = 0; k < arr4Count; k++)
					printf("%c ", arr4[k]);
				printf("\n");
			}
		}
	}
}


void VirtualPuzzle(int** puzzle)
{
	int iLoop, iLoop2;

	for (iLoop = 0; iLoop < SIZE; iLoop++)
		for (iLoop2 = 0; iLoop2 < SIZE; iLoop2++)
			virtualPuzzle[iLoop * SIZE + iLoop2] = (char)(puzzle[iLoop][iLoop2]);
}


int heuristic()
{
	int iBlank, inv_row = 0, inv_col = 0, iTemp, iLoop, iLoop2, lower_bound = 0;
	int md_row = 0, md_col = 0;
	char Trans[boardSIZE];

	// ###### ����� ������ ���� ######
	for (iLoop = 0; iLoop < boardSIZE; iLoop++)
	{
		if (virtualPuzzle[iLoop] == BLANK) {  
			iBlank = iLoop;
			continue;
		}
		iTemp = virtualPuzzle[iLoop];

		for (iLoop2 = iLoop + 1; iLoop2 < boardSIZE; iLoop2++)
			if (iTemp > virtualPuzzle[iLoop2]) inv_row++;
	}

	// ###### ������ ������ ���� ######

	for (iLoop = 0; iLoop < SIZE; iLoop++)
		for (iLoop2 = 0; iLoop2 < SIZE; iLoop2++)
			Trans[iLoop2 * SIZE + iLoop] = change[virtualPuzzle[iLoop * SIZE + iLoop2]];

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
			boardState[bSEND][iLoop] = virtualPuzzle[iLoop];
		bSEND++;
		if (bSEND >= 6) bsSTART++;
	}

	// ###### IDA* ���� ######
	if (mode == 0) CUTOFF = lower_bound; 
	else CUTOFF = midCutOfff; 
	while (1) {
		nextCutOff = 1000000;
		NodeCount = 0;
		// ���� ��ǥ�� ã�Ҵٸ� Ž�� �ߴ�
		int ret;
		if (ret = Search(inv_row, inv_col, iBlank, -1, 0) == TRUE) break;
		else {
			if (mode == 0 && NodeCount > searchCutOff) return FALSE;
			else CUTOFF = nextCutOff;  // Ž���� �����Ͽ��ٸ� lower bound �� ����
		}
	}
	return TRUE;
}


int Search(int inv_rowo, int inv_colo, int iBlank, int iPrev, int depth)
{
	int iTemp, iLoop, iLoop2, iLoop3, iLoop4, NextMove, n, n2, lower_bound, distant;
	int inv_row, inv_col, equal;
	direction course;

	// Ž�� �ð��� ����� ��� Ž���� �ߴ�
	if (mode == 0 && NodeCount > searchCutOff) return FALSE;

	depth++; // ���� ����

	for (iLoop = 0; iLoop < 4; iLoop++)  // 4����(��,�Ʒ�,����,������)�� ���ؼ�
	{
		NextMove = iBlank + direct[iLoop];
		// ������ ���� �ڸ����� �˻�
		if (NextMove < 0 || NextMove > boardSIZE - 1 || direct[iLoop] == 1
			&& NextMove % SIZE == 0 || direct[iLoop] == -1
			&& NextMove % SIZE == SIZE - 1) continue;
		if (NextMove == iPrev) continue;  // ��� ������ ��ȣ��� �״�� �� �д�.
		n = virtualPuzzle[NextMove];  // �̵��� ��ȣ�� ������

		inv_row = inv_rowo;
		inv_col = inv_colo;

		switch (iLoop) {  // ���ڸ� �Ʒ��� �̵�
		case 0:
			course = DOWN;
			for (iLoop2 = NextMove + 1; iLoop2 < iBlank; iLoop2++)
				if (virtualPuzzle[iLoop2] > n) inv_row++; else inv_row--;
			break;
		case 1:  // ���ڸ� �������� �̵�
			course = LEFT;
			n2 = change[n];
			for (iLoop2 = iBlank + SIZE; iLoop2 < boardSIZE; iLoop2 += SIZE)
				if (change[virtualPuzzle[iLoop2]] > n2) inv_col--; else inv_col++;
			for (iLoop2 = NextMove - SIZE; iLoop2 >= 0; iLoop2 -= SIZE)
				if (change[virtualPuzzle[iLoop2]] > n2) inv_col--; else inv_col++;
			break;
		case 2:  // ���ڸ� ���� �̵�
			course = UP;
			for (iLoop2 = iBlank + 1; iLoop2 < NextMove; iLoop2++)
				if (virtualPuzzle[iLoop2] > n) inv_row--; else inv_row++;
			break;
		case 3:  // ���ڸ� ���������� �̵�
			course = RIGHT;
			n2 = change[n];
			for (iLoop2 = NextMove + SIZE; iLoop2 < boardSIZE; iLoop2 += SIZE)
				if (change[virtualPuzzle[iLoop2]] > n2) inv_col++; else inv_col--;
			for (iLoop2 = iBlank - SIZE; iLoop2 >= 0; iLoop2 -= SIZE)
				if (change[virtualPuzzle[iLoop2]] > n2) inv_col++; else inv_col--;
		}

		// �ڽ� ����� lower bound ����
		lower_bound = inverseTABLE[inv_row] + inverseTABLE[inv_col];

		if (!mode) NodeCount++;  // Ž���� ��� ���� ����
		if (sameCheck) {
			// ���� �������� ���� ���Դ� �������� üũ
			virtualPuzzle[NextMove] = BLANK;
			virtualPuzzle[iBlank] = n;
			for (iLoop3 = bsSTART; iLoop3 < bSEND; iLoop3++)
			{
				equal = 0;
				for (iLoop4 = 0; iLoop4 < boardSIZE; iLoop4++)
				{
					if (boardState[iLoop3][iLoop4] == virtualPuzzle[iLoop4]) equal++;
				}
				if (equal == 25) break;
			}
			virtualPuzzle[NextMove] = n;
			virtualPuzzle[iBlank] = BLANK;
			if (equal == 25) continue;  // �ߺ��̸� �� ���� ���� ����
		}

		// ���� �ð��ȿ� ��ǥ�� ã�� �������� �ٻ�Ž���� �ϱ� ���� �߰� ��ǥ ������ ����
		if (mode == 0 && (tempBound > lower_bound)) {
			tempBound = lower_bound;  // inversion �� ����
			tempDepth = depth;  // ���� ����
			tempCutOff = CUTOFF;  // ���� ���� ����
			tempDir = iLoop;  // ���� ����
		}

		// �߰� ��ǥ ����, ���� ��ǥ ����
		if (lower_bound == 0 || mode == 1 && middleBound == lower_bound &&
			midDepth == depth && middleDir == iLoop && midCutOfff == CUTOFF) {
			CUTOFF = depth;
			SOLUTION[depth - 1] = course;  // �̵� ���� ���
			return TRUE;
		}
		else if (depth + lower_bound <= CUTOFF) {  // ���� ���� ���� ���ų� �۴ٸ�
		// ���� �����ǿ��� ���� �̵�
			virtualPuzzle[NextMove] = BLANK;
			virtualPuzzle[iBlank] = n;
			if (Search(inv_row, inv_col, NextMove, iBlank, depth)) {
				SOLUTION[depth - 1] = course;  // �̵� ���� ���
				return TRUE;
			}
			// ���� �������� �����·� �ǵ��� ����
			virtualPuzzle[NextMove] = n;
			virtualPuzzle[iBlank] = BLANK;
		}
		else {
			// ���� ���� ������ ����
			if (nextCutOff > depth + lower_bound) nextCutOff = depth + lower_bound;
		}
	}
	return FALSE;
}