#include<iostream>

struct Node
{
    Node* next;
    int data;

    Node(int data, Node* next = nullptr)
        :next(next), data(data)
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

Node* reverse(Node* head)
{
    Node* current = head, *prev = nullptr, *next = nullptr;
    while(current != nullptr)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}
void printList(Node* head)
{
    while(head!= nullptr)
    {
        std::cout<<head->data<<" ";
        head = head->next;
    }
    std::cout<<std::endl;
}
Node* createSample1()
{
    return new Node(1, new Node(2, new Node(3, new Node(4, new Node(5)))));
}
Node* createSample2()
{
    return new Node(3);
}
Node* createSample3()
{
    return nullptr;
}
void testReverse()
{
    Node* test = createSample1();
    std::cout<<"Before reverse: ";
    printList(test);

    std::cout<<"After reverse: ";
    Node* result = reverse(test);
    printList(result);

    destroyList(result);

}
int main()
{
    testReverse();
    return 0;
}
