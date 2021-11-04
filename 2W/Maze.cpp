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
		//�̷� ������� Ȧ���� ����
		if (SIZE & 1) return false;
		bool ret = true;
		InitBoard();

	}

private:
	void InitBoard() {
		//¦�� �ε����� ��� ������, �׿ܿ��� ��
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
		//1.Ȧ�� �ε������� ������ �Ǵ� �Ʒ��� �� ����
		//2. �̷ο��� �����ġ ã�� ����
		srand((unsigned int)time(NULL));
		for (int i = 1; i < SIZE; i += 2)
		{
			for (int j = 1; j < SIZE; j += 2)
			{
				//������ �ε��������� ����
				if (i == SIZE - 2 && j == SIZE - 2) continue;
				//�� �Ʒ��ٿ����� ���������� �� �����
				if (i == SIZE - 2) {
					board[i][j + 1] = ROAD;
					continue;
				}
				//�� �������ٿ����� �Ʒ��� �� �����
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

		//node ������ ������� �Ҵ�
		matrix.resize(nodeCount);
		for (int i = 0; i < nodeCount; i++)
		{
			matrix[i].resize(nodeCount);
		}

		//������� ����ġ ���ϱ�
		while (!nodeLocation.empty()) {
			pair<int, int> location = nodeLocation.front();
			nodeLocation.pop();
			int curRow = location.first;
			int curCol = location.second;

			//�����ʿ� ���� ������ ������ Node���� ����ġ ����Ͽ� ������Ŀ� ����		
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

			//���ʿ� ���� ������ ���� Node���� ����ġ ����Ͽ� ������Ŀ� ����
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