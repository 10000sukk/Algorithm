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
			if (puzzle[i / 5][i % 5] != i + 1)	// �ٸ���
				ret = false;
		}
		return ret;
	}
};

bool solvability(int tile[][MAXN]);

int main() {
	printf("�����Լ�\n ������ ������ ���� �Է� : ");
	int t;
	scanf("%d",&t);

	for (int a = 0; a < t; a++) {
		//�̵��ϱ� �� �迭�� �Է¹޴´�
		printf("���� �Է�\n");
		int arr[MAXN][MAXN];
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				scanf("%d", &arr[i][j]);
		PUZZLE p(arr);
		printf("�ʱ� ��� :\n");
		p.show();

		// #���� �̵�ȸ�� ���.... �� �Է¹޴´�
		printf("#?, �̵�ȸ��, ���, �Է�\n");
		char str1[5];
		int recSize;
		char rec[500];
		cin >> str1;		//#?
		cin >> recSize;		//�̵�ȸ��
		for (int i = 0; i < recSize; i++)
			cin >> rec[i];

		// ��ΰ� �����ϴ��� �Ǵ��ϰ� �˷��ش�
		if (solvability(p.puzzle) == false) {
			printf("�� ������ ��ΰ� ����\n");
		}
		else {
			// ���� ��δ�� �̵��غ���
			printf("���� �̵� ����\n");
			for (int i = 0; i < recSize; i++)
				p.move(rec[i]);

			// ������ ���и� ����Ѵ�
			if (p.checkPuzzle())
				printf("����");
			else printf("����");
		}
	}
	return 0;
}
bool solvability(int tile[][MAXN])
{// 0~24���� �� ���ִ� ������ ������ ã�� �� �ִ��� �˷��ش�
	int line[MAXN * MAXN], cnt = 0, inversion = 0;


	// ���� �迭�� �ű�
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