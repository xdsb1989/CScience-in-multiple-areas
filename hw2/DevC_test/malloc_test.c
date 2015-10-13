#include<stdio.h>
#include<stdlib.h>

struct link{
       int child;
       struct link *next;
};
typedef struct link * Link,link1;

struct firstnote{
       int A;
       struct link *nextlink;
};

struct queue{
       int note;
       int level;
       struct queue *nextnote;
};
typedef struct queue * line,queue1;

main()
{
      int num;
      //int *array;
      printf("input the number of notes: ");
      scanf("%d",&num);
      struct firstnote *list;
      
      //typedef struct link link1;
      //array=malloc(num*sizeof(int));
      list=malloc(sizeof(struct firstnote)*num);//动态申请N行链表 
      
      int i=0,a;
      
      while(i<num)
      {
          int flag=1;
          Link newptr,current;
          //head=malloc(sizeof(Link));
          current=malloc(sizeof(link1));
          printf("input the first note:\n");
          scanf("%d",&a);
          list[i].A=a;
          list[i].nextlink=current;
          //current=head;
          printf("input the second note:\n");
          scanf("%d",&a);
          current->child=a;
          current->next=NULL;
          printf("input the flag:");
          scanf("%d",&flag);
          while(flag!=0)
          {
              newptr=malloc(sizeof(link1));
              if (newptr==NULL)
                   break;
              printf("input the next note:\n");
              scanf("%d",&a);
              newptr->child=a;
              current->next=newptr;
              newptr->next=NULL;
              current=newptr;
              printf("input the flag:");
              scanf("%d",&flag);
              //free(newptr);
              newptr=NULL;
              //free(newptr);
          }
          i++;
          current=NULL;
          //free(current);
          
      }
      for (i=0;i<num;i++)
      {
          Link temp1;
          printf("\n note %d has these notes",list[i].A);
          temp1=list[i].nextlink;
          while(temp1!=NULL)
          {
              printf("%d ->",temp1->child);
              temp1=temp1->next;
              if (temp1==NULL)
                 printf("\n");
          }
      }
      
      
      int sum[100]={0};
      i=0;
      //typedef struct queue queue1;
      while(i<num)//每个点都进行计算 
      {
          int number=1; 
          line head,present,new_ptr,Newptr;;//queue的链表 
          Link temp2;//
          
          temp2=list[i].nextlink;//获取第i行的第一个数据  
          present=malloc(sizeof(queue1)); //current用来组织queue链表 
          present->note = temp2->child;
          present->level=1;
          temp2=temp2->next;
          present->nextnote=NULL;
          head=present;
          while (temp2!=NULL)
          {
                new_ptr=malloc(sizeof(queue1));
                if (new_ptr==NULL)
                   break;
                new_ptr->note=temp2->child;
                new_ptr->level=1;
                present->nextnote=new_ptr;
                new_ptr->nextnote=NULL;
                present=new_ptr;//current作为queue的节点，head作为queue的头节点，始终贯穿整个流程 
                
                temp2=temp2->next;
                number++;//总个数加1
                //free(new_ptr);
                new_ptr=NULL;
                //free(new_ptr);
          }
          //free(temp2);
          sum[i]=number*1;
          if (number<num-1)
          {
              line head1;//head1,指向queue当前的第一个元素,代表即将要抛出的元素 
              head1=head;
              while (number<num-1)
              {
                  int j;
                  for (j=0;j<num;j++)//for循环为了找到list[j]， 
                      if (head1->note == list[j].A)
                         break;
                  Link temp3;//Link代表每一个子链表类型，temp3代表子链表的“第一个数据” 
                  temp3=list[j].nextlink;        
                  while (temp3!=NULL&&number<num-1)//当temp3循环结束后，head1就要向queue队列后移一位 
                  {
                        line scan;//用scan作为一个指针，遍历所有已经纳入队列的点，包括抛出的点 
                        scan=head;                       
                        while(scan!=NULL)//判断temp3的child是否和已经存在的queue队列的节点重复 
                        {
                            if(temp3->child==scan->note)
                                break;
                            scan=scan->nextnote;    
                        }
                        if (scan==NULL && temp3->child!=list[i].A)//如果不重复，将此点纳入queue队列 
                        {
                            line Newptr;
                            Newptr=malloc(sizeof(queue1));
                            if (Newptr==NULL)
                               break;
                            Newptr->note=temp3->child;
                            Newptr->level=head1->level+1;//即将加入的点的度数等于即将抛出的点的度数加1 
                            Newptr->nextnote=NULL;
                            present->nextnote=Newptr;
                            present=Newptr;
                            sum[i]=sum[i]+present->level;
                            number++;//number加1表示又有一个新节点纳入queue，当number数量等于num-1时，该次循环终止
                            
                            //Newptr=NULL;
                            //free(Newptr);
                            Newptr=NULL;
                        }
                        temp3=temp3->next;
                  }//如果该循环结束了，就代表该把queue的第一个元素排除，并移到下一个元素 
                  head1=head1->nextnote;//头节点向后移一位                  
              }//该循环结束就意味着第i个节点的所有最短路径已经得到                           
          }
          i++;
          //free(present);
          present=NULL;
          //free(present);          
      }//循环结束，也就意味着sum[i]存储了所有节点的最短路径值
      //free(list);
      list=NULL;
      int k;
      for (k=0;k<num;k++)
      {
          printf("%d   ",sum[k]);
      }
      scanf("%d",&k);
      printf("%d",k);
      system("pause");
}
