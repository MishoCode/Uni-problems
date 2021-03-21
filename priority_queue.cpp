#include<iostream>

class PriorityQueue
{
public:
    PriorityQueue()
        :head(nullptr)
    {}
    PriorityQueue(const PriorityQueue& other) = delete;
    PriorityQueue& operator=(const PriorityQueue& other) = delete;
    ~PriorityQueue()
    {
        Node* first = head;
        Node* second = nullptr;
        while(first != nullptr)
        {
            second = first->next;
            delete first;
            first = second;
        }
    }

    void push(char el, int p)
    {
        Node* newNode = new Node(nullptr, el,p);
        if(empty() || newNode->priority > head->priority)
        {
            newNode->next = head;
            head = newNode;
        }
        else
        {
            Node* first = head;
            while(first->next != nullptr && first->next->priority > newNode->priority)
            {
                first = first->next;
            }

            newNode->next = first->next;
            first->next = newNode;
        }
        
    }
    char pop()
    {
        if(empty())
            throw "Attempt to remove from empty queue!";
        char result = head->data;
        delete head;
        head = head->next;
        return result;
    }
    char peek() const
    {
        if(empty())
            throw "Attempt to peek in empty queue!";
        return head->data;
    }
    bool empty() const
    {
        return head == nullptr;
    }
    void print() const
    {
        Node* first = head;
        while(first != nullptr)
        {
            std::cout<<first->data<<" ";
            first = first->next;
        }
        std::cout<<std::endl;
    }
private:
    struct Node
    {
        char data;
        int priority;
        Node* next;

        Node(Node* next = nullptr, char data = 'a', int priority = 0)
            :next(next), data(data), priority(priority)
        {}

    };

    Node* head;
};

int main()
{
    PriorityQueue pq;
    std::cout<<pq.empty()<<std::endl; //1
    //std::cout<<pq.peek()<<std::endl; // exception

    
    pq.push('c',(int)('c'));
    pq.push('a',(int)('a'));
    pq.push('b',(int)('b'));
    pq.push('z',(int)('z'));
    pq.push('t',(int)('t'));
    pq.push('a',(int)('a'));
    pq.print();

    std::cout<<pq.pop()<<std::endl; //z
    pq.push('x',(int)('x'));
    pq.print(); //x,t,c,b,a,a
    std::cout<<pq.empty()<<std::endl;
    std::cout<<pq.pop()<<std::endl; //x
    std::cout<<pq.pop()<<std::endl; //t
    pq.push('z', (int)('z'));
    pq.push('h', (int)('h'));
    pq.push('e', (int)('e'));
    pq.print(); //z, h, e, c, b, a, a
    return 0;
}