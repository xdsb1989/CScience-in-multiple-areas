/*Using the Greedy algorithm to find out the shortest way from original to the 
  destination.The output maybe correct,incorrect or there is no output*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <string.h>
#include"read_map.h"

struct search_path{//after each has his father in the shortest pathes,we need to find all the shortest path to the destination,
       int pre_label;
       int unique;
};

struct each_path{//later I will create a struct array to store each shortest path,each path is a list.
       int unique_num;
       int x;
       int y;
       float distance;
       float section_distance;//from the previous turning intersection to the present turning intersection
       struct each_path *next_node;
};
typedef struct each_path *path_link;

int  Index(int );//use the unique number to find the poisition in the adjance list
void Insert_start_destination(int ,int ,int ,char *,char *);//insert the start and destination node in the adjance list
void get_BFS_list(struct search_path *,int ,int );//I will use BFS search method to find out all the shortest pathes
void Greedy(int *);
void get_the_ways(struct each_path *,struct search_path *);//store all the shortest pathes in a struct array
void turn_by_turn(struct each_path *,int );//output each path in turn by turn method

main()
{     
      FILE *f;
      char filename[50];
      printf("input the name of the file:");
      scanf("%s",filename);//the file's name can be absolute path,include the .txt example: D:\\file1\\file2\\test.txt
      f=fopen(filename,"r");
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
      if (start_unique=='\0' || destination_unique=='\0')//if we don't get the unique number for start and destination nodes,we stop.
      {
           system("pause");
           return 0;
           }
      if (start_unique == destination_unique)//if the start node has the same coordinate as the destination node.stop.
      {
           printf("the start point is the same as destination!\n");
           system("pause");
           return 0;
           }
      int k=1;
      int i,j;
      int flag=0;
      Greedy(&flag);//flag is 0 means the algorithm can not find a path 
      if (flag==0)
      {
           system("pause");
           return 0;
      }
      struct search_path BFS_array[50];
      
      int label;
      label=Index(destination_unique);
      BFS_array[1].unique=destination_unique;
      i=1;
      int from,present;//"from" and "present" are labels in the array 
      from=2;
      j=from;
      present=from+adj_list[label].father_num;
      while (i<=adj_list[label].father_num)//begin at the destination,so that store the destination's father firstly
      {
            BFS_array[j].unique=adj_list[label].father_unique_num[i];
            BFS_array[j].pre_label=1;
            j++;
            i++;
            }
      get_BFS_list(BFS_array,from,present);//"from" to store the present first father's position,and "present" to store the array's present position
      i=1;
      int counter=0;
      while(BFS_array[i].unique!='\0')//"counter" is to get the total number of the shortest pathes
      {
            if (BFS_array[i].unique==start_unique)
                  counter++;
            i++;
      }
      struct each_path shortest_ways[counter+1];
      get_the_pathes(shortest_ways,BFS_array);
      int ways=counter;
      for (i=1;i<=ways;i++)//for each shortest path,store each node's distance between he and his father
      {
          path_link present;
          present=&shortest_ways[i];
          float pre_x,pre_y;
          if (present->unique_num==1)//if the unique number is 1,do some special operations
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
                if (present->unique_num==2)//if the next node is destination node,also do some special operations
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
      turn_by_turn(shortest_ways,ways);//turn by turn output each shortest path
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
          if (present->unique_num==1)//if the presetn node is start node,take the x and y value in special ways
          {
                x1=start_x;
                yl=start_y;
          }
          else if (present->unique_num!=1)
          {
                x1=present->x;
                yl=present->y;
          }
          if (next->unique_num==2)//if the next node is destination node,take the x and y value in special ways
          {
                x2=destination_x;
                y2=destination_y;
          }
          else if (next->unique_num!=2)
          {
                x2=next->x;
                y2=next->y;
          }
          if (x1>x2 && yl>y2)//diceide the first direction
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
          char start_street[20];
          present_label=Index(present->unique_num);
          next_label=Index(next->unique_num);
          for (j=1;j<=adj_list[present_label].present_num;j++)//find the start_street name
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
          printf("on %s.\n",start_street);//start_street must be the same street for both first node and the second node
          if (future==NULL)//if  future==NULL means they are very closed.
          {
                float distance,miles,decimal;//to find out the miles in 1 decimal place and the foot in integer
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
                
                int same_street=0;//to check whether the future node has the same as the previous two nodes
                char same_street_name[20];
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
                if (same_street==1)//if they are in the same street
                {
                      future->section_distance=future->distance+next->section_distance;
                      future=future->next_node;
                      next=next->next_node;
                      present=present->next_node;
                      if (future==NULL)
                      {
                            float distance,miles,decimal;//to find out the miles in 1 decimal place and the foot in integer
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
                            for (k=1;k<=adj_list[future_label].present_num;k++)//if they are still in a same street,continue to find.Until emerge a node in a different street.
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
                                  float distance,miles,decimal;//to find out the miles in 1 decimal place and the foot in integer
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
                            if (go_ahead==0)//has to stop and turn a direction
                            {
                                  float distance,miles,decimal;//to find out the miles in 1 decimal place and the foot in integer
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
                                  direction(x1,yl,x2,y2,x3,y3);//output the direction by using three pairs of coordinates
                                  next_label=Index(next->unique_num);
                                  char next_street[10];
                                  for (j=1;j<=adj_list[next_label].present_num;j++)//find the street name after turn a direction
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
                                  printf("onto %s\n",next_street);//out put the next street name
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
                      float distance,miles,decimal;//to find out the miles in 1 decimal place and the foot in integer
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
                      for (j=1;j<=adj_list[next_label].present_num;j++)//find the street name after turn a direction
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
                      printf("onto %s\n",next_street);//output the next street name
                      future=future->next_node;
                      next=next->next_node;
                      present=present->next_node;
                      next->section_distance=next->distance;
                      if (future==NULL)
                      {
                            float distance,miles,decimal;//to find out the miles in 1 decimal place and the foot in integer
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
          if (i<ways)//if the path is over
                printf("/---------------------Next Path-------------------/\n");  
      }
}

int Index(int unique)//get the label from the adjance list
{
      int i=1;
      while (unique!=adj_list[i].unique_num)
            i++;
      return i;
}

get_the_pathes(struct each_path *shortest_ways,struct search_path *BFS_array)//after having a BFS array,then we will bulid a struct array to store all the shortest path
{
      int j=1;
      int i;
      for (i=2;BFS_array[i].unique!='\0';i++)
      {
          if (BFS_array[i].unique == start_unique)//if we find the start node,then go back to find his child,and use his child to find the next child
          {//in this time,all the data in the array will have only one child
                int label;
                path_link current,newptr;
                current=&shortest_ways[j];
                shortest_ways[j].unique_num=start_unique;
                label=BFS_array[i].pre_label;    
                while (label!=1)//label==1 means find the start node.
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
                j++; //j is to record how many shortest path we have
          }
      }
}

void Greedy(int *flag)
{
      int visited_set[50];
      int i,j;
      visited_set[1]=start_unique;
      int set_num=1;//set_num is to store how many visited nodes already have
      while(visited_set[set_num]!=destination_unique)//when the last visited node in the set is not the destination,continue
      {
          i=1;
          int label;
          label=Index(visited_set[set_num]);
          adj_link temp;
          temp=&adj_list[label];
          temp=temp->next_node;//temp is the neighbor of the start node
          float min_distance;
          int new_unique;
          
          *flag=0;
          while (temp!=NULL)
          {
                for (j=1;j<=set_num;j++)//if the node is not visited
                    if (temp->unique_num==visited_set[j])
                         break;
                if (j>set_num && *flag==0)//if j>set_num means not repeated,and if flag==0 means it's the first time to get a link
                {
                     min_distance=temp->distance;
                     new_unique=temp->unique_num;
                     *flag=1;//once it get a no repeated link,set flag=1.
                }
                else if (j>set_num && *flag==1)//if already have at least one link,then compare and get the shortest one
                {
                     if (min_distance>temp->distance)
                     {
                          min_distance=temp->distance;
                          new_unique=temp->unique_num;
                     }
                }
                temp=temp->next_node;
          }
          if (*flag==0)//if flag==0 means all the neighbor of the current has been visited,then there is no way outlet
          {
                printf("The algorithm can not find out the shortest way!!!!\n");
                return;
          }
          else//if flag==1 means find a shortest lenth
          {
                int new_label;
                new_label=Index(new_unique);
                adj_list[new_label].father_num=1;
                adj_list[new_label].father_unique_num[1]=adj_list[label].unique_num;
                set_num++;
                visited_set[set_num]=new_unique;//record the shortest node to the set
          }
      }
}

void get_BFS_list(struct search_path *BFS_array,int from,int present)
{
      int stop_label;
      int flag=0;
      stop_label=present;//Every time stop_label is equal to the present.
      while (from<stop_label)//when the present father is over,the loop is finished.
      {
            int unique_num;//is the current father's unique number
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
            flag=1;//if the "from" is not small than stop_label,then means there is no children come out.then the function terminates.Once the loop is executed,means has at least one child
            from++;
      }
      if (flag==1)
            return get_BFS_list(BFS_array,from,present);
}
