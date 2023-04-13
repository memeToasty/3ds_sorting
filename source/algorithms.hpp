#ifndef ALGORITHMS_H
#define ALGORITHMS_H
void swap(unsigned short index1, unsigned short index2);


// Quick sort
int partition(int p, int r);
void quickSort(int p, int r);
void quickSortInit(void *arg);

// Insertion sort
void insertionSort(void *arg);

// Heap sort
void maxHeapify(unsigned int i, unsigned int heapSize);
void buildMaxHeap(unsigned int heapSize);
void heapSort(void *arg);

// Merge sort
void merge(unsigned int p, unsigned int q, unsigned int r);
void mergeSort(unsigned int p, unsigned int r);
void mergeSortInit(void *arg);

// Bubble sort
void bubbleSort(void *arg);

// Selection sort
void selectionSort(void *arg);

#endif