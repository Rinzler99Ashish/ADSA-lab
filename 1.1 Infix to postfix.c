#include<stdio.h>
#include <stdbool.h>
#define max 100

char stack[max];
int top=-1;

void push(char ch)
{
    if(top>=max-1)
        printf("Stack Overflow\n");
    else
        stack[++top]=ch;
}
char pop()
{
    if(top==-1)
    {
        printf("Stack Underflow\n");
        return '\0';
    }
    else
        return stack[top--];
}

char peek()
{
    if(top==-1)
    {
        printf("Stack is empty\n");
        return '\0';
    }
    else    
        return stack[top]; 
}

int precedence(char ch)
{
    if(ch=='*' || ch=='/')
        return 2;
    else if(ch=='+' || ch=='-')
        return 1;
    return 0;
}

void post_fix(char infix[],char postfix[])
{
    int j=0;
    for(int i=0;infix[i]!='\0';i++)
    {
        char ch=infix[i];

        if(ch>='0' && ch<='9')
            postfix[j++]=ch;
        else if(ch=='(')
            push(ch);
        else if(ch==')')
        {
            while(peek()!='(')
                postfix[j++]=pop();
            pop();
        }
        else
        {
            while(top!=-1 && peek()!='(' && precedence(peek())>=precedence(ch))
                postfix[j++]=pop();
            push(ch);
        }
    }
    while (top!=-1)
        postfix[j++]=pop();
    postfix[j]='\0';
}

int main()
{
    char infix[max],postfix[max];
    printf("Enter infix expression: ");
    scanf("%s",infix);

    post_fix(infix,postfix);
    printf("%s",postfix);
    
}