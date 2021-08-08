#pragma once
#include<iostream>

template<class T>
class BinarySearchTree{
public:
	BinarySearchTree();
	~BinarySearchTree();

	void add(const T& x);
	void remove(const T& x);
	void printInorder() const;
	void printDot(std::ostream& out) const;
	bool search(const T& x) const;

private:
	struct Node {
		T data;
		Node* left;
		Node* right;
	};

	Node* root;
	void deleteTree(Node* root);

	Node* add(Node* node, const T& x);
	Node* findMin(Node* node) const;
	Node* remove(Node* node, const T& x);
	bool search(Node* node, const T& x) const;
	void printInorder(Node* node) const;
	void printDot(Node* node, std::ostream& out) const;
};



