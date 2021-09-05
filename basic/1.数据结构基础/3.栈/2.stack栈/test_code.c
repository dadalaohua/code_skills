#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define MAXSIZE 10

int stack[MAXSIZE];
int Top=-1;

/************************************************************************/
/*                                                                      */
/************************************************************************/
void push(void)
{
    int item;
    if(Top == MAXSIZE - 1)
    {
        printf("\nThe Stack Is Full");
        exit(0);
    }
    else
    {
        printf("Enter the element to be inserted ");
        scanf("%d",&item);
        Top= Top+1;
        stack[Top] = item;
    }
}

int pop(void)
{
    int item;
    if(Top == -1)
    {
        printf("The stack is Empty");
        exit(0);
    }
    else
    {
        item = stack[Top];
        Top = Top-1;
    }
    return(item);
}

void traverse(void)
{
    int i;
    if(Top == -1)
    {
        printf("The Stack is Empty");
        exit(0);
    }
    else
    {
        for(i=Top;i>=0;i--)
        {
            printf("Traverse the element ");
            printf("%d\n",stack[i]);
        }
    }
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int choice;
    char ch;
    do
    {
        printf("\n1. PUSH ");
        printf("\n2. POP ");
        printf("\n3. TRAVERSE ");
        printf("\nEnter your choice ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1: push();
                break;
            case 2: printf("\nThe deleted element is %d ",pop());
                break;
            case 3: traverse();
                break;
            default: printf("\nYou Entered Wrong Choice");
        }
        printf("\nDo You Wish To Continue (Y/N)");
        fflush(stdin);
        scanf("%c",&ch);
        scanf("%c",&ch);
        //printf("\nch %c", ch);
    }while(ch=='Y' || ch=='y');
    
    printf("\n");
    
    return 0;
}