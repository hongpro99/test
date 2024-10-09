#include <iostream>
#include <stack>
#include "post.h"
using namespace std;

int GetVal(Token& opnd)
{
    if (opnd.type == NUM) return opnd.ival;
    return 0; // ID인 경우는 0을 return하자
}

Token UnaryOp(int op, Token& x)
{
    
    Token tmp; tmp.type = NUM;
    if (op == UMINUS)
    {
        tmp.ival = -GetVal(x);
    }
    else if (op == '!')
    {
        tmp.ival = !GetVal(x);
    }
    else
        throw "Invalid unary operator";
    return tmp;
}

Token BinaryOp(int op, Token& left, Token& right)
{
    if (!left.IsOperand() || !right.IsOperand())
        throw "Two Operands required for Binary Operation";
    Token tmp;
    tmp.type = NUM;
    int val1 = GetVal(left), val2 = GetVal(right);
    if (op == '+')
        tmp.ival = val1 + val2;
    else if (op == '-')
        tmp.ival = val1 - val2;
    else if (op == '*')
        tmp.ival = val1 * val2;
    else if (op == '/')
        tmp.ival = val1 / val2;
    else if (op == '%')
        tmp.ival = val1 % val2;
    else if (op == '<')
        tmp.ival = val1 < val2;
    else if (op == '>')
        tmp.ival = val1 > val2;
    else if (op == GE)
        tmp.ival = val1 >= val2;    
    else if (op == LE)
        tmp.ival = val1 <= val2;
    else if (op == EQ)
        tmp.ival = val1 == val2;
    else if (op == NE)
        tmp.ival = val1 != val2;
    else if (op == AND)
        tmp.ival = val1 && val2;
    else if (op == OR)
        tmp.ival = val1 || val2;
    else if (op == '=')
        throw "Assignment Not Yet Implemented";
    else
        throw "No such binary operator";
    return tmp;
}

Token DeleteFromStack(stack<Token>& stack)
{
    if (stack.empty()) throw "Trying to pop from an empty stack";
    Token tmp = stack.top();
    stack.pop();
    return tmp;
}

void Eval(Expression e)
{
    stack<Token> stack;
    Token opnd1, opnd2;

    for (Token x = NextToken(e, false); x != '#';
        x = NextToken(e, false))
    {
        if (x.IsOperand())
        {
            stack.push(x);
        }
        else
        {
            if (x.type == UMINUS || x.type == '!')
            {
                opnd1 = DeleteFromStack(stack);
                stack.push(UnaryOp(x.type, opnd1));
            }
            else
            {
                opnd2 = DeleteFromStack(stack);
                opnd1 = DeleteFromStack(stack);
                stack.push(BinaryOp(x.type, opnd1, opnd2));
            }
        }
    }
    cout << DeleteFromStack(stack) << endl;
}
