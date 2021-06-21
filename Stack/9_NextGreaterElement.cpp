/***
 *
 * Program to print the next greater element in a vector, using a stack
 *
 * Algorithm:
 *
 * For each element read
 *  1.  If Stack is empty push
 *  2.  If value < stack.top
 *      Push to stack.
 *  3.  Else (Stack Top is less than current element)
 *      For each stack.top < value
 *          print stack.top -> value
 *      
 *      Push 'value' to stack
 *
 *  4.  For all remaining elements in stack
 *          pring next greater element : -1 
 *
***/

#ifdef DEBUG

/***
Input:
    13, 7, 6, 10, 12

1.
    13 -> Push
2.    
    7  -> Push
3.    
    6  -> Push
    Stack |13|7|6|
4.
    10
    Now 10 > 6

    print s.top(6),(10) pop(6)
    print s.top(7),(10) pop(7)

    10 -> Push
    Stack |13|10|
5.
    12
    print s.top(10), 12 pop(10)
    12 -> Push    

6.
    Stack |13|12|
    while(!stack.empty())

    print s.top(12), -1
    print s.top(13), -1
***/
#endif

#include <iostream>
#include <vector>
#include <stack>

void printNextGreaterElement(const std::vector<int> numbers)
{
    std::stack<int> stackNums;

    for(const auto & num: numbers)
    {
        if(stackNums.empty())
        {
            stackNums.push(num);
        }
        else
        {
            while(!stackNums.empty() && (stackNums.top() < num))
            {
                std::cout << stackNums.top() << "-->" << num << std::endl;
                stackNums.pop();
            }
            stackNums.push(num);
        }
    }

    while(!stackNums.empty())   {
        std::cout << stackNums.top() << "--> -1 " << std::endl;
        stackNums.pop();
    }
}

int main()
{
    std::vector<int> nums = {13, 7, 6, 10, 12};

    printNextGreaterElement(nums);

    return 0;
}
