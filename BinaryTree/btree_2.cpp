#include <iostream>
#include <vector>

// Merge two binary search trees

struct Node
{
	int data;
	Node *left, *right;

	Node(int data, Node *left = nullptr, Node *right = nullptr)
		: data(data), left(left), right(right)
	{
	}
};

void printInorder(Node *root)
{
	if (root == nullptr)
		return;
	printInorder(root->left);
	std::cout << root->data << " ";
	printInorder(root->right);
}
void destroyTree(Node *root)
{
	if (root == nullptr)
		return;

	destroyTree(root->left);
	destroyTree(root->right);
	delete root;
}
void storeInorder(Node *root, std::vector<int> &arr)
{
	if (root == nullptr)
		return;

	storeInorder(root->left, arr);
	arr.push_back(root->data);
	storeInorder(root->right, arr);
}
void mergeArrays(const std::vector<int> &arr1, const std::vector<int> &arr2, std::vector<int> &result)
{
	size_t len1 = arr1.size();
	size_t len2 = arr2.size();
	size_t i = 0, j = 0, k = 0;
	while (i < len1 && j < len2)
	{
		if (arr1[i] < arr2[j])
		{
			result.push_back(arr1[i]);
			i++;
		}
		else
		{
			result.push_back(arr2[j]);
			j++;
		}
		k++;
	}

	while (i < len1)
	{
		result.push_back(arr1[i]);
		k++;
		i++;
	}
	while (j < len2)
	{
		result.push_back(arr2[j]);
		k++;
		j++;
	}
}
Node *createBSTfromSortedArray(const std::vector<int> &arr, size_t start, size_t end)
{
	if (arr.empty() || start >= end)
		return nullptr;

	size_t mid = (start + end) / 2;
	Node *root = new Node(arr[mid]);
	root->left = createBSTfromSortedArray(arr, start, mid);
	root->right = createBSTfromSortedArray(arr, mid + 1, end);
	return root;
}
Node *mergeBST(Node *root1, Node *root2)
{
	if (root1 == nullptr)
		return root2;
	if (root2 == nullptr)
		return root1;
	std::vector<int> arr1;
	std::vector<int> arr2;
	storeInorder(root1, arr1);
	storeInorder(root2, arr2);

	std::vector<int> result;
	mergeArrays(arr1, arr2, result);

	size_t len = result.size();
	return createBSTfromSortedArray(result, 0, len);
}

int main()
{
	Node *root1 = new Node(100, new Node(50, new Node(20), new Node(70)), new Node(300));
	Node *root2 = new Node(80, new Node(40), new Node(120));

	Node *mergedTree = mergeBST(root1, root2);
	printInorder(mergedTree);
	std::cout << "\n";

	destroyTree(root1);
	destroyTree(root2);
	destroyTree(mergedTree);
}
