// Target Project 
// Visual studio 2019
// Window SDK version : 10.0.18362.0

#include <stdio.h>
#include <vector>
#include <chrono>

#define RECURSIVE_LIMIT 40
#define MEMO_LIMIT 4004

typedef long long LL;

typedef LL (*Func)(int);

const int maxSize = 10004;
const int unknown = -1;
LL memo[maxSize];

LL  RecurseFibonacci(int n) {
	if (n < 2) return n;
	else return RecurseFibonacci(n - 1) + RecurseFibonacci(n - 2);
}

/*
* MeMoFibonacci���� ȣ��
*/
LL MemoFibonacciUtil(int n) {
	if (memo[n] != unknown) return memo[n];
	if (n < 2) return n;
	LL lResult = MemoFibonacciUtil(n - 1) + MemoFibonacciUtil(n - 2);
	memo[n] = lResult;
	return lResult;
}
/*
* memo ���� ���� �Ǻ���ġ ȣ�� �� memory set
*/
LL MemoFibonacci(int n) {
	memset(memo, unknown, maxSize);
	return MemoFibonacciUtil(n);
}

LL TableFibonacci(int n) {
	LL* table = (LL*)malloc((n+1)*sizeof(LL));
	table[0] = 0;
	table[1] = 1;
	for (int i = 2;i <= n;i++) {
		table[i] = table[i - 1] + table[i - 2];
	}
	LL iResult = table[n];
	free(table);
	return iResult;
}

/*
* function�� ���� �ð� ��� �Լ�, ������ microseconds
*/
LL  GetFuncRunTime(Func func, int n) {
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
	func(n);
	std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
	std::chrono::microseconds us = std::chrono::duration_cast<std::chrono::microseconds> (end - start);
	return us.count();
}

/*
* ������ ����� �ð� ��� ���
* recursive�� 40������(�ð��ʰ�)
* memoization�� 4000������(Stack Overflow)
*/
void PrintCompareResult(int num) {
	printf("[case f(%d)] ", num);

	if (num <= RECURSIVE_LIMIT) {
		LL recurseTime = GetFuncRunTime(RecurseFibonacci, num);
		printf("	recrsive:% lld us, ", recurseTime);
	}
	if (num < MEMO_LIMIT) {
		LL memoTime = GetFuncRunTime(MemoFibonacci, num);
		printf("	Memo : %lld us, ", memoTime);
	}
	LL talbeTime = GetFuncRunTime(TableFibonacci, num);
	printf("	Table : %lld us, \n", talbeTime);

}

/*
* fibonacci ��� ���� ���� �ٸ��� false ��ȯ
*/
bool UnitTest() {
	for (int i = 10; i < 20; i++)
	{
		LL rec = RecurseFibonacci(i);
		LL memo = MemoFibonacci(i);
		LL table = TableFibonacci(i);
		if (rec != memo || rec != table || memo != table) {
			return false;
		}
	}
	return true;
}

int main() {

	//fibonacci �Լ��� ����ؾ� ���ɰ��
	if (UnitTest()) {
		PrintCompareResult(1);
		PrintCompareResult(10);
		PrintCompareResult(20);
		PrintCompareResult(30);
		PrintCompareResult(40);
		PrintCompareResult(50);
		PrintCompareResult(100);
		PrintCompareResult(1000);
		PrintCompareResult(2000);
		PrintCompareResult(3000);
		PrintCompareResult(4000);
		PrintCompareResult(5000);
		PrintCompareResult(7500);
		PrintCompareResult(10000);
	}
	else {
		printf("Fibonacci Function failure\n");
	}


	return 0;
}