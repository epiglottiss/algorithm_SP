#include <iostream>
#include <chrono>
#include <algorithm>

#define MAXNUM 10000001

using namespace std;
using namespace chrono;

int ascendingArr[MAXNUM];
int descendingArr[MAXNUM];
int randomArr[MAXNUM];

int resultArr[MAXNUM];	//매번 정렬한 결과 담는 배열
int temp[MAXNUM];		//mergeSort용 임시 배열
typedef void(*Sort)(int*);	//정렬 함수 포인터

/*
* 3개 배열 초기화
* random배열은 짝수 index일 때 ascendingArr와 같고, 홀수 index일 때 descendingArr와 같음
*/
void InitArrs() {
	for (int i = 1; i < MAXNUM; i++)
	{
		ascendingArr[i] = i;
		descendingArr[i] = MAXNUM - i;
		if (i & 0) 
			randomArr[i] = ascendingArr[i];
		else
			randomArr[i] = descendingArr[i];
	}
}

/*
* 정렬 결과 확인
* 모든 정렬 결과는 오름차순 정렬
*/
bool CheckSortResult() {
	bool ret = true;
	for (int i = 1; i < MAXNUM; i++)
	{
		if (resultArr[i] != i) {
			ret = false;
			break;
		}
	}
	return ret;
}

/*
* 정렬 시간 계산 함수
* sort 시작 전과 후의 time point값의 차로 계산
* 정렬이 안되어 있으면 -1 반환
*/
long long GetSortTime(int* arr, Sort sort) {
	system_clock::time_point tp = system_clock::now();
	sort(arr);
	if (CheckSortResult() == false) {
		return -1;
	}
	milliseconds ms = duration_cast<chrono::milliseconds>(system_clock::now()-tp);
	return ms.count();
}

void InsertionSort(int* arr) {
	int num,i,j;
	memcpy(resultArr, arr, MAXNUM*sizeof(int));	
	for (i = 2; i < MAXNUM; i++)
	{
		num = resultArr[i];
		for (j = i - 1;j >= 1 && num < resultArr[j];j--) {
			resultArr[j + 1] = resultArr[j];
		}
		resultArr[j+1] = num;
	}
}

void MergeSortUtil(int* arr, int left, int right){
	if (left == right) return;
	int mid = (left + right) / 2;
	MergeSortUtil(arr, left, mid);
	MergeSortUtil(arr, mid + 1, right);

	int k = left;
	int L = left;
	int R = mid+1;
	while (L <= mid && R <= right) {
		temp[k++] = arr[L] <= arr[R] ? arr[L++] : arr[R++];
	}
	if (L > mid) {
		for (int i = R; i <= right; i++)
		{
			temp[k++] = arr[i];
		}
	}
	else {
		for (int i = L; i <= mid; i++)
		{
			temp[k++] = arr[i];

		}
	}
	for (int i = left; i <= right; i++)
	{
		arr[i] = temp[i];
	}

}
void MergeSort(int* arr) {
	memcpy(resultArr, arr, MAXNUM * sizeof(int));
	MergeSortUtil(resultArr, 1, MAXNUM-1 );
}

void QuickSortUtil(int* arr, int left, int right) {
	int i = left, j = right;
	int pivot = arr[(left + right) / 2];
	int temp;
	do
	{
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i <= j)
		{
			swap(arr[i], arr[j]);
			i++;
			j--;
		}
	} while (i <= j);

	if (left < j)
		QuickSortUtil(arr, left, j);

	if (i < right)
		QuickSortUtil(arr, i, right);
}
void QuickSort(int* arr) {
	memcpy(resultArr, arr, MAXNUM * sizeof(int));
	QuickSortUtil(resultArr, 1, MAXNUM - 1);
}



int main()
{
	InitArrs();
	cout << "[Ascending Array] Insertion Sort : " << GetSortTime(ascendingArr, InsertionSort) <<"ms"<< endl;
	cout << "[Ascending Array] Merge Sort : " << GetSortTime(ascendingArr, MergeSort) << "ms"<< endl;
	cout << "[Ascending Array] Quick Sort : " << GetSortTime(ascendingArr, QuickSort) << "ms" << endl;

	//cout << "[Descending Array] Insertion Sort : " << GetSortTime(descendingArr, InsertionSort) << "ms" << endl;
	cout << "[Descending Array] Merge Sort : " << GetSortTime(descendingArr, MergeSort) << "ms" << endl;
	cout << "[Descending Array] Quick Sort : " << GetSortTime(descendingArr, QuickSort) << "ms" << endl;
	
	//cout << "[Random Array] Insertion Sort : " << GetSortTime(randomArr, InsertionSort) << "ms" << endl;
	cout << "[Random Array] Merge Sort : " << GetSortTime(randomArr, MergeSort) << "ms" << endl;
	cout << "[Random Array] Quick Sort : " << GetSortTime(randomArr, QuickSort) << "ms" << endl;

}
