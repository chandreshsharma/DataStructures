/***
 * Program to implement a stack using the STL queue container.
 *
 * The queue::size() method gives the current elements count, and the same number of elements are popped and pushed back.
 * This is to maintain the last element pushed at the front of the queue.
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

};

void Stack::push(int val)
{
/// We can choose to arrange the elements in either the push or the pop
/// Choosing the push, for now.
/// Elements inserted 1, 2, 3

    /// Push the new element to the queue
    q.push(val);

    /// Pop each element other than the one inserted, to ensure the new element is at the front of the queue.
    for(int i=1;i<q.size();++i) {
        int val = q.front();
        q.pop();
        q.push(val);    
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
