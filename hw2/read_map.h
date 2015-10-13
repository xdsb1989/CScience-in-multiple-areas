#ifndef fit
#define fit
struct node_info{//include the information for each node
       char street_name[30];
       int x;
       int y;
       int house_num;
       int unique_num;//each node has an unique number which is some kind of ID
}original_data[30][20];//the original_data store the original data information

struct adj_vertex{//this structure is to build the adjancey list
       char street_name[5][30];//consider the node may have no more than 5 street name
       int house_num[5];//consider the node may have no more than 5 house number
       int present_num;//to save how many different house number and street_name the node has
       float distance;//distance between every two vertexes
       int unique_num;//That is the "ID" for each node
       int father_unique_num[5];//for one shortest way,there is no more than 5 father for one node
       int father_num;//number of each note's fathers(the father for the node is on the shortest path)
       float distance_to_start_node;//at this moment,the distance to the start node
       struct adj_vertex *next_node;
}adj_list[70];
typedef struct adj_vertex *adj_link;

int list_num=1;//list number is to remember how many different node in the graph
int street_num=1;//remember how many street in the graph
float mile;// the miles for one unit
int start_unique;//the unique number of start node
int destination_unique;//the unique number of destination node
float start_x;
float start_y;
float destination_x;
float destination_y;
int start_house;
int destination_house;
char start_street[20];//store the name of start street
char destination_street[20];//store the name of destination street

get_the_map(FILE *f)
{
      
      char street[20][30];
      fscanf(f,"%f",&mile);
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
               if (ch!='\n')//store the information of each vertex in the file
               {//generate the unique number for each different node
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
      
      for (j=1;j<=street_num;j++)//visit every street in the original data,and create the adjance list. 
      {
          i=1;
          while (original_data[j][i].unique_num!='\0')//loop will stop while there is no more data in present street
          {
                adj_link newptr,current;//create object to build the adjance list
                
                k=1;
                repeat_flag=0;//the flag to indicate if this node is repeated.
                while (adj_list[k].unique_num!='\0')//this loop is to chech if a protential node is already visited in the list
                {
                      if(original_data[j][i].unique_num==adj_list[k].unique_num)//if the node is visited
                      {
                          int temp;
                          repeat_flag=1;//set the flag as 1
                          
                          adj_list[k].present_num=adj_list[k].present_num+1;//means this node has one more street and one more house number
                          temp=adj_list[k].present_num;
                          adj_list[k].house_num[temp]=original_data[j][i].house_num;
                          strcpy(adj_list[k].street_name[temp],original_data[j][i].street_name);
                          
                          current=&adj_list[k];//find the current position in the list 
                          while (current->next_node!=NULL)//move to the end of the node's children 
                          {
                                current=current->next_node;
                          }
                          
                          if (original_data[j][i-1].unique_num!='\0')//if the node's left has another node,store this node as his child
                          {
                              int X,Y;
                              newptr=malloc(sizeof(struct adj_vertex));
                              newptr->unique_num=original_data[j][i-1].unique_num;
                              
                              X=original_data[j][i-1].x-original_data[j][i].x;
                              Y=original_data[j][i-1].y-original_data[j][i].y;
                              newptr->distance=sqrt(pow(X,2)+pow(Y,2));//store the distance from this node to his child
                              newptr->next_node=NULL;
                              current->next_node=newptr;
                              current=newptr;
                          }
                          if (original_data[j][i+1].unique_num!='\0')//if the node's right has another node,store this node as his child
                          {
                              int X,Y;
                              newptr=malloc(sizeof(struct adj_vertex));
                              newptr->unique_num=original_data[j][i+1].unique_num;
                              
                              X=original_data[j][i+1].x-original_data[j][i].x;
                              Y=original_data[j][i+1].y-original_data[j][i].y;
                              newptr->distance=sqrt(pow(X,2)+pow(Y,2));//store the distance from this node to his child
                              newptr->next_node=NULL;
                              current->next_node=newptr;
                              current=newptr;
                          }
                          break;
                      }
                      k++;
                }//
                
                if (repeat_flag==0)//flag==0 means this node has never been visited before,so that add one more line in the adjance list
                {
                      int temp;
                      adj_list[list_num].unique_num=original_data[j][i].unique_num;
                      adj_list[list_num].present_num=1;
                      temp=adj_list[list_num].present_num;
                      adj_list[list_num].house_num[temp]=original_data[j][i].house_num;
                      strcpy(adj_list[list_num].street_name[temp],original_data[j][i].street_name);
                      
                      adj_list[list_num].next_node=NULL;
                      current=&adj_list[list_num];
                      
                      if (original_data[j][i+1].unique_num!='\0')//if the node's right has another node,store this node as his child
                      {
                          int X,Y;
                          newptr=malloc(sizeof(struct adj_vertex));
                          newptr->unique_num=original_data[j][i+1].unique_num;
                          
                          X=original_data[j][i+1].x-original_data[j][i].x;
                          Y=original_data[j][i+1].y-original_data[j][i].y;
                          newptr->distance=sqrt(pow(X,2)+pow(Y,2));//store the distance from this node to his child
                          newptr->next_node=NULL;
                          current->next_node=newptr;
                          current=newptr;
                      }
                      if (original_data[j][i-1].unique_num!='\0')//if the node's left has another node,store this node as his child
                      {
                          int X,Y;
                          newptr=malloc(sizeof(struct adj_vertex));
                          newptr->unique_num=original_data[j][i-1].unique_num;
                          
                          X=original_data[j][i-1].x-original_data[j][i].x;
                          Y=original_data[j][i-1].y-original_data[j][i].y;
                          newptr->distance=sqrt(pow(X,2)+pow(Y,2));//store the distance from this node to his child
                          newptr->next_node=NULL;
                          current->next_node=newptr;
                          current=newptr;
                      }
                      list_num++;//after add one node in the list,list_num increase one more
                }     
                i++;//
          }//
      }
      list_num--;//after building the adjance list,the list_num needs to be minus 1. 
}

void direction(float x1,float yl,float x2,float y2,float x3,float y3)//define the direction in each intersection
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
      for (i=1;i<=street_num;i++)//check if the start street name is existed in the map
          if (strcmp(start_street,original_data[i][1].street_name)==0)
             break;
      if (i>street_num)
      {
          printf("The start street is not existed!\n");
          return;
      }
      else if(i<=street_num)//if the start street is existed
      { 
          j=1;
          while (original_data[i][j].unique_num!='\0')
          {
                  if (start_house==original_data[i][j].house_num)//if the start is the original vertex in the graph,then just take it
                  {
                      start_unique=original_data[i][j].unique_num;
                      int label;
                      label=Index(start_unique);
                      //adj_list[label].distance_to_start_node=0.0;
                      printf("the coordinate of start is:x=%d,y=%d\n",start_unique/100,start_unique%100);
                      break;
                  }
                  else//if it is not the original vertex
                  {
                      if (start_house<original_data[i][j].house_num && start_house>original_data[i][j+1].house_num && original_data[i][j+1].unique_num!='\0' || start_house>original_data[i][j].house_num && start_house<original_data[i][j+1].house_num && original_data[i][j+1].unique_num!='\0')   
                      {//find the insert position
                          if (strcmp(start_street,destination_street)==0 && start_house==destination_house)//if the start node has the same street name and house number as the destination node
                          {
                                printf("The start place is the same as the destination place!!\n");
                                return;
                          }
                          housenumber_a=original_data[i][j].house_num;//store the previous house number and the next house number
                          housenumber_b=original_data[i][j+1].house_num;
                          
                          float factor;//factor is to find the precise position in between two vertexes
                          float X,Y;
                          factor=(float)(original_data[i][j].house_num-start_house)/(original_data[i][j].house_num-original_data[i][j+1].house_num);
                          
                          start_x=(original_data[i][j+1].x-original_data[i][j].x)*factor + original_data[i][j].x;
                          start_y=(original_data[i][j+1].y-original_data[i][j].y)*factor + original_data[i][j].y;
                          printf("the coordinate of start is:x=%f,y=%f\n",start_x,start_y);
                          start_unique=1;//if the start node is an new node which between two vertexes,then give it a special unique number
                          list_num++;//add one more line in the adjance list
                          adj_list[list_num].unique_num=start_unique;//
                          adj_list[list_num].house_num[1]=start_house;
                          strcpy(adj_list[list_num].street_name[1],start_street);
                          adj_list[list_num].present_num=1;//only has one house number and street name
                          adj_list[list_num].distance_to_start_node=0.0;
                              
                          adj_link newptr,current;
                          adj_list[list_num].next_node=NULL;
                          current=&adj_list[list_num];//
                          int k;
                          for (k=j;k<=j+1;k++)
                          {
                                  newptr=malloc(sizeof(struct adj_vertex));
                                  newptr->unique_num=original_data[i][k].unique_num;
                                  
                                  X=original_data[i][k].x-start_x;
                                  Y=original_data[i][k].y-start_y;
                                  newptr->distance=sqrt(pow(X,2)+pow(Y,2));//store the distance from this node to his child
                                  newptr->next_node=NULL;
                                  current->next_node=newptr;
                                  current=newptr;
                          }
                          break;
                      }
                      j++;
                  }
          }
          if (original_data[i][j].unique_num=='\0')//if the house can not be found       
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
                      {//find the position to insert
                          float factor;
                          float X,Y;
                          factor=(float)(original_data[i][j].house_num-destination_house)/(original_data[i][j].house_num-original_data[i][j+1].house_num);
                          
                          destination_x=(original_data[i][j+1].x-original_data[i][j].x)*factor + original_data[i][j].x;
                          destination_y=(original_data[i][j+1].y-original_data[i][j].y)*factor + original_data[i][j].y;
                          printf("the coordinate of destination is:x=%f,y=%f\n",destination_x,destination_y);
                          
                          if (strcmp(start_street,destination_street)==0 && housenumber_a==original_data[i][j].house_num && housenumber_b==original_data[i][j+1].house_num)
                          {//if the start node and the destination node are in two same vertexes,then just output the distance between each other
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
                          for (k=j;k<=j+1;k++)//add destination node as his neighbours' children.j is the label for his two neighbours
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
                          list_num++;//add destination node to the adjance list 
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
          if (original_data[i][j].unique_num=='\0')//if the house can not be found       
          {
              printf("The destination house number is not existed!\n");
              return;
          }        
      }
}
#endif
