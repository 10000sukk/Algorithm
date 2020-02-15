#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#define PAGE_SIZE 512   /* page size */
#define MAX_D 8     /* max bitstring */
#define POW(x, y) (int) pow(x,y)
int nameToKey(char* name);//name 을 이용해서 키를 만들어내는 함수
//레코드 Struct 정의
struct Record
{char name[120];  /* name field */
char address[150]; /*address field*/
char major[100]; /*major field*/
int phoneNumber; /*phoneNumber field*/
int key; // name 을 이용해서 계산
};
//버켓 Struct 정의
struct Bucket
{int header;       /* bucket header */
int recordCnt;      /* bucket 내의 record 개수 */
struct Record record[3]; /* bucket 내의 record fields */
};
struct Directory
{int header;     /* directory의 header */
int table[512][3];  /* directory table - index, bucket number, header value*/
};
struct BlockManager
{int blockCnt;   /* Current Block 개수 */
int blockTable[512]; /* 전체 block의 현재 할당 상황 기록 field */
};
FILE* g_pInputStream;  /* input 파일의 핸들 */
FILE* g_pHashStream;  /* Hash 파일의 핸들 */
struct Directory* directory; /* directory */
struct BlockManager  blockManager; /* Block manager */
//////////////////////////////////////////////////////////////////////////////
int nameToKey(char* name) {
int key = 0;
int n = 0;
while (name[n] != NULL) {
key = key + (n+1)*(int)name[n];
n++;
}
key = key + 987654;
key = key % 12345;
return key;
}int PseudoKeyFunc(char key, int digits)
{int i;
int pseudo_key = 0;
int bit = 0;
/* key의 뒤 8자리 bit string에서 digits 만큼의 bit string을 얻기 */
for (i = MAX_D - 1; i >= MAX_D - digits; --i)
{
bit = (key & POW(2, i)) > 0 ? 1 : 0;
pseudo_key += POW(2, i - (MAX_D - digits)) * bit; /* 해당 bit를 누적 */
}
return pseudo_key;
}//insert 함수
int Insert(char* name , char* address , char* major , int phoneNumber)
{int i, j, k, temp;
int pseudo_key = 0;  /* 입력 key의 pseudo key*/
int bucketNum = -1;  /* 할당될 bucket의 number */
struct Bucket bucket, newBucket; /* disk의 bucket을 가져올 struct */
struct Record record;
struct Directory* newDirectory;
int key = nameToKey(name);
/* pseudo_key를 얻어 directory 참조 */
pseudo_key = PseudoKeyFunc(key, directory->header);
bucketNum = directory->table[pseudo_key][1];
/* 얻어온 bucket number를 통해 disk access */
if (bucketNum >= 0)
{
/* 해당 bucket 위치 찾아 읽기 */
fseek(g_pHashStream, PAGE_SIZE * bucketNum, SEEK_SET);
j = fread(&bucket, sizeof(struct Bucket), 1, g_pHashStream);
if (j == 0)
{ /* bucket 존재하지 않음 */
printf("Error occurred while reading hash file.\n");
return -1;
}
// 이미 해당 key가 존재하는지 확인

if (bucket.recordCnt > 0)
{
for (i = 0; i < bucket.recordCnt; ++i)
{
if (bucket.record[i].key == key)
{ // 해당 key 존재
printf("Insert failed. Key (%s) already exists.\n", name);
return 0;
}
}
}

/* 여유 공간이 있는지 확인 */
if (bucket.recordCnt < 3)
{ /* 여유 공간이 있으면 삽입 */
record.key = key;
memcpy(record.name, name, 120); //record.name = name;
memcpy(record.address, address, 150);
memcpy(record.major, major, 100);
record.phoneNumber = phoneNumber;
bucket.record[bucket.recordCnt] = record;
bucket.recordCnt++;
/* 바뀐 내용 disk에 쓰기 */
fseek(g_pHashStream, PAGE_SIZE * bucketNum, SEEK_SET);
fwrite(&bucket, sizeof(struct Bucket), 1, g_pHashStream);
/* block manager update */
blockManager.blockTable[bucketNum] = 1;

printf("( 이름: %s , 주소: %s , 전공: %s , 전화번호: %d) inserted.!\n",name , address , major, phoneNumber);

}
else
{ /* bucket에 여유 공간이 없으면 split */
while (1)
{
/* directory를 확장해야 하는지 check */
if (directory->header < (bucket.header + 1))
{
/* ----------------------------------------
 directory 확장
---------------------------------------- */
if (directory->header >= MAX_D)
{ /* 이미 full인지 check */
printf("Error. reached the maximum entry.\n");
return 0;
}
/* 새 directory 만들어 카피 */
newDirectory = (struct Directory*)malloc(sizeof(struct Directory));
memset(newDirectory, 0, sizeof(struct Directory));
newDirectory->header = directory->header + 1;
for (i = 0; i < 512; ++i)
{
newDirectory->table[i][0] = -1;
newDirectory->table[i][1] = -1;
newDirectory->table[i][2] = 0;
}
for (i = 0; i < POW(2, newDirectory->header); ++i)
{
newDirectory->table[i][0] = i;
newDirectory->table[i][1] = directory->table[i / 2][1];
newDirectory->table[i][2] = directory->table[i / 2][2];
}
free(directory);
directory = newDirectory;
printf("directory가 두배로 늘어났습니다!");
}
/* ----------------------------------------
 overflow가 발생한 bucket을 split
---------------------------------------- */
/* 새로운 bucket 생성 */
memset(&newBucket, 0, sizeof(struct Bucket));
newBucket.header = bucket.header;
newBucket.recordCnt = 0;
/* record를 두 bucket에 분배 */
bucket.recordCnt = 0;
for (i = 0; i < 3; ++i)
{
if (PseudoKeyFunc(bucket.record[i].key, bucket.header + 1) % 2 == 0)
{ /* 첫번째 bucket */
bucket.record[bucket.recordCnt] = bucket.record[i];
bucket.recordCnt++;
}
else
{ /* 두번째 bucket*/
newBucket.record[newBucket.recordCnt] = bucket.record[i];
newBucket.recordCnt++;
}
}
bucket.header++;
newBucket.header++;
printf("버켓이 split 되었습니다! ");
/* disk에 free block이 있는지 확인 */
temp = -1;
for (i = 0; i < blockManager.blockCnt; ++i)
{
if (blockManager.blockTable[i] == 0) /* free block*/
{
temp = i;
break;
}
}
if (temp != -1)
{ /* free block 존재 - 해당 block에 write */
}
else
{ /* 새로운 block 할당 */
temp = blockManager.blockCnt;
blockManager.blockCnt++;
}
/* 해당 free block에 할당 */
fseek(g_pHashStream, PAGE_SIZE * temp, SEEK_SET);
fwrite(&newBucket, sizeof(struct Bucket), 1, g_pHashStream);
blockManager.blockTable[temp] = 1;
fseek(g_pHashStream, PAGE_SIZE * bucketNum, SEEK_SET);
fwrite(&bucket, sizeof(struct Bucket), 1, g_pHashStream);
/* directory의 bucket index 변경 */
j = POW(2, directory->header - bucket.header + 1);
k = PseudoKeyFunc(key, bucket.header - 1) * j; /* directory의 첫번째 바뀔 부분 index*/
for (i = 0; i < j / 2; i++, k++)
{
directory->table[k][1] = bucketNum;
directory->table[k][2] = bucket.header;
}
for (i = 0; i < j / 2; i++, k++)
{
directory->table[k][1] = temp;
directory->table[k][2] = newBucket.header;
}
/* 입력받은 key 삽입 */
pseudo_key = PseudoKeyFunc(key, directory->header);
bucketNum = directory->table[pseudo_key][1];
/* 해당 bucket 위치 찾아 읽기 */
fseek(g_pHashStream, PAGE_SIZE * bucketNum, SEEK_SET);
j = fread(&bucket, sizeof(struct Bucket), 1, g_pHashStream);
if (j == 0)
{ /* bucket 존재하지 않음 */
printf("Error occurred while reading hash file.\n");
return -1;
}
/* ----------------------------------------
 여유 공간이 있으면 삽입
---------------------------------------- */
/* 여유 공간이 있는지 확인 */
if (bucket.recordCnt < 3)
{ /* 여유 공간이 있으면 삽입 */
record.key = key;
memcpy(record.name, name, 120); //record.name = name;
memcpy(record.address, address, 150);
memcpy(record.major, major, 100);
record.phoneNumber = phoneNumber;
bucket.record[bucket.recordCnt] = record;
bucket.recordCnt++;
/* 바뀐 내용 disk에 쓰기 */
fseek(g_pHashStream, PAGE_SIZE * bucketNum, SEEK_SET);
fwrite(&bucket, sizeof(struct Bucket), 1, g_pHashStream);
/* block manager update */
blockManager.blockTable[bucketNum] = 1;

printf("(이름: %s , 주소: %s , 전공: %s , 전화번호: %d) inserted!.\n", name, address, major, phoneNumber);

return 0;
}
/* 여유 공간이 없는 경우 계속 loop을 돌며 directory 확장 */
}
}
}
else
{
printf("Error occurred while inserting.\n");
return -1;
}
return 0;
}// 삭제 함수
int Delete(char name[150])
{int key = nameToKey(name);
int i, j, k, temp;
int b1, b2, cnt;
int pseudo_key = 0;  /* 삭제될 key의 pseudo key*/
int bucketNum = -1;  /* bucket의 number */
struct Bucket bucket, buddyBucket; /* disk에서 bucket과 buddy bucket을 가져올 struct */
struct Directory* newDirectory;
/* pseudo_key를 얻어 directory 참조 */
pseudo_key = PseudoKeyFunc(key, directory->header);
bucketNum = directory->table[pseudo_key][1];
/* 얻어온 bucket number를 통해 disk access */
if (bucketNum >= 0)
{
/* 해당 bucket 위치 찾아 읽기 */
fseek(g_pHashStream, PAGE_SIZE * bucketNum, SEEK_SET);
j = fread(&bucket, sizeof(struct Bucket), 1, g_pHashStream);
if (j == 0)
{ /* bucket 존재하지 않음 */
printf("Error occurred while reading hash file.\n");
return -1;
}
/* 해당 key가 존재하는지 확인 */
temp = -1;
if (bucket.recordCnt > 0)
{
for (i = 0; i < bucket.recordCnt; ++i)
{
if (bucket.record[i].key == key)
{ /* 해당 key 존재 */
temp = i;
break;
}
}
if (temp == -1)
{ /* 해당 이름이 없음 */
printf("Delete failed. name (%s) does not exist.\n", name);
return 0;
}
}
else
{ /* 해당 bucket에 record 없음 */
printf("Delete failed. name (%s) does not exist.\n", name);
return 0;
}
/* Bucket에서 key 삭제. bucket 정렬 */

printf("(%s) deleted!\n", bucket.record[temp].name);

for (i = temp; i < bucket.recordCnt - 1; ++i)
{
bucket.record[i] = bucket.record[i + 1];
}
bucket.recordCnt--;
/* disk에 쓰기 */
fseek(g_pHashStream, PAGE_SIZE * bucketNum, SEEK_SET);
fwrite(&bucket, sizeof(struct Bucket), 1, g_pHashStream);
/* bucket이 비거나 merge 가능하면 buddy bucket을 찾아 계속해서 merge */
while (bucket.header >= 2)
{
/* buddy bucket 찾기 */
b1 = PseudoKeyFunc(key, bucket.header - 1);
b2 = PseudoKeyFunc(key, bucket.header);
cnt = POW(2, directory->header - bucket.header); /* 연관된 leaf의 개수 */
k = (b2 + (b1 * 2 == b2 ? 1 : -1)) * cnt;  /* 연관된 leaf 중 첫번째 leaf index */
temp = directory->table[k][1];
if (temp < 0)
{
return 0;
}
/* disk에서 buddy bucket 읽어 오기 */
memset(&buddyBucket, 0, sizeof(struct Bucket));
fseek(g_pHashStream, PAGE_SIZE * temp, SEEK_SET);
j = fread(&buddyBucket, sizeof(struct Bucket), 1, g_pHashStream);
if (j == 0)
{ /* bucket 존재하지 않음 */
printf("Error occurred while reading hash file.\n");
return -1;
}
/* merge 해야 하는지 check */
if ((bucket.header != buddyBucket.header) ||
(bucket.recordCnt + buddyBucket.recordCnt > 4))
{ /* merge될 필요 없음 */
break;
}
/* ----------------------------------------
  merge
 ---------------------------------------- */
 /* buddyBucket에서 bucket으로 record copy */
for (i = 0; i < buddyBucket.recordCnt; ++i)
{
bucket.record[bucket.recordCnt] = buddyBucket.record[i];
bucket.recordCnt++;
}
bucket.header--;
fseek(g_pHashStream, PAGE_SIZE * bucketNum, SEEK_SET);
fwrite(&bucket, sizeof(struct Bucket), 1, g_pHashStream);
/* directory에서 leaf 조정 */
directory->table[pseudo_key][2] = bucket.header;
for (i = 0; i < cnt; ++i)
{ /* buddy 변경 */
directory->table[k + i][1] = bucketNum;
directory->table[k + i][2] = bucket.header;
}
/* buddyBucket 제거 */
/*blockManager.blockCnt--;*/
blockManager.blockTable[temp] = 0; /* free blcok으로 set */
memset(&buddyBucket, 0, sizeof(struct Bucket));
fseek(g_pHashStream, PAGE_SIZE * temp, SEEK_SET);
fwrite(&buddyBucket, sizeof(struct Bucket), 1, g_pHashStream);
/* directory가 줄어들 수 있는지 확인 */
j = 0;
for (i = 0; i < POW(2, directory->header); ++i)
{
if (directory->table[i][2] >= directory->header)
{
j = 1;
break;
}
}
if (j == 0)
{ /* bucket의 모든 header 값이 directory header 값보다 작은 경우 */
 /* ----------------------------------------
  directory 축소
 ---------------------------------------- */
newDirectory = (struct Directory*)malloc(sizeof(struct Directory));
memset(newDirectory, 0, sizeof(struct Directory));
newDirectory->header = directory->header - 1;
for (i = 0; i < 512; ++i)
{
newDirectory->table[i][0] = -1;
newDirectory->table[i][1] = -1;
newDirectory->table[i][2] = 0;
}
for (i = 0; i < POW(2, newDirectory->header); ++i)
{
newDirectory->table[i][0] = i;
newDirectory->table[i][1] = directory->table[i * 2][1];
newDirectory->table[i][2] = directory->table[i * 2][2];
}
free(directory);
directory = newDirectory;
}
}
}
else
{
printf("Error occurred while deleting.\n");
return -1;
}
return 0;
}//검색 함수
int Retrieve(char name[150])
{int key = nameToKey(name);
int i, j, temp;
int pseudo_key = 0;  /* 삭제될 key의 pseudo key*/
int bucketNum = -1;  /* bucket의 number */
struct Bucket bucket; /* disk에서 bucket을 가져올 struct */
/* pseudo_key를 얻어 directory 참조 */
pseudo_key = PseudoKeyFunc(key, directory->header);
bucketNum = directory->table[pseudo_key][1];
/* 얻어온 bucket number를 통해 disk access */
if (bucketNum >= 0)
{
/* 해당 bucket 위치 찾아 읽기 */
fseek(g_pHashStream, PAGE_SIZE * bucketNum, SEEK_SET);
j = fread(&bucket, sizeof(struct Bucket), 1, g_pHashStream);
if (j == 0)
{ /* bucket 존재하지 않음 */
printf("Error occurred while reading hash file.\n");
return -1;
}
/* 해당 key가 존재하는지 확인 */
temp = -1;
if (bucket.recordCnt > 0)
{
for (i = 0; i < bucket.recordCnt; ++i)
{
if (bucket.record[i].key == key)
{ /* 해당 key 존재 */
temp = i;
printf("(이름: %s , 주소: %s , 전공: %s , 전화번호: %d) found\n", bucket.record[temp].name , bucket.record[temp].address , bucket.record[temp].major , bucket.record[temp].phoneNumber);
break;
}
}
if (temp == -1)
{ /* 해당 key 없음 */
printf("Search failed. Name (%s) was not found.\n", name);
return 0;
}
}
else
{ /* 해당 bucket에 record 없음 */
printf("Search failed. Key (%s) was not found.\n", name);
return 0;
}
}
else
{
printf("Error occurred while searching.\n");
return -1;
}
return 0;
}// 해쉬 출력 함수
void PrintHash()
{int i, j;
int prevBucket = -1;
struct Bucket bucket;
char bitStr[10];
printf("======================================================================\n");
printf("Directory (%d)         Hash State \n", directory->header);
printf("======================================================================\n");
for (i = 0; i < POW(2, directory->header); ++i)
{
/* ----------------------------------------
 bit string 생성
---------------------------------------- */
for (j = 0; j < directory->header; ++j)
{
bitStr[j] = (directory->table[i][0] & POW(2, directory->header - j - 1)) > 0 ? '1' : '0';
}
bitStr[directory->header] = '\0';
/* ----------------------------------------
 directory 내용 출력
---------------------------------------- */
printf("[%s] [B: %d]", bitStr, directory->table[i][1]);
if (directory->table[i][1] != prevBucket)
{
prevBucket = directory->table[i][1];
/* ----------------------------------------
 해당 bucket 내용 출력
---------------------------------------- */
fseek(g_pHashStream, PAGE_SIZE * prevBucket, SEEK_SET);
j = fread(&bucket, sizeof(struct Bucket), 1, g_pHashStream);
if (j == 0)
{ /* bucket 존재하지 않음 */
printf("Error occurred while reading hash file.\n");
return;
}
printf("\t[B: %d](%d)  ", prevBucket, bucket.header);
for (j = 0; j < bucket.recordCnt; ++j)
{
printf("(키 : %d 이름: %s , 주소: %s , 전공: %s , 전화번호: %d) found\n", bucket.record[j].key,  bucket.record[j].name, bucket.record[j].address, bucket.record[j].major, bucket.record[j].phoneNumber);
}
}
printf("\n");
}
printf("\n");
}int main(int argc, char* argv[])
{int i, key;
char c;
char name[120];
char address[150];
char major[100];
int phoneNumber;
struct Bucket bucket;
/* -------------------------------------
Directory 초기화
   ------------------------------------- */
directory = (struct Directory*)malloc(sizeof(struct Directory));
memset(directory, 0, sizeof(struct Directory));
directory->header = 0;
for (i = 0; i < 512; ++i)
{
directory->table[i][0] = -1;
directory->table[i][1] = -1;
directory->table[i][2] = 0;
}
/* directory에 초기 table 생성 */
directory->header = 2;
for (i = 0; i < 4; ++i)
{
directory->table[i][0] = i; /*bit string */
directory->table[i][1] = 0;  /* bucket number는 0 */
directory->table[i][1] = 0;
}
/* -------------------------------------
 Block manager 초기화
------------------------------------- */
blockManager.blockCnt = 0;
for (i = 0; i < 512; ++i)
{
blockManager.blockTable[i] = 0;
}
/* -------------------------------------
 File 열기
------------------------------------- */
/* input.txt 파일 열기 */
if ((g_pInputStream = fopen("C:\\Users\\김환석\\Desktop\\임시파일\\input.txt", "r+")) == NULL)
{
// input 파일을 열 수 없음
printf("input.txt file cannot be opened!\n");
return -1;
}
else {
printf("input.txt file is opened!!!\n");
}
/* hash.txt 파일 열기 */
if ((g_pHashStream = fopen("C:\\Users\\김환석\\Desktop\\임시파일\\hash.txt", "w+")) == NULL) /* overwrite */
{
/* hash 파일을 열 수 없음 */
printf("hash.txt file cannot be opened!\n");
return -1;
}
else {
printf("hash.txt file is opened!!!\n");
}
/* 초기 bucket 생성 */
blockManager.blockCnt = 4;
memset(&bucket, 0, sizeof(struct Bucket));
bucket.header = 0;
bucket.recordCnt = 0;
for (i = 0; i < 4; ++i)
{
fwrite(&bucket, sizeof(struct Bucket), 1, g_pHashStream);
}
/* -------------------------------------
 input file을 읽어 명령 수행
------------------------------------- */
printf("[Extendible Hashing] Started\n\n");
while (1)
{
if (fscanf(g_pInputStream, "%c", &c) == EOF)
{ /* EOF에 도달 */
break;
}
switch (c)
{
case 'I':
case 'i': /* insert */
if (fscanf(g_pInputStream, "%s %s %s %d", name , address , major , &phoneNumber) == EOF)
{
printf("Error occurred. Input file corrupted.\n");
return -1;
}
if (Insert(name , address , major , phoneNumber) == 0)
{
PrintHash();
}
break;
case 'D':
case 'd': /* delete */
if (fscanf(g_pInputStream, "%s", name) == EOF)
{
printf("Error occurred. Input file corrupted.\n");
return -1;
}
if (Delete(name) == 0)
{
PrintHash();
}
break;
case 'R':
case 'r': /* retrieve */
if (fscanf(g_pInputStream, "%s", name) == EOF)
{
printf("Error occurred. Input file corrupted.\n");
return -1;
}
if (Retrieve(name) == 0)
{
PrintHash();
}
break;
default:
break;
}
}
/* -------------------------------------
 종료
------------------------------------- */
fclose(g_pInputStream);
fclose(g_pHashStream);
printf("\n[Extendible Hashing] Ended\n\n");
return 0;
}
