#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack
{	
	int capacity;
	int top;
	char *arr;
};

struct stack * create(int cap)
{
	struct stack *s;
	s=(struct stack *)malloc(sizeof(struct stack));
	s->capacity=cap;
	s->top=-1;
	s->arr=(char *)malloc(sizeof(char) * cap);

	return s;
}

void push(struct stack *s, char data)
{
	if(s->top==s->capacity-1)
	{
		printf("Overflow\n");
	}
	else
	{
		s->top+=1;
		s->arr[s->top]=data;
	}
}

char pop(struct stack *s)
{
	char data;
	if(s->top==-1)
	{
		printf("Empty\n");
	}
	data=s->arr[s->top];
	s->top-=1;
	return data;
}

int preced(char ch)
{
	if(ch=='/' || ch=='*')
	{
		return 2;
	}
	else if(ch=='+' || ch=='-')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int operands(char ch)
{
	if(ch>='a' && ch<='z'  ||  ch>='A' && ch<='Z')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int operators(char ch)
{
	if(ch=='+' || ch=='-' || ch=='*' || ch=='/')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void reverse(char *str)
{
	int len, temp;
	len=strlen(str);
	for(int i=0; i<len/2; i++)
	{
		temp=str[i];
		str[i]=str[len-i-1];
		str[len-i-1]=temp;
	}
}

char * infix_to_prefix(char * Q)
{
	char ch;
	struct stack *s;
	s=create(20);

	reverse(Q);
	char *P;
	P=malloc(sizeof(char) * (strlen(Q)+1));

	int i=0, j=0;

	while(Q[i]!='\0')
	{
		if(operands(Q[i]))
		{
			P[j]=Q[i];
			i++, j++;
		}
		else if(Q[i]==')')
		{
			push(s,Q[i]);
			i++;
		}
		else if(Q[i]=='(')
		{
			while(s->top!=-1 && s->arr[s->top]!=')')
			{
				P[j]=pop(s);
				j++;
			}
			if(s->top!=-1)
				ch=pop(s);
			i++;
		}
		else
		{
			while(s->top!=-1 && preced(Q[i])<= preced(s->arr[s->top]))
			{
				P[j]=pop(s);
				j++;
			}
			push(s,Q[i]);
			i++;
		}
	}

	while(s->top!=-1 && s->arr[s->top]!=')')
	{
		P[j]=pop(s);
		j++;
	}
	if(s->top!=-1)
		ch=pop(s);
	
	reverse(P);
	P[j]='\0';
	
	return P;
}

int main()
{
	char *exp="(A+B)";

	printf("Prefix: %s\n",infix_to_prefix(exp));
	return 0;
}