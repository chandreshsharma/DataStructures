/***
 *
 * Program to convert a Post expression to an Infix expression.
 *
 * Algorithm:
 * The expression is read from Left to Right, cause the operands are stored at the beginning of the string
 *
 * For a operand read push it to the stack
 * When an operator is read, pop the top two elements from the stack
 *      . Create a new subexpression with "(op1 + oper + op2)"
 *      . Push this to the stack.
 * When the string has been read the stack contains the Infix form of the expresssion.
 *
***/

#include <iostream>
#include <stack>

class PostfixToInfix {

public:
    std::string convertToInfix(const std::string & postfix);

    PostfixToInfix(const std::string& prefix):_postfix(prefix){
    }   

    std::string getInfix() {
        return convertToInfix(_postfix);
    }   

    std::string getPostfix() {
        return _postfix;
    }   
protected:
    void populateInfix(const char & c); 

    std::string _postfix;
    std::string _infix;

    std::stack<std::string> _s; 
};

void PostfixToInfix::populateInfix(const char & c)
{
    if(std::isalpha(c)) { /// Push the operand to the stack
        _s.push(std::string(1,c));
    }
    else    {
        /// This is an operator, pop the two operands from the stack and create the expression
        /// 
        /// NOTE: The expression is being evaluated each character from left to right
        /// So the first operand is pushed, and then the second operand is pushed 
        /// When reading the stack the 2nd operand is above the 1st operand.

        const std::string op2 = _s.top(); _s.pop();
        const std::string op1 = _s.top(); _s.pop();
        const std::string expression = ("(" + op1 + c + op2 + ")");

        /// Push back the expression created to the stack
        _s.push(expression);
    }
}

std::string PostfixToInfix::convertToInfix(const std::string & postfix)
{
    for(const char & c: postfix)
        populateInfix(c);

    return _s.top();
}

int main()
{
    PostfixToInfix p2I1("AB*CD/+");
    std::cout << "Postfix: " << p2I1.getPostfix() << ", Infix: " << p2I1.getInfix() << std::endl;

    PostfixToInfix p2I2("ABCD/+*");
    std::cout << "Postfix: " << p2I2.getPostfix() << ", Infix: " << p2I2.getInfix() << std::endl;

    return 0;
}
