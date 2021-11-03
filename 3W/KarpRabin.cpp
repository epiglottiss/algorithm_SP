#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <Windows.h>
#define SRC_SIZE 100
#define PTN_SIZE 2
#define TEST_CNT 100

class KarpRabin {
	char source[SRC_SIZE+1];	//������ ã�� ��ü ���ڿ�
	char pattern[PTN_SIZE+1]; //ã�� ������ ���ڿ�
	std::vector<int> patternLocation;	//������ ���� ��ġ�� ����
	int seedNumber;		//�� ���ڷ� ���׽� ���
	long long patternKey;		//pattern�� �ؽð� ���
	std::vector<int> patternLocation_NoKR;	//���ڿ��� ���� ���ؼ� ã�� �˰����� ��� ������ ����
public:
	/*
	* ������ ���ڿ��� ���Ϲ��ڿ� ����
	* ���� �߰� Ƚ���� �ø��� ���� ���ĺ� 5���� ����
	*/
	void InitString() {
		seedNumber = 256;
		srand((unsigned int)time(NULL));
		for (int i = 0; i < SRC_SIZE; i++)
		{
			source[i] = rand() %5 + 'a';
		}
		source[SRC_SIZE] = '\0';
		for (int i = 0; i < PTN_SIZE; i++)
		{
			pattern[i] = rand() % 5 + 'a';
		}
		pattern[PTN_SIZE] = '\0';

		patternLocation.clear();
	}
	/*
	* karpRabin �˰������� ���� ã�� ����
	* 1. ���Ϲ��ڿ��� ���� ���
	* 2. ��ü ���ڿ��� ù ���� ���
	* 3. 1�� 2�� ���Ͽ� ��� ����
	* 4. ��ü ���ڿ����� skip�� append�� �ݺ��Ͽ� ���� ã��
	*/
	void SearchPattern() {
		
		patternKey = 0;
		for (int i = 0; i < PTN_SIZE; i++)
		{
			Append(patternKey, pattern[i]);
		}

		long long keyInSrc = 0;
		for (int i = 0; i < PTN_SIZE; i++)
		{
			Append(keyInSrc, source[i]);
		}

		if (keyInSrc == patternKey) {
			patternLocation.push_back(0);
		}

		for (int i = 1; i <= SRC_SIZE-PTN_SIZE; i++)
		{
			Skip(keyInSrc, source[i - 1]);
			Append(keyInSrc, source[i + PTN_SIZE - 1]);
			if (keyInSrc == patternKey) {
				patternLocation.push_back(i);
			}
		}
		SearchPatern_NoKR();
	}

	/*
	* ��� ���
	* karp Rabin �˰��� ���� ���� �ϳ��� ������ ���� ����� �ٸ��� ������� �ʴ´�.
	* ������ �߰ߵ� index�� �ش� index���� ������ ����Ͽ� ������ ������ ��ġ�ϴ��� Ȯ��
	*/
	void PrintResult() {
		if (CompareVector() == false) {
			printf("Result is not correct\n");
			return;
		}
		printf("source is %s\n", source);
		printf("pattern is %s\n", pattern);
		printf("Total Pattern : %d\n", patternLocation.size());
		for (int location : patternLocation)
		{
			char patternInSrc[PTN_SIZE+1];
			strncpy(patternInSrc, source + location, PTN_SIZE);
			patternInSrc[PTN_SIZE] = '\0';
			printf("At %d : %s\n", location, patternInSrc);
		}
		printf("\n");
	}
private:
	/*
	* �� ���� ���ڿ��� �Է¹޾� hash �� ���
	*/
	void Append(long long& current, char c) {
		current = current * seedNumber + (long long)(c - 'a');
	}
	/*
	* ù ���ڿ��� �����Ͽ� hash�� ���
	*/
	void Skip(long long& current, char c) {
		current = current - (long long)(c - 'a') * (long long)pow(seedNumber, PTN_SIZE - 1);
	}
	/*
	* Karp Rabin �˰��� ���� ���� �ϳ��� ������ ���� ��� ã��
	*/
	void SearchPatern_NoKR() {
		patternLocation_NoKR.clear();
		for (int i = 0; i <= SRC_SIZE-PTN_SIZE; i++)
		{
			char ptn[PTN_SIZE+1];
			strncpy(ptn, source + i, PTN_SIZE);
			ptn[PTN_SIZE] = '\0';
			if (strcmp(ptn, pattern) == 0) {
				patternLocation_NoKR.push_back(i);
			}
		}
	}
	/*
	* Karp Rabin �˰���� ���� ã�� �˰����� ���Ͽ� ���� �߰� ��ġ�� �ٸ��� false ��ȯ
	*/
	bool CompareVector() {
		if (patternLocation.size() != patternLocation_NoKR.size())
			return false;

		for (int i = 0; i < patternLocation.size(); i++)
		{
			if (patternLocation[i] != patternLocation_NoKR[i])
				return false;
		}
		return true;
	}

};
int main() {
	KarpRabin kr;
	for (int i = 0; i < TEST_CNT; i++)
	{
		kr.InitString();
		kr.SearchPattern();
		kr.PrintResult();
		Sleep(1000);
	}
}