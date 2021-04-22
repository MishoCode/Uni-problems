#include<iostream>
#include<stack>
#include<cassert>

// Design a stack that maintains getMinElement operation
// Operations push, pop and getMin need to take O(1) time

class StackWithMinOperation
{
public:
    bool isEmpty()const;
    int peek()const;
    void push(int x);
    int pop();
    int getMin()const;

    StackWithMinOperation(const std::stack<int>& st, const std::stack<int>& minElement);
private:
    std::stack<int> st;
    std::stack<int> minElement; // the top of this stack stores the min value of st
};



bool StackWithMinOperation::isEmpty()const
{
    return st.empty();
}
int StackWithMinOperation::peek()const
{
    assert(!st.empty());
    return st.top();
}
void StackWithMinOperation::push(int x)
{
    if(st.empty() || st.top() >= x)
    {
        minElement.push(x);
    }
    st.push(x);
}
int StackWithMinOperation::pop()
{
    assert(!st.empty());
    int t = st.top();
    st.pop();
    if(t == minElement.top())
    {
        minElement.pop();
    }
    
}
int StackWithMinOperation::getMin()const
{
    assert(!st.empty() && !minElement.empty());
    return minElement.top();
}

StackWithMinOperation::StackWithMinOperation(const std::stack<int>& st, const std::stack<int>& minElement)
{
    this->st = st;
    this->minElement = minElement;
}

int main()
{
    std::stack<int> s;
    std::stack<int> minElement;
    StackWithMinOperation testStack(s, minElement);

    //std::cout<<testStack.getMin()<<std::endl;//exception

    testStack.push(6);
    std::cout<<testStack.getMin()<<std::endl;//6

    testStack.push(3);
    std::cout<<testStack.getMin()<<std::endl;//3

    testStack.push(4);
    std::cout<<testStack.getMin()<<std::endl;//3

    testStack.push(-1);
    std::cout<<testStack.getMin()<<std::endl;//-1
    
    testStack.push(-1);
    std::cout<<testStack.getMin()<<std::endl;//-1

    testStack.push(12);
    std::cout<<testStack.getMin()<<std::endl;//-1

    testStack.push(15);
    std::cout<<testStack.getMin()<<std::endl;//-1

    testStack.pop();
    std::cout<<testStack.getMin()<<std::endl;//-1

    testStack.pop();
    std::cout<<testStack.getMin()<<std::endl;//-1

    testStack.pop();
    std::cout<<testStack.getMin()<<std::endl;//-1

    testStack.pop();
    std::cout<<testStack.getMin()<<std::endl;//3

    testStack.pop();
    std::cout<<testStack.getMin()<<std::endl;//3

    testStack.push(-2);
    std::cout<<testStack.getMin()<<std::endl;//-2

    testStack.pop();
    std::cout<<testStack.getMin()<<std::endl;//3
    return 0;
}