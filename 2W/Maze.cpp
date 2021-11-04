#include<stdio.h>
#include <vector>
#include <queue>
#include <time.h>
using namespace std;
#define SIZE 1001
#define ROAD -1
#define WALL -2

const int direction[2][4] = { {0,1,0,-1},{1,0,-1,0} };

class Maze {
	int board[SIZE][SIZE];
	vector<vector<int>> matrix;
public:
	bool InitializeMaze() {
		//미로 사이즈는 홀수만 가능
		if (SIZE & 1) return false;
		bool ret = true;
		InitBoard();

	}

private:
	void InitBoard() {
		//짝수 인덱스는 모두 벽으로, 그외에는 길
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				if (i & 1 || j & 1) {
					board[i][j] = WALL;
				}
				else
					board[i][j] = ROAD;
			}
		}

		queue<pair<int, int>> nodeLocation;
		int nodeCount = 0;
		//1.홀수 인덱스에서 오른쪽 또는 아래로 길 생성
		//2. 미로에서 노드위치 찾는 역할
		srand((unsigned int)time(NULL));
		for (int i = 1; i < SIZE; i += 2)
		{
			for (int j = 1; j < SIZE; j += 2)
			{
				//마지막 인덱스에서는 정지
				if (i == SIZE - 2 && j == SIZE - 2) continue;
				//맨 아래줄에서는 오른쪽으로 길 만들기
				if (i == SIZE - 2) {
					board[i][j + 1] = ROAD;
					continue;
				}
				//맨 오른쪽줄에서는 아래로 길 만들기
				if (j == SIZE - 2) {
					board[i + 1][j] = ROAD;
					continue;
				}
				if (rand() & 0) {
					board[i][j + 1] = ROAD;
				}
				else {
					board[i + 1][j] = ROAD;
				}

				int nodeCheck[2] = { 0,0 };
				for (int k = 0; k < 4; k++)
				{
					int nextRow = i + direction[0][k];
					int nextCol = j + direction[1][k];
					if (board[nextRow][nextCol] = ROAD) {
						nodeCheck[k % 2] += 1;
					}
				}
				if ((nodeCheck[0] == 2 && nodeCheck[1] == 0) || 
					(nodeCheck[0] == 0 && nodeCheck[1] == 2)) {
					continue;
				}
				nodeLocation.push({ i,j });
				board[i][j] =  nodeCount++;
			}
		}

		//node 개수로 인접행렬 할당
		matrix.resize(nodeCount);
		for (int i = 0; i < nodeCount; i++)
		{
			matrix[i].resize(nodeCount);
		}

		//인접행렬 가중치 구하기
		while (!nodeLocation.empty()) {
			pair<int, int> location = nodeLocation.front();
			nodeLocation.pop();
			int curRow = location.first;
			int curCol = location.second;

			//오른쪽에 길이 있으면 오른쪽 Node까지 가중치 계산하여 인접행렬에 담음		
			int nextRow = location.first + 0;
			int nextCol = location.second + 1;
			if (board[nextRow][nextCol] == ROAD) {
				while (true) {
					if (board[nextRow][nextCol] != ROAD) break;
					nextCol++;
				}
				int curNode = board[curRow][curCol];
				int nextNode = board[nextRow][nextCol];
				int length = nextCol - curCol;
				matrix[curNode][nextNode] = length;
				matrix[nextNode][curNode] = length;
			}

			//위쪽에 길이 있으면 위쪽 Node까지 가중치 계산하여 인접행렬에 담음
			nextRow = location.first - 1;
			nextCol = location.second + 0;
			if (board[nextRow][nextCol] == ROAD) {
				while (true) {
					if (board[nextRow][nextCol] != ROAD) break;
					nextCol++;
				}
				int curNode = board[curRow][curCol];
				int nextNode = board[nextRow][nextCol];
				int length = nextCol - curCol;
				matrix[curNode][nextNode] = length;
				matrix[nextNode][curNode] = length;
			}		
		}
	}

};