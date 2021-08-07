#include "BinarySearchTree.h"

template<class T>
BinarySearchTree<T>::BinarySearchTree()
	:root(nullptr)
{}

template<class T>
BinarySearchTree<T>::~BinarySearchTree() {
	deleteTree(root);
}

template<class T>
void BinarySearchTree<T>::deleteTree(Node* root) {
	if (root == nullptr) {
		return;
	}

	deleteTree(root->left);
	deleteTree(root->right);
	delete root;
}

template<class T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::add(Node* node, const T& x) {
	if (node == nullptr) {
		node = new Node{ x,nullptr,nullptr };
	}

	if (x < node->data) {
		node->left = add(node->left, x);
	}
	else if(x > node->data){
		node->right = add(node->right, x);
	}

	return node;
}

template<class T>
void BinarySearchTree<T>::add(const T& x){
	root = add(root, x);
}

template<class T>
void BinarySearchTree<T>::printInorder(Node* node) const {
	if (node == nullptr) {
		return;
	}

	printInorder(node->left);
	std::cout << node->data << " ";
	printInorder(node->right);
}
template<class T>
void BinarySearchTree<T>::printInorder() const {
	printInorder(root);
	std::cout << std::endl;
}

template<class T>
void BinarySearchTree<T>::printDot(Node* node, std::ostream& out) const {
	if (node == nullptr) {
		return;
	}

	printDot(node->left, out);

	out << (long)node << "[label=\"" << node->data << "\"]\n";
	if (node->left != nullptr) {
		out << (long)node << " -> " << (long)node->left << "[color=red]\n";
	}
	if (node->right != nullptr) {
		out << (long)node << " -> " << (long)node->right << "[color=blue]\n";
	}

	printDot(node->right, out);
}

template<class T>
void BinarySearchTree<T>::printDot(std::ostream& out) const {
	out << "digraph{\n";
	printDot(root, out);
	out << "}\n";
}
