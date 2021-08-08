#include<iostream>
#include<fstream>
#include"BinarySearchTree.h"
#include"BinarySearchTree.cpp"

int main() {

	BinarySearchTree<int> t;
	t.add(12);
	t.add(18);
	t.add(5);
	t.add(9);
	t.add(3);
	t.add(7);
	t.add(11);
	t.add(15);
	t.add(27);
	t.add(16);
	t.add(14);

	std::ofstream file("bst_add.dot");
	t.printDot(file);
	file.close();

	t.remove(5);
	file.open("bst_remove.dot");
	t.printDot(file);
	file.close();

	t.remove(15);
	t.remove(11);
	file.open("bst_remove2.dot");
	t.printDot(file);
	file.close();

	std::cout << t.search(100) << std::endl; // 0
	std::cout << t.search(3) << std::endl; // 1
	std::cout << t.search(27) << std::endl; // 1
	std::cout << t.search(-1) << std::endl; // 0
	std::cout << t.search(12) << std::endl; // 1
}