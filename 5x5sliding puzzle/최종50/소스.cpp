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
#define maxNODE      80000000           // 최대 탐색 가능한 노드 수
#define minNODE      8000000            // 중복 체크시 최대 탐색 가능한 노드 수


// 전역변수
char virtualPuzzle[boardSIZE];                      // 가상 보드
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
int middleBound, tempSolve, tempBound;  // 중간 목표 inversion 값
int middleDir, tempDir;                  // 중간 목표 방향
int midDepth, tempDepth;              // 중간 목표 깊이
int midCutOfff, tempCutOff;            // 중간 목표 깊이 제한
int mode;                                  // 최종,중간 목표 탐색 모드 설정
int NodeCount;                            // 탐색한 총 노드 수
int searchCutOff;                         // 깊이 제한치

int sameCheck;                           // 중복체크 실행,정지 설정
int nextCutOff;                           // 다음 탐색에 사용될 깊이 제한치
int argc1;
char** argv1;


// 함수
void VirtualPuzzle(int** puzzle);
int heuristic();
int Search(int inv_rowo, int inv_colo, int iBlank, int iPrev, int depth);


// 메인알고리즘
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
		puzzle = getPuzzleStatus();  // 보드 정보를 가져옴
		VirtualPuzzle(puzzle);  // 보드 정보를 가상 보드에 저장
		// 중간 목표를 찾아가기 위한 변수들 초기화
		middleBound = tempBound = tempSolve = midCutOfff = tempCutOff = 1000000;
		NodeCount = tempDepth = midDepth = mode = 0;
		tempDir = 4;
		int ret;
		if ((ret = heuristic()) == TRUE) {  // 최종 목표에 도달
		   // 완성된 상태로 퍼즐을 맞춤
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
			ret1 = heuristic();  // 근사 탐색
			// 중간 목표 상태로 퍼즐을 맞춤
			for (iLoop = 0; iLoop < CUTOFF; iLoop++) move(SOLUTION[iLoop]);
			// Cycle이 존재할 경우 최대 2번 움직인 게임판 상태밖에는 찾지를 못한다.
			// Normal search 결과 2번 이하의 이동 횟수 구해졌을 때는 Cycle이 존재
			// 한다고 간주한다.
			if (CUTOFF <= 2) {  // 탐색 그래프에 cycle 존재할 경우 중복 체크를 실행
				sameCheck = 1; searchCutOff = minNODE;
			}
			else {  // Cycle 이 없다면 중복체크 하지 않음
				sameCheck = 0; searchCutOff = maxNODE;
			}
		}
	}

}

void puzzleSolution() {
	int t = -1;
	printf(">>T 입력 : ");
	scanf("%d", &t);


	for (int i = 0; i < t; i++) {

		int** puzzle, iLoop, iLoop2, iLoop3;

		printf("\n>>5*5 퍼즐 입력\n");
		puzzle = initialize(argc1, argv1);

		 // 퍼즐 모양 복사본을 하나 만들어놓고 나중에 쓴다
		int arr[5][5];
		for (int j = 0; j < SIZE; j++) {
			for (int k = 0; k < SIZE; k++) {
				arr[j][k] = _startPuzzle[j][k];
			}
		}


		// real ida, 여기서 무조건 최적을 찾는다고 가정한다
		SSS55::ida55(arr, i);
		// 위 함수에서 못찾은 경우 아래 함수들을 이용해 정답을 찾는다

		if (SSS55::pass == false && SSS55::canSolve == true) {

			T = i;



			// /4 모드
			arrMode = 0;
			for (iLoop = 0; iLoop < inverseSIZE; iLoop++) {
				inverseTABLE[iLoop] = (char)((iLoop / 4) + (iLoop % 4));
			}
			step2(puzzle, iLoop, iLoop2, iLoop3);




			// /3 모드
			// 백업된 어레이로 퍼즐판 초기화
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




			// /2 모드
			// 백업된 어레이로 퍼즐판 초기화
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




			// /3 %4 모드
			// 백업된 어레이로 퍼즐판 초기화
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




			// 경로 출력 부분, /2, /3, /4 중 가장 작은 것을 출력한다
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

	// ###### 행방향 전도수 구함 ######
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

	// ###### 열방향 전도수 구함 ######

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

	//초기 lower bound 설정
	lower_bound = inverseTABLE[inv_row] + inverseTABLE[inv_col];

	if (mode == 0) {  // 근사탐색이 아니라면
	   // 게임판 상태를 저장
		for (iLoop = 0; iLoop < boardSIZE; iLoop++)
			boardState[bSEND][iLoop] = virtualPuzzle[iLoop];
		bSEND++;
		if (bSEND >= 6) bsSTART++;
	}

	// ###### IDA* 실행 ######
	if (mode == 0) CUTOFF = lower_bound; 
	else CUTOFF = midCutOfff; 
	while (1) {
		nextCutOff = 1000000;
		NodeCount = 0;
		// 최종 목표를 찾았다면 탐색 중단
		int ret;
		if (ret = Search(inv_row, inv_col, iBlank, -1, 0) == TRUE) break;
		else {
			if (mode == 0 && NodeCount > searchCutOff) return FALSE;
			else CUTOFF = nextCutOff;  // 탐색에 실패하였다면 lower bound 를 증가
		}
	}
	return TRUE;
}


int Search(int inv_rowo, int inv_colo, int iBlank, int iPrev, int depth)
{
	int iTemp, iLoop, iLoop2, iLoop3, iLoop4, NextMove, n, n2, lower_bound, distant;
	int inv_row, inv_col, equal;
	direction course;

	// 탐색 시간이 길어질 경우 탐색을 중단
	if (mode == 0 && NodeCount > searchCutOff) return FALSE;

	depth++; // 깊이 증가

	for (iLoop = 0; iLoop < 4; iLoop++)  // 4방향(위,아래,왼쪽,오른쪽)에 대해서
	{
		NextMove = iBlank + direct[iLoop];
		// 보드의 가장 자리인지 검사
		if (NextMove < 0 || NextMove > boardSIZE - 1 || direct[iLoop] == 1
			&& NextMove % SIZE == 0 || direct[iLoop] == -1
			&& NextMove % SIZE == SIZE - 1) continue;
		if (NextMove == iPrev) continue;  // 방금 움직인 번호라면 그대로 놔 둔다.
		n = virtualPuzzle[NextMove];  // 이동할 번호를 가져옴

		inv_row = inv_rowo;
		inv_col = inv_colo;

		switch (iLoop) {  // 숫자를 아래로 이동
		case 0:
			course = DOWN;
			for (iLoop2 = NextMove + 1; iLoop2 < iBlank; iLoop2++)
				if (virtualPuzzle[iLoop2] > n) inv_row++; else inv_row--;
			break;
		case 1:  // 숫자를 왼쪽으로 이동
			course = LEFT;
			n2 = change[n];
			for (iLoop2 = iBlank + SIZE; iLoop2 < boardSIZE; iLoop2 += SIZE)
				if (change[virtualPuzzle[iLoop2]] > n2) inv_col--; else inv_col++;
			for (iLoop2 = NextMove - SIZE; iLoop2 >= 0; iLoop2 -= SIZE)
				if (change[virtualPuzzle[iLoop2]] > n2) inv_col--; else inv_col++;
			break;
		case 2:  // 숫자를 위로 이동
			course = UP;
			for (iLoop2 = iBlank + 1; iLoop2 < NextMove; iLoop2++)
				if (virtualPuzzle[iLoop2] > n) inv_row--; else inv_row++;
			break;
		case 3:  // 숫자를 오른쪽으로 이동
			course = RIGHT;
			n2 = change[n];
			for (iLoop2 = NextMove + SIZE; iLoop2 < boardSIZE; iLoop2 += SIZE)
				if (change[virtualPuzzle[iLoop2]] > n2) inv_col++; else inv_col--;
			for (iLoop2 = iBlank - SIZE; iLoop2 >= 0; iLoop2 -= SIZE)
				if (change[virtualPuzzle[iLoop2]] > n2) inv_col++; else inv_col--;
		}

		// 자식 노드의 lower bound 설정
		lower_bound = inverseTABLE[inv_row] + inverseTABLE[inv_col];

		if (!mode) NodeCount++;  // 탐색한 노드 수를 저장
		if (sameCheck) {
			// 현재 게임판이 전에 나왔던 상태인지 체크
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
			if (equal == 25) continue;  // 중복이면 그 노드로 가지 못함
		}

		// 일정 시간안에 목표를 찾지 못했을때 근사탐색을 하기 위한 중간 목표 정보를 저장
		if (mode == 0 && (tempBound > lower_bound)) {
			tempBound = lower_bound;  // inversion 값 저장
			tempDepth = depth;  // 깊이 저장
			tempCutOff = CUTOFF;  // 깊이 제한 저장
			tempDir = iLoop;  // 방향 저장
		}

		// 중간 목표 도달, 최종 목표 도달
		if (lower_bound == 0 || mode == 1 && middleBound == lower_bound &&
			midDepth == depth && middleDir == iLoop && midCutOfff == CUTOFF) {
			CUTOFF = depth;
			SOLUTION[depth - 1] = course;  // 이동 방향 기록
			return TRUE;
		}
		else if (depth + lower_bound <= CUTOFF) {  // 깊이 제한 보다 같거나 작다면
		// 가상 게임판에서 숫자 이동
			virtualPuzzle[NextMove] = BLANK;
			virtualPuzzle[iBlank] = n;
			if (Search(inv_row, inv_col, NextMove, iBlank, depth)) {
				SOLUTION[depth - 1] = course;  // 이동 방향 기록
				return TRUE;
			}
			// 가상 게임판을 전상태로 되돌려 놓음
			virtualPuzzle[NextMove] = n;
			virtualPuzzle[iBlank] = BLANK;
		}
		else {
			// 다음 깊이 제한을 설정
			if (nextCutOff > depth + lower_bound) nextCutOff = depth + lower_bound;
		}
	}
	return FALSE;
}