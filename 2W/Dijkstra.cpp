#include <stdio.h>
#include <queue>
#include <vector>
using namespace std;

//Node 개수 지정
#define SIZE 5

struct NodeInfo {
	int dest;
	int cost;
	vector<int> path;
};

/*
* priority queue에 struct 담기 위해 overloading
* 최소힙을 위해 부등호 방향을 바꿈
*/
bool operator<(NodeInfo info1, NodeInfo info2) {
	return info1.cost > info2.cost;
}

/*
* Node와 Edge의 정보 담는 2D 배열
*/
vector< vector< pair<int,int> > > graph(SIZE);
/*
* 최소 경로 값 담는 배열
*/
vector<int> shortest(SIZE);
/*
* 방문한 경로 담는 배열
*/
vector<vector<int>> visit(SIZE);

void Dijkstra(int start) {
	for (int i = 0; i < SIZE; i++)
	{
		shortest[i] = 2100000000;
	}
	priority_queue < NodeInfo > smallest;
	smallest.push({ start, 0, {start} });
	while (!smallest.empty()) {
		int current = smallest.top().dest;
		int distance = smallest.top().cost;
		vector<int> currentPath = smallest.top().path;
		smallest.pop();
		if (shortest[current] < distance) continue;
		int size = graph[current].size();
		for (int i = 0; i < size; i++)
		{
			int nextDest = graph[current][i].first;
			int nextCost = graph[current][i].second + distance;
			vector<int> nextPath = currentPath;
			nextPath.push_back(nextDest);
			if (nextCost < shortest[nextDest]) {
				shortest[nextDest] = nextCost;
				visit[nextDest] = nextPath;
				smallest.push({ nextDest, nextCost, nextPath });
			}
		}
	}
}

void printResult() {
	for (int i = 1; i < SIZE;i++) {
		printf("A to %c : %d\n", 'A' + i, shortest[i]);
		for (int node : visit[i]) {
			printf("%c ", node + 'A');
		}
		printf("\n\n");
	}
}
int main() {
	graph[0].push_back({ 1,10 });
	graph[0].push_back({ 2,3 });
	graph[1].push_back({ 2,1 });
	graph[1].push_back({ 3,2 });
	graph[2].push_back({ 1,4 });
	graph[2].push_back({ 3,8 });
	graph[2].push_back({ 4,2 });
	graph[3].push_back({ 4,7 });
	graph[4].push_back({ 3,9 });
	Dijkstra(0);
	printResult();

	graph.clear();
	graph.resize(SIZE);
	graph[0].push_back({ 1,10 });
	graph[0].push_back({ 2,3 });
	graph[1].push_back({ 2,1 });
	graph[1].push_back({ 3,2 });
	graph[2].push_back({ 1,4 });
	graph[2].push_back({ 3,8 });
	graph[2].push_back({ 4,2 });
	graph[3].push_back({ 4,-7 });
	graph[4].push_back({ 3,9 });
	Dijkstra(0);
	printResult();

	return 0;

}