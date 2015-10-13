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
         
         for (m=1;m<=k2;m++)//针对unchild[]中的点进行遍历
         {
             if (unchild[m]!=0)
                for (l=1;l<=k1;l++)//将每个子节点都遍历
                {
                    int a,b;
                    a=unchild[m],b=child[l];//a代表将要求的节点，b代表此时的子节点 
                    if (array[i][b]+array[b][a]<array[i][a])   
                        if (array[i][b]+array[b][a]<temp)
                        {
                            temp=array[i][b]+array[b][a]; 
                            //array[i][a]=array[i][b]+array[b][a];
                            //array[a][i]=array[i][b]+array[b][a];
                            A=a;//记录下来最小的目标节点 
                            B=b;//记录下来通过的子节点 
                            M=m;//M用来记录将要消去的unchild[]集合中的点的位置 
                            //unchild[m]=0;//每当原来的非子节点找到路径后，就将unchild[m]清空
                            //count++;//count用来记录已经消除的非子节点 
                        }
                 }         
         }
         array[i][A]=array[i][B]+array[B][A];//update             
         array[A][i]=array[i][B]+array[B][A];//update 
         unchild[M]=0;//清空已经得到的目标节点 
         count++;//记录消去节点的总数，用来判断程序是否停止 
         k1=k1+1;//新的子节点长度，该长度在每次执行完后加1 
         child[k1]=A;//将求到的节点纳入子节点集合当中 
         
         if (count<k2)
            return search(array,child,unchild,k1,k2,i,count);//回溯继续求解 
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
