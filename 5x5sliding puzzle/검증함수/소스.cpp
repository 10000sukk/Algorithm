#pragma warning(disable :4996)
#include <iostream>
#include <cstdio>
#define MAXN 5
using std::cin; using std::cout; using std::endl;

class PUZZLE {
public:
	int puzzle[MAXN][MAXN];
	PUZZLE(int arr[MAXN][MAXN]) {
		for (int i = 0; i < MAXN; i++)
			for (int j = 0; j < MAXN; j++)
				puzzle[i][j] = arr[i][j];
	}
	void show() {
		printf("\n");
		for (int i = 0; i < MAXN; i++) {
			for (int j = 0; j < MAXN; j++)
				printf("%2d ", puzzle[i][j]);
			printf("\n");
		}
	}
	void move(const char d) {
		int x = blank() / MAXN;
		int y = blank() % MAXN;
		switch (d) {
		case 'D':
			std::swap(puzzle[x][y], puzzle[x + 1][y]);
			break;
		case 'R':
			std::swap(puzzle[x][y], puzzle[x][y + 1]);
			break;
		case 'U':
			std::swap(puzzle[x][y], puzzle[x - 1][y]);
			break;
		case 'L':
			std::swap(puzzle[x][y], puzzle[x][y - 1]);
			break;
		}
		show();
	}
	int blank() {
		for (int i = 0; i < MAXN; i++)
			for (int j = 0; j < MAXN; j++)
				if (puzzle[i][j] == MAXN * MAXN)
					return i * MAXN + j;
	}
	bool checkPuzzle() {
		bool ret = true;
		for (int i = 0; i < 25; i++) {
			if (puzzle[i / 5][i % 5] != i + 1)	// 다르면
				ret = false;
		}
		return ret;
	}
};

bool solvability(int tile[][MAXN]);

int main() {
	printf("검증함수\n 검증할 퍼즐의 개수 입력 : ");
	int t;
	scanf("%d",&t);

	for (int a = 0; a < t; a++) {
		//이동하기 전 배열을 입력받는다
		printf("퍼즐 입력\n");
		int arr[MAXN][MAXN];
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				scanf("%d", &arr[i][j]);
		PUZZLE p(arr);
		printf("초기 모양 :\n");
		p.show();

		// #순서 이동회수 경로.... 를 입력받는다
		printf("#?, 이동회수, 경로, 입력\n");
		char str1[5];
		int recSize;
		char rec[500];
		cin >> str1;		//#?
		cin >> recSize;		//이동회수
		for (int i = 0; i < recSize; i++)
			cin >> rec[i];

		// 경로가 존재하는지 판단하고 알려준다
		if (solvability(p.puzzle) == false) {
			printf("이 문제는 경로가 없다\n");
		}
		else {
			// 받은 경로대로 이동해본다
			printf("퍼즐 이동 시작\n");
			for (int i = 0; i < recSize; i++)
				p.move(rec[i]);

			// 성공과 실패를 출력한다
			if (p.checkPuzzle())
				printf("성공");
			else printf("실패");
		}
	}
	return 0;
}
bool solvability(int tile[][MAXN])
{// 0~24까지 라벨 되있는 퍼즐이 정답을 찾을 수 있는지 알려준다
	int line[MAXN * MAXN], cnt = 0, inversion = 0;


	// 선형 배열로 옮김
	for (int i = 0; i < MAXN; i++)
		for (int j = 0; j < MAXN; j++)
			line[cnt++] = tile[i][j]-1;

	for (int i = 0; i < MAXN * MAXN; i++)
		if (line[i] < MAXN * MAXN - 1)
		{
			for (int j = i + 1; j < MAXN * MAXN; j++)
				if (line[i] > line[j])
					inversion++;
		}

	if (inversion % 2 == 0)
		return true;
	else
		return false;

}