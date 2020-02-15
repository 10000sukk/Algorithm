#include <stdio.h>
#include <stdlib.h>
#define arrSize 10000
#define TRUE -1
#define FALSE -2
#define SWAP(a,b,c) c=a, a=b, b=c

int arr[arrSize+1];
void setarrRandom();
void checkarrSort();


void insertionSort();
int shiftVacOfInsertionSort(int xindex, int currentKey);

void QuickSort(int first, int last);
int partitionOfQuickSort(int first, int last);

void MergeSort(int first, int last);
void Merge(int first, int mid, int last_1);


typedef struct {
    int hArr[arrSize + 1];
    int hSize;
}Heap;
void arrToHeap(Heap* heap);
void pushHeap(Heap* heap, int key);
int popHeap(Heap* heap);
void heapSort(Heap* heap);

int main() {
    int i;
    int line = 2;
    
    
    setarrRandom();
    checkarrSort();
    printf("InsertionSort를 실행합니다\n");
    insertionSort();
    checkarrSort();
    printf("\n");

    
    setarrRandom();
    checkarrSort();
    printf("QuickSort를 실행합니다\n");
    QuickSort(0, arrSize);
    checkarrSort();
    printf("\n");

    setarrRandom();
    checkarrSort();
    printf("MergeSort를 실행합니다\n");
    MergeSort(0, arrSize - 1);
    checkarrSort();
    printf("\n");
    
    
    Heap heap;
    heap.hSize = 0;
    setarrRandom();
    arrToHeap(&heap);
    checkarrSort();
    printf("HeapSort를 실행합니다\n");
    heapSort(&heap);
    checkarrSort();
    printf("\n");

    return 0;
}

void setarrRandom() {
    int i;
    srand(time());
    printf("랜덤배열 생성중입니다\n");
    for (i = 0; i < arrSize; ++i) {
        arr[i] = rand();
    }
}
void checkarrSort() {
    int i;
    int ret = TRUE;
    printf("오름차순 정렬되었는지 확인중입니다\n");
    for (i = 0; i < arrSize - 1; ++i) {
        
        if (arr[i] > arr[i + 1]) {
            ret = FALSE;
            break;
        }
    }
    if (ret == TRUE)
        printf("complete\n");
    else
        printf("fail\n");
}


void insertionSort() {
    int xindex;
    for (xindex = 1; xindex < arrSize; ++xindex) {
        int currentKey = arr[xindex];
        int xLoc = shiftVacOfInsertionSort(xindex, currentKey);
        arr[xLoc] = currentKey;
    }
}
int shiftVacOfInsertionSort(int xindex, int currentKey) {
    int i;
    for (i = xindex; i > 0; i--) {
        
        if (arr[i - 1] > currentKey)
            arr[i] = arr[i - 1];
        else break;
    }
    
    return i;
}


void QuickSort(int first, int last) {
    if (first < last) {
        int splitPoint = partitionOfQuickSort(first, last);
        
        QuickSort(first, splitPoint - 1);
        QuickSort(splitPoint + 1, last);
    }
}
int partitionOfQuickSort(int first, int last) {
    int pivot, temp;
    int low, high;

    low = first;
    pivot = arr[low];
    high = last + 1;

    do {
        do {
            low++;
        } while (low <= last && arr[low] < pivot);
        do {
            high--;
        } while (high >= first && arr[high] > pivot);
        if (low < high) SWAP(arr[low], arr[high], temp);
    } while (low < high);
    SWAP(arr[first], arr[high], temp);
    return high;
}


void MergeSort(int first, int last_1) {
    if (first < last_1) {
        int mid = (first + last_1) / 2;
        MergeSort(first, mid);
        MergeSort(mid + 1, last_1);
        Merge(first, mid, last_1);
    }
}
void Merge(int first, int mid, int last_1) {
    int C[arrSize];
    int i = first;
    int j = mid + 1;
    int k = first;
    int l;

    while (i <= mid && j <= last_1) {
        if (arr[i] <= arr[j])
            C[k++] = arr[i++];
        else C[k++] = arr[j++];
    }

    if (i >= mid + 1)
        for (l = j; l <= last_1; l++)
            C[k++] = arr[l];
    else
        for (l = i; l <= mid; l++)
            C[k++] = arr[l];

    for (l = first; l <= last_1; l++)
        arr[l] = C[l];

    return;
}


void arrToHeap(Heap * heap) {
    int i = 0;
    for (i = 0; i < arrSize; i++)
        pushHeap(heap, arr[i]);
}
void pushHeap(Heap * heap, int key) {
    int i;
    i = ++(heap->hSize);

    while ((i != 1) && (key > heap->hArr[i / 2])) {
        heap->hArr[i] = heap->hArr[i / 2];
        i = i / 2;
    }
    heap->hArr[i] = key;
}
int popHeap(Heap * heap) {
    int parent, child;
    int key, temp;

    key = heap->hArr[1];
    temp = heap->hArr[heap->hSize--];
    parent = 1; child = 2;

    while (child <= heap->hSize) {
        
        if ((child < heap->hSize) && (heap->hArr[child] < heap->hArr[child + 1]))
            child++;

        
        if (temp >= heap->hArr[child])
            break;

        
        heap->hArr[parent] = heap->hArr[child];
        parent = child;
        child = parent * 2;
    }

    heap->hArr[parent] = temp;
    return key;

}
void heapSort(Heap* heap) {
    int i = arrSize;
    for (i = arrSize-1; i >= 0; i--) {
        arr[i] = popHeap(heap);
    }
}
