/***
 * A program to evalaute an expression passed as a string
 *
 * Algorithm:
 * The algorithm follows the same steps as to convert from a Infix to a Postfix expression.
 *
 * For each character read
 * 1. If its a digit insert in the numbers stack
 * 2. If its an open parenthesis '(' insert in operator stack
 * 3. If its an operator
 *    check if the precedence is greater than operator stack.top
 *    If yes
 *       push operator to operator stack
 *    else
 *       while stack not empty and precedence (stack.top) >= precedence(token)
 *         read the two numbers
 *         read the operator
 *         calculate the new number
 *         insert new number to stack.
 * 4. If its a closing brace ')'
 *    while stack.top() is not equal to '(' opening brace.
 *         read the two numbers
 *         read the operator
 *         calculate the new number
 *         insert new number to stack.
 *
 *
***/

#include <iostream>
#include <stack>

constexpr int getNum(char c) { return(c - '0'); }

int getValue(const char & op1, const char & op2, const char & oper)
{
    switch(oper)
    {   
        case '+':
            return getNum(op1) + getNum(op2);
        case '-':
            return getNum(op1) - getNum(op2);
        case '*':
            return getNum(op1) * getNum(op2);
        case '/':
            return getNum(op1) / getNum(op2);
    }

    return  std::numeric_limits<int>::max();
}

int getPrecedence(const char & op)
{
    switch(op)
    {
        case '^':
            return 3;
        case '/':
        case '*':
            return 2;
        case '+':
        case '-':
            return 1;
        /// The open parenthesis doesn't have a precedence, however since its maintained in the stack
        /// we set it to the lowest precedence.
        /// The ( is pushed so that when a closing parenthesis is read, all operators between the closing
        /// and the opening parenthesis are added to the expression.    
        case '(':
            return -1;
    }

    return -1;
}

int evaluateExpression(const std::string & expression)
{
    using charStack = std::stack<char>;
    charStack stackNum;
    charStack stackOper;

    auto calcAndPushNum = [] (charStack & stackN, charStack & stackOp)
    {
        /// Pop the two operands and apply the operator
        const char op2 = stackN.top(); stackN.pop();
        const char op1 = stackN.top(); stackN.pop();
        const char oper = stackOp.top(); stackOp.pop();

        char value = '0' + getValue(op1, op2, oper);
        stackN.push(value);
    };
  
    for(const char & token: expression)
    {
        if(std::isspace(token))
            continue;

        if(std::isdigit(token))
        {
            stackNum.push(token);
        }
        else if (stackOper.empty() || token == '(')
        {
            stackOper.push(token);
        }
        else if(token == ')')   /// This is a closing brace
        {
            /// While an opening brace is not encountered, calculate the value of the entire expression.
            /// Insert it back to the stack
            while(stackOper.top() != '(')
            {
                calcAndPushNum(stackNum, stackOper);
            }
            stackOper.pop();    /// pop the '('
        }
        else    /// this is an operator
        {
            /// If operator's precedence is greater than the stack's top insert.
            if(!stackOper.empty() &&
                (getPrecedence(token) > getPrecedence(stackOper.top()))
              )
            {
               stackOper.push(token);
            }
            /// Pop the operands and the operator and calculate the value
            else
            {
                while(!stackOper.empty() &&
                      getPrecedence(stackOper.top() <= getPrecedence(token)))
                {
                    calcAndPushNum(stackNum, stackOper);
                }
                stackOper.push(token);
            }
        }
    }

    while(!stackOper.empty())
    {
        calcAndPushNum(stackNum, stackOper);
    }

    int val = stackNum.top() - '0'; stackNum.pop();
    return val;
}

int main()
{
    std::cout << "expression(3 + 2 * 5) value: " << evaluateExpression("3 + 2 * 5") << std::endl;
    std::cout << "expression(9 + 2 * 6) value: " << evaluateExpression("9 + 2 * 6") << std::endl;
    std::cout << "expression(7 * 2 + 5) value: " << evaluateExpression("7 * 2 + 5") << std::endl;
    std::cout << "expression(5 * ( 2 + 2 )) value: " << evaluateExpression("5 * ( 2 + 2 )") << std::endl;
    std::cout << "expression(9 * ( 2 + 2 ) / 4) value: " << evaluateExpression("9 * ( 2 + 2 ) / 4") << std::endl;

    return 0;
}
