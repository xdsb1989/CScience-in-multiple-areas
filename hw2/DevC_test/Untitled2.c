#include<stdio.h>
#include"stdlib.h"
#include <malloc.h>

int search(int array[][100],int *child, int unchild[],int k1,int k2,int i,int count)
{
         //int x=0;
         int l,m,A,B,M;
         
         //int newchild[100]={0};
         //newchild=(int*)malloc(k2*sizeof(int));
         int temp = 9999;
         
         for (m=1;m<=k2;m++)//���unchild[]�еĵ���б���
         {
             if (unchild[m]!=0)
                for (l=1;l<=k1;l++)//��ÿ���ӽڵ㶼����
                {
                    int a,b;
                    a=unchild[m],b=child[l];//a����Ҫ��Ľڵ㣬b�����ʱ���ӽڵ� 
                    if (array[i][b]+array[b][a]<array[i][a])   
                        if (array[i][b]+array[b][a]<temp)
                        {
                            temp=array[i][b]+array[b][a]; 
                            //array[i][a]=array[i][b]+array[b][a];
                            //array[a][i]=array[i][b]+array[b][a];
                            A=a;//��¼������С��Ŀ��ڵ� 
                            B=b;//��¼����ͨ�����ӽڵ� 
                            M=m;//M������¼��Ҫ��ȥ��unchild[]�����еĵ��λ�� 
                            //unchild[m]=0;//ÿ��ԭ���ķ��ӽڵ��ҵ�·���󣬾ͽ�unchild[m]���
                            //count++;//count������¼�Ѿ������ķ��ӽڵ� 
                        }
                 }         
         }
         array[i][A]=array[i][B]+array[B][A];//update             
         array[A][i]=array[i][B]+array[B][A];//update 
         unchild[M]=0;//����Ѿ��õ���Ŀ��ڵ� 
         count++;//��¼��ȥ�ڵ�������������жϳ����Ƿ�ֹͣ 
         k1=k1+1;//�µ��ӽڵ㳤�ȣ��ó�����ÿ��ִ������1 
         child[k1]=A;//���󵽵Ľڵ������ӽڵ㼯�ϵ��� 
         
         if (count<k2)
            return search(array,child,unchild,k1,k2,i,count);//���ݼ������ 
         else
             return **array;
     }

main()
{
      int links,notes;
      printf("input the number of notes: ");
      scanf("%d",&notes);
      printf("input the number of links: ");
      scanf("%d",&links);
      //int network[notes]={0};
      int i,j;
      
      int *child;
      child=(int*)malloc(notes*sizeof(int));
      
      int unchild[100]={0};
      //unchild=(int*)malloc(notes*sizeof(int));
      
      int network[100][100]={0};
      //network=(int **)malloc(notes*sizeof(int *));
      //for (i=1;i<=notes;i++)
      //    *(network+i)=(int *)malloc(notes*sizeof (int));
      
      for (i=1;i<=notes;i++)
          for (j=1;j<=notes;j++)
              network[i][j]=9999;
      int q,p;
      for (i=1;i<=links;i++)
      {
          printf("input the start notes and the final notes: \n");
          scanf("%d %d",&q,&p);
          network[q][p]=1;
          network[p][q]=1;
      }
     
      int k1,k2;
      for (i=1;i<=notes;i++)
      {
          k1=0,k2=0;
          for (j=1;j<=notes;j++)
          {
              if (i==j)
                 continue;
              if (network[i][j]<9999)
              {   
                  k1++;
                  child[k1]=j;                  
              }              
              else if (network[i][j]==9999)
              {
                  k2++;
                  unchild[k2]=j;                  
              }                            
          }
          if (k2>0)
              search(network,child,unchild,k1,k2,i,0);
      }   
      
      for (i=1;i<=notes;i++)
          for (j=1;j<=notes;j++)
              if (i==j)
                  printf("0 ");
              else if (j==notes)
                  printf("%d\n",network[i][j]);
              else
                  printf("%d ",network[i][j]);
      
      //for (i=1;i<=notes;i++) 
      //{ 
      //   free(network[i]);  
      //   }
      
      //free (network);  
      system("pause");
}
