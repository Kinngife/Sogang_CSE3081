#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <ctime>
using namespace std;
void insertionsort(vector<int> &arr, int left, int right);
int partition(vector<int> &arr, int left, int right);
void quicksort(vector<int> &arr, int left, int right);
void merge(vector<int> &arr, int left, int mid, int right);
void mergesort(vector<int> &arr, int left, int right);
void mysort(vector<int> &arr, int left, int right);

int main(int argc, char **argv)
{
	char *infile = argv[1];
	char *index = argv[2];
	FILE *input = fopen(infile, "r");
	if (input == NULL)
		return 0;

	clock_t start = clock();

	int N;
	fscanf(input, "%d", &N);
	vector<int> arr(N);
	for (int i = 0; i < N; i++)
		fscanf(input, "%d", &arr[i]);

	// 1. insertion sort
	if (!strcmp(index, "1"))
		insertionsort(arr, 0, N - 1);

	// 2. quick sort
	else if (!strcmp(index, "2"))
		quicksort(arr, 0, N - 1);

	// 3. merge sort
	else if (!strcmp(index, "3"))
		mergesort(arr, 0, N - 1);

	// 4. my sort
	else if (!strcmp(index, "4"))
		mysort(arr, 0, N - 1);

	clock_t end = clock();
	double time = end - start;

	char outfile[22] = "result_";
	strcat(outfile, index);
	strcat(outfile, "_");
	strcat(outfile, infile);
	FILE *result = fopen(outfile, "w");

	fprintf(result, "%s\n", infile);
	fprintf(result, "%s\n", index);
	fprintf(result, "%d\n%.6f\n", N, time / CLOCKS_PER_SEC);
	for (int i = 0; i < N; i++)
		fprintf(result, "%d ", arr[i]);
	fprintf(result, "\n");
	fclose(input);
	fclose(result);
	return 0;
}

// 1. insertion sort
void insertionsort(vector<int> &arr, int left, int right)
{
	for (int i = left + 1; i <= right; i++)
	{
		int key = arr[i];
		int idx = i - 1;
		while (0 <= idx && key < arr[idx])
		{
			arr[idx + 1] = arr[idx];
			idx--;
		}
		arr[idx + 1] = key;
	}
}

// 2. quick sort
int partition(vector<int> &arr, int left, int right)
{
	int pivot = arr[right];
	int idx = left - 1;
	for (int i = left; i < right; i++)
	{
		if (arr[i] <= pivot)
		{
			idx++;
			swap(arr[idx], arr[i]);
		}
	}
	swap(arr[idx + 1], arr[right]);
	return idx + 1;
}
void quicksort(vector<int> &arr, int left, int right)
{
	if (left >= right)
		return;

	int mid = partition(arr, left, right);
	quicksort(arr, left, mid - 1);
	quicksort(arr, mid + 1, right);
}

// 3. merge sort
void merge(vector<int> &arr, int left, int mid, int right)
{
	int leftlen = mid - left + 1;
	int rightlen = right - mid;
	vector<int> L(leftlen);
	vector<int> R(rightlen);

	for (int i = 0; i < leftlen; i++)
		L[i] = arr[i + left];
	for (int i = 0; i < rightlen; i++)
		R[i] = arr[i + mid + 1];

	int i = 0, j = 0, k = left;
	while (i < leftlen && j < rightlen)
	{
		if (L[i] <= R[j])
			arr[k++] = L[i++];
		else
			arr[k++] = R[j++];
	}
	while (i < leftlen)
		arr[k++] = L[i++];
	while (j < rightlen)
		arr[k++] = R[j++];
}
void mergesort(vector<int> &arr, int left, int right)
{
	if (left >= right)
		return;

	int mid = (left + right) / 2;
	mergesort(arr, left, mid);
	mergesort(arr, mid + 1, right);
	merge(arr, left, mid, right);
}

// 4. my sort
void mysort(vector<int> &arr, int left, int right)
{
	if (left >= right)
		return;

	if (right - left + 1 <= 100)
	{
		insertionsort(arr, left, right);
		return;
	}

	int mid = (left + right) / 2;
	if (arr[left] > arr[mid])
		swap(arr[left], arr[mid]);
	if (arr[mid] > arr[right])
		swap(arr[mid], arr[right]);
	if (arr[left] > arr[mid])
		swap(arr[left], arr[mid]);
	swap(arr[mid], arr[right]);

	int mymid = partition(arr, left, right);
	mysort(arr, left, mymid - 1);
	mysort(arr, mymid + 1, right);
}