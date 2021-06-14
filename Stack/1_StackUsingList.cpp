/***
 *
 * Implement Stack using an STL list
 *
***/

#include <iostream>
#include <list>

class Stack{
public:
    void pop();
    void push(const int & val);
    int top();
    void print();

protected:
    std::list<int> values;
};

void Stack::push(const int & val)
{   
    values.push_back(val);
}

void Stack::pop()
{   
    if(values.empty())  {
        std::cout << "Stack Underflow !!" << std::endl;
        return;
    }
    values.pop_back();
}

int Stack::top()
{   
    if(values.empty())   {
        std::cout << "Empty Stack !!" << std::endl;
        ///return INT_MAX;
        return std::numeric_limits<int>::max();
    }
    return(*(values.rbegin()));
}

void Stack::print()
{
    std::cout << "Stack Contents:" << std::endl << std::endl;

    std::list<int>::reverse_iterator ritr = values.rbegin();
    for(;ritr != values.rend(); ++ritr) {
        std::cout << "| " << *ritr << " |" << std::endl;
        std::cout << "-----" << std::endl;
   }
}

int main()
{
    Stack s;
    std::cout <<"Stack top:" << s.top() << std::endl;

    s.push(10);
    s.push(12);
    s.push(30);
    s.push(45);

    std::cout <<"Stack top:" << s.top() << std::endl;
    s.print();

    std::cout << "Popping 2 elements" << std::endl;
    s.pop();
    s.pop();

    std::cout <<"Stack top:" << s.top() << std::endl;
    s.print();

    std::cout << "Adding 3 elements" << std::endl;
    s.push(60);
    s.push(23);
    s.push(18);

    std::cout <<"Stack top:" << s.top() << std::endl;
    s.print();

    return 0;
}
