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
#define maxNODE      9000000           // 최대 탐색 가능한 노드 수
#define minNODE      9000000            // 중복 체크시 최대 탐색 가능한 노드 수

// declaring global variables
char virtualBoard[boardSIZE];                      // 가상 보드
int boardState[500][boardSIZE];              // 보드 상태 저장
int bsSTART, bSEND;                        // 이전 게임판 상태를 저장한 큐 포인터
char inverseTABLE[inverseSIZE];                  // 이동횟수 계산 테이블
int CUTOFF;                                // 깊이 제한치
char change[] = {                          // 행과 열을 서로 바꾸기 위해
   0,
   1, 6,11,16,21,
   2, 7,12,17,22,
   3, 8,13,18,23,
   4, 9,14,19,24,
   5,10,15,20,25
};
int direct[] = { -SIZE, 1, SIZE, -1 };
direction SOLUTION[200];                   // 최소 이동 순서를 저장
// 근사탐색에 사용되는 변수들
int middle_bound, temp_solve, temp_bound;  // 중간 목표 inversion 값
int middle_dir, temp_dir;                  // 중간 목표 방향
int middle_depth, temp_depth;              // 중간 목표 깊이
int middle_cutoff, temp_cutoff;            // 중간 목표 깊이 제한
int mode;                                  // 최종,중간 목표 탐색 모드 설정
int node_count;                            // 탐색한 총 노드 수
int search_cutoff;                         // 깊이 제한치

int state_check;                           // 중복체크 실행,정지 설정
int next_cutoff;                           // 다음 탐색에 사용될 깊이 제한치

// define sub-functions
void virtual_board(int** puzzle);
int heuristic();
int Search(int inv_rowo, int inv_colo, int iBlank, int iPrev, int depth);
void puzzleSolution(void);
int argc1;
char** argv1;

//환석퍼즐배열
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
	printf(">>T 입력 : ");
	scanf("%d", &t);


	for (int i = 0; i < t; i++) {

		int** puzzle, iLoop, iLoop2, iLoop3;

		printf("\n>>5*5 퍼즐 입력\n");
		puzzle = initialize(argc1, argv1);

		int arr[5][5];
		for (int j = 0; j < SIZE; j++) {
			for (int k = 0; k < SIZE; k++) {
				arr[j][k] = _np[j][k];
			}
		}
		// real ida
		SSS55::ida55(arr, i);

		// 우찬이
		if (SSS55::pass == false && SSS55::canSolve == true) {
		//if (true) {
			T = i;
			// 전도수를 이용하여 이동 횟수를 구하기 위한 테이블 준비
			for (iLoop = 0; iLoop < inverseSIZE; iLoop++)
				inverseTABLE[iLoop] = (char)((iLoop / 4) + (iLoop % 4));

			search_cutoff = maxNODE;
			bsSTART = bSEND = state_check = 0;
			// main loop
			while (1) {

				puzzle = get_status();  // 보드 정보를 가져옴
				virtual_board(puzzle);  // 보드 정보를 가상 보드에 저장
				// 중간 목표를 찾아가기 위한 변수들 초기화
				middle_bound = temp_bound = temp_solve = middle_cutoff = temp_cutoff = 1000000;
				node_count = temp_depth = middle_depth = mode = 0;
				temp_dir = 4;

				if (heuristic()) {  // 최종 목표에 도달
				   // 완성된 상태로 퍼즐을 맞춤
					for (iLoop = 0; iLoop < CUTOFF; iLoop++) move(SOLUTION[iLoop]);
					break;
				}
				else {
					// 제한 시간동안 최종 목표에 도달하지 못했다면, 목표에
					// 가장 근접한 중간 목표 상태로 퍼즐을 맞춤
					mode = 1;
					middle_depth = temp_depth;
					middle_bound = temp_bound;
					middle_dir = temp_dir;
					middle_cutoff = temp_cutoff;
					heuristic();  // 근사 탐색
					// 중간 목표 상태로 퍼즐을 맞춤
					for (iLoop = 0; iLoop < CUTOFF; iLoop++) move(SOLUTION[iLoop]);
					// Cycle이 존재할 경우 최대 2번 움직인 게임판 상태밖에는 찾지를 못한다.
					// Normal search 결과 2번 이하의 이동 횟수 구해졌을 때는 Cycle이 존재
					// 한다고 간주한다.
					if (CUTOFF <= 2) {  // 탐색 그래프에 cycle 존재할 경우 중복 체크를 실행
						state_check = 1; search_cutoff = minNODE;
					}
					else {  // Cycle 이 없다면 중복체크 하지 않음
						state_check = 0; search_cutoff = maxNODE;
					}
				}
			}
		}


		// 환석 추가

		for (int j = 0; j < SIZE; j++) {
			for (int k = 0; k < SIZE; k++) {
				_np[j][k] = arr[j][k];
			}
		}

		puzzle = initialize1(argc1, argv1);

		// real ida
		//SSS55::ida55(arr, i);

		// 우찬이2
		//if (SSS55::pass == false && SSS55::canSolve == true) {
		if (true) {
			T = i;
			// 전도수를 이용하여 이동 횟수를 구하기 위한 테이블 준비
			for (iLoop = 0; iLoop < inverseSIZE; iLoop++)
				inverseTABLE[iLoop] = (char)((iLoop / 2) + (iLoop % 2));

			search_cutoff = maxNODE;
			bsSTART = bSEND = state_check = 0;
			// main loop
			while (1) {

				puzzle = get_status();  // 보드 정보를 가져옴
				virtual_board(puzzle);  // 보드 정보를 가상 보드에 저장
				// 중간 목표를 찾아가기 위한 변수들 초기화
				middle_bound = temp_bound = temp_solve = middle_cutoff = temp_cutoff = 1000000;
				node_count = temp_depth = middle_depth = mode = 0;
				temp_dir = 4;

				if (heuristic()) {  // 최종 목표에 도달
				   // 완성된 상태로 퍼즐을 맞춤
					for (iLoop = 0; iLoop < CUTOFF; iLoop++) move1(SOLUTION[iLoop]);
					break;
				}
				else {
					// 제한 시간동안 최종 목표에 도달하지 못했다면, 목표에
					// 가장 근접한 중간 목표 상태로 퍼즐을 맞춤
					mode = 1;
					middle_depth = temp_depth;
					middle_bound = temp_bound;
					middle_dir = temp_dir;
					middle_cutoff = temp_cutoff;
					heuristic();  // 근사 탐색
					// 중간 목표 상태로 퍼즐을 맞춤
					for (iLoop = 0; iLoop < CUTOFF; iLoop++) move1(SOLUTION[iLoop]);
					// Cycle이 존재할 경우 최대 2번 움직인 게임판 상태밖에는 찾지를 못한다.
					// Normal search 결과 2번 이하의 이동 횟수 구해졌을 때는 Cycle이 존재
					// 한다고 간주한다.
					if (CUTOFF <= 2) {  // 탐색 그래프에 cycle 존재할 경우 중복 체크를 실행
						state_check = 1; search_cutoff = minNODE;
					}
					else {  // Cycle 이 없다면 중복체크 하지 않음
						state_check = 0; search_cutoff = maxNODE;
					}
				}
			}
		}
	}
}


///////////////////////////////////////////////////////////////
// 이동방법을 미리 구하기 위해 가상 보드를 생성
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
	// 현재의 게임판에서 다음에 생성될 게임판의 형태는 총 4가지이다.
	// 공백을 중심으로 위, 아래, 왼쪽, 오른쪽 숫자를 옮기는 경우가 그것인데,
	// 이와 같은 경우들은 자식노드가 2 - 4 개인 Tree 구조로 만들 수 있다.
	// 이 Tree의 leaf node 중에 우리가 원하는 최종 목표가 있을 것이고, 이 최종
	// 목표를 찾는다면 해당 게임판을 완성할 수 있는 경로를 알 수 있다.

	// 깊이 우선 탐색, 너비 우선 탐색은 목표에 잘 근접하고 있는지 알 수 없는 맹목
	// 적인 탐색 방법이어서, 탐색시간이 많이 걸린다. 탐색 시간을 단축 시키기 위해
	// 평가 함수와 깊이 제한을 이용하여 탐색을 하는 iteratice deepening A* 알고리즘을
	// 사용하였다.

	// 평가 함수는 inversion 을 사용하였다.

	// IDA* 알고리즘을 이용하여 최종 목표 노드를 찾는다면 효율적인 경로를 찾을 수 있겠
	// 지만, 탐색해야 할 Tree의 깊이가 깊어 진다면 이 또한 시간이 엄청 걸리게 된다.
	// (지수 함수 만큼 노드 수가 증가 하므로...)

	// 그래서 일정 갯수의 노드를 탐색했다면 탐색을 중지 하고, 탐색한 노드 중 최종 목표에
	// 근접한 노드로 게임판을 변경하고, 다시 탐색을 시작한다. 최단 경로는 아니지만 탐색
	// 시간을 줄이는데 상당한 효과를 얻을 수 있었다.

	// 탐색그래프가 트리 모양이 아닌 cycle 이 포함된 경우도 있다.
	// 이 경우 프로그램은 무한 루프에 빠지고 마는데 이를 해결하기 위해 이전 게임판 상태를
	// 저장하여 똑같은 게임판이 나오지 않도록 중복체크를 하였다.

	int iBlank, inv_row = 0, inv_col = 0, iTemp, iLoop, iLoop2, lower_bound = 0;
	int md_row = 0, md_col = 0;
	char Trans[boardSIZE];

	// ###### 행방향 전도수 구함 ######
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

	// ###### 열방향 전도수 구함 ######
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

	//초기 lower bound 설정
	lower_bound = inverseTABLE[inv_row] + inverseTABLE[inv_col];

	if (mode == 0) {  // 근사탐색이 아니라면
	   // 게임판 상태를 저장
		for (iLoop = 0; iLoop < boardSIZE; iLoop++)
			boardState[bSEND][iLoop] = virtualBoard[iLoop];
		bSEND++;
		if (bSEND >= 6) bsSTART++;
	}

	// ###### IDA* 실행 ######
	if (mode == 0) CUTOFF = lower_bound;  // if Normal search mode
	else CUTOFF = middle_cutoff;  // if Approximate search mode
	while (1) {
		next_cutoff = 1000000;
		node_count = 0;
		// 최종 목표를 찾았다면 탐색 중단
		if (Search(inv_row, inv_col, iBlank, -1, 0)) break;
		else {
			if (mode == 0 && node_count > search_cutoff) return FALSE;
			else CUTOFF = next_cutoff;  // 탐색에 실패하였다면 lower bound 를 증가
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

	// 탐색 시간이 길어질 경우 탐색을 중단
	if (mode == 0 && node_count > search_cutoff) return FALSE;

	depth++; // increase tree depth

	for (iLoop = 0; iLoop < 4; iLoop++)  // 4방향(위,아래,왼쪽,오른쪽)에 대해서
	{
		NextMove = iBlank + direct[iLoop];
		// 보드의 가장 자리인지 검사
		if (NextMove < 0 || NextMove > boardSIZE - 1 || direct[iLoop] == 1
			&& NextMove % SIZE == 0 || direct[iLoop] == -1
			&& NextMove % SIZE == SIZE - 1) continue;
		if (NextMove == iPrev) continue;  // 방금 움직인 번호라면 그대로 놔 둔다.
		n = virtualBoard[NextMove];  // 이동할 번호를 가져옴

		inv_row = inv_rowo;
		inv_col = inv_colo;

		// 숫자 이동에 따른 전도수 변화를 계산

		// □□□□□ 숫자를 상하로 이동할 경우 행방향 전도수만 변한다.
		// □□▽■■ 열방향 전도수는 변하지 않는다. 전도수 변화를 위해서 왼쪽
		// ■■△□□ 그림의 4개의 숫자 부분만 계산하면 됨.
		// □□□□□
		// □□□□□

		// □□■□□ 마찬가지로 좌우로 움직이는 경우도 열방향 전도수만 변한다.
		// □□■□□ 이때도 검은 사각형의 4개 숫자에 대해서만 계산해 줌.
		// □▷◁□□
		// □■□□□
		// □■□□□
		switch (iLoop) {  // 숫자를 아래로 이동
		case 0:
			course = DOWN;
			for (iLoop2 = NextMove + 1; iLoop2 < iBlank; iLoop2++)
				if (virtualBoard[iLoop2] > n) inv_row++; else inv_row--;
			break;
		case 1:  // 숫자를 왼쪽으로 이동
			course = LEFT;
			n2 = change[n];
			for (iLoop2 = iBlank + SIZE; iLoop2 < boardSIZE; iLoop2 += SIZE)
				if (change[virtualBoard[iLoop2]] > n2) inv_col--; else inv_col++;
			for (iLoop2 = NextMove - SIZE; iLoop2 >= 0; iLoop2 -= SIZE)
				if (change[virtualBoard[iLoop2]] > n2) inv_col--; else inv_col++;
			break;
		case 2:  // 숫자를 위로 이동
			course = UP;
			for (iLoop2 = iBlank + 1; iLoop2 < NextMove; iLoop2++)
				if (virtualBoard[iLoop2] > n) inv_row--; else inv_row++;
			break;
		case 3:  // 숫자를 오른쪽으로 이동
			course = RIGHT;
			n2 = change[n];
			for (iLoop2 = NextMove + SIZE; iLoop2 < boardSIZE; iLoop2 += SIZE)
				if (change[virtualBoard[iLoop2]] > n2) inv_col++; else inv_col--;
			for (iLoop2 = iBlank - SIZE; iLoop2 >= 0; iLoop2 -= SIZE)
				if (change[virtualBoard[iLoop2]] > n2) inv_col++; else inv_col--;
		}

		// 자식 노드의 lower bound 설정
		lower_bound = inverseTABLE[inv_row] + inverseTABLE[inv_col];

		if (!mode) node_count++;  // 탐색한 노드 수를 저장
		if (state_check) {
			// 현재 게임판이 전에 나왔던 상태인지 체크
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
			if (equal == 25) continue;  // 중복이면 그 노드로 가지 못함
		}

		// 일정 시간안에 목표를 찾지 못했을때 근사탐색을 하기 위한 중간 목표 정보를 저장
		if (mode == 0 && (temp_bound > lower_bound)) {
			temp_bound = lower_bound;  // inversion 값 저장
			temp_depth = depth;  // 깊이 저장
			temp_cutoff = CUTOFF;  // 깊이 제한 저장
			temp_dir = iLoop;  // 방향 저장
		}

		// 중간 목표 도달, 최종 목표 도달
		if (lower_bound == 0 || mode == 1 && middle_bound == lower_bound &&
			middle_depth == depth && middle_dir == iLoop && middle_cutoff == CUTOFF) {
			CUTOFF = depth;
			SOLUTION[depth - 1] = course;  // 이동 방향 기록
			return TRUE;
		}
		else if (depth + lower_bound <= CUTOFF) {  // 깊이 제한 보다 같거나 작다면
		// 가상 게임판에서 숫자 이동
			virtualBoard[NextMove] = BLANK;
			virtualBoard[iBlank] = n;
			if (Search(inv_row, inv_col, NextMove, iBlank, depth)) {
				SOLUTION[depth - 1] = course;  // 이동 방향 기록
				return TRUE;
			}
			// 가상 게임판을 전상태로 되돌려 놓음
			virtualBoard[NextMove] = n;
			virtualBoard[iBlank] = BLANK;
		}
		else {
			// 다음 깊이 제한을 설정
			if (next_cutoff > depth + lower_bound) next_cutoff = depth + lower_bound;
		}
	}
	return FALSE;
	getchar();
}