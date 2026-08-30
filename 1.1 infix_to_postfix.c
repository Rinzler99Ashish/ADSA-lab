#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#define max 100
char stack[max];
int top=-1;
char pop() { return stack[top--]; }
void push(char item) { stack[++top]=item; }
char peek() { return stack[top]; }

int precedence(char a)
{
    if(a=='*' || a=='/')
        return 2;
    else if(a=='+' || a=='-')
        return 1;
    return 0;
}

void infix_to_postfix(char *infix, char *postfix)
{    
    int j=0;
    for(int i=0;infix[i]!='\0';i++)
    {
        if((infix[i]>='A' && infix[i]<='Z') || (infix[i]>='a' && infix[i]<='z'))
            postfix[j++]=infix[i];
        else if(infix[i]=='(')
            push('(');
        else if(infix[i]==')')
        {
            while(top!=-1 && peek()!='(')
                postfix[j++]=pop();   
            pop();
        }
        else
        {
            while(top!=-1 && peek()!='(' && precedence(peek()) >= precedence(infix[i]))
                postfix[j++]=pop();
            push(infix[i]);
        }
    }
    while(top!=-1)
        postfix[j++]=pop();
    postfix[j]='\0';
}
int main()
{
    char infix[max],postfix[max];
    printf("Enter: ");
    scanf("%s",infix);
    infix_to_postfix(infix,postfix);
    printf("%s",postfix);
}