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
	char source[SRC_SIZE+1];	//패턴을 찾을 전체 문자열
	char pattern[PTN_SIZE+1]; //찾을 패턴인 문자열
	std::vector<int> patternLocation;	//패턴의 시작 위치를 담음
	int seedNumber;		//이 숫자로 다항식 계산
	long long patternKey;		//pattern의 해시값 계산
	std::vector<int> patternLocation_NoKR;	//문자열을 직접 비교해서 찾는 알고리즘의 경우 패턴을 담음
public:
	/*
	* 임의의 문자열과 패턴문자열 생성
	* 패턴 발견 횟수를 늘리기 위해 알파벳 5개로 한정
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
	* karpRabin 알고리즘으로 패턴 찾기 시작
	* 1. 패턴문자열의 값을 계산
	* 2. 전체 문자열의 첫 값을 계산
	* 3. 1과 2를 비교하여 결과 저장
	* 4. 전체 문자열에서 skip과 append를 반복하여 패턴 찾기
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
	* 결과 출력
	* karp Rabin 알고리즘 말고 직접 하나씩 비교했을 때의 결과와 다르면 출력하지 않는다.
	* 패턴이 발견된 index와 해당 index에서 패턴을 출력하여 실제로 패턴이 일치하는지 확인
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
	* 맨 뒤의 문자열을 입력받아 hash 값 계산
	*/
	void Append(long long& current, char c) {
		current = current * seedNumber + (long long)(c - 'a');
	}
	/*
	* 첫 문자열을 제거하여 hash값 계산
	*/
	void Skip(long long& current, char c) {
		current = current - (long long)(c - 'a') * (long long)pow(seedNumber, PTN_SIZE - 1);
	}
	/*
	* Karp Rabin 알고리즘 말고 직접 하나씩 비교했을 때의 결과 찾기
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
	* Karp Rabin 알고리즘과 직접 찾는 알고리즘을 비교하여 패턴 발견 위치가 다르면 false 반환
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