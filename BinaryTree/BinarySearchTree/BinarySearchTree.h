#pragma once
#include<iostream>

template<class T>
class BinarySearchTree{
public:
	BinarySearchTree();
	~BinarySearchTree();

	void add(const T& x);
	void printInorder() const;
	void printDot(std::ostream& out) const;

private:
	struct Node {
		T data;
		Node* left;
		Node* right;
	};

	Node* root;
	void deleteTree(Node* root);

	Node* add(Node* current, const T& x);
	void printInorder(Node* node) const;
	void printDot(Node* node, std::ostream& out) const;
};



