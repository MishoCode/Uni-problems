#include <iostream>
#include <cassert>

// Find the sum of all left leaves in a given binary tree

struct Node
{
    int data;
    Node *left;
    Node *right;

    Node(int data, Node *left = nullptr, Node *right = nullptr)
        : data(data), left(left), right(right)
    {
    }
};

void deleteTree(Node *&root)
{
    if (root == nullptr)
    {
        return;
    }

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
    root = nullptr;
}

void inorder(Node *root)
{
    if (root == nullptr)
    {
        return;
    }

    inorder(root->left);
    std::cout << root->data << " ";
    inorder(root->right);
}

bool isLeaf(Node *root)
{
    assert(root != nullptr);
    return root->left == nullptr && root->right == nullptr;
}

int sumOfLeftLeaves(Node *root)
{
    if (root == nullptr)
    {
        return 0;
    }

    if (root->left != nullptr && isLeaf(root->left))
    {
        return root->left->data + sumOfLeftLeaves(root->right);
    }
    else if (root->left != nullptr && !isLeaf(root->left))
    {
        return sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);
    }
    else if (root->left == nullptr)
    {
        return sumOfLeftLeaves(root->right);
    }
}

void test()
{
    Node *root1 = new Node(1, new Node(9), new Node(20, new Node(15), new Node(7)));
    int result1 = sumOfLeftLeaves(root1);
    std::cout << result1 << std::endl; // 24
    deleteTree(root1);

    Node *root2 = new Node(1, nullptr, new Node(2, nullptr, new Node(3, nullptr, nullptr)));
    int result2 = sumOfLeftLeaves(root2);
    std::cout << result2 << std::endl; // 0
    deleteTree(root2);

    Node *root3 = new Node(1, new Node(2, new Node(3, nullptr, nullptr), nullptr), nullptr);
    int result3 = sumOfLeftLeaves(root3);
    std::cout << result3 << std::endl; // 3
    deleteTree(root3);
}

int main()
{
    test();
    return 0;
}