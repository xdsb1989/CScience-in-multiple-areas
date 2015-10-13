#include<stdio.h>
#include<stdlib.h>
#include <string.h>

struct people_card{
       char name[10];
       int ID;
       struct people_card *next_people;
};
typedef struct people_card  *people_link;

int main()
{
      FILE *f;
      char ch1[30][10]={0};
      char ch2[30][10]={0};

      f=fopen("toy-graph.txt","r");
      
      int i=0;
      while(!feof(f))
      {
        fscanf(f,"%s %s\n",&ch1[i],&ch2[i]);
        printf("%s,%s\n",ch1[i],ch2[i]);
        i++;
      }
      printf("%d\n",i);//iΪһ��������
       
      struct people_card *people_list;
      people_list=malloc(sizeof(struct people_card)*(i+1));//��������������Ŀռ����Ӧ��Ϊi+1 
      
      int lines;
      int people_num=1;//������1��ʼ 
    
      for (lines=0;lines<i;lines++)
      {
          if (lines==0)//�տ�ʼʱ���ȸ�ֵ�����˽������� 
          {
             strcpy(people_list[people_num].name,ch1[lines]);
             people_list[people_num].ID=people_num;
             strcpy(people_list[people_num+1].name,ch2[lines]);
             people_list[people_num+1].ID=people_num+1;
             
             people_num=people_num+2;
          }
          else
          {
              int mark; 
              for (mark=1;mark<people_num;mark++)//�������е�������������ظ����ͼ��������� 
                  if (strcmp(people_list[mark].name,ch1[lines])==0)
                     break; 
              if (mark==people_num)
              {
                  strcpy(people_list[people_num].name,ch1[lines]);
                  people_list[people_num].ID=people_num;
                  people_num++;
                  }
              for (mark=1;mark<people_num;mark++)
                  if (strcmp(people_list[mark].name,ch2[lines])==0)
                     break;
              if (mark==people_num)
              {
                  strcpy(people_list[people_num].name,ch2[lines]);
                  people_list[people_num].ID=people_num;
                  people_num++;
                  } 
          }
      }
      int label;
      for (label=1;label<people_num;label++)
      {
          printf("%d\t%s\n",people_list[label].ID,people_list[label].name);
          }
      int j;
      
      for (j=1;j<people_num;j++)//ÿ���˲���,��ʼ��������ṹ 
      {
          int k;
          people_link newptr,current;
          
          people_list[j].next_people=NULL; 
          current=&people_list[j];
          
          for (k=0;k<i;k++)//ÿһ�в��� 
          {
              if (strcmp(people_list[j].name,ch1[k])==0)
              {    
                  newptr=malloc(sizeof(struct people_card));
                  strcpy(newptr->name,ch2[k]);
                  
                  int n=1;
                  while(strcmp(ch2[k],people_list[n].name)!=0)//��children��ID 
                  {
                      n++;
                  }
                  newptr->ID=people_list[n].ID;
                  newptr->next_people=NULL;
                  current->next_people=newptr;
                  current=newptr;
              }
              else if (strcmp(people_list[j].name,ch2[k])==0)
              {    
                  newptr=malloc(sizeof(struct people_card));
                  strcpy(newptr->name,ch1[k]);
                  
                  int n=1;
                  while(strcmp(ch1[k],people_list[n].name)!=0)//��children��ID 
                  {
                      n++;
                  }
                  newptr->ID=people_list[n].ID;
                  newptr->next_people=NULL;
                  current->next_people=newptr;
                  current=newptr;
              }
          }//ѭ���������ļ��е�����һ���Ѿ��������            
      }//ѭ��������ÿ���˵��ӽڵ��Ѿ���� 
      people_link temp;
      for (j=1;j<people_num;j++)
      {
          temp=people_list[j].next_people;
          printf("\nthe people who connect with %s are:\n",people_list[j].name);
          while (temp!=NULL)
          {
                printf("%s\t",temp->name);
                temp=temp->next_people;
          }
          
      }
      fclose(f);
      system("pause");
}
