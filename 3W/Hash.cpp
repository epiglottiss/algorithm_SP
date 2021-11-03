#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

#define DATA_RANGE 200 //0~200������ �������� ������ ����
#define DATA_SIZE 100 //100���� ������ ����

class Hash {
	int divisor;
	int data[DATA_SIZE];
	int* table;
public:
	Hash(int div) {
		divisor = div;
		table = new int[div] {0, };
	}

	~Hash() { delete(table); }

private:
	/*
	* �ʱ� ������ ����, 0~200���� ���� ����
	*/
	void InitData() {
		srand((unsigned int)time(NULL));
		for (int i = 0; i < DATA_SIZE; i++)
		{
			data[i] = rand() % DATA_RANGE;
		}
	}
	/*
	* �ؽ� ���̺� �ʱⰪ 0
	*/
	void InitTable() {
		for (int i = 0; i < divisor; i++)
		{
			table[i] = 0;
		}
	}
	/*
	* �ؽ� ���̺� �Է�
	*/
	void Hashing() {
		for (int i = 0; i < DATA_SIZE; i++)
		{
			int index = data[i] % divisor;
			table[index] += 1;
		}
	}

	/*
	* Load Factor ���
	* table�� index�� �ϳ� �̻� ������ +1
	*/
	double GetLoadFactor() {
		int filled = 0;
		for (int i = 0; i < divisor; i++)
		{
			filled += table[i] > 0 ? 1 : 0;
		}
		return (double) filled / divisor;
	}

public:
	/*
	* ���� ������ �����Ͽ�
	*/
	double GetRandomLoadFactor() {
		InitData();
		InitTable();
		Hashing();
		return GetLoadFactor();
	}

	/*
	* ������ �� ���� �ٲ�
	*/
	void SetDivisor(int div) {
		delete(table);
		divisor = div;
		table = table = new int[div] {0, };
	}

	int GetDivisor() { return divisor; }
};

Hash hash(20);

void PrintResult(int repeat) {
	for (int i = 0; i < repeat; i++)
	{
		printf("[Hash Table] divisor = %d,  Load Factor = %.2lf\n", hash.GetDivisor(), hash.GetRandomLoadFactor());
		Sleep(1000);
	}
	printf("\n");
}

int main() {
	printf("[Direct Access Table] Load Factor = %.1f\n", (double) DATA_SIZE / DATA_RANGE);

	PrintResult(5);
	hash.SetDivisor(47);
	PrintResult(5);
	hash.SetDivisor(64);
	PrintResult(5);
	hash.SetDivisor(71);
	PrintResult(5);
	hash.SetDivisor(97);
	PrintResult(5);
	hash.SetDivisor(199);
	PrintResult(5);
	return 0;
}
