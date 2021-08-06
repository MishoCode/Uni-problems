#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<unordered_set>

class Graph {
public:
	Graph(std::istream& in = std::cin) {
		init(in);
	}

	~Graph() {
		delete[] graph;
		delete[] used;
	}

	void clearUsed() {
		for (int i = 0; i < numberOfVertices; i++) {
			used[i] = false;
		}
	}

	void bfsPrint(int start) {
		std::queue<int> bfsQueue;
		bfsQueue.push(start);
		used[start] = true;

		while (!bfsQueue.empty()) {
			int current = bfsQueue.front();
			bfsQueue.pop();
			std::cout << current << " ";

			for (int i = 0; i < graph[current].size(); i++) {
				if (!used[graph[current][i]]) {
					bfsQueue.push(graph[current][i]);
					used[graph[current][i]] = true;
				}
			}
		}
	}

	void dfsPrint(int start) {
		used[start] = true;
		std::cout << start << " ";
		
		for (int i = 0; i < graph[start].size(); i++) {
			if (!used[graph[start][i]]) {
				dfsPrint(graph[start][i]);
			}
		}
	}

	void bfsLevelsPrint(int start) {
		std::queue<int> q;
		int levelsCount = 0;

		used[start] = true;
		q.push(start);
		q.push(-1);

		while (!q.empty()) {
			int current = q.front();
			q.pop();

			if (current == -1) {
				std::cout << "\n";
				if (q.empty()) {
					return;
				}
				q.push(-1);
			}
			else {
				std::cout << current << " ";
				for (int i = 0; i < graph[current].size(); i++) {
					if (!used[graph[current][i]]) {
						q.push(graph[current][i]);
						used[graph[current][i]] = true;
					}
				}
			}
		}
	}

	int shortestBetween(int start, int end) {
		std::queue<std::pair<int,int>> q;
		used[start] = true;
		q.push(std::make_pair(start,0));

		while (!q.empty()) {
			int current = q.front().first;
			int dist = q.front().second;
			q.pop();

			if (current == end) {
				return dist;
			}

			for (int i = 0; i < graph[current].size(); i++) {
				int temp = graph[current][i];
				if (!used[temp]) {
					q.push(std::make_pair(temp,dist+1));
					used[temp] = true;
				}
			}
		}

		return -1;
	}

	int longestBetween(int start, int end) {
		if (start == end) {
			return 0;
		}
		used[start] = true;
		int maxLen = 0;
		for (int i = 0; i < graph[start].size(); i++) {
			if (!used[graph[start][i]]) {
				int pathLen = longestBetween(graph[start][i], end) + 1;
				maxLen = std::max(pathLen, maxLen);
			}
		}
		used[start] = false;

		return maxLen == 0 ? -1 : maxLen;
	}


private:
	int numberOfVertices;
	std::vector<int>* graph;
	bool* used;

	void init(std::istream& in) {
		in >> numberOfVertices;
		graph = new std::vector<int>[numberOfVertices];
		used = new bool[numberOfVertices];

		int numberOfEdges;
		in >> numberOfEdges;
		for (int i = 0; i < numberOfEdges; i++) {
			int first, second;
			in >> first >> second;
			graph[first].push_back(second);
			graph[second].push_back(first);
		}
	}
};

void testTraverse(){
    std::cout<<"Enter graph data:\n";
	Graph g1;
	g1.clearUsed();
	std::cout << "BFS print: ";
	g1.bfsPrint(1);
	std::cout << std::endl;

	g1.clearUsed();
	std::cout << "DFS print: ";
	g1.dfsPrint(1);
    std::cout<<std::endl;
}
void testLevelPrint(){
    std::cout<<"Enter graph data:\n";
	Graph g2;
	g2.clearUsed();
	std::cout << "BFS levels print:\n";
	g2.bfsLevelsPrint(0);
	std::cout << std::endl;
}

void testShortestPath(){
    std::cout<<"Enter graph data:\n";
	Graph g2;
	g2.clearUsed();
    std::cout << "Shortest: " << g2.shortestBetween(0, 5) << std::endl; // 2
	g2.clearUsed();
	std::cout << "Shortest: " << g2.shortestBetween(0, 0) << std::endl; // 0
	g2.clearUsed();
	std::cout << "Shortest: " << g2.shortestBetween(0, 6) << std::endl; // -1
	g2.clearUsed();
	std::cout << "Shortest: " << g2.shortestBetween(0, 3) << std::endl; // 1
}
void testLongestPath(){
    std::cout<<"Enter graph data:\n";
	Graph g2;
	g2.clearUsed();
    std::cout << "Longest: " << g2.longestBetween(1, 5) << std::endl; // 4
    g2.clearUsed();
    std::cout << "Longest: " << g2.longestBetween(1, 1) << std::endl; // 0
    g2.clearUsed();
    std::cout << "Longest: " << g2.longestBetween(1, 2) << std::endl; // 1
    g2.clearUsed();
    std::cout << "Longest: " << g2.longestBetween(1, 6) << std::endl; // -1
}
int main() {
    //testTraverse();
    //testLevelPrint();
    //testShortestPath();
    testLongestPath();
	return 0;
}

/*
g1:
6
7
0 3
0 1
1 2
1 3
3 4
3 5
4 5

g2:
7
7
0 3
0 1
1 2
1 3
3 4
3 5
4 5

g3:
10
5
0 1
2 3
4 5
6 7
8 9

g4:
5
2
0 3
3 4
*/