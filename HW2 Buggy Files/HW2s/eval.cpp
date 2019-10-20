#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

//Declarations:
string clearSpaces(string infix);
bool valid(string nsInfix);
string convertToPostfix(string nsInfix);

//Implementations:
string clearSpaces(string infix)
{
	string nsInfix = "";
    for (int i = 0; i < infix.length(); i++)// get rid of spaces
    {
    	if (infix[i] != ' ')
    		nsInfix += infix[i];
    }
    return nsInfix;
}

bool validString(string nsInfix)
{
	//			T  F  (  )  ^  &  !
    if (nsInfix[0] == '^' || nsInfix[0] == '&' ||
    nsInfix[nsInfix.length()-1] == '^' || nsInfix[nsInfix.length()-1] == '&')
    	return false; //cannot start or end with operator

    for (int i = 0; i < nsInfix.length()-1; i++)
    {
    	if (nsInfix[i] == '^' || nsInfix[i] == '&' 
    		|| nsInfix[i] == '!')// can only be followed by T,F,(,!
    	{							//cannot be the end
    		if (nsInfix[i+1] == '^'||nsInfix[i+1] == '&'||
    			nsInfix[i+1] == ')'||i+1 == nsInfix.length()-1)
    			return false;
    	}
    	
    	if (nsInfix[i] == 'T'||nsInfix[i] == 'F')// only ^,&,) can follow letter
    	{											//unless it is the end
    		if (nsInfix[i+1] != '^'||nsInfix[i+1] != '&'||nsInfix[i+1] != ')'
    			|| i+1 != nsInfix.length()-1)
				return false;
    	}
    	if (nsInfix[i] == '(')// only !,T,F follow. cannot mark end
    	{
    		if (nsInfix[i+1] != '!'||nsInfix[i+1] != 'T'||nsInfix[i+1] != 'F'
    			|| i+1 == nsInfix.length()-1)
				return false;
    	}
    	if (nsInfix[i] == ')')// only ^,& follow, unless the end
    	{
    		if (nsInfix[i+1] != '^'||nsInfix[i+1] != '&'
    			|| i+1 != nsInfix.length()-1)
				return false;
    	}
    }
    return true;
}

string convertToPostfix(string nsInfix)
{
	stack<char> charstack;
    string pf;

    int counter=0;// advances to next char in string
    int parentheses=0; //checks for unmatched parentheses

    while(counter<nsInfix.length())//go through string to make pf
    {
        char curr = nsInfix[counter];

    	// Add char to string:
        if(curr== 'T' || curr== 'F')//while stack is a character
            pf += (curr);
        else if (curr == '('){
            charstack.push(curr);
            parentheses++;

        }
        else if ((curr== '^' || curr== '&' || curr== '!') && charstack.empty())
            charstack.push(curr);//if curr is an operator, empty stack
        else if (!charstack.empty())//if curr is an operator, && stack not empty
        {
            if (curr == '!')
            {
                while(charstack.top() != '&' || charstack.top() != '^' ||
                      charstack.top() != '(' )//check precedence for !
                {
                    pf += charstack.top();
                    charstack.pop();
                }
            }
            if (curr == '&')
            {
                while(charstack.top() != '^' || charstack.top() != '(' )
                {                               //check precedence for &
                    pf += charstack.top();
                    charstack.pop();
                }
            }
            if (curr == '^')
            {
                while( charstack.top() != '(' )//check precedence for ^
                {
                    pf += charstack.top();
                    charstack.pop();
                }
            }
            charstack.push(curr);
        }
        else if (curr == ')' && parentheses != 0)
        {
            while( charstack.top() != '(' )
            {
                pf += charstack.top(); //add operators to string
                charstack.pop();
            }
            parentheses--;
            charstack.pop(); //pop off '('
        }
        counter++; //move onto next char
    }
    if (parentheses != 0) {
        return "invalid string";
    }
    while(!charstack.empty())
    {
        pf += charstack.top(); //add remaining operators to string
        charstack.pop();
    }

    if (pf.empty())
    	return "invalid string";

    return pf;
}

int evaluate(string infix, string& postfix, bool& result)
{
	string nsInfix = clearSpaces(infix);//use infix without spaces
	if (!validString(nsInfix))// check if valid string
    	return 1;
	if (convertToPostfix(nsInfix) == "invalid string")//catch bad infix
		return 1;
    postfix = convertToPostfix(nsInfix);//set postfix to Postfix
    stack<bool> boolstack;

    for (int i = 0; i < postfix.length(); i++)//add bools to stack, push off
    {										//updated bool to end with result
    	char curr = postfix[i];
    	if (curr == 'T')
    		boolstack.push(true); //push true or false
    	else if (curr == 'F')
    		boolstack.push(false);
    	else if (curr == '!')// ! appears after previous T/F, so must change it
       	{
    		bool temp = boolstack.top();
    		boolstack.pop();
    		boolstack.push(!temp);
    	}
    	else //curr is either (, ), ^, &
    	{
    		bool op2 = boolstack.top();//save most recent T/F
            boolstack.pop();
            if (boolstack.empty())//cannot be just an operator
                return 1;
            bool op1 = boolstack.top();//save second to last T/F
            boolstack.pop();
            if (curr == '^')  //curr is ^ operator
            {
                if (op1 != op2)   //true if they are opposite
                    boolstack.push(true);
                else
                    boolstack.push(false);
            }
            if (curr == '&')  //curr is & operator
            {
                if (op1 && op2)   //true if both are true
                    boolstack.push(true);
                else
                    boolstack.push(false);
            }
    	}
    }
    result = boolstack.top();
    return 0;
}

int main()
{
    string pf;
    bool answer;
    assert(evaluate("T^ F", pf, answer) == 0  &&  pf == "TF^"  &&  answer);
    assert(evaluate("T^", pf, answer) == 1);
    assert(evaluate("F F", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("()", pf, answer) == 1);
    assert(evaluate("()T", pf, answer) == 1);
    assert(evaluate("T(F^T)", pf, answer) == 1);
    assert(evaluate("T(&T)", pf, answer) == 1);
    assert(evaluate("(T&(F^F)", pf, answer) == 1);
    assert(evaluate("T|F", pf, answer) == 1);
    assert(evaluate("", pf, answer) == 1);
    assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0
           &&  pf == "FF!TF&&^"  &&  !answer);
    assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
    assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);
    cout << "Passed all tests" << endl;
}
