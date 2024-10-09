//B911208 È«¼®¹®

#include <iostream>
#include "post.h"
using namespace std;

void Eval(Expression e);

int main(void)
{
    char line[MAXLEN];
    while (cin.getline(line, MAXLEN))
    {
        Expression e(line); // Assume postfix notation
        try
        {
            Eval(e);

        }
        catch (char const* msg)
        {
            cerr << "Exception: " << msg << endl;
        }
    }
}
