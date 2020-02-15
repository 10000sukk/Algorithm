#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <ctime>
using namespace std;
#define IDALIMIT 20

namespace SSS55 {
	int T;
	const int MAXN = 5, MAXSTEP = 700, MAXP = 24;
	bool canSolve;

	int tile[MAXN][MAXN];
	const int dr[4] = { 1, 0, -1, 0 }, dc[4] = { 0, 1, 0, -1 }, opp[4] = { 2, 3, 0, 1 }; //ROW, COL,�ݴ� (dr[i], dc[i])
	//(dr[0], dr[0]) �� �Ʒ���,  opp[0] �� 2 = ����
	int tr[MAXP], tc[MAXP], upper;
	char rec[MAXSTEP]; // ��� ����
	const char name[4] = { 'D', 'R', 'U', 'L' };
	bool pass;

	void initialization();
	int heuristic(int tile[][MAXN]);
	bool valid(int r, int c);
	bool solvability(int r, int tile[][MAXN]);
	void IDA(int depth, int r, int c, int est, int pre);
	int getBlank();

	int ida55Limit = 0;      // 1000000 = > 1
	int ida55LImitReal = 0;   // 250 => �� 1��


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
					printf("%2d ", puzzle[i][j] + 1);
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

		}
		int blank() {
			for (int i = 0; i < MAXN; i++)
				for (int j = 0; j < MAXN; j++)
					if (puzzle[i][j] == MAXN * MAXN)
						return i * MAXN + j;
		}
	};



	void  ida55(int arr[5][5], int t)
	{
		T = t;
		ida55Limit = 0;      // 1000000 = > 1
		ida55LImitReal = 0;   // 250 => �� 1��

		printf("\n> 1�� Ž����.. %d�� ��� ����ǰ� �������ֽ��ϴ�\n> ", IDALIMIT);


		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				tile[i][j] = arr[i][j];


		initialization();
		pass = false;
		int sr, sc;


		for (int i = 0; i < MAXN; i++) {
			for (int j = 0; j < MAXN; j++) {
				tile[i][j]--;
			}
		}

		sr = getBlank() / MAXN;
		sc = getBlank() % MAXN;

		printf("\a");
		if (!solvability(sr, tile)) { canSolve = false; printf("#%d -1\n", T + 1); }
		else
		{
			canSolve = true;
			int cost = heuristic(tile);
			upper = min(MAXSTEP, cost); // ���� ����
			while (!pass)
			{
				//printf("-");
				IDA(0, sr, sc, cost, -1);
				upper = min(upper + 2, MAXSTEP); // ������ �÷��ش�.
				if (ida55LImitReal == IDALIMIT) {
					printf("\n> 2�� Ž����..\n");
					return;
				}
			}
		}
		printf("\a");
	}

	int getBlank() {
		int i = -1;
		for (i = 0; i < MAXN * MAXN; i++)
			if (tile[i / MAXN][i % MAXN] == MAXN * MAXN - 1)
				return i;
		return i;
	}


	void initialization()
	{
		for (int i = 0; i < MAXP; i++)
			tr[i] = i / MAXN, tc[i] = i % MAXN;
	}

	int heuristic(int tile[][MAXN]) //����ư �Ÿ��� heuristic function ���� ����Ͽ���.
	{
		int ret = 0;
		for (int i = 0; i < MAXN; i++)
			for (int j = 0; j < MAXN; j++)
				if (tile[i][j] < MAXN * MAXN - 1)
					ret += abs(i - tr[tile[i][j]]) + abs(j - tc[tile[i][j]]);
		return ret;
	}

	bool valid(int r, int c) // Ÿ���� �̵������� �������� �˷��ش�
	{
		return r >= 0 && r < MAXN && c >= 0 && c < MAXN;
	}

	bool solvability(int r, int tile[][MAXN])
	{// 0~24���� �� ���ִ� ������ ������ ã�� �� �ִ��� �˷��ش�
		int line[MAXN * MAXN], cnt = 0, inversion = 0;

		for (int i = 0; i < MAXN; i++)
			for (int j = 0; j < MAXN; j++)
				line[cnt++] = tile[i][j];

		for (int i = 0; i < MAXN * MAXN; i++)
			if (line[i] < MAXN * MAXN - 1)
			{
				for (int j = i + 1; j < MAXN * MAXN; j++)
					if (line[i] > line[j])
						inversion++;
			}
		//printf("\n�ι��� ���� %d \n", inversion);


		if (inversion % 2 == 0)
			return true;
		else
			return false;

	}

	void IDA(int depth, int r, int c, int est, int pre)
	{   //   ����,   ��ĭrow, ��ĭcol, ���� ���, ���� �̵��� ����
		ida55Limit++;
		if (ida55Limit == 10000000) {
			ida55LImitReal++;
			printf("%d ", ida55LImitReal);
			ida55Limit = 0;
		}
		if (ida55LImitReal == IDALIMIT)
			return;

		if (pass) return;
		if (est == 0) // ��θ� ã�� ���
		{
			pass = true;

			PUZZLE p(tile);

			printf("\n#%d %d ", T + 1, depth);
			for (int i = 0; i < depth; i++) {
				printf("%c ", rec[i]);
				p.move(i);
			}
			printf("\n");
			//p.show(); //  �ϼ��� ������ ������
			//printf("\n�̵� ȸ�� = %d \n", depth);
			return;
		}

		for (int i = 0; i < 4; i++) // 4���� �������� �̵��Ѵ�.
			if (i != pre) //���� �̵��ߴ� ������ ���������δ� �̵����� �ʴ´�.
			{
				int nr = r + dr[i], nc = c + dc[i], oCost, nCost, bak;

				if (valid(nr, nc))
				{

					bak = tile[nr][nc];
					oCost = abs(nr - tr[bak]) + abs(nc - tc[bak]);
					nCost = abs(r - tr[bak]) + abs(c - tc[bak]);

					// ���ݱ��� ���� heuristic cost�� ���� ���� upper ���� �۰ų� ���ٸ� �� ã�ư��� �����Ƿ� ��� ȣ�� �Ѵ�.
					if (depth + est + nCost - oCost + 1 <= upper)
					{
						tile[r][c] = bak, tile[nr][nc] = MAXN * MAXN - 1;   // �ٲٱ�
						rec[depth] = name[i];//��� ����
						IDA(depth + 1, nr, nc, est + nCost - oCost, opp[i]); // ���ȣ��
						tile[r][c] = MAXN * MAXN - 1, tile[nr][nc] = bak; // ������� �ٲٱ�
						if (pass) return;   // ��ΰ� ������ ����
					}
				}
			}
	}
}
