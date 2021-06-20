/***
 *
 * Program to convert a Prefix expression to an Infix expression.
 *
 * Algorithm:
 * The expression is read from Right to left, cause the operands are stored at the end of the string
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

class PrefixToInfix {

public:
    std::string convertToInfix(const std::string & prefix);
    
    PrefixToInfix(const std::string& prefix):_prefix(prefix){
    }
    
    std::string getInfix() {
        return convertToInfix(_prefix);
    }
    
    std::string getPrefix() {
        return _prefix;
    }
protected:
    void populateInfix(const char & c);
  
    std::string _prefix;
    std::string _infix;
    
    std::stack<std::string> _s;
};

void PrefixToInfix::populateInfix(const char & c)
{
///    std::cout << "c: " << c << std::endl;

    if(std::isalpha(c)) { /// Push the alphabet to the stack
        _s.push(std::string(1,c));
    }
    else    {
        /// This is an operator, pop the two operands from the stack and create the expression
        /// 
        /// NOTE: The expression is being evaluated each character from right to left
        /// So the second operand is pushed, and then the first operand is pushed 
        /// When reading the stack the 1st operand is above the 2nd operand.

        const std::string op1 = _s.top(); _s.pop();
        const std::string op2 = _s.top(); _s.pop();
        const std::string expression = ("(" + op1 + c + op2 + ")");

        /// Push back the expression created to the stack
        _s.push(expression);
    }
}

std::string PrefixToInfix::convertToInfix(const std::string & prefix)
{
    /// For a prefix expression, read from right to left evaluating each character.

    ///std::for_each(prefix.rbegin(), prefix.rend(), PrefixToInfix::populateInfix);
    for(auto it=prefix.rbegin(); it != prefix.rend(); ++it)
        populateInfix(*it);

    return _s.top();
}

int main()
{
    PrefixToInfix pre2In1("*A+B/CD");
    std::cout << "Prefix: " << pre2In1.getPrefix() << ", Infix: " << pre2In1.getInfix() << std::endl;

    PrefixToInfix pre2In2("/*A+BCD");
    std::cout << "Prefix: " << pre2In2.getPrefix() << ", Infix: " << pre2In2.getInfix() << std::endl;

    return 0;
}
