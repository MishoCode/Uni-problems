#include<iostream>
#include<fstream>
#include"BinarySearchTree.h"
#include"BinarySearchTree.cpp"

int main() {
	BinarySearchTree<int> t;
	t.add(10);
	t.add(16);
	t.add(11);
	t.add(20);
	t.add(9);
	t.add(17);
	t.add(8);
	t.add(10);
	t.add(6);
	t.add(4);
	t.add(25);
	t.add(24);
	

	std::ofstream file("bst.dot");
	t.printInorder();
	t.printDot(file);
}