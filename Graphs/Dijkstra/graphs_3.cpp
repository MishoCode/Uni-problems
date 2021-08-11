#include<iostream>
#include<vector>
#include<algorithm>
#include<set>

const int _INFINITY = (~(1 << 31));

using ShortestPaths = std::vector<std::pair<int, std::vector<int>>>;

class Graph {
public:
	Graph() {
		init();
	}

	~Graph() {
		delete[] graph;
		delete[] used;
		delete[] prev;
          	delete[] cost;
	}

	void clearUsed() {
		for (int i = 0; i < numberOfVertices; i++) {
			used[i] = false;
		}
		for (int i = 0; i < numberOfVertices; i++) {
			prev[i] = -1;
		}
    }

	ShortestPaths dijkstra(int start) {
		ShortestPaths allShortestPaths;

		std::set<int> spt; // shortest paths tree
		used[start] = true;

		int* dist = new int[numberOfVertices];
		for (int i = 0; i < numberOfVertices; i++) {
			dist[i] = _INFINITY;
			spt.insert(i);
		}

		dist[start] = 0;

		while (!spt.empty()) {

			int current = *spt.begin();
			for (auto i : spt) {
				if (dist[current] > dist[i]) {
					current = i;
				}
			}
			spt.erase(current);
			used[current] = true;

			for (int k = 0; k < graph[current].size(); k++) {
				int neighbour = graph[current][k];
				int fromStartToI = dist[current] + cost[current][k];
				if (!used[neighbour] && fromStartToI < dist[neighbour]) {
					dist[neighbour] = fromStartToI;
					prev[neighbour] = current;
				}
			}

		}

		for (int i = 0; i < numberOfVertices; i++) {
			std::vector<int> currentShortestPath;
			if (i == start) {
				currentShortestPath.push_back(i);
				allShortestPaths.push_back(std::make_pair(0, currentShortestPath));
				continue;
			}

			int current = i;
			while (current != -1) {
				currentShortestPath.push_back(current);
				current = prev[current];
			}

			std::reverse(currentShortestPath.begin(), currentShortestPath.end());
			allShortestPaths.push_back(std::make_pair(dist[i],currentShortestPath));
		}

		delete[] dist;

		return allShortestPaths;
	}

private:
	int numberOfVertices;
	std::vector<int>* graph;
	bool* used;
	int* prev;
	std::vector<int>* cost;

	void init() {
		std::cin >> numberOfVertices;
		graph = new std::vector<int>[numberOfVertices];
		used = new bool[numberOfVertices];
		prev = new int[numberOfVertices];
		cost = new std::vector<int>[numberOfVertices];

		for (int i = 0; i < numberOfVertices; i++) {
			prev[i] = -1;
		}

		int numberOfEdges;
		std::cin >> numberOfEdges;
		for (int i = 0; i < numberOfEdges; i++) {
			int first, second;
			std::cin >> first >> second;
			graph[first].push_back(second);
			graph[second].push_back(first);

			int weight;
			std::cin >> weight;
			cost[first].push_back(weight);
			cost[second].push_back(weight);
		}
	}
};

void printSolution(ShortestPaths shortestPaths){
	std::cout << "All shortest paths:\n";
	for (int i = 0; i < shortestPaths.size(); i++) {
		std::cout << "Shortest path to vertex "<< i << " | Path value: " << shortestPaths[i].first << " | Shortest path: ";
        std::vector<int> path = shortestPaths[i].second;
		for (int j = 0; j < path.size(); j++) {
			std::cout << path[j] << " ";
		}
		std::cout << std::endl;
	}
}
void testDijkstra(){
    Graph g1;
	g1.clearUsed();
    int startVertex;
    std::cout << "Enter the start vertex: ";
    std::cin >> startVertex;
    ShortestPaths allShortestPaths = g1.dijkstra(startVertex);
	printSolution(allShortestPaths);
}

int main() {
    testDijkstra();
	return 0;
}

/*
g1:
7
9
0 1 1
0 4 1
0 3 4
1 4 3
2 5 3
3 2 3
4 2 3
4 6 1
6 5 10
*/
