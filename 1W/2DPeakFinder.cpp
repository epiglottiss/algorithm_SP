#include <iostream>
#include <ctime>
#include <Windows.h>
using namespace std;

#define SIZE 5

int board[SIZE][SIZE];
int direction[2][4] = { {0,0,1,-1},{1,-1,0,0} };

struct PeakInfo {
	int value;
	int row;
	int col;
};
void InitBoard() {
	srand((unsigned int)time(NULL));
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			board[i][j] = rand() % 100;
		}
	}
}

PeakInfo Find2DPeak() {
	PeakInfo ret;
	int row = SIZE / 2;
	int col = SIZE / 2;
	int max = board[row][col];
	bool isMoved = true;
	while (isMoved) {
		isMoved = false;
		for (int i = 0; i < 4; i++)
		{
			int newRow = row + direction[0][i];
			int newCol = col + direction[1][i];
			if (newRow < 0 || newCol < 0 || newRow >= SIZE || newCol >= SIZE)
				continue;
			if (board[newRow][newCol] > max) {

				row = newRow;
				col = newCol;
				max = board[row][col];
				isMoved = true;
				break;
			}
		}

	}
	ret.col = col;
	ret.row = row;
	ret.value = board[row][col];
	return ret;
}

void PrintBoard() {
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			printf("%3d", board[i][j]);
		}
		printf("\n");
	}
}

int main() {
	for (int i = 0; i < 5; i++)
	{
		InitBoard();
		PrintBoard();
		PeakInfo peakInfo = Find2DPeak();
		printf("Peak is %d at %d,%d\n", peakInfo.value, peakInfo.col+1, peakInfo.row+1);
		printf("\n");
		Sleep(1000);
	}

}