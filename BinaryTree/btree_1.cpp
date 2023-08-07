#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <queue>

template <class T>
struct Node
{
	Node<T> *left;
	Node<T> *right;
	T data;

	Node(const T &data, Node<T> *left = nullptr, Node<T> *right = nullptr)
		: data(data), left(left), right(right)
	{
	}
	~Node()
	{
		delete left, right;
	}

	bool addLeft(const T &data)
	{
		if (left == nullptr)
		{
			left = new Node<T>(data);
			return true;
		}
		return false;
	}
	bool addRight(const T &data)
	{
		if (right == nullptr)
		{
			right = new Node<T>(data);
			return true;
		}
		return false;
	}
	bool addNode(const std::string path, const T &data)
	{
		assert(!path.empty());

		if (path.size() == 1)
		{
			if (path.front() == 'L')
				return addLeft(data);
			else if (path.front() == 'R')
				return addRight(data);

			return false;
		}

		if (path[0] == 'L')
		{
			if (!hasLeft())
				return false;
			return left->addNode(path.substr(1), data);
		}
		else if (path[0] == 'R')
		{
			if (!hasRight())
				return false;
			return right->addNode(path.substr(1), data);
		}

		return false;
	}
	bool isLeaf() const
	{
		return left == nullptr && right == nullptr;
	}
	bool hasLeft() const
	{
		return left != nullptr;
	}
	bool hasRight() const
	{
		return right != nullptr;
	}
	void printLNR() const
	{
		if (hasLeft())
			left->printLNR();
		std::cout << data << " ";
		if (hasRight())
			right->printLNR();
	}
};

// finds the sum of leaves with even depth and the product of leaves with odd depth
std::pair<int, int> traverseLeaves(Node<int> *root, int depth = 0)
{
	if (root == nullptr)
		return std::make_pair(0, 1);
	if (root->isLeaf())
	{
		if (depth % 2 == 0)
		{
			return std::make_pair(root->data, 1);
		}
		else
		{
			return std::make_pair(0, root->data);
		}
	}
	std::pair<int, int> result1 = traverseLeaves(root->left, depth + 1);
	std::pair<int, int> result2 = traverseLeaves(root->right, depth + 1);
	return std::make_pair(result1.first + result2.first, result1.second * result2.second);
}

const Node<int> *const SENTINEL = nullptr;

// creates a list of all the nodes in each depth in a binary tree
void getLevels(Node<int> *root, std::vector<std::vector<Node<int> *>> &levels)
{
	if (root == nullptr)
		return;

	std::queue<Node<int> *> bfsQueue;
	bfsQueue.push(root);
	bfsQueue.push(nullptr);
	std::vector<Node<int> *> currentLevel;
	while (!bfsQueue.empty())
	{
		Node<int> *element = bfsQueue.front();
		if (element == SENTINEL)
		{

			levels.push_back(currentLevel);
			currentLevel.clear();
			bfsQueue.pop();
			if (bfsQueue.empty())
				return;
			bfsQueue.push(nullptr);
		}
		else
		{
			currentLevel.push_back(element);
			if (element->hasLeft())
				bfsQueue.push(element->left);

			if (element->hasRight())
				bfsQueue.push(element->right);

			bfsQueue.pop();
		}
	}
}

Node<int> *createBSTfromSortedArray(int nodes[], int start, int end)
{
	if (end < start)
		return nullptr;
	int mid = start + (end - start) / 2;
	Node<int> *root = new Node<int>(nodes[mid]);
	root->left = createBSTfromSortedArray(nodes, start, mid - 1);
	root->right = createBSTfromSortedArray(nodes, mid + 1, end);
	return root;
}
Node<int> *createBSTfromSortedArray(int nodes[], int size)
{
	return createBSTfromSortedArray(nodes, 0, size - 1);
}

template <class T>
int checkHeight(Node<T> *root)
{
	if (root == nullptr)
		return -1;

	int leftHeight = checkHeight(root->left);
	if (leftHeight == INT_MIN)
		return INT_MIN;

	int rightHeight = checkHeight(root->right);
	if (rightHeight == INT_MIN)
		return INT_MIN;

	int heightDiff = leftHeight - rightHeight;
	if (abs(heightDiff) > 1)
		return INT_MIN;
	else
		return std::max(leftHeight, rightHeight) + 1;
}

template <class T>
bool isBalanced(Node<T> *root)
{
	return checkHeight(root) != INT_MIN;
}

Node<int> *createSample()
{
	Node<int> *root = new Node<int>(5);
	root->addLeft(3);
	root->addRight(6);
	root->addNode("LR", 4);
	root->addNode("RR", 7);
	root->addNode("LL", 2);
	root->addNode("LLL", 1);
	return root;
}
Node<int> *createSample2()
{
	Node<int> *root = new Node<int>(1);
	root->addLeft(2);
	root->addRight(100);
	root->addNode("LL", 3);
	root->addNode("LLL", 4);
	root->addNode("LLLL", 5);
	root->addNode("LLLLL", 6);
	root->addNode("LLLLLR", 7);
	return root;
}
void testTraverseLeaves()
{
	Node<int> *root = createSample();
	std::pair<int, int> result = traverseLeaves(root);
	std::cout << result.first << " " << result.second << std::endl;
	delete root;
}

void testGetLevels()
{
	Node<int> *root = createSample();
	std::vector<std::vector<Node<int> *>> levels;
	getLevels(root, levels);

	for (auto i : levels)
	{
		for (auto j : i)
		{
			std::cout << j->data << " ";
		}
		std::cout << std::endl;
	}
	delete root;
}
void testCreateBSTfromSortedArray()
{
	const int n = 7;
	int *arr = new int[n];
	for (int i = 0; i < n; i++)
	{
		arr[i] = i + 1;
	}
	Node<int> *root = createBSTfromSortedArray(arr, 7);
	root->printLNR();
	delete[] arr;
	delete root;
}
void testIsBalanced()
{
	Node<int> *root1 = createSample();
	std::cout << isBalanced(root1) << std::endl; // 1

	Node<int> *root2 = createSample2();
	std::cout << isBalanced(root2) << std::endl; // 0

	delete root1, root2;
}
int main()
{
	std::cout << "Test traverseLeaves:\n";
	testTraverseLeaves();
	std::cout << "======================\n";

	std::cout << "Test getLevels:\n";
	testGetLevels();
	std::cout << "======================\n";

	std::cout << "Test create BST from sorted array:\n";
	testCreateBSTfromSortedArray();
	std::cout << "======================\n";

	std::cout << "Test is balancecd:\n";
	testIsBalanced();
	return 0;
}