/***
 * Program to convert an Infix expression to a Postfix expression.
 *
 * When reading the expression from left to right.
 *      1.  Print the operand
 *      2.  Push the operator to the stack if the precedence of the operator is greater than that at the top of the stack.
 *      Else
 *          Pop all operators with precedence less than or equal to the operator read.
***/

#include <iostream>
#include <stack>

class InfixToPostfix    {   

public:
    InfixToPostfix(const std::string & infix);   
    std::string getPostfix();

    inline std::string getInfix() const {
        return _infix;
    }   

protected:
    int getPrecedence(const char & op);

    std::string _infix;
    std::stack<char> s;
};

InfixToPostfix::InfixToPostfix(const std::string & infix):_infix(infix){
}

int InfixToPostfix::getPrecedence(const char & op) 
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

std::string InfixToPostfix::getPostfix()
{
    std::string postfix("");

    for(unsigned long int i=0; i<_infix.length(); ++i)
    {
        const char c = _infix.at(i);

        if(c == '(') {
            s.push(c);
        }
        /// If character read is a closing brace, pop all elements till an opening brace is found.    
        else if(c == ')') {
            while(s.top() != '(')
            {
                postfix += s.top();
                s.pop();
            }
            /// pop the opening brace.
            s.pop();
        }
        /// If this is an operand, add to the postfix string
        else if(std::isalpha(c))    {
            postfix += c;
        }
        /// Check the precedence of the operator and either push or pop previously pushed operators.
        else if(s.empty() ||
                getPrecedence(c) > getPrecedence(s.top()))
            s.push(c);
        else
        {
            /// If the precedence of the operator pushed is equal to the current operator
            /// the pushed operator would be the first in the expression sequence, being read first.
            /// Hence the check for < and =
            while(!s.empty() &&
                    getPrecedence(c) <= getPrecedence(s.top()))
            {
                postfix += s.top();
                s.pop();
            }
            s.push(c);
        }
    }

    while(!s.empty())
    {
        postfix+=s.top();
        s.pop();
    }

    return postfix;
}

#ifdef DEBUG

a+b*(c^d-e)^(f+g*h)-i

Stack:      +, +*, +*(, +*(^,
Postfix:    a, ab, ab, abc, abcd

#endif

int main()
{
    InfixToPostfix i2p("a+b*c");
    std::cout << "Postfix expression: " << i2p.getPostfix() << " for infix:" << i2p.getInfix() << std::endl;

    InfixToPostfix i2p1("a*b+c");
    std::cout << "Postfix expression: " << i2p1.getPostfix() << " for infix:" << i2p1.getInfix() << std::endl;

    InfixToPostfix i2p2("a+b*(c^d-e)^(f+g*h)-i");
    std::cout << "Postfix expression: " << i2p2.getPostfix() << " for infix:" << i2p2.getInfix() << std::endl;

    InfixToPostfix i2p3("(a*(b+(c/d)))");
    std::cout << "Postfix expression: " << i2p3.getPostfix() << " for infix:" << i2p3.getInfix() << std::endl;
    
    return 0;
}
