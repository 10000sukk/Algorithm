# include <stdio.h>
# define MAX_SIZE 100

void inc_insertion_sort(int list[], int first, int last, int gap){
  int i, j, key;
  for(i=first+gap; i<=last; i=i+gap){
    key = list[i];
    for(j=i-gap; j>=first && list[j]>key; j=j-gap){
      list[j+gap] = list[j]; // 레코드를 gap만큼 오른쪽으로 이동
    }
    list[j+gap] = key;
  }
}
void shell_sort(int list[], int n){
  int i, gap;
  for(gap=n/2; gap>0; gap=gap/2){
    if((gap%2) == 0)(
      gap++;
    )
 
    for(i=0; i<gap; i++){
      inc_insertion_sort(list, i, n-1, gap);
    }
  }
}void main(){
  int i;
  int n = MAX_SIZE;
  int list[n] = {10, 8, 6, 20, 4, 3, 22, 1, 0, 15, 16};
  shell_sort(list, n);
  for(i=0; i<n; i++){
    printf("%d\n", list[i]);
  }
}

seletion sort

>
#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <ctime>
#define MAXSIZE 1000
int A[MAXSIZE];


int Partition(int list[], int left, int right)
{
int pivot = list[left];
int i = left + 1, j = right;

while (i <= j) {
while (list[i] <= pivot && i <= right) i++;
while (list[j] >= pivot && j >= (left + 1)) j--;
if (i <= j) std::swap(list[i], list[j]);
}
std::swap(list[left], list[j]);
return j;
}


int Select(int list[], int left, int right, int k)
{
int nth = Partition(list, left, right);

if (nth == k) return list[nth];
else if (nth > k) Select(list, left, nth - 1, k);
else if (nth < k) Select(list, nth + 1, right, k);
}
