#include<iostream>

struct Node
{
	Node* next;
	int data;

	Node(int data, Node* next = nullptr)
		:data(data), next(next)
	{}
};

struct PartialSum
{
	Node* head;
	int carry;

	PartialSum()
		:head(nullptr), carry(0)
	{}
};

void destroyList(Node* head)
{
	Node* curr = head, *next = nullptr;
	while (curr != nullptr)
	{
		next = curr->next;
		delete curr;
		curr = next;
	}
}

void printList(Node* head)
{
	while (head != nullptr)
	{
		std::cout << head->data << " ";
		head = head->next;
	}
	std::cout << std::endl;
}
int getLength(Node* head)
{
	int len = 0;
	while (head != nullptr)
	{
		head = head->next;
		len++;
	}
	return len;
}
Node* pushFront(Node*& head, int x)
{
	Node* newNode = new Node(x, head);
	head = newNode;
	return head;
}
void makePadding(Node*& head, int n)
{
	for (int i = 0; i < n; i++)
	{
		pushFront(head, 0);
	}
}
PartialSum sumListsHelper(Node* l1, Node* l2)
{
	if (l1 == nullptr || l2 == nullptr) //here we are sure that l1 and l2 have the same length
	{
		PartialSum p;
		return p;
	}
	PartialSum p = sumListsHelper(l1->next, l2->next);
	int value = l1->data + l2->data + p.carry;
	p.head = pushFront(p.head, value%10);
	p.carry = value / 10;
	return p;
}
Node* sumLists(Node* l1, Node* l2)
{
	int len1 = getLength(l1);
	int len2 = getLength(l2);
	if (len1 < len2)
	{
		makePadding(l1, len2 - len1);
	}
	else if (len2 < len1)
	{
		makePadding(l2, len1 - len2);
	}

	PartialSum p = sumListsHelper(l1, l2);
	if (p.carry == 0)
	{
		return p.head;
	}

	return pushFront(p.head, p.carry);
}
void testSumLists()
{
	Node* node1 = new Node(1, new Node(2, new Node(3, new Node(4))));
	Node* node2 = new Node(5, new Node(6, new Node(7)));

	Node* result = sumLists(node1, node2);
	printList(result);

	destroyList(node1);
	destroyList(node2);
	destroyList(result);
}

int main()
{
	testSumLists();
	return 0;
}