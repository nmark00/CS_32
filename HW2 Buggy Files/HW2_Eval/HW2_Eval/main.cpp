#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

//Declarations:
string clearSpaces(string infix);
bool valid(string nsInfix);
int precedence(char curr);
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
    //    T  F  (  )  ^  &  !
    if (nsInfix[0] == '^' || nsInfix[0] == '&' ||
        nsInfix[nsInfix.length()-1] == '^' || nsInfix[nsInfix.length()-1] == '&')
        return false; //cannot start or end with operator
    
    for (int i = 0; i < nsInfix.length()-1; i++)
    {
        if (nsInfix[i] == '^' || nsInfix[i] == '&'
            || nsInfix[i] == '!')// can only be followed by T,F,(,!
        {                            //cannot be the end
            if (nsInfix[i+1] == '^'||nsInfix[i+1] == '&'||
                nsInfix[i+1] == ')'||i+1 == nsInfix.length())
            {
                //cerr<<"failed operator"<<endl;
                return false;
            }
        }
        
        if (nsInfix[i] == 'T'||nsInfix[i] == 'F')// only ^,&,) can follow letter
        {                                            //unless it is the end
            if (nsInfix[i+1] == '^'||nsInfix[i+1] == '&'||nsInfix[i+1] == ')'
                || i == nsInfix.length()-1) { continue; }
            else
            {
                //cerr<<"failed T/F"<<endl;
                return false;
            }
        }
        if (nsInfix[i] == '(')// only !,T,F,( follow. cannot mark end
        {
            if (nsInfix[i+1] == '!'||nsInfix[i+1] == 'T'||nsInfix[i+1] == 'F'
                 ||nsInfix[i+1] == '(') { continue; }
            else
            {
                //cerr<<"failed '('"<<endl;
                return false;
            }
        }
        if (nsInfix[i] == ')')// only ^,&,) follow, unless the end
        {
            if (nsInfix[i+1] == '^'||nsInfix[i+1] == '&'
                || i+1 == nsInfix.length()||nsInfix[i+1] == ')'){ continue; }
            else
            {
                //cerr<<"failed ')'"<<endl;
                return false;
            }
        }
    }
    return true;
}

int precedence(char curr)
{
    switch (curr)
    {
        case '!':       //! has highest precedence
            return 2;
        case '&':       //& 2nd precedence
            return 1;
        case '^':
            return 0;   // last precedence
        default:
            return -1;
    }
}

string convertToPostfix(string nsInfix)
{
    stack<char> charstack;
    string pf = "";
    
    int counter=0;// advances to next char in string
    int parentheses=0; //checks for unmatched parentheses
    
    while(counter<nsInfix.length())//go through string to make pf
    {
        char curr = nsInfix[counter];
        
        // Add char to string:
        if(curr== 'T' || curr== 'F')//while stack is a character
            pf += (curr);
        else if (curr == '(')//always push (
        {
            charstack.push(curr);
            parentheses++;
        }
        else if (curr == ')' && parentheses > 0)//should have ( already
        {
            while( charstack.top() != '(' && !charstack.empty())
            {
                pf += charstack.top(); //add operators to string
                charstack.pop();
            }
            parentheses--;
            charstack.pop(); //pop off '('
        }
        else if (curr== '^' || curr== '&' || curr== '!')
        {
            while (!charstack.empty() && charstack.top() != '(' &&
                   precedence(curr) <= precedence(charstack.top()))
            {
                pf += charstack.top();
                charstack.pop();
            }
            charstack.push(curr);
        }
        counter++; //move onto next char
    }//end of while loop
    
    if (parentheses != 0)//must have matching ( )
        return "invalid string";
    
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
    {                                        //updated bool to end with result
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
    
    assert(evaluate("T^ F", pf, answer) == 0 &&  pf == "TF^"  &&  answer );
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
    //cout << "Passed all tests" << endl;
}
