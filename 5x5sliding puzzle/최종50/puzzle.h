#define SIZE 5
#define BLANK SIZE * SIZE
#define FALSE 0
#define TRUE !FALSE

int arrMode;	// 0 , 1, 2
char arr1[700];	//...   /4
char arr2[700];	//...   /3
char arr3[700]; //...   /2
char arr4[700]; //...   /3, %4
int arr1Count;
int arr2Count;
int arr3Count;
int arr4Count;


// 빈칸
typedef struct {
	int row;
	int col;
} position;

typedef enum {
	LEFT,
	RIGHT,
	UP,
	DOWN
} direction;

typedef enum {
	ERROR = -1,
	SUCCESS = 1
} status;


// 함수정의
int** initialize(int, char**);
int** getPuzzleStatus(void);
status move(direction);
position getPuzzlePosition(void);
int** re_initialize(int, char**);

//정답 저장소와 퍼즐 저장소
char s[700];
int count = 0;

int _startPuzzle[SIZE][SIZE] = { {0, }, };
int _trycount = 0;
position __pos;
int T;




int** getPuzzleStatus(void)
{
	int i, j;
	int** __startPuzzle;

	__startPuzzle = (int**)malloc(SIZE * sizeof(int*));
	__startPuzzle[0] = (int*)malloc(SIZE * SIZE * sizeof(int*));

	for (i = 1; i < SIZE; i++)
		__startPuzzle[i] = __startPuzzle[0] + i * SIZE;

	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++)
			__startPuzzle[i][j] = _startPuzzle[i][j];

	return (__startPuzzle);
}

// 재검색을 위한 퍼즐 초기화
int** re_initialize(int, char**) {
	int i = 0;

	int** __startPuzzle;

	_trycount = 0;

	count = 0;

	__startPuzzle = getPuzzleStatus();
	__pos = getPuzzlePosition();

	//printf("Initial state:\n");
	//view_puzzle();

	return (__startPuzzle);
}

// 초반 초기화 함수, 퍼즐도 입력받는다
int** initialize(int, char**)
{
	int i = 0;

	int** __startPuzzle;

	_trycount = 0;

	count = 0;

	for (int j = 0; j < SIZE; j++) {
		for (int k = 0; k < SIZE; k++) {
			scanf_s("%d", &_startPuzzle[j][k]);
		}
	}

	__startPuzzle = getPuzzleStatus();
	__pos = getPuzzlePosition();

	return (__startPuzzle);
}

position getPuzzlePosition(void)
{
	int i, j;
	int flag = TRUE;
	position _pos;

	for (i = 0; i < SIZE && flag; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			if (_startPuzzle[i][j] == BLANK)
			{
				_pos.row = i;
				_pos.col = j;

				flag = FALSE;
				break;
			}
		}
	}

	return (_pos);
}

void swap_position(int row, int col)
{
	int tmp;

	tmp = _startPuzzle[__pos.row][__pos.col];
	_startPuzzle[__pos.row][__pos.col] = _startPuzzle[row][col];
	_startPuzzle[row][col] = tmp;
	__pos.row = row;
	__pos.col = col;
}

status move(direction dir)
{
	int tmp;
	int i, j, endflag = TRUE;

	_trycount++;
	tmp = _startPuzzle[__pos.row][__pos.col];

	switch (dir)
	{
	case UP:
		if (__pos.row == SIZE - 1) return (ERROR);
		swap_position(__pos.row + 1, __pos.col);
		s[count] = 'D'; count++;
		break;
	case DOWN:
		if (__pos.row == 0) return (ERROR);
		swap_position(__pos.row - 1, __pos.col);
		s[count] = 'U'; count++;
		break;
	case LEFT:
		if (__pos.col == SIZE - 1) return (ERROR);
		swap_position(__pos.row, __pos.col + 1);
		s[count] = 'R'; count++;
		break;
	case RIGHT:
		if (__pos.col == 0) return (ERROR);
		swap_position(__pos.row, __pos.col - 1);
		s[count] = 'L'; count++;
		break;
	}

	for (i = 0; i < SIZE && endflag; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			if (_startPuzzle[i][j] != i * SIZE + j + 1)
			{
				endflag = FALSE;
				break;
			}
		}
	}


	// 환석's 제거기
	if (endflag)
	{
		while (1) {
			int nn1 = 0;

			for (int i = 0; i < count - 1; i++) {
				char a = s[i];
				char b = s[i + 1];


				if (a == 'R' && b == 'L') {

					for (int j = i + 2; j <= count + 1; j++) {
						s[j - 2] = s[j];
						s[j - 1] = s[j + 1];
					}
					nn1++; count = count - 2;
				}
				else if (a == 'L' && b == 'R') {

					for (int j = i + 2; j <= count + 1; j++) {
						s[j - 2] = s[j];
						s[j - 1] = s[j + 1];
					}
					nn1++; count = count - 2;
				}
				else if (a == 'D' && b == 'U') {

					for (int j = i + 2; j <= count + 1; j++) {
						s[j - 2] = s[j];
						s[j - 1] = s[j + 1];
					}
					nn1++;  count = count - 2;
				}
				else if (a == 'U' && b == 'D') {

					for (int j = i + 2; j <= count + 1; j++) {
						s[j - 2] = s[j];
						s[j - 1] = s[j + 1];
					}
					nn1++;  count = count - 2;
				}

			}
			if (nn1 == 0) break;

		}


		// 이곳에 왔으면 찾은 경우이다.
		// /4, /3, /2 경우 세가지 모두 저장
		if (arrMode == 0) {
			for (int i = 0; i < count; i++) {
				arr1[i] = s[i];
			}
			arr1Count = count;
		}
		else if (arrMode == 1) {		
			for (int i = 0; i < count; i++) {
				arr2[i] = s[i];
			}
			arr2Count = count;
		}
		else if(arrMode == 2) {
			for (int i = 0; i < count; i++) {
				arr3[i] = s[i];
			}
			arr3Count = count;
		}
		else if(arrMode == 3) {
			for (int i = 0; i < count; i++) {
				arr4[i] = s[i];
			}
			arr4Count = count;
		}
	}
	return (SUCCESS);
}