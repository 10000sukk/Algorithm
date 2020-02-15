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
	const int dr[4] = { 1, 0, -1, 0 }, dc[4] = { 0, 1, 0, -1 }, opp[4] = { 2, 3, 0, 1 }; //ROW, COL,반대 (dr[i], dc[i])
	//(dr[0], dr[0]) 은 아래로,  opp[0] 는 2 = 위로
	int tr[MAXP], tc[MAXP], upper;
	char rec[MAXSTEP]; // 경로 저장
	const char name[4] = { 'D', 'R', 'U', 'L' };
	bool pass;

	void initialization();
	int heuristic(int tile[][MAXN]);
	bool valid(int r, int c);
	bool solvability(int r, int tile[][MAXN]);
	void IDA(int depth, int r, int c, int est, int pre);
	int getBlank();

	int ida55Limit = 0;      // 1000000 = > 1
	int ida55LImitReal = 0;   // 250 => 약 1분


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
		ida55LImitReal = 0;   // 250 => 약 1분

		printf("\n> 1차 탐색중.. %d일 경우 종료되게 설정되있습니다\n> ", IDALIMIT);


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
			upper = min(MAXSTEP, cost); // 제한 설정
			while (!pass)
			{
				//printf("-");
				IDA(0, sr, sc, cost, -1);
				upper = min(upper + 2, MAXSTEP); // 제한을 올려준다.
				if (ida55LImitReal == IDALIMIT) {
					printf("\n> 2차 탐색중..\n");
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

	int heuristic(int tile[][MAXN]) //맨해튼 거리를 heuristic function 으로 사용하였다.
	{
		int ret = 0;
		for (int i = 0; i < MAXN; i++)
			for (int j = 0; j < MAXN; j++)
				if (tile[i][j] < MAXN * MAXN - 1)
					ret += abs(i - tr[tile[i][j]]) + abs(j - tc[tile[i][j]]);
		return ret;
	}

	bool valid(int r, int c) // 타일을 이동했을때 유요한지 알려준다
	{
		return r >= 0 && r < MAXN && c >= 0 && c < MAXN;
	}

	bool solvability(int r, int tile[][MAXN])
	{// 0~24까지 라벨 되있는 퍼즐이 정답을 찾을 수 있는지 알려준다
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
		//printf("\n인버스 개수 %d \n", inversion);


		if (inversion % 2 == 0)
			return true;
		else
			return false;

	}

	void IDA(int depth, int r, int c, int est, int pre)
	{   //   깊이,   빈칸row, 빈칸col, 실제 비용, 전에 이동한 방향
		ida55Limit++;
		if (ida55Limit == 10000000) {
			ida55LImitReal++;
			printf("%d ", ida55LImitReal);
			ida55Limit = 0;
		}
		if (ida55LImitReal == IDALIMIT)
			return;

		if (pass) return;
		if (est == 0) // 경로를 찾은 경우
		{
			pass = true;

			PUZZLE p(tile);

			printf("\n#%d %d ", T + 1, depth);
			for (int i = 0; i < depth; i++) {
				printf("%c ", rec[i]);
				p.move(i);
			}
			printf("\n");
			//p.show(); //  완성된 퍼즐을 보여줌
			//printf("\n이동 회수 = %d \n", depth);
			return;
		}

		for (int i = 0; i < 4; i++) // 4가지 방향으로 이동한다.
			if (i != pre) //전에 이동했던 방향의 역방향으로는 이동하지 않는다.
			{
				int nr = r + dr[i], nc = c + dc[i], oCost, nCost, bak;

				if (valid(nr, nc))
				{

					bak = tile[nr][nc];
					oCost = abs(nr - tr[bak]) + abs(nc - tc[bak]);
					nCost = abs(r - tr[bak]) + abs(c - tc[bak]);

					// 지금까지 비용과 heuristic cost를 더한 것이 upper 보다 작거나 같다면 잘 찾아가고 있으므로 재귀 호출 한다.
					if (depth + est + nCost - oCost + 1 <= upper)
					{
						tile[r][c] = bak, tile[nr][nc] = MAXN * MAXN - 1;   // 바꾸기
						rec[depth] = name[i];//경로 저장
						IDA(depth + 1, nr, nc, est + nCost - oCost, opp[i]); // 재귀호출
						tile[r][c] = MAXN * MAXN - 1, tile[nr][nc] = bak; // 원래대로 바꾸기
						if (pass) return;   // 경로가 있으면 종료
					}
				}
			}
	}
}
