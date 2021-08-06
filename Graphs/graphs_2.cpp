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
		delete[] prev;
	}

	void clearUsed() {
		for (int i = 0; i < numberOfVertices; i++) {
			used[i] = false;
		}
		for (int i = 0; i < numberOfVertices; i++) {
			prev[i] = -1;
		}
	}

	void allPaths(int start, int end, std::vector<std::vector<int>>& paths) {
		used[start] = true;
		if (start == end) {
			std::vector<int> path;
			int i = start;

			while (i != -1) {
				path.push_back(i);
				i = prev[i];
			}

			std::reverse(path.begin(), path.end());
			paths.push_back(path);
			for (int i = 0; i < path.size(); i++) {
				std::cout << path[i] << " ";
			}
			std::cout << std::endl;
		}
		
		for (int i = 0; i < graph[start].size(); i++) {
			if (!used[graph[start][i]]) {
				prev[graph[start][i]] = start;
				allPaths(graph[start][i], end,paths);
			}
		}
		used[start] = false;
	}
    
	bool validPath(const std::vector<int>& path, const std::unordered_set<int>& m, int n) {
		if (path.size() <= n) {
			return false;
		}
		for (int i = 0; i < path.size()-1; i++) {
			if (m.find(path[i]) != m.end() && m.find(path[i + 1]) != m.end()) {
				return false;
			}
		}
		return true;
	}

	bool pathExists(int start, int end, const std::unordered_set<int>& m, int n) {
		std::vector<std::vector<int>> paths;
		allPaths(start, end, paths);
		for (auto i : paths) {
			if (validPath(i,m,n)) {
				return true;
			}
		}
		return false;
	}

	std::vector<int> bfs(int start) {
		std::vector<int> bfsResult;

		std::queue<int> q;
		q.push(start);
		used[start] = true;

		while (!q.empty()) {
			int current = q.front();
			q.pop();
			bfsResult.push_back(current);

			for (int i = 0; i < graph[current].size(); i++) {
				int neighbour = graph[current][i];
				if (!used[neighbour]) {
					q.push(neighbour);
					used[neighbour] = true;
				}
			}
		}

		return bfsResult;
	}

	int countConnectedComponents() {
		int count = 0;
		for (int i = 0; i < numberOfVertices; i++) {
			if (!used[i]) {
				bfs(i);
				count++;
			}
		}

		return count;
	}

	std::vector<std::vector<int>> getConnectedComponents() {
		std::vector<std::vector<int>> components;
		for (int i = 0; i < numberOfVertices; i++) {
			if (!used[i]) {
				std::vector<int> currentComponent = bfs(i);
				components.push_back(currentComponent);
			}
		}

		return components;
	}

	int getMinVertexInTheComponent(const std::vector<int>& connectedComponent, int* topValues) {
		int min = topValues[connectedComponent[0]];
		for (int i = 1; i < connectedComponent.size(); i++) {
			if (topValues[connectedComponent[i]] < min) {
				min = topValues[connectedComponent[i]];
			}
		}

		return min;
	}

	int sumOfVertices(int* topValues) {
		int result = 0;

		std::vector<std::vector<int>> components = getConnectedComponents();
		for (const std::vector<int>& c : components) {
			int minVertex = getMinVertexInTheComponent(c,topValues);
			result += minVertex;
		}

		return result;
	}

private:
	int numberOfVertices;
	std::vector<int>* graph;
	bool* used;
	int* prev;

	void init(std::istream& in) {
        in >> numberOfVertices;
		graph = new std::vector<int>[numberOfVertices];
		used = new bool[numberOfVertices];
		prev = new int[numberOfVertices];

		for (int i = 0; i < numberOfVertices; i++) {
			prev[i] = -1;
		}

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

void testPathExists(){
    std::cout<<"Enter graph data:\n";
    Graph g2;
    g2.clearUsed();
	std::unordered_set<int> m;
	m.insert(2);
	m.insert(4);
	m.insert(5);
	m.insert(3);
	std::cout << "All paths:\n";
	std::cout << (g2.pathExists(1, 5, m, 3) ? "YES" : "NO") << std::endl;    
}

void testCountConnectedComponents(){
    std::cout<<"Enter graph data:\n";
    Graph g2;
    g2.clearUsed();
    std::cout << "Count: " << g2.countConnectedComponents() << std::endl; //2

    std::cout<<"Enter graph data:\n";
    Graph g3;
    g3.clearUsed();
    std::cout << "Count: " << g3.countConnectedComponents() << std::endl; //5
}

void testSumOfVerices(){
    std::cout<<"Enter graph data:\n";
    Graph g3;
	g3.clearUsed();
	int topValues1[] = { 10, 60, 20, 70, 30, 80, 40, 90, 50, 100 };
	std::cout << "Sum: " << g3.sumOfVertices(topValues1) << std::endl; // 150

    std::cout<<"Enter graph data:\n";
    Graph g4;
	g4.clearUsed();
	int topValues2[] = { 20, 50, 30, 40, 80 };
	std::cout << "Sum: " << g4.sumOfVertices(topValues2) << std::endl; //100

    
}
int main() {
    //testPathExists();
    //testCountConnectedComponents();
    testSumOfVerices();
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