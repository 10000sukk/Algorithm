#define SIZE 5
#define BLANK SIZE * SIZE
#define FALSE 0
#define TRUE !FALSE

/* return status */
typedef enum {
	ERROR = -1,
	SUCCESS = 1
} status;

/* moving direction */
typedef enum {
	LEFT,
	RIGHT,
	UP,
	DOWN
} direction;

/* blank position */
typedef struct {
	int row;
	int col;
} position;

/* function declaration */

int** initialize(int, char**);
int** get_status(void);
status move(direction);
position get_position(void);

//2단계를 위한것
char s[700];
int count = 0;

//3단계를 위한것
char s1[700];
int count1 = 0;


int _np[SIZE][SIZE] = { {0, }, };
int _trycount = 0;
position __pos;
int T;


int** get_status(void)
{
	int i, j;
	int** __np;

	__np = (int**)malloc(SIZE * sizeof(int*));
	__np[0] = (int*)malloc(SIZE * SIZE * sizeof(int*));

	for (i = 1; i < SIZE; i++)
		__np[i] = __np[0] + i * SIZE;

	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++)
			__np[i][j] = _np[i][j];

	return (__np);
}

int** initialize(int, char**)
{
	int i = 0;

	int** __np;

	_trycount = 0;

	count = 0;
	

	for (int j = 0; j < SIZE; j++) {
		for (int k = 0; k < SIZE; k++) {
			scanf_s("%d", &_np[j][k]);
		}
	}

	__np = get_status();
	__pos = get_position();

	//printf("Initial state:\n");
	//view_puzzle();

	return (__np);
}

//환석추가
int** initialize1(int, char**)
{
	int i = 0;

	int** __np;

	_trycount = 0;

	count = 0;


	

	__np = get_status();
	__pos = get_position();

	//printf("Initial state:\n");
	//view_puzzle();

	return (__np);
}



position get_position(void)
{
	int i, j;
	int flag = TRUE;
	position _pos;

	for (i = 0; i < SIZE && flag; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			if (_np[i][j] == BLANK)
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

	tmp = _np[__pos.row][__pos.col];
	_np[__pos.row][__pos.col] = _np[row][col];
	_np[row][col] = tmp;
	__pos.row = row;
	__pos.col = col;
}

status move(direction dir)
{
	int tmp;
	int i, j, endflag = TRUE;

	_trycount++;
	tmp = _np[__pos.row][__pos.col];

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
			if (_np[i][j] != i * SIZE + j + 1)
			{
				endflag = FALSE;
				break;
			}
		}
	}



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
					nn1++; count = count - 2;
				}
				else if (a == 'U' && b == 'D') {

					for (int j = i + 2; j <= count + 1; j++) {
						s[j - 2] = s[j];
						s[j - 1] = s[j + 1];
					}
					nn1++; count = count - 2;
				}

			}
			if (nn1 == 0) break;

		}



		/*
		printf("\n#%d %d ", T + 1, count);
		for (int i = 0; i < count; i++) {
			printf("%c ", s[i]);
		}
		printf("\n"); printf("\a");
		
		*/

		//환석 추가
		for (int i = 0; i < count; i++) {
			s1[i] = s[i];
		}
		count1 = count;

		/*
		printf("\n#%d %d ", T + 1, count1);
		for (int i = 0; i < count1; i++) {
			printf("%c ", s1[i]);
		}
		printf("\n"); printf("\a");
		*/


	}

	return (SUCCESS);
}


//3단계를 위한 move함수
status move1(direction dir)
{
	int tmp;
	int i, j, endflag = TRUE;

	_trycount++;
	tmp = _np[__pos.row][__pos.col];

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
			if (_np[i][j] != i * SIZE + j + 1)
			{
				endflag = FALSE;
				break;
			}
		}
	}



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
					nn1++; count = count - 2;
				}
				else if (a == 'U' && b == 'D') {

					for (int j = i + 2; j <= count + 1; j++) {
						s[j - 2] = s[j];
						s[j - 1] = s[j + 1];
					}
					nn1++; count = count - 2;
				}

			}
			if (nn1 == 0) break;

		}

		// 없앤 만큼 전체 개수를 빼준다

		printf("첫번째 카운트 : %d  ,  두번째 카운트 : %d\n", count1, count);
		if (count <= count1) {
			printf("\n#%d %d ", T + 1, count);
			for (int i = 0; i < count; i++) {
				printf("%c ", s[i]);
			}
			printf("\n"); printf("\a");
		}
		else
		{
			printf("\n#%d %d ", T + 1, count1);
			for (int i = 0; i < count1; i++) {
				printf("%c ", s1[i]);
			}
			printf("\n"); printf("\a");
		}

		

		





	}

	return (SUCCESS);
}