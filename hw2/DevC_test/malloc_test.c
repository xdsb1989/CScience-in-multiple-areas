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
      list=malloc(sizeof(struct firstnote)*num);//��̬����N������ 
      
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
      while(i<num)//ÿ���㶼���м��� 
      {
          int number=1; 
          line head,present,new_ptr,Newptr;;//queue������ 
          Link temp2;//
          
          temp2=list[i].nextlink;//��ȡ��i�еĵ�һ������  
          present=malloc(sizeof(queue1)); //current������֯queue���� 
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
                present=new_ptr;//current��Ϊqueue�Ľڵ㣬head��Ϊqueue��ͷ�ڵ㣬ʼ�չᴩ�������� 
                
                temp2=temp2->next;
                number++;//�ܸ�����1
                //free(new_ptr);
                new_ptr=NULL;
                //free(new_ptr);
          }
          //free(temp2);
          sum[i]=number*1;
          if (number<num-1)
          {
              line head1;//head1,ָ��queue��ǰ�ĵ�һ��Ԫ��,������Ҫ�׳���Ԫ�� 
              head1=head;
              while (number<num-1)
              {
                  int j;
                  for (j=0;j<num;j++)//forѭ��Ϊ���ҵ�list[j]�� 
                      if (head1->note == list[j].A)
                         break;
                  Link temp3;//Link����ÿһ�����������ͣ�temp3����������ġ���һ�����ݡ� 
                  temp3=list[j].nextlink;        
                  while (temp3!=NULL&&number<num-1)//��temp3ѭ��������head1��Ҫ��queue���к���һλ 
                  {
                        line scan;//��scan��Ϊһ��ָ�룬���������Ѿ�������еĵ㣬�����׳��ĵ� 
                        scan=head;                       
                        while(scan!=NULL)//�ж�temp3��child�Ƿ���Ѿ����ڵ�queue���еĽڵ��ظ� 
                        {
                            if(temp3->child==scan->note)
                                break;
                            scan=scan->nextnote;    
                        }
                        if (scan==NULL && temp3->child!=list[i].A)//������ظ������˵�����queue���� 
                        {
                            line Newptr;
                            Newptr=malloc(sizeof(queue1));
                            if (Newptr==NULL)
                               break;
                            Newptr->note=temp3->child;
                            Newptr->level=head1->level+1;//��������ĵ�Ķ������ڼ����׳��ĵ�Ķ�����1 
                            Newptr->nextnote=NULL;
                            present->nextnote=Newptr;
                            present=Newptr;
                            sum[i]=sum[i]+present->level;
                            number++;//number��1��ʾ����һ���½ڵ�����queue����number��������num-1ʱ���ô�ѭ����ֹ
                            
                            //Newptr=NULL;
                            //free(Newptr);
                            Newptr=NULL;
                        }
                        temp3=temp3->next;
                  }//�����ѭ�������ˣ��ʹ���ð�queue�ĵ�һ��Ԫ���ų������Ƶ���һ��Ԫ�� 
                  head1=head1->nextnote;//ͷ�ڵ������һλ                  
              }//��ѭ����������ζ�ŵ�i���ڵ���������·���Ѿ��õ�                           
          }
          i++;
          //free(present);
          present=NULL;
          //free(present);          
      }//ѭ��������Ҳ����ζ��sum[i]�洢�����нڵ�����·��ֵ
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
