/***
 *
 * A program to verify if the parenthesis are balanced
 *
***/

#include <iostream>
#include <stack>

bool isParenthesisBalanced(const std::string & expr)
{   
    std::stack<char> parenStack;
    
    for(const char & c: expr)
    {   
        /// Push the opening parenthesis to the stack
        if(c == '(' || c == '{' || c == '[')
        {   
            parenStack.push(c);
        }
        else
        {   
            if(parenStack.empty())
                return false;
            else
            {   
                /// Read the top of the stack and compare to the char read
                if( parenStack.top() == '(' && c != ')' ||
                    parenStack.top() == '{' && c != '}' ||
                    parenStack.top() == '[' && c != ']'
                  ) 
                {   
                    return false;
                }
                else /// pop the opening parenthesis from the stack
                {   
                    parenStack.pop();
                }
            }
        }
    }

    return (parenStack.empty());
}

int main()
{
    const std::string expr1 = "{{[](){}}}";
    std::cout << "expresssion: " << expr1 << ", balanced: " << std::boolalpha << isParenthesisBalanced(expr1) << std::endl;

    const std::string expr2 = "{{](){}}}";
    std::cout << "expresssion: " << expr2 << ", balanced: " << std::boolalpha << isParenthesisBalanced(expr2) << std::endl;

    const std::string expr3 = "{{[]()";
    std::cout << "expresssion: " << expr3 << ", balanced: " << std::boolalpha << isParenthesisBalanced(expr3) << std::endl;

    const std::string expr4 = "[]()}}";
    std::cout << "expresssion: " << expr4 << ", balanced: " << std::boolalpha << isParenthesisBalanced(expr4) << std::endl;

    const std::string expr5 = "{{[";
    std::cout << "expresssion: " << expr5 << ", balanced: " << std::boolalpha << isParenthesisBalanced(expr5) << std::endl;

    return 0;
}
