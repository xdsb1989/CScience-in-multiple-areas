#include<stdio.h>
#include<stdlib.h>

struct link{
       int child;
       struct link *next;
       struct link *previous;
}list[10];

typedef struct link *Link;

main()
{
      Link head,start,temp,temp1;
      int i,j=1;
      
      //typedef struct link *list;
      
      i=1;
      int a;
      //head=malloc(sizeof(Link)); 
      //start=malloc(sizeof(Link)); 
      head=malloc(sizeof(Link));
      
      printf("input the first note:\n");
      scanf("%d",&a);
      list[0].child=a;
      list[0].next=NULL;
      list[0].previous=NULL;
      //start->child=a;
      //start->next=NULL;
      start=&list[0];
      head=start;
      printf("input the flag:\n");
      scanf("%d",&i);
      while(i!=0)
      {
          Link newptr;
          printf("input the note:\n");
          scanf("%d",&a);
          newptr=malloc(sizeof(struct link)); 
          newptr->child=a;
          newptr->next=NULL;
          
          newptr->previous=start;
          start->next=newptr;          
          start=newptr;
          printf("input the flag:\n");
          scanf("%d",&i);
          }
      temp=&list[0];
      while(temp!=NULL)
      {
          printf("%d ->",temp->child);
          temp1=temp;
          temp=temp->next;
      }
      //temp=temp->previous;
      
      
      while(temp1!=NULL)
      {
          printf("%d ->",temp1->child);
          temp1=temp1->previous;
      }
      
      system("pause");    

}
