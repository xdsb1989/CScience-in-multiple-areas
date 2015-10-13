#include<stdio.h>
#include<stdlib.h>

struct note{
       char c;
       struct note *nextptr;
       };

typedef struct note * listnote;

void fun (listnote *,listnote *,char a,int count);
void printlist(listnote);
char dele(listnote *);
main()
{
      listnote startptr;
      listnote head;
      char a;
      int i=2,count=1;
      
      int num2,num3;
      float num1;
      num2=2;
      num3=3;
      scanf("%d",&num3);
      num1=(float)1/num3;
      num1=num1*11;
      
      printf("%f",num1);
      
      
      while(i!=1)
      {
          switch (i)
          {
              case 2:
              printf("input the char:");
              scanf("\n%c",&a);          
              fun(&startptr,&head,a,count);
              //printlist(startptr); 
              printlist(head);
              printf("input the flag:");
              scanf("\n%d",&i);
              count++;
              break;
              
              case 3:
              printf("the char output is:\n");
              a=dele(&head);
              printf("%c\n",a);
              printlist(head);
              printf("input the flag:");
              scanf("\n%d",&i);
              count--;
              break;
              
              default:
              break;
          }
      }

      //printlist(head); 
      system("pause");
}

char dele(listnote *head)
{
     char a;
     listnote temp;
     if (*head==NULL)
        printf("Queue is empty\n");
     else
     {
         a=(*head)->c;
         temp=*head;
         *head=(*head)->nextptr;
         //free(temp);
         return a;
     }
}

void fun(listnote *ptr,listnote *head,char a,int count)
{
         listnote newptr,current,temp; 
         newptr=(struct note*)malloc(sizeof(listnote));        
         newptr->c=a;
         if (count == 1)
         {
            *head=newptr;
            newptr->nextptr=NULL;
            *ptr=newptr;
         }

                 else
                 {
                     temp=NULL;
                     current=*head;
                     while (current!=NULL && a>current->c)
                     {
                           temp=current;
                           current=current->nextptr;
                     }
                     if (current==NULL)
                     {
                         (*ptr)->nextptr=newptr;
                         newptr->nextptr=NULL;
                         *ptr=newptr;
                         return fun(ptr,head,a,count);
                     }
                     else if(temp == NULL)
                     {
                          newptr->nextptr=*head;
                          *head=newptr;
                     }
                     else
                     {
                         temp->nextptr=newptr;
                         newptr->nextptr=current;
                     }
                 }
}

void printlist(listnote ptr)
{
     if (ptr==NULL)
          printf("list is empty.\n");
      else
      {
          while (ptr!=NULL)
          {
                printf("%c-->",ptr->c);
                ptr=ptr->nextptr;
          }
      }
}
