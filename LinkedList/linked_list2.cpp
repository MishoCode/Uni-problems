#include<iostream>
#include<set>

struct Node
{
	int data;
	Node* next;

	Node(int data, Node* next = nullptr)
		:data(data), next(next)
	{}
	
};
Node* createSample1()
{
	return new Node(1, 
		new Node(2, 
			new Node(2, 
				new Node(2, 
					new Node(1, 
						new Node(7, 
							new Node(3)))))));
}
void print(Node* head)
{
	while (head != nullptr)
	{
		std::cout << head->data << " ";
		head = head->next;
	}
	std::cout << std::endl;
}

void removeDuplicates(Node* head)
{
	Node* curr = head;
	while (curr != nullptr && curr->next != nullptr)
	{
		Node* runner = curr;
		while (runner->next != nullptr)
		{
			if (runner->next->data == curr->data)
			{
				Node* temp = runner->next;
				runner->next = runner->next->next;
				delete temp;
			}
			else
			{
				runner = runner->next;
			}
		}
		curr = curr->next;
	}
}
void removeDuplicates2(Node* head)
{
	std::set<int> elements;
	elements.insert(head->data);
	Node* temp = head;
	while (temp->next != nullptr)
	{
		if (elements.count(temp->next->data) > 0)
		{
			Node* dup = temp->next;
			temp->next = temp->next->next;
			delete dup;
		}
		else
		{
			temp = temp->next;
			elements.insert(temp->data);
		}
	}
}
Node* lastElementsHelper(Node* head, int k, int& i)
{
	if (head == nullptr)
		return nullptr;

	Node* curr = lastElementsHelper(head->next, k, i);
	i++;
	if (k == i)
		return head;
	return curr;
}

//returns a list of the last k elements
Node* lastElements(Node* head, int k)
{
	int i = 0;
	return lastElementsHelper(head, k, i);
}
Node* lastElementsIterative(Node* head, int k)
{
	Node* startPointer = head;
	Node* endPointer = head;
	for (int i = 0; i < k; i++)
	{
		if (endPointer == nullptr) // the size of the list is less than k
			return nullptr; 
		endPointer = endPointer->next;
	}

	while (endPointer != nullptr)
	{
		startPointer = startPointer->next;
		endPointer = endPointer->next;
	}
	return startPointer;
}
int main()
{
	std::cout << "Original list: ";
	print(createSample1());

	std::cout << "Remove duplicates: ";
	Node* sample1 = createSample1();
	removeDuplicates(sample1);
	print(sample1);

	std::cout << "Remove duplicates(second approach): ";
	Node* sample2 = createSample1();
	removeDuplicates2(sample1);
	print(sample1);

	std::cout << "Last 3 elements: ";
	print(lastElements(createSample1(),3));

	std::cout << "Last 3 elements(iterative approach): ";
	print(lastElements(createSample1(), 3));
	return 0;
}