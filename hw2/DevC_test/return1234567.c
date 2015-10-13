#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <string.h>
struct node_info{
       char street_name[20];
       int x;
       int y;
       int house_num;
       int unique_num;
}original_data[20][20];

struct adj_vertex{
       char street_name[10][20];
       int house_num[10];
       int present_num;
       float distance;
       int unique_num;
       int father_unique_num[10];
       int father_num;
       float distance_to_start_node;
       struct adj_vertex *next_node;
}adj_list[70];
typedef struct adj_vertex *adj_link;

struct shorter_path{
       float distance;
       int unique_from;
       int unique_to;
};

struct search_path{
       int pre_label;
       int unique;
};

struct each_path{
       int unique_num;
       int x;
       int y;
       float distance;
       struct each_path *next_node;
};
typedef struct each_path *path_link;

int list_num=1;
int start_unique;
int destination_unique;
float x1;
float yl;
float x2,y2;

void Insert_start_destination(int ,int ,int ,char *,char *);
void get_BFS_list(struct search_path *,int ,int );
void Dijkstra();
int  Index(int );
void get_the_ways(struct each_path *,struct search_path *);

main()
{
      FILE *f;
      f=fopen("NewYork.txt","r");
      
      char ch;
      float mile;
      
      char street[20][20];
      fscanf(f,"%f",&mile);
      
      int k=0,street_num=1,i=1,j;
      ch=fgetc(f);
      ch=fgetc(f);
      
      int flag=1;
      while(!feof(f))
      {
          if (flag==1)
          {
             while (ch!=',')
             {
                   street[street_num][k]=ch;
                   k++;
                   ch=fgetc(f);
             }
             street[street_num][k]='\0';
             flag=0;
          }
          else if (flag==0)
          {
               if (ch!='\n')
               { 
                  fscanf(f,"%d %d %d",&original_data[street_num][i].x,&original_data[street_num][i].y,&original_data[street_num][i].house_num);
                  strcpy(original_data[street_num][i].street_name,street[street_num]);
                  original_data[street_num][i].unique_num=original_data[street_num][i].x*100+original_data[street_num][i].y;
                  i++;
               }
               else if (ch=='\n')
               {
                  flag=1;
                  street_num++;
                  k=0;
                  i=1;
               }      
               ch=fgetc(f);
          }    
      }
      printf("%f\n",mile);
      
      int repeat_flag;
      
      for (j=1;j<=street_num;j++)//开始每条街遍历 street_num记录有多少条街道 
      {
          i=1;
          while (original_data[j][i].unique_num!='\0')//该街道内的节点循环 
          {
                adj_link newptr,current;
                
                k=1;
                repeat_flag=0;
                while (adj_list[k].unique_num!='\0')//判断新的节点是否和已有的list重复 
                {
                      if(original_data[j][i].unique_num==adj_list[k].unique_num)
                      {
                          int temp;
                          repeat_flag=1;//如果重复
                          
                          adj_list[k].present_num=adj_list[k].present_num+1;
                          temp=adj_list[k].present_num;
                          adj_list[k].house_num[temp]=original_data[j][i].house_num;
                          strcpy(adj_list[k].street_name[temp],original_data[j][i].street_name);
                          
                          current=&adj_list[k];
                          while (current->next_node!=NULL)//当子链表的下一个元素不为空时，继续 
                          {
                                current=current->next_node;
                          }
                          
                          if (original_data[j][i-1].unique_num!='\0')
                          {
                              int X,Y;
                              newptr=malloc(sizeof(struct adj_vertex));
                              newptr->unique_num=original_data[j][i-1].unique_num;
                              
                              X=original_data[j][i-1].x-original_data[j][i].x;
                              Y=original_data[j][i-1].y-original_data[j][i].y;
                              newptr->distance=sqrt(pow(X,2)+pow(Y,2));
                              newptr->next_node=NULL;
                              current->next_node=newptr;
                              current=newptr;
                          }
                          if (original_data[j][i+1].unique_num!='\0')
                          {
                              int X,Y;
                              newptr=malloc(sizeof(struct adj_vertex));
                              newptr->unique_num=original_data[j][i+1].unique_num;
                              
                              X=original_data[j][i+1].x-original_data[j][i].x;
                              Y=original_data[j][i+1].y-original_data[j][i].y;
                              newptr->distance=sqrt(pow(X,2)+pow(Y,2));
                              newptr->next_node=NULL;
                              current->next_node=newptr;
                              current=newptr;
                          }
                          break;
                      }
                      k++;
                }//此循环结束后可以知道 original_data[j][i]是否在之前重复过 
                
                if (repeat_flag==0)//如果 original_data[j][i]没有在之前的adj_list[]出现过，则在adj_list[]中新增加一个点 
                {
                      int temp;
                      adj_list[list_num].unique_num=original_data[j][i].unique_num;
                      adj_list[list_num].present_num=1;
                      temp=adj_list[list_num].present_num;
                      adj_list[list_num].house_num[temp]=original_data[j][i].house_num;
                      strcpy(adj_list[list_num].street_name[temp],original_data[j][i].street_name);
                      
                      adj_list[list_num].next_node=NULL;
                      current=&adj_list[list_num];
                      
                      if (original_data[j][i+1].unique_num!='\0')
                      {
                          int X,Y;
                          newptr=malloc(sizeof(struct adj_vertex));
                          newptr->unique_num=original_data[j][i+1].unique_num;
                          
                          X=original_data[j][i+1].x-original_data[j][i].x;
                          Y=original_data[j][i+1].y-original_data[j][i].y;
                          newptr->distance=sqrt(pow(X,2)+pow(Y,2));
                          newptr->next_node=NULL;
                          current->next_node=newptr;
                          current=newptr;
                      }
                      if (original_data[j][i-1].unique_num!='\0')
                      {
                          int X,Y;
                          newptr=malloc(sizeof(struct adj_vertex));
                          newptr->unique_num=original_data[j][i-1].unique_num;
                          
                          X=original_data[j][i-1].x-original_data[j][i].x;
                          Y=original_data[j][i-1].y-original_data[j][i].y;
                          newptr->distance=sqrt(pow(X,2)+pow(Y,2));
                          newptr->next_node=NULL;
                          current->next_node=newptr;
                          current=newptr;
                      }
                      list_num++;//list_num增加一位   
                }     
                i++;//循环到下一个节点 
          }//结束后循环到下一条街道    
      }
      list_num--;//list_num比实际的点个数多1 
      
      char start_street[20];
      char destination_street[20];
      int start_house;
      int destination_house;
      
      printf("input the start street name and the house number:\n");
      gets(start_street);
      scanf("%d",&start_house);
      getchar();
      printf("input the destination street name and the house number:\n");
      gets(destination_street);
      scanf("%d",&destination_house);
      
      printf("%s + %d\n",start_street,start_house);
      printf("%s + %d\n",destination_street,destination_house);
      
      Insert_start_destination(street_num,start_house,destination_house,start_street,destination_street);
      if (start_unique=='\0' || destination_unique=='\0')
      {
           system("pause");
           return 0;
           }
      if (start_unique == destination_unique)
      {
           printf("the start point is the same as destination!");
           system("pause");
           return 0;
           }
      printf("%d    %d\n",start_unique,destination_unique);
      k=1;
      while (k<=list_num)
      {
            adj_link temp;
            temp=&adj_list[k];
            printf("the node %d connect these nodes:\n",temp->unique_num);
            i=1;
            while(temp->house_num[i]!='\0')
            {
                printf("%s,%d\n",temp->street_name[i],temp->house_num[i]);
                i++;
            }
            temp=temp->next_node;
            while (temp!=NULL)
            {
                  printf("                         node %d has the distance %f\n",temp->unique_num,temp->distance);
                  temp=temp->next_node;
                  }
            k++;
      }
      Dijkstra();//Dijkstra算法存储从起点开始，每个点到起点的最短路径的父亲节点 
      struct search_path BFS_array[50];
      /*the destination node has his father nodes,and these father nodes also have their own father nodes.
        So it's a tree,and I use the BFS method to find every shortest path.
      */
      int label;
      label=Index(destination_unique);
      BFS_array[1].unique=destination_unique;
      i=1;
      int from,present;//from 和 to 都是数组的角标 
      from=2;
      j=from;
      present=from+adj_list[label].father_num;
      while (i<=adj_list[label].father_num)//此次循环得到终点以及终点的父节点，将他们纳入BFS_array这个集合 
      {
            BFS_array[j].unique=adj_list[label].father_unique_num[i];
            BFS_array[j].pre_label=1;
            j++;
            i++;
            }
      get_BFS_list(BFS_array,from,present);////////!!!!!!!!!!!!!
      i=1;
      int counter=0;
      while(BFS_array[i].unique!='\0')//get the total number of the shortest pathes
      {
            if (BFS_array[i].unique==start_unique)
                  counter++;
            i++;
      }
      struct each_path shortest_ways[counter+1];
      get_the_pathes(shortest_ways,BFS_array);
      int ways=counter;
      for (i=1;i<=ways;i++)
      {
          path_link present;
          present=&shortest_ways[i];
          float pre_x,pre_y;
          if (present->unique_num==1)
          {
                pre_x=x1;
                pre_y=yl;
          }
          else
          {
                present->x=present->unique_num/100;
                present->y=present->unique_num%100;
                pre_x=present->x;
                pre_y=present->y;
          }
          present=present->next_node;
          while(present!=NULL)
          {
                float X,Y;
                if (present->unique_num==2)
                {
                      X=pre_x-x2;
                      Y=pre_y-y2;
                      present->distance=sqrt(pow(X,2)+pow(Y,2));
                      printf("%d  %f  %f  %f->",present->unique_num,x2,y2,present->distance);
                }
                else
                {
                      present->x=present->unique_num/100;
                      present->y=present->unique_num%100;
                      X=pre_x-present->x;
                      Y=pre_y-present->y;
                      present->distance=sqrt(pow(X,2)+pow(Y,2));
                      pre_x=present->x;
                      pre_y=present->y;
                      printf("%d  %d  %d  %f->",present->unique_num,present->x,present->y,present->distance);
                }
                present=present->next_node;
          }
          printf("\n");
      }
      system("pause");
}

int Index(int unique)
{
      int i=1;
      while (unique!=adj_list[i].unique_num)
            i++;
      return i;
}

get_the_pathes(struct each_path *shortest_ways,struct search_path *BFS_array)
{
      int j=1;
      int i;
      for (i=2;BFS_array[i].unique!='\0';i++)
      {
          if (BFS_array[i].unique == start_unique)
          {
                
                int label;
                path_link current,newptr;
                current=&shortest_ways[j];
                shortest_ways[j].unique_num=start_unique;
                label=BFS_array[i].pre_label;    
                while (label!=1)
                {
                    newptr=malloc(sizeof(struct each_path));
                    newptr->unique_num=BFS_array[label].unique;
                    newptr->next_node=NULL;    
                    current->next_node=newptr;    
                    current=newptr;
                    label=BFS_array[label].pre_label;
                    
                }
                newptr=malloc(sizeof(struct each_path));
                newptr->unique_num=destination_unique;
                newptr->next_node=NULL;    
                current->next_node=newptr;    
                current=newptr; 
                j++;  
          }
      }
}

void Dijkstra()
{
      int visited_set[50];
      int i,j;
      visited_set[1]=start_unique;
      int set_num=1;//set_num用来记录已经纳入的节点集合的节点数目 
      while(visited_set[set_num]!=destination_unique)//当该集合的最后一个节点不是终点时，继续 
      {
          i=1;
          j=1;
          int label;
          struct shorter_path lenth_compare[20]={0};
          while (i<=set_num)
          {
                //get the present unique number
                label=Index(visited_set[i]);//label得到adj_list数组的角标 
                
                adj_link temp;
                temp=&adj_list[label];
                temp=temp->next_node;
                while (temp!=NULL)
                {
                      int n;
                      for (n=1;n<=set_num;n++)
                          if (visited_set[n]==temp->unique_num)
                             break;   
                      if (n>set_num)
                      {
                          float a;
                          a=temp->distance+adj_list[label].distance_to_start_node;//目前的父节点到起点的距离加上子节点到父节点的距离 
                          lenth_compare[j].distance=a;
                          lenth_compare[j].unique_from=adj_list[label].unique_num;
                          lenth_compare[j].unique_to=temp->unique_num;
                          j++;
                      }
                      temp=temp->next_node;     
                }
                i++;
          }
          int k=1;
          float min_distance;
          min_distance=lenth_compare[k].distance;
          k++;
          while (k<j)//j代表目前 lenth_compare[]数组内的元素数目 
          {
                if (min_distance>lenth_compare[k].distance)
                     min_distance=lenth_compare[k].distance;
                k++;
          }
          
          for (k=1;k<j;k++)
          {
                if (min_distance==lenth_compare[k].distance)
                {
                      if (lenth_compare[k].unique_to==destination_unique)
                      {
                            int num_of_father=1;
                            label=Index(destination_unique);
                            while (k<j)
                            {
                                if (lenth_compare[k].distance==min_distance && lenth_compare[k].unique_to==destination_unique)
                                {
                                    adj_list[label].distance_to_start_node=min_distance;
                                    adj_list[label].father_unique_num[num_of_father]=lenth_compare[k].unique_from;
                                    num_of_father++;
                                }
                                k++;
                            }
                            adj_list[label].father_num=num_of_father-1;
                            set_num++;
                            visited_set[set_num]=destination_unique;
                            break;
                      }
                      else//如果该线段不是以终点结尾 
                      {
                            int num_of_father=1;
                            int temp;
                            temp=lenth_compare[k].unique_to;
                            label=Index(temp);
                            while (k<j)
                            {
                                if (lenth_compare[k].distance==min_distance && lenth_compare[k].unique_to==temp)
                                {
                                    adj_list[label].distance_to_start_node=min_distance;
                                    adj_list[label].father_unique_num[num_of_father]=lenth_compare[k].unique_from;
                                    num_of_father++;
                                }
                                k++;
                            }
                            adj_list[label].father_num=num_of_father-1;
                            set_num++;
                            visited_set[set_num]=temp;
                            break;     
                      }
                }          
          }
      }
}

void get_BFS_list(struct search_path *BFS_array,int from,int present)
{
      int stop_label;
      int flag=0;
      stop_label=present;
      while (from<stop_label)
      {
            int unique_num;
            int label;
            int times;
            int i;
            unique_num=BFS_array[from].unique;
            if (unique_num==start_unique)
            {
                  from++;
                  continue;
            }
            label=Index(unique_num);
            times=adj_list[label].father_num;
            for (i=1;i<=times;i++)
            {
                  BFS_array[present].unique=adj_list[label].father_unique_num[i];
                  BFS_array[present].pre_label=from;
                  present++;
            }
            flag=1;
            from++;
      }
      if (flag==1)
            return get_BFS_list(BFS_array,from,present);
}

void Insert_start_destination(int street_num,int start_house,int destination_house,char *start_street,char *destination_street)
{
      int housenumber_a,housenumber_b;
      int i,j;
      for (i=1;i<=street_num;i++)
          if (strcmp(start_street,original_data[i][1].street_name)==0)
             break;
      if (i>street_num)
      {
          printf("The start street is not existed!\n");
          return;
      }
      else if(i<=street_num)
      { 
          j=1;
          while (original_data[i][j].unique_num!='\0')
          {
                  if (start_house==original_data[i][j].house_num)
                  {
                      start_unique=original_data[i][j].unique_num;
                      break;
                  }
                  else
                  {
                      if (start_house<original_data[i][j].house_num && start_house>original_data[i][j+1].house_num && original_data[i][j+1].unique_num!='\0' || start_house>original_data[i][j].house_num && start_house<original_data[i][j+1].house_num && original_data[i][j+1].unique_num!='\0')   
                      {//找到插入！！！的位置 
                          if (strcmp(start_street,destination_street)==0 && start_house==destination_house)
                          {
                                printf("The start place is the same as the destination place!!\n");
                                return;
                          }
                          housenumber_a=original_data[i][j].house_num;
                          housenumber_b=original_data[i][j+1].house_num;
                          
                          float factor;
                          float X,Y;
                          factor=(float)(original_data[i][j].house_num-start_house)/(original_data[i][j].house_num-original_data[i][j+1].house_num);
                          printf("factor is: %f\n",factor);
                          
                          x1=(original_data[i][j+1].x-original_data[i][j].x)*factor + original_data[i][j].x;
                          yl=(original_data[i][j+1].y-original_data[i][j].y)*factor + original_data[i][j].y;
                          printf("%f   %f\n",x1,yl);
                          start_unique=1;
                          list_num++;
                          adj_list[list_num].unique_num=start_unique;
                          adj_list[list_num].house_num[1]=start_house;
                          strcpy(adj_list[list_num].street_name[1],start_street);
                          adj_list[list_num].distance_to_start_node=0.0;
                              
                          adj_link newptr,current;
                          adj_list[list_num].next_node=NULL;
                          current=&adj_list[list_num];
                          int k;
                          for (k=j;k<=j+1;k++)
                          {
                                  newptr=malloc(sizeof(struct adj_vertex));
                                  newptr->unique_num=original_data[i][k].unique_num;
                                  
                                  X=original_data[i][k].x-x1;
                                  Y=original_data[i][k].y-yl;
                                  newptr->distance=sqrt(pow(X,2)+pow(Y,2));
                                  newptr->next_node=NULL;
                                  current->next_node=newptr;
                                  current=newptr;
                          }
                          
                          break;
                      }
                      j++;
                  }
          }
          if (original_data[i][j].unique_num=='\0')//意味着直到终点都没找到合适的位置       
          {
              printf("The strat house number is not existed!\n");
              return;
          }        
      }
      
      for (i=1;i<=street_num;i++)
          if (strcmp(destination_street,original_data[i][1].street_name)==0)
             break;
      if (i>street_num)
      {
          printf("The destination street is not existed!\n");
          return;
      }
      else if(i<=street_num)
      {
          j=1;
          while (original_data[i][j].unique_num!='\0')
          {
                  if (destination_house==original_data[i][j].house_num)
                  {
                      destination_unique=original_data[i][j].unique_num;
                      break;
                  }
                  else
                  {
                      if (destination_house<original_data[i][j].house_num && destination_house>original_data[i][j+1].house_num && original_data[i][j+1].unique_num!='\0' || destination_house>original_data[i][j].house_num && destination_house<original_data[i][j+1].house_num && original_data[i][j+1].unique_num!='\0')   
                      {//找到插入！！！的位置 
                          float factor;
                          float X,Y;
                          factor=(float)(original_data[i][j].house_num-destination_house)/(original_data[i][j].house_num-original_data[i][j+1].house_num);
                          printf("factor is: %f\n",factor);
                          
                          x2=(original_data[i][j+1].x-original_data[i][j].x)*factor + original_data[i][j].x;
                          y2=(original_data[i][j+1].y-original_data[i][j].y)*factor + original_data[i][j].y;
                          printf("%f   %f\n",x2,y2);
                          
                          if (strcmp(start_street,destination_street)==0 && housenumber_a==original_data[i][j].house_num && housenumber_b==original_data[i][j+1].house_num)
                          {
                                float distance;
                                X=x1-x2;
                                Y=yl-y2;
                                distance=sqrt(pow(X,2)+pow(Y,2));
                                printf("The start place is very closed to the destination place,the distance is %f\n",distance);
                                return;
                          }
                          destination_unique=2;
                          int k;
                          for (k=j;k<=j+1;k++)
                          {
                                  int m;
                                  m=Index(original_data[i][k].unique_num);
                                        
                                  adj_link newptr,current;
                                  current=&adj_list[m];
                                  while (current->next_node!=NULL)
                                        current=current->next_node;
                                  
                                  newptr=malloc(sizeof(struct adj_vertex));
                                  newptr->unique_num=destination_unique;
                                  
                                  X=original_data[i][k].x-x2;
                                  Y=original_data[i][k].y-y2;
                                  newptr->distance=sqrt(pow(X,2)+pow(Y,2));
                                  newptr->next_node=NULL;
                                  current->next_node=newptr;
                                  current=newptr;
                          }
                          list_num++;//给终点加入adj_list，方便之后求turn by turn 
                          adj_list[list_num].unique_num=destination_unique;
                          adj_list[list_num].house_num[1]=destination_house;
                          strcpy(adj_list[list_num].street_name[1],destination_street);
                          adj_link newptr,current;
                          adj_list[list_num].next_node=NULL;
                          current=&adj_list[list_num];
                          for (k=j;k<=j+1;k++)
                          {
                                  newptr=malloc(sizeof(struct adj_vertex));
                                  newptr->unique_num=original_data[i][k].unique_num;
                                  
                                  X=original_data[i][k].x-x2;
                                  Y=original_data[i][k].y-y2;
                                  newptr->distance=sqrt(pow(X,2)+pow(Y,2));
                                  newptr->next_node=NULL;
                                  current->next_node=newptr;
                                  current=newptr;
                          }
                          break;
                      }
                      j++;
                  }
          }
          if (original_data[i][j].unique_num=='\0')//意味着直到终点都没找到合适的位置       
          {
              printf("The destination house number is not existed!\n");
              return;
          }        
      }
}
