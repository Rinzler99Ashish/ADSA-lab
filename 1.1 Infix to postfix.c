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

bool validity(char *infix)
{
    int n=strlen(infix);
    for(int i=0;i<n-1;i++)
        if((infix[i]>='0' && infix[i]<='9')&&(infix[i+1]>='0' && infix[i+1]<='9'))
            return false;

    for(int i=0;i<n;i++)
    {
        char ch=infix[i];
        if(!(ch=='+' || ch=='-' ||ch=='/' ||ch=='*' ||ch=='(' ||ch==')' || (ch>='0' && ch<='9')))
            return false;
    }

    int c=0;
    for(int i=0;i<n;i++)
    {
        char ch=infix[i];
        if(ch=='(')
            c++;
        else if(ch==')')
            c--;
        if(c<0 || ((i==n-1) && (c!=0)))
            return false;
    }
    return true;
}

int main()
{
    char infix[max],postfix[max];
    printf("Enter infix expression: ");
    scanf("%s",infix);

    if(validity(infix))
    { 
        post_fix(infix,postfix);
        printf("%s",postfix);
    }
    else
    {
        printf("Invalid Input\nEnter only '+, '-', '/', '*', '(', ')' and single digits constant");
    }
}