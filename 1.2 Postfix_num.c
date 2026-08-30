#include<stdio.h>
#include <string.h>
#include <stdlib.h>

#define max 100

char stack[max];
int top=-1;

char pop()
{
    return stack[top--];
}

void push(char item)
{
    stack[++top]=item;
}

char peek()
{
    return stack[top];
}

int sstack[max];
int ttop=-1;
int ppop()
{
    return sstack[ttop--];
}
void ppush(int item)
{
    sstack[++ttop]=item;
}
int ppeek()
{
    return sstack[ttop];
}

int precedence(char a)
{
    if(a=='*' || a=='/')
        return 2;
    else if(a=='+' || a=='-')
        return 1;
    
    return 0;
}

void find_digit(int *digit, char *infix)
{
    int a=0, k=0, j=0, n=strlen(infix),seen = 0;
    char ret[max];
    
    for(int i=0;infix[i]!='\0';i++)
    {
        if(infix[i]>='0' && infix[i]<='9')
        {
            a=(a*10)+(infix[i]-'0');
            seen = 1;
        }
        else
        {
            if(seen)
            {
                digit[k++]=a;
                ret[j++]='A';
                a=0;
                seen=0;
            }
            ret[j++]=infix[i];        
        }
    }
    if(seen)
    {
        digit[k++]=a;
        ret[j++]='A';
    }
    ret[j]='\0';
    strcpy(infix,ret);
    digit[k]=-1;
}

void infix_to_postfix(char *infix, char *postfix)
{    
    int j=0;
    for(int i=0;infix[i]!='\0';i++)
    {
        if(infix[i]>='A')
            postfix[j++]='A';
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
    
    int digit[max];
    find_digit(digit,infix);


    infix_to_postfix(infix,postfix);
    
    int w=0,ans=0,temp;
    printf("%s\n",postfix);

    for(int i=0;postfix[i]!='\0';i++)
    {
        if(postfix[i]=='A')
            ppush(digit[w++]);
        else
        {
            int a=ppop();
            int b=ppop();
            if(postfix[i]=='*')
                ppush(b*a);
            else if(postfix[i]=='/')
                ppush(b/a);
            else if(postfix[i]=='-')
                ppush(b-a);
            else if(postfix[i]=='+')
                ppush(b+a);
        }
    }
    printf("%d",ppop());
}