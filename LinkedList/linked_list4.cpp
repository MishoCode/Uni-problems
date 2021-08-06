#include<iostream>

struct Node {
	int data;
	Node* next;

	Node(int data, Node* next = nullptr)
		:data(data), next(next)
	{}
};

void printList(Node* head) {
	while (head != nullptr) {
		std::cout << head->data << " ";
		head = head->next;
	}
	std::cout << std::endl;
}

void destroyList(Node* head) {
	Node* curr = head, * next = nullptr;
	while (curr != nullptr) {
		next = curr->next;
		delete curr;
		curr = next;
	}
}

Node* pushFront(Node*& head, int x) {
	Node* newNode = new Node(x, head);
	head = newNode;
	return head;
}

int getLength(Node* head) {
	int len = 0;
	while (head != nullptr) {
		len++;
		head = head->next;
	}

	return len;
}

Node* reverseList(Node*& head) {
	Node* prev = nullptr, * curr = head, * next = nullptr;
	while (curr != nullptr) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}

	return prev;
}
int listToNum(Node* head) {
	int result = 0;
	while (head != nullptr) {
		result = result * 10 + head->data;
		head = head->next;
	}
	return result;
}


Node* numToList(int number) {
	Node* head = nullptr;
	while (number != 0) {
		int digit = number % 10;
		head = pushFront(head, digit);
		number /= 10;
	}

	return head;
}

std::pair<Node*, Node*> splitLsit(Node* head) {
	int length = getLength(head);
	int i = length / 2;
	Node* temp = head;
	Node* firstHalf = nullptr, * secondHalf = nullptr;
	while (i > 0) {
		firstHalf = pushFront(firstHalf, temp->data);
		temp = temp->next;
		i--;
	}
	
	while (temp != nullptr) {
		secondHalf = pushFront(secondHalf, temp->data);
		temp = temp->next;
	}

	return std::make_pair(reverseList(firstHalf), reverseList(secondHalf));
}

Node* mergeLists(Node*& left, Node* right) {
	if (left == nullptr) {
		return right;
	}

	Node* temp = left;
	while (temp->next != nullptr) {
		temp = temp->next;
	}
	temp->next = right;

	return left;
}

Node* inc(Node* head) {
	std::pair<Node*, Node*> halves = splitLsit(head);

	int leftNum = listToNum(halves.first);
	int rightNum = listToNum(halves.second);

	Node* left = numToList(leftNum - 1);
	Node* right = numToList(rightNum + 1);

	return mergeLists(left, right);
}

Node* createSample1() {
	return new Node(1, new Node(9, new Node(0, new Node(0, new Node(9, new Node(9, new Node(9, new Node(9)))))))); 
}
Node* createSample2() {
	return new Node(1, new Node(0, new Node(1, new Node(9)))); 
}
Node* createSample3() {
	return new Node(1, new Node(2)); 
}
Node* createSample4() {
	return new Node(1, new Node(9)); 
}

void testInc() {
	Node* head1 = createSample1();
	printList(inc(head1)); // 189910000

	Node* head2 = createSample2(); // 920
	printList(inc(head2));

	Node* head3 = createSample3(); // 3
	printList(inc(head3));

	Node* head4 = createSample4(); // 10
	printList(inc(head4));

	destroyList(head1);
	destroyList(head2);
	destroyList(head3);
	destroyList(head4);
}

int main() {
	testInc();

	return 0;
}