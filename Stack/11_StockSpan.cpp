/***
 *
 * A program to implement the Stock Span problem
 *
 * The stock span is to calculate the number of consequtive days for which the price of the stock has risen.
 * OR
 * The span for on a given day i is defined as the maximum number of consecutive days,
 * for which the price of the stock on the current day is less than or equal to its price on the given day.
 *
***/

#include <iostream>
#include <vector>
#include <stack>

void calculateSpan(const std::vector<int> & price, std::vector<int> & span)
{   
    std::stack<int> stackPriceIdx;
    
    /// The first day price doesn't have any price to compare, initialize the stack day 1 index;
    stackPriceIdx.push(0);
    span[0] = 1;  /// Day 1 span is 1
    
    for(int index = 1; index < price.size(); ++ index)
    {   
        /// While the top index is less than the current price, check the price at the next top index.
        /// Pop and continue
        /// This gives us the span for the current days price.
        
        while(!stackPriceIdx.empty() && price[stackPriceIdx.top()] <= price[index])
            stackPriceIdx.pop();
        
        /// Now all the indexes with values less than or equal to the current days price(and index) have been popped
        /// At this stage either the stack is empty (all the prices from the first day are less than the current day's price)
        /// OR some days price(and index) have been reached.
        ///
        /// So the new span would be the difference between the top's index OR the empty stack
        
        span[index] = (stackPriceIdx.empty() ? (index + 1) : index - stackPriceIdx.top());
        
        /// Push the current index
        stackPriceIdx.push(index);
    }
}

void printSpan(const std::vector<int> & span)
{
    for(int i=0; i<span.size(); ++i)  {
        std::cout << "span[" << i << "]:" << span[i] << std::endl;
    }
}

int main()
{
    std::vector<int> price{100, 24, 25, 90, 120, 70};
    std::vector<int> span(price.size(),1);

    calculateSpan(price, span);
    printSpan(span);

    return 0;
}
