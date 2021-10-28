#define SIZE 100
#define TESTSIZE 21
#include<stdio.h>

class MaxHeap {
	int tree[SIZE];
	int size;
public:
	MaxHeap() {
		size = 0;
	}

	void Insert(int i) {
		int index = ++size;
		tree[index] = i;
		while (index != 1 && tree[index / 2] < i) {
			tree[index] = tree[index / 2];
			index /= 2;
		}
		tree[index] = i;
	}

	void Insert(int* arr, int arrSize) {
		for (int i = 0; i < arrSize; i++)
		{
			Insert(arr[i]);
		}
	}

	void Delete() {
		if (size <= 0) {
			printf("size is 0\n");
			return;
		}

		int index = 1;
		int child = 2;
		int lastNum = tree[size--];
		tree[index] = lastNum;

		while (index <= size && (tree[child] > lastNum || tree[child + 1] > lastNum)) {
			int larger;
			int newIndex;
			if (child > size) break;
			if (tree[child] > tree[child + 1]) {
				larger = tree[child];
				newIndex = index * 2;
			}
			else {
				larger = tree[child + 1];
				newIndex = index * 2 + 1;
			}
			tree[index] = larger;
			index = newIndex;
			child = index * 2;
		}
		tree[index] = lastNum;
	}

	int GetMaxNum() { return tree[1]; }

	int GetHeapSize() { return size; }

	void Print() {
		int index = 1;
		int count = 1;
		int height = 1;
		int num = size + 1;
		while (num > 1) {
			num /= 2;
			height++;
		}
		for (int i = 1; i <= height; i++)
		{
			for (int j = 0; j < count && index <= size; j++)
			{
				printf("%3d", tree[index++]);
			}
			count *= 2;
			printf("\n");
		}
	}
};

int main() {
	int arr[TESTSIZE];
	for (int i = 0; i < TESTSIZE; i++)
	{
		arr[i] = i;
	}
	MaxHeap maxHeap;
	maxHeap.Insert(arr, TESTSIZE);
	maxHeap.Print();
	printf("Max is %d\n\n", maxHeap.GetMaxNum());

	while (maxHeap.GetHeapSize() > 1) {
		maxHeap.Delete();
		maxHeap.Print();
		printf("Max is %d\n\n", maxHeap.GetMaxNum());
	}
	return 0;
}