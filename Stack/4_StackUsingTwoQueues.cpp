/***
 * Program to implement a stack using two STL queue containers.
 *
 * The first queue holds all the elements, and the second is used as a temporary queue to arrange the elements.  
 *
***/

#include <iostream>
#include <queue>

class Stack{
public:
    void push(int val);
    void pop();
    void print();
    constexpr inline int top() const {
        return q.front();
    }   

protected:
    std::queue<int> q;
    std::queue<int> tmpQ;

};

void Stack::push(int val)
{
/// We can choose to arrange the elements in either the push or the pop
/// Choosing the push, for now.
/// Elements inserted 1, 2, 3

    /// Pop each element other than the one inserted, to ensure the new element is at the front of the queue.
    while(!q.empty())   {   
        int val = q.front();
        tmpQ.push(val);
        q.pop();
    }   

    /// Push the new element to the queue
    q.push(val);

    /// Bring all the elements back to the queue.
    while(!tmpQ.empty())   {
        int val = tmpQ.front();
        q.push(val);
        tmpQ.pop();
    }
}

void Stack::pop()
{
    q.pop();
}

void Stack::print()
{
    for(int i=1;i<=q.size();++i) {
        int val = q.front();
        std::cout << "| " << val << " |" << std::endl;
        q.pop();
        q.push(val);
    }
}

int main()
{
    Stack s;

    for(int i=1;i<=5;++i)
        s.push(i*10);

    std::cout << "Stack Contents: " << std::endl;
    s.print();

    s.pop();
    s.pop();

    std::cout << "Stack after popping two elements:" << std::endl;
    s.print();

    s.push(1);
    s.push(2);
    s.push(3);

    std::cout << "Stack after inserting three elements" << std::endl;
    s.print();

    return 0;
}
