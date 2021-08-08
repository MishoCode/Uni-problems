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
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::findMin(Node* node) const {
	if (node == nullptr) {
		return nullptr;
	}

	if (node->left == nullptr) {
		return node;
	}
	else {
		return findMin(node->left);
	}
}

template<class T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::remove(Node* node, const T& x) {
	if (node == nullptr) {
		return nullptr;
	}
	else if (x < node->data) {
		node->left = remove(node->left, x);
	}
	else if (x > node->data) {
		node->right = remove(node->right, x);
	}
	else {
		Node* temp = nullptr;
		if (node->left != nullptr && node->right != nullptr) {
			temp = findMin(node->right);
			node->data = temp->data;
			node->right = remove(node->right, temp->data);
		}
		else if(node->left == nullptr){
			temp = node;
			node = node->right;
			delete temp;
		}
		else if (node->right == nullptr) {
			temp = node;
			node = node->left;
			delete temp;
		}
	}

	return node;
}

template<class T>
void BinarySearchTree<T>::remove(const T& x) {
	root = remove(root, x);
}

template<class T>
bool BinarySearchTree<T>::search(Node* node, const T& x) const {
	if (node == nullptr) {
		return false;
	}
	else if (x < node->data) {
		return search(node->left, x);
	}
	else if (x > node->data) {
		return search(node->right, x);
	}
	else {
		return true;
	}
}

template<class T>
bool BinarySearchTree<T>::search(const T& x) const {
	return search(root, x);
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

