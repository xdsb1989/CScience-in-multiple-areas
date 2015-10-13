#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <string.h>
#include"1.h"
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
       float section_distance;
       struct each_path *next_node;
};
typedef struct each_path *path_link;

int  Index(int );
void Insert_start_destination(int ,int ,int ,char *,char *);
void get_BFS_list(struct search_path *,int ,int );
void Dijkstra();
void get_the_ways(struct each_path *,struct search_path *);
void turn_by_turn(struct each_path *,int );

main()
{     
      FILE *f;
      char filename[50];
      printf("input the name of the file:");
      scanf("%s",filename);//the file's name can be absolute path,include the .txt example: D:\\file1\\file2\\test.txt
      f=fopen(filename,"rb");
      if (f==NULL)//if can not open the file,stop the program
      {
         printf("OMG,the file is not existed!\n");
         system("pause");
         return;
         }
      get_the_map(f);
      getchar();
      printf("input the start street name:");
      gets(start_street);
      printf("input the start house number:");
      scanf("%d",&start_house);
      getchar();
      printf("input the destination street name:");
      gets(destination_street);
      printf("input the destination house number:");
      scanf("%d",&destination_house);
      
      Insert_start_destination(street_num,start_house,destination_house,start_street,destination_street);
      if (start_unique=='\0' || destination_unique=='\0')
      {
           system("pause");
           return 0;
           }
      if (start_unique == destination_unique)
      {
           printf("the start point is the same as destination!\n");
           system("pause");
           return 0;
           }
      int k=1;
      int i,j;
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
                pre_x=start_x;
                pre_y=start_y;
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
                      X=pre_x-destination_x;
                      Y=pre_y-destination_y;
                      present->distance=sqrt(pow(X,2)+pow(Y,2))*mile;
                }
                else
                {
                      present->x=present->unique_num/100;
                      present->y=present->unique_num%100;
                      X=pre_x-present->x;
                      Y=pre_y-present->y;
                      present->distance=sqrt(pow(X,2)+pow(Y,2))*mile;
                      pre_x=present->x;
                      pre_y=present->y;
                }
                present=present->next_node;
          }
      }
      turn_by_turn(shortest_ways,ways);
      system("pause");
}

void turn_by_turn(struct each_path *shortest_ways,int ways)//"ways" save the number of the shorest ways,shortest_ways[] save all the shortest pathes
{
      int i;
      printf("/---------------------Next Path-------------------/\n");  
      for (i=1;i<=ways;i++)
      {
          path_link present,next,future;
          present=&shortest_ways[i];
          next=present->next_node;
          future=next->next_node;
          next->section_distance=next->distance;
          
          float x1,yl,x2,y2,x3,y3;
          if (present->unique_num==1)
          {
                x1=start_x;
                yl=start_y;
          }
          else if (present->unique_num!=1)
          {
                x1=present->x;
                yl=present->y;
          }
          if (next->unique_num==2)
          {
                x2=destination_x;
                y2=destination_y;
          }
          else if (next->unique_num!=2)
          {
                x2=next->x;
                y2=next->y;
          }
          if (x1>x2 && yl>y2)
                printf("Head SouthWest ");
          else if (x1<x2 && yl>y2)
                printf("Head SouthEast ");
          else if (x1>x2 && yl<y2)
                printf("Head NorthWest ");
          else if (x1<x2 && yl<y2)
                printf("Head NorthEest ");
          else if (x1>x2 && yl==y2)
                printf("Head West ");
          else if (x1<x2 && yl==y2)
                printf("Head Eest ");
          else if (x1==x2 && yl<y2)
                printf("Head North ");
          else if (x1==x2 && yl>y2)
                printf("Head South ");
          int present_label,future_label,next_label;
          int j,k;
          char start_street[10];
          present_label=Index(present->unique_num);
          next_label=Index(next->unique_num);
          for (j=1;j<=adj_list[present_label].present_num;j++)
          {
                int get_name=0;
                for (k=1;k<=adj_list[next_label].present_num;k++)
                if (strcmp(adj_list[present_label].street_name[j],adj_list[next_label].street_name[k])==0)
                {
                      get_name=1;
                      strcpy(start_street,adj_list[present_label].street_name[j]);
                      break;
                }     
                if (get_name==1)
                break;
          }
          printf("on %s.\n",start_street);
          if (future==NULL)
          {
                float distance,miles,decimal;
                int integer,feet;
                
                distance=next->section_distance;
                distance=distance*10;
                integer=distance/1;
                decimal=distance-integer;
                miles=(float)integer/10;   
                feet=5280*decimal/10;
                if (miles==0)
                     printf("stop on street %s,house number is %d,in %d foot.\n",destination_street,destination_house,feet);
                else if (feet==0)
                     printf("stop on street %s,house number is %d,in %.1f miles.\n",destination_street,destination_house,miles);
                else if (miles>0 && feet>0)
                     printf("stop on street %s,house number is %d,in %.1f miles and %d foot.\n",destination_street,destination_house,miles,feet);
          }
          while (future!=NULL)
          {
                present_label=Index(present->unique_num);
                future_label=Index(future->unique_num);
                next_label=Index(next->unique_num);
                
                int same_street=0;
                char same_street_name[10];
                for (j=1;j<=adj_list[present_label].present_num;j++)
                {
                      int get_name=0;
                      for (k=1;k<=adj_list[next_label].present_num;k++)
                          if (strcmp(adj_list[present_label].street_name[j],adj_list[next_label].street_name[k])==0)
                          {
                                 get_name=1;
                                 strcpy(same_street_name,adj_list[present_label].street_name[j]);
                                 break;
                          }     
                      if (get_name==1)
                          break;
                }
                for (k=1;k<=adj_list[future_label].present_num;k++)
                      if (strcmp(same_street_name,adj_list[future_label].street_name[k])==0)
                      {
                          same_street=1;
                          break;
                          }
                if (same_street==1)
                {
                      future->section_distance=future->distance+next->section_distance;
                      future=future->next_node;
                      next=next->next_node;
                      present=present->next_node;
                      if (future==NULL)
                      {
                            float distance,miles,decimal;
                            int integer,feet;
                            distance=next->section_distance;
                            distance=distance*10;
                            integer=distance/1;
                            decimal=distance-integer;
                            miles=(float)integer/10;   
                            feet=5280*decimal/10;
                            
                            if (miles==0)
                                 printf("stop on street %s,house number is %d,in %d foot.\n",destination_street,destination_house,feet);
                            else if (feet==0)
                                 printf("stop on street %s,house number is %d,in %.1f miles.\n",destination_street,destination_house,miles);
                            else if (miles>0 && feet>0)
                                 printf("stop on street %s,house number is %d,in %.1f miles and %d foot.\n",destination_street,destination_house,miles,feet);
                      }
                      while (future!=NULL)
                      {
                            int go_ahead=0;
                            future_label=Index(future->unique_num);
                            for (k=1;k<=adj_list[future_label].present_num;k++)
                                  if (strcmp(same_street_name,adj_list[future_label].street_name[k])==0)
                                  {
                                        go_ahead=1;
                                        future->section_distance=future->distance+next->section_distance;
                                        future=future->next_node;
                                        next=next->next_node;
                                        present=present->next_node;
                                        break;
                                  }
                            if (future==NULL)
                            {
                                  float distance,miles,decimal;
                                  int integer,feet;
                                  distance=next->section_distance;
                                  distance=distance*10;
                                  integer=distance/1;
                                  decimal=distance-integer;
                                  miles=(float)integer/10;   
                                  feet=5280*decimal/10;
                                  if (miles==0)
                                       printf("stop on street %s,house number is %d,in %d foot.\n",destination_street,destination_house,feet);
                                  else if (feet==0)
                                       printf("stop on street %s,house number is %d,in %.1f miles.\n",destination_street,destination_house,miles);
                                  else if (miles>0 && feet>0)
                                       printf("stop on street %s,house number is %d,in %.1f miles and %d foot.\n",destination_street,destination_house,miles,feet);
                            }
                            if (go_ahead==0)
                            {
                                  float distance,miles,decimal;
                                  int integer,feet;
                                  distance=next->section_distance;
                                  distance=distance*10;
                                  integer=distance/1;
                                  decimal=distance-integer;
                                  miles=(float)integer/10;   
                                  feet=5280*decimal/10;
                                  
                                  if (miles==0)
                                       printf("go to the vertex %d %d in %d foot.And then ",next->x,next->y,feet);
                                  else if (feet==0)
                                       printf("go to the vertex %d %d in %.1f miles.And then ",next->x,next->y,miles);
                                  else if (miles>0 && feet>0)
                                       printf("go to the vertex %d %d in %.1f miles and %d foot.And then ",next->x,next->y,miles,feet);
                                       
                                  if (present->unique_num==1 && future->unique_num==2)
                                  {
                                        x1=start_x;
                                        yl=start_y;
                                        x2=next->x;
                                        y2=next->y;
                                        x3=destination_x;
                                        y3=destination_y;
                                        }
                                  else if (present->unique_num==1 && future->unique_num!=2)
                                  {
                                        x1=start_x;
                                        yl=start_y;
                                        x2=next->x;
                                        y2=next->y;
                                        x3=future->x;
                                        y3=future->y;
                                        }      
                                  else if (present->unique_num!=1 && future->unique_num==2)
                                  {
                                        x1=present->x;
                                        yl=present->y;
                                        x2=next->x;
                                        y2=next->y;
                                        x3=destination_x;
                                        y3=destination_y;
                                        }
                                  else if (present->unique_num!=1 && future->unique_num!=2)
                                  {
                                        x1=present->x;
                                        yl=present->y;
                                        x2=next->x;
                                        y2=next->y;
                                        x3=future->x;
                                        y3=future->y;
                                        }
                                  direction(x1,yl,x2,y2,x3,y3);
                                  next_label=Index(next->unique_num);
                                  char next_street[10];
                                  for (j=1;j<=adj_list[next_label].present_num;j++)
                                  {
                                        int get_name=0;
                                        for (k=1;k<=adj_list[future_label].present_num;k++)
                                        if (strcmp(adj_list[next_label].street_name[j],adj_list[future_label].street_name[k])==0)
                                        {
                                              get_name=1;
                                              strcpy(next_street,adj_list[next_label].street_name[j]);
                                              break;
                                        }     
                                        if (get_name==1)
                                        break;
                                  }
                                  printf("onto %s\n",next_street);
                                  future=future->next_node;
                                  next=next->next_node;
                                  present=present->next_node;
                                  next->section_distance=next->distance;
                                  if (future==NULL)
                                  {
                                          float distance,miles,decimal;
                                          int integer,feet;
                                          distance=next->section_distance;
                                          distance=distance*10;
                                          integer=distance/1;
                                          decimal=distance-integer;
                                          miles=(float)integer/10;   
                                          feet=5280*decimal/10;
                                          if (miles==0)
                                               printf("stop on street %s,house number is %d,in %d foot.\n",destination_street,destination_house,feet);
                                          else if (feet==0)
                                               printf("stop on street %s,house number is %d,in %.1f miles.\n",destination_street,destination_house,miles);
                                          else if (miles>0 && feet>0)
                                               printf("stop on street %s,house number is %d,in %.1f miles and %d foot.\n",destination_street,destination_house,miles,feet);
                                  }
                                  break;
                            }
                      }
                }
                if (same_street==0)
                {
                      float distance,miles,decimal;
                      int integer,feet;
                      distance=next->section_distance;
                      distance=distance*10;
                      integer=distance/1;
                      decimal=distance-integer;
                      miles=(float)integer/10;   
                      feet=5280*decimal/10;
                                  
                      if (miles==0)
                           printf("go to the vertex %d %d in %d foot.And then ",next->x,next->y,feet);
                      else if (feet==0)
                           printf("go to the vertex %d %d in %.1f miles.And then ",next->x,next->y,miles);
                      else if (miles>0 && feet>0)
                           printf("go to the vertex %d %d in %.1f miles and %d foot.And then ",next->x,next->y,miles,feet);
                      if (present->unique_num==1 && future->unique_num==2)
                      {
                              x1=start_x;
                              yl=start_y;
                              x2=next->x;
                              y2=next->y;
                              x3=destination_x;
                              y3=destination_y;
                             }
                      else if (present->unique_num==1 && future->unique_num!=2)
                      {
                              x1=start_x;
                              yl=start_y;
                              x2=next->x;
                              y2=next->y;
                              x3=future->x;
                              y3=future->y;
                      }      
                      else if (present->unique_num!=1 && future->unique_num==2)
                      {
                              x1=present->x;
                              yl=present->y;
                              x2=next->x;
                              y2=next->y;
                              x3=destination_x;
                              y3=destination_y;
                      }
                      else if (present->unique_num!=1 && future->unique_num!=2)
                      {
                              x1=present->x;
                              yl=present->y;
                              x2=next->x;
                              y2=next->y;
                              x3=future->x;
                              y3=future->y;
                      }
                      direction(x1,yl,x2,y2,x3,y3);
                      
                      char next_street[10];
                      for (j=1;j<=adj_list[next_label].present_num;j++)
                      {
                            int get_name=0;
                            for (k=1;k<=adj_list[future_label].present_num;k++)
                            if (strcmp(adj_list[next_label].street_name[j],adj_list[future_label].street_name[k])==0)
                            {
                                  get_name=1;
                                  strcpy(next_street,adj_list[next_label].street_name[j]);
                                  break;
                            }     
                            if (get_name==1)
                            break;
                      }
                      printf("onto %s\n",next_street);
                      future=future->next_node;
                      next=next->next_node;
                      present=present->next_node;
                      next->section_distance=next->distance;
                      if (future==NULL)
                      {
                            float distance,miles,decimal;
                            int integer,feet;
                            distance=next->section_distance;
                            distance=distance*10;
                            integer=distance/1;
                            decimal=distance-integer;
                            miles=(float)integer/10;   
                            feet=5280*decimal/10;
                            if (miles==0)
                                 printf("stop on street %s,house number is %d,in %d foot.\n",destination_street,destination_house,feet);
                            else if (feet==0)
                                 printf("stop on street %s,house number is %d,in %.1f miles.\n",destination_street,destination_house,miles);
                            else if (miles>0 && feet>0)
                                 printf("stop on street %s,house number is %d,in %.1f miles and %d foot.\n",destination_street,destination_house,miles,feet);
                      }
                }
          }
          if (i<ways)
                printf("/---------------------Next Path-------------------/\n");  
      }
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
                      /*if (lenth_compare[k].unique_to==destination_unique)
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
                      }*/
                      //else//如果该线段不是以终点结尾 
                      //{
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
                      //}
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
