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

#define MIN_ARR_SIZE 2 //사용할 문자열의 최소 길이
#define MAX_ARR_SIZE 5	//사용할 문자열의 최대 길이
#define CHAR_COUNT 3	//사용할 문자 개수, A~ count만큼
#define TEST_CASE 10

class Strings {
	int arrMemSizeCol;		//배열에 첫 index는 비울 것이므로 memory size = arr size +1
	int arrMemSizeRow;	//두 수열 크기가 다른 경우만 사용
	vector<char> arrCol;	//memo의 column에 위치할 배열
	vector<char> arrRow;	//memo의 row에 위치할 배열
	vector<vector<int>> memo;
public:
	Strings() {
	}

	/*
	* 임의의 문자로 지정한 크기만큼의 두 배열을 무작위로 생성
	* 두 배열의 사이즈는 같은 것으로 함
	* 배열 첫 인덱스는 취급하지 않음
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
	* 입력한 벡터로 배열 생성
	* 입력한 배열에서 첫 인덱스는 'X'로 하여 취급하지 않음
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
	* LCS 찾는 알고리즘 구현
	* 1. column과 row의 0번째 index는 모두 0으로 함
	* 2. bottum up으로 lcs 알고리즘으로 memo 기록
	* 3. memo의 최우측하단에서부터 memo의 수가 0이될 때 까지 문자열 찾는 알고리즘 실행
	* 4. 기록한 문자열 reverse하여 반환
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
	* Edit Distance 구현
	* 1. 0번째 index의 값 초기화
	* 2. bottum up으로 edit Distance 알고리즘 적용
	* 3. memo의 최우측 하단 값 반환
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
	* 두 배열 출력, 0번째 index는 취급하지 않음
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
	* memo의 0번째 index 값들을 0으로 초기화
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
	* 두 배열 크기가 같을 경우 그 크기로 배열 할당
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
	* 두 배열 크기가 다를 경우 각각 입력하여 배열 할당
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
	//교재 재연
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