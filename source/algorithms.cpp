#include "algorithms.h"
#include "globals.h"
#include "visuals.h"
#include "helpers.h"

#include <math.h>


void swap(unsigned short index1, unsigned short index2)
{
	unsigned int temp = array[index1];
	array[index1] = array[index2];
	array[index2] = temp;
}

int partition(int p, int r) {
	unsigned int pivot = array[r];
	int i = p-1;
	for (int j = p; j < r; j++) {
		if (array[j] <= pivot) {
			i++;
			accessElement(j);
			ThreadSleep(delayMs);
			swap(j,i);
		}
	}
	i++;
	accessElement(r);
	ThreadSleep(delayMs);
	swap(r,i);
	return i;
}

void quickSort(int p, int r) {
	if (p < r) {
		int q = partition(p,r);
		quickSort(p,q-1);
		quickSort(q+1,r);	
	}
}

void quickSortInit(void *arg) {
	quickSort(0, arrayLen-1);
}

void insertionSort(void *arg)
{
	for (unsigned int i = 1; i < arrayLen; i++)
	{
		unsigned short j = i;
		while (j > 0 && array[j] < array[j - 1])
		{
			swap(j, j - 1);
			j--;
			accessElement(j);
			ThreadSleep(delayMs);
		}
	}
	doneSorting = true;
	finishSorting();
}

void maxHeapify(unsigned int i, unsigned int heapSize)
{
	unsigned int left = (2 * i) + 1;
	unsigned int right = (2 * i) + 2;

	accessElement(i);
	ThreadSleep(delayMs);

	unsigned int largest = i;
	if (left < heapSize && array[i] < array[left])
	{
		largest = left;
	}

	if (right < heapSize && array[largest] < array[right])
	{
		largest = right;
	}
	if (largest != i)
	{
		swap(i, largest);
		maxHeapify(largest, heapSize);
	}
}

void buildMaxHeap(unsigned int heapSize)
{
	for (int i = (int)(floor((double)heapSize / (double)2) + 1); i >= 0; i--)
	{
		printf("%i\n", i);
		maxHeapify(i, heapSize);
	}
}

void heapSort(void *arg)
{
	unsigned int heapSize = arrayLen;
	buildMaxHeap(heapSize);
	for (unsigned int i = arrayLen - 1; i > 0; i--)
	{
		accessElement(i);
		ThreadSleep(delayMs);

		swap(0, i);
		heapSize--;
		maxHeapify(0, heapSize);
	}

	doneSorting = true;
	finishSorting();
}

void merge(unsigned int p, unsigned int q, unsigned int r)
{
	// Make 2 new Arrays with 1 extra space for the sentinel cards
	// Sizes of both arrays
	unsigned int leftSize = (q - p + 1) + 1;
	unsigned int rightSize = (r - q) + 1;
	unsigned int *left = (unsigned int *)malloc(leftSize * sizeof(unsigned int));
	unsigned int *right = (unsigned int *)malloc(rightSize * sizeof(unsigned int));

	// Fill arrays with respective values
	for (unsigned short i = 0; i < leftSize; i++)
	{
		left[i] = array[p + i];
	}

	for (unsigned short i = 0; i < rightSize; i++)
	{
		right[i] = array[q + 1 + i];
	}

	// add sentinels
	left[leftSize - 1] = UINT8_MAX;
	right[rightSize - 1] = UINT8_MAX;

	unsigned short leftHead = 0;
	unsigned short rightHead = 0;
	for (unsigned short i = p; i <= r; i++)
	{
		accessElement(i);
		ThreadSleep(delayMs);
		if (left[leftHead] < right[rightHead])
		{
			array[i] = left[leftHead];
			leftHead++;
		}
		else
		{
			array[i] = right[rightHead];
			rightHead++;
		}
	}

	free(left);
	free(right);
}
void mergeSort(unsigned int p, unsigned int r)
{
	if (p < r)
	{
		unsigned int q = (p + r) / 2;
		mergeSort(p, q);
		mergeSort(q + 1, r);
		merge(p, q, r);
	}
}

void mergeSortInit(void *arg)
{
	mergeSort(0, arrayLen - 1);
	doneSorting = true;
	finishSorting();
}