#ifndef fit
#define fit
struct node_info{
       char street_name[20];
       int x;
       int y;
       int house_num;
       int unique_num;
}original_data[30][20];

struct adj_vertex{
       char street_name[5][20];
       int house_num[5];
       int present_num;//to save how many different house number and street_name the node has
       float distance;//distance between every two vertexes
       int unique_num;
       int father_unique_num[5];
       int father_num;//number of each note's fathers(the father for the node is on the shortest path)
       float distance_to_start_node;
       struct adj_vertex *next_node;
}adj_list[70];
typedef struct adj_vertex *adj_link;

int list_num=1;
int street_num=1;
float mile;
int start_unique;
int destination_unique;
float start_x;
float start_y;
float destination_x;
float destination_y;
int start_house;      
int destination_house;
char start_street[20];
char destination_street[20];

get_the_map(FILE *f)
{
      
      char street[20][20];
      fscanf(f,"%f",&mile);
      printf("%f\n",mile);
      char ch;
      int k=0,i=1,j;
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
}

void direction(float x1,float yl,float x2,float y2,float x3,float y3)
{
      if (x1-x2==0 && x2-x3!=0)
      {
            if (x3>x2 && y2>yl)
                printf("turn right!");
            else if (x3<x2 && y2>yl)
                printf("turn left!");
            else if (x3>x2 && y2<yl)    
                printf("turn left!");
            else if (x3<x2 && y2<yl)    
                printf("turn right!");
      }
      else if (x3-x2==0 && x1-x2!=0)
      {
            if (y3>y2 && x1>x2)
                printf("turn right!");
            else if (y3>y2 && x1<x2)
                printf("turn left!");
            else if (y3<y2 && x1>x2)    
                printf("turn left!");
            else if (y3<y2 && x1<x2)    
                printf("turn right!");
      }
      else if (x3-x2==0 && x1-x2==0)
            printf("go straight!");
      else
      {
            float tan1;
            float tan2;
            tan1=fabs((y2-yl)/(x2-x1));
            tan2=fabs((y3-y2)/(x3-x2));
            if (tan1==tan2)
            {
                tan1=(y2-yl)/(x2-x1);
                tan2=(y3-y2)/(x3-x2);
                if (tan1==tan2)
                     printf("go straight!");
                else if (tan1>tan2)
                {
                     if (x1<x2 && x3<x2)
                          printf("turn left!");
                     else if (x1<x2 && x3>x2)
                          printf("turn right!");     
                     else if (x1>x2 && x3>x2)
                          printf("turn left!");
                     else if (x1>x2 && x3<x2)
                          printf("turn right!");
                          }
                else if (tan1<tan2)
                {
                     if (x1<x2 && x3<x2)
                          printf("turn right!");
                     else if (x1<x2 && x3>x2)
                          printf("turn left!");     
                     else if (x1>x2 && x3>x2)
                          printf("turn right!");
                     else if (x1>x2 && x3<x2)
                          printf("turn left!");
                          }
            }
            else if (tan1>tan2)
            {
                if (x3>x2 && y2>yl)
                    printf("turn right!");
                else if (x3<x2 && y2>yl)
                    printf("turn left!");
                else if (x3>x2 && y2<yl)    
                    printf("turn left!");
                else if (x3<x2 && y2<yl)    
                    printf("turn right!");
            }
            else if (tan1<tan2)
            {
                if (y3>y2 && x1>x2)
                    printf("turn right!");
                else if (y3>y2 && x1<x2)
                    printf("turn left!");
                else if (y3<y2 && x1>x2)    
                    printf("turn left!");
                else if (y3<y2 && x1<x2)    
                    printf("turn right!");
            }
      }         
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
                      printf("the coordinate of start is:x=%d,y=%d\n",start_unique/100,start_unique%100);
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
                          
                          start_x=(original_data[i][j+1].x-original_data[i][j].x)*factor + original_data[i][j].x;
                          start_y=(original_data[i][j+1].y-original_data[i][j].y)*factor + original_data[i][j].y;
                          printf("the coordinate of start is:x=%f,y=%f\n",start_x,start_y);
                          start_unique=1;
                          list_num++;
                          adj_list[list_num].unique_num=start_unique;
                          adj_list[list_num].house_num[1]=start_house;
                          strcpy(adj_list[list_num].street_name[1],start_street);
                          adj_list[list_num].present_num=1;
                          adj_list[list_num].distance_to_start_node=0.0;
                              
                          adj_link newptr,current;
                          adj_list[list_num].next_node=NULL;
                          current=&adj_list[list_num];
                          int k;
                          for (k=j;k<=j+1;k++)
                          {
                                  newptr=malloc(sizeof(struct adj_vertex));
                                  newptr->unique_num=original_data[i][k].unique_num;
                                  
                                  X=original_data[i][k].x-start_x;
                                  Y=original_data[i][k].y-start_y;
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
      //begin to find the destination_street and insert the other node
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
                      printf("the coordinate of destination is:x=%d,y=%d\n",destination_unique/100,destination_unique%100);
                      break;
                  }
                  else
                  {
                      if (destination_house<original_data[i][j].house_num && destination_house>original_data[i][j+1].house_num && original_data[i][j+1].unique_num!='\0' || destination_house>original_data[i][j].house_num && destination_house<original_data[i][j+1].house_num && original_data[i][j+1].unique_num!='\0')   
                      {//找到插入！！！的位置 
                          float factor;
                          float X,Y;
                          factor=(float)(original_data[i][j].house_num-destination_house)/(original_data[i][j].house_num-original_data[i][j+1].house_num);
                          
                          destination_x=(original_data[i][j+1].x-original_data[i][j].x)*factor + original_data[i][j].x;
                          destination_y=(original_data[i][j+1].y-original_data[i][j].y)*factor + original_data[i][j].y;
                          printf("the coordinate of destination is:x=%f,y=%f\n",destination_x,destination_y);
                          
                          if (strcmp(start_street,destination_street)==0 && housenumber_a==original_data[i][j].house_num && housenumber_b==original_data[i][j+1].house_num)
                          {
                                float distance;
                                X=start_x-destination_x;
                                Y=start_y-destination_y;
                                distance=sqrt(pow(X,2)+pow(Y,2));
                                distance=distance*mile;
                                printf("The start place is very closed to the destination place.");
                                if (X>0 && Y>0)
                                printf("Head SouthWest ");
                                else if (X<0 && Y>0)
                                printf("Head SouthEast ");
                                else if (X>0 && Y<0)
                                printf("Head NorthWest ");
                                else if (X<0 && Y<0)
                                printf("Head NorthEest ");
                                else if (X>0 && Y==0)
                                printf("Head West ");
                                else if (X<0 && Y==0)
                                printf("Head Eest ");
                                else if (X==0 && Y<0)
                                printf("Head North ");
                                else if (X==0 && Y>0)
                                printf("Head South ");
                                
                                printf("on %s \n",start_street);
                                float miles,decimal;
                                int integer,feet;
                                distance=distance*10;
                                integer=distance/1;
                                decimal=distance-integer;
                                miles=(float)integer/10;   
                                feet=5280*decimal/10;
                                
                                if (miles==0)
                                     printf("the distance is %d foot.\n",feet);
                                else if (feet==0)
                                     printf("the distance is %.1f miles.\n",miles);                                
                                else if (miles>0 && feet>0)
                                     printf("the distance is %.1f miles and %d foot\n",miles,feet); 
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
                                  
                                  X=original_data[i][k].x-destination_x;
                                  Y=original_data[i][k].y-destination_y;
                                  newptr->distance=sqrt(pow(X,2)+pow(Y,2));
                                  newptr->next_node=NULL;
                                  current->next_node=newptr;
                                  current=newptr;
                          }
                          list_num++;//给终点加入adj_list，方便之后求turn by turn 
                          adj_list[list_num].unique_num=destination_unique;
                          adj_list[list_num].house_num[1]=destination_house;
                          strcpy(adj_list[list_num].street_name[1],destination_street);
                          adj_list[list_num].present_num=1;
                          
                          adj_link newptr,current;
                          adj_list[list_num].next_node=NULL;
                          current=&adj_list[list_num];
                          for (k=j;k<=j+1;k++)
                          {
                                  newptr=malloc(sizeof(struct adj_vertex));
                                  newptr->unique_num=original_data[i][k].unique_num;
                                  
                                  X=original_data[i][k].x-destination_x;
                                  Y=original_data[i][k].y-destination_y;
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
#endif
