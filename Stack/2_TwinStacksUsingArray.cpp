/***
 *
 * Program to implement two stacks using a single array.
 * 
 * The two stacks grow for the ends of the array inwards. No array elements are reserved for a stack 
 * and either stack can occupy all elements of the array.
 *
***/

#include <iostream>

class TwinStacks
{
public:
    void push1(int val);
    void push2(int val);

    void pop1();
    void pop2();

    constexpr inline int getTop1() const;
    constexpr inline int getTop2() const;

    void print();

    TwinStacks(const int & stackSize=256):numElements(stackSize), top1(-1), top2(numElements){
        stackElements = new int[numElements];

        for(int i=0;i<numElements;++i)  {
            stackElements[i] = 0;
        }   
    }   

    ~TwinStacks()
    {   
        delete[] stackElements;
        stackElements = nullptr;
    }   
protected:
    int numElements;   /// The array can hold maximum 256 elements.
    int * stackElements;
    int top1;
    int top2;
};

void TwinStacks::print()
{
    for(int i=0;i<numElements;++i)  {
        std::cout << "| " << stackElements[i] << " |, ";
    }
    std::cout << std::endl;
}

void TwinStacks::push1(int val)
{
    /// Verify if the two stacks are adjacent OR all locations occupied by the first stack.
    if(top1 + 1 == top2)  {
        std::cout << "Stack Full !!" << std::endl;
        return;
    }

    stackElements[++top1] = val;
}
void TwinStacks::push2(int val)
{
    /// Verify if the two stacks are adjacent OR all locations occupied by the second stack.
    if(top2 - 1 == top1) {
        std::cout << "Stack Full !!" << std::endl;
        return;
    }

    stackElements[--top2] = val;
}

constexpr inline int TwinStacks::getTop1() const
{
   return stackElements[top1];
}

constexpr inline int TwinStacks::getTop2() const
{
   return stackElements[top2];
}

void TwinStacks::pop1()
{
    if(top1 > -1)
        --top1;
    else
       std::cout << "Stack Empty !!" << std::endl;
}

void TwinStacks::pop2()
{
    if(top2 < numElements)
        ++top2;
    else
       std::cout << "Stack Empty !!" << std::endl;
}

int main()
{
    TwinStacks ts(10);

    for(int i=1;i<=5;++i)  {
        ts.push1(i*10);
        ts.push2(i*100);

        if(i == 3)  {
            ts.print();
            std::cout << "Stack1 Top: " << ts.getTop1() << std::endl;
            std::cout << "Stack2 Top: " << ts.getTop2() << std::endl;
        }
    }

    ts.print();
    std::cout << "Stack1 Top: " << ts.getTop1() << std::endl;
    std::cout << "Stack2 Top: " << ts.getTop2() << std::endl;

    /// Stack Full conditions
    ts.push1(60);
    ts.push2(600);

    for(int i=1;i<=4;++i)  {
        ts.pop1();
        ts.pop2();
    }
    std::cout << "Post popping 4 elements from each stack" << std::endl;
    std::cout << "Stack1 Top: " << ts.getTop1() << std::endl;
    std::cout << "Stack2 Top: " << ts.getTop2() << std::endl;

    return 0;
}
