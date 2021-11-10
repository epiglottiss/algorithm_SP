// Target Project 
// Visual studio 2019
// Window SDK version : 10.0.18362.0

#include <stdio.h>
#include <vector>
#include <time.h>
#include <string>
#include <algorithm>
#include <Windows.h>
using namespace std;

#define MIN_ARR_SIZE 2 //����� ���ڿ��� �ּ� ����
#define MAX_ARR_SIZE 5	//����� ���ڿ��� �ִ� ����
#define CHAR_COUNT 3	//����� ���� ����, A~ count��ŭ
#define TEST_CASE 10

class Strings {
	int arrMemSizeCol;		//�迭�� ù index�� ��� ���̹Ƿ� memory size = arr size +1
	int arrMemSizeRow;	//�� ���� ũ�Ⱑ �ٸ� ��츸 ���
	vector<char> arrCol;	//memo�� column�� ��ġ�� �迭
	vector<char> arrRow;	//memo�� row�� ��ġ�� �迭
	vector<vector<int>> memo;
public:
	Strings() {
	}

	/*
	* ������ ���ڷ� ������ ũ�⸸ŭ�� �� �迭�� �������� ����
	* �� �迭�� ������� ���� ������ ��
	* �迭 ù �ε����� ������� ����
	*/
	void CreateRandomArrs() {
		srand((unsigned int)time(NULL));

		arrMemSizeCol = (rand() % MAX_ARR_SIZE);
		if (arrMemSizeCol < MIN_ARR_SIZE) {
			arrMemSizeCol += MIN_ARR_SIZE;
		}
		arrMemSizeCol += 1;	

		arrMemSizeRow = (rand() % MAX_ARR_SIZE);
		if (arrMemSizeRow < MIN_ARR_SIZE) {
			arrMemSizeRow += MIN_ARR_SIZE;
		}
		arrMemSizeRow += 1;
		ResizeArr(arrMemSizeCol, arrMemSizeRow);
		
		for (int i = 1; i < arrMemSizeCol; i++)
		{
			arrCol[i] = (rand() % CHAR_COUNT + 'A');
		}
		for (int i = 1; i < arrMemSizeRow; i++)
		{
			arrRow[i] = (rand() % CHAR_COUNT + 'A');
		}
	}

	/*
	* �Է��� ���ͷ� �迭 ����
	* �Է��� �迭���� ù �ε����� 'X'�� �Ͽ� ������� ����
	*/
	void CreateArr(vector<char>& arrCol, vector<char>& arrRow) {
		arrMemSizeCol = arrCol.size() + 1;
		arrMemSizeRow = arrRow.size() + 1;
		ResizeArr(arrMemSizeCol, arrMemSizeRow);
		this->arrCol = arrCol;
		this->arrRow = arrRow;

		this->arrCol.insert(this->arrCol.begin(), 'X');
		this->arrRow.insert(this->arrRow.begin(), 'X');
	}
	
	/*
	* LCS ã�� �˰��� ����
	* 1. column�� row�� 0��° index�� ��� 0���� ��
	* 2. bottum up���� lcs �˰������� memo ���
	* 3. memo�� �ֿ����ϴܿ������� memo�� ���� 0�̵� �� ���� ���ڿ� ã�� �˰��� ����
	* 4. ����� ���ڿ� reverse�Ͽ� ��ȯ
	*/
	string FindLCS() {
		string sResult;
		InitMemo();
		int rowSize = arrRow.size();
		int colSize = arrCol.size();
		for (int i = 1; i < rowSize; i++)
		{
			for (int j = 1; j < colSize; j++)
			{
				if (arrRow[i] == arrCol[j]) {
					memo[i][j] = memo[i - 1][j - 1] + 1;
				}
				else {
					memo[i][j] = max(memo[i - 1][j], memo[i][j - 1]);
				}
			}
		}

		int row = arrRow.size() -1;
		int col = arrCol.size()-1;
		while (true) {
			int num = memo[row][col];
			if (num == 0)
				break;
			if (memo[row][col - 1] == num && memo[row - 1][col] == num) {
				col--;
			}
			else if (memo[row][col - 1] == num) {
				col--;
			}
			else if (memo[row - 1][col] == num) {
				row--;
			}
			else {
				sResult += arrCol[col];
				row--;
				col--;
			}
		}
		reverse(sResult.begin(), sResult.end());
		return sResult;
	}

	/*
	* Edit Distance ����
	* 1. 0��° index�� �� �ʱ�ȭ
	* 2. bottum up���� edit Distance �˰��� ����
	* 3. memo�� �ֿ��� �ϴ� �� ��ȯ
	*/
	int FindEditDistance() {
		string sResult;

		int rowSize = arrRow.size();
		int colSize = arrCol.size();
		for (int i = 0; i < colSize; i++)
		{
			memo[0][i] = i;
		}
		for (int i = 0; i < rowSize; i++)
		{
			memo[i][0] = i;
		}
		for (int i = 1; i < rowSize; i++)
		{
			for (int j = 1; j < colSize; j++)
			{
				if (arrRow[i] == arrCol[j]) {
					memo[i][j] = memo[i - 1][j - 1];
				}
				else {
					memo[i][j] = min(memo[i - 1][j], min(memo[i][j - 1], memo[i-1][j-1]))+1 ;
				}
			}
		}

		return memo[rowSize-1][colSize-1];
	}

	/*
	* �� �迭 ���, 0��° index�� ������� ����
	*/
	void PrintArrs() {
		printf("Arr1 : ");
		for (int i = 1; i < arrCol.size(); i++)
		{
			printf("%c", arrCol[i]);
		}
		printf("\n");

		printf("Arr2 : ");
		for (int i = 1; i < arrRow.size(); i++)
		{
			printf("%c", arrRow[i]);
		}
		printf("\n");
	}

	void PrintMemo() {
		for (int i = 0; i < memo.size(); i++)
		{
			for (int j = 0; j < memo[0].size(); j++)
			{
				printf("%2d", memo[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}
private:
	/*
	* memo�� 0��° index ������ 0���� �ʱ�ȭ
	*/
	void InitMemo() {
		for (int i = 0; i < arrCol.size(); i++)
		{
			memo[0][i] = 0;
		}
		for (int i = 0; i < arrRow.size(); i++)
		{
			memo[i][0] = 0;
		}
	}

	/*
	* �� �迭 ũ�Ⱑ ���� ��� �� ũ��� �迭 �Ҵ�
	*/
	void ResizeArr(int size) {
		arrCol.resize(size);
		arrRow.resize(size);
		memo.resize(size);
		for (int i = 0; i < size; i++)
		{
			memo[i].resize(size);
		}
	}

	/*
	* �� �迭 ũ�Ⱑ �ٸ� ��� ���� �Է��Ͽ� �迭 �Ҵ�
	*/
	void ResizeArr(int colSize, int rowSize) {
		arrCol.resize(colSize);
		arrRow.resize(rowSize);
		memo.resize(rowSize);
		for (int i = 0; i < rowSize; i++)
		{
			memo[i].resize(colSize);
		}
	}

};

int main() {

	Strings strings;

#pragma region LCS TEST
	//���� �翬
	vector<char> vec1 = { 'A','B','C','B','D','A','B' };
	vector<char> vec2 = { 'B','D','C','A','B','A' };
	strings.CreateArr(vec1, vec2);
	strings.PrintArrs();
	printf("Longest Common Substring is %s\n", strings.FindLCS().c_str());
	strings.PrintMemo();

	//Test Case
	for (int i = 0; i < TEST_CASE; i++)
	{
		strings.CreateRandomArrs();
		strings.PrintArrs();
		printf("Longest Common Substring is %s\n\n", strings.FindLCS().c_str());
		Sleep(1000);
	}
#pragma endregion

	
#pragma region Edit Distance Test

	vec1 = { 'W','A','L','L','E','T' };
	vec2 = { 'W','A','L','N','U','T' };

	strings.CreateArr(vec1, vec2);
	strings.PrintArrs();
	printf("Edit Distance is %d\n\n", strings.FindEditDistance());
	strings.PrintMemo();

	for (int i = 0; i < TEST_CASE; i++)
	{
		strings.CreateRandomArrs();
		strings.PrintArrs();
		printf("Edit Distance is %d\n\n", strings.FindEditDistance());
		Sleep(1000);
	}
#pragma endregion

	

	return 0;
}