/*algorithm3 base on the BFS algorithm,but the goal is to find out which vertex appears the most times
  in a graph.And if there are sevearl paths between two vertexes,they will share the importance
*/

#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define TOP_NUM 3  //TOP_NUM is for the out put,because we will find the top 3 vertexes and the ties

struct people_card{//people_card is for saving every vertex's info
       char name[10];//name[] is to save the name of the vertex
       int ID;//ID is to calculate the order and distinguish each vertex
       double score;
       struct people_card *next_people;//using the Adjacency list,*next_people links to the connected vertexes one by one
}*people_list;//the people_list[] array is to save all the vertexes
typedef struct people_card  *people_link;//create *people_link to declare other indicators

struct queue{//queue is the structor to save the collected vertexes which can be sure is the shortest vertex
       int ID;//for each vertex only save the ID
       struct queue *next_note;
       int **previous_notes;//the matrix is to save each way and the passing vertexes
       int previous_ways;//previous_ways is to save the number of the paths to the start node
};
typedef struct queue  * line;

void function(line *,line *,line *,int parents,int children,int people_num,int i,int visited_num);//the recursion function is to calculate the passing nodes
float *note_score;//using a array[] to save the score of each node,it will be updated dynamic

main()
{
      FILE *f;
      char filename[50]={0};
      printf("input the name of the file:");
      scanf("%s",filename);//the file's name can be absolute path,include the .txt example: D:\\file1\\file2\\test.txt
      f=fopen(filename,"r");//only read method to visit the file
      if (f==NULL)//if can not open the file,stop the program
      {
         printf("OMG,the file is not existed!\n");
         system("pause");
         return 0;
         }
           
      char A[10];//A and B is some temp variable,will not be used,just to calculate the lines in the file.
      char B[10];
      int i=0;
      while(!feof(f))//calculate how many lines are there in the file,and save it in i
      {
        fscanf(f,"%s %s\n",A,B);
        i++;
      }
      
      char ch1[i][10];//ch1 is to save the left column in the file
      char ch2[i][10];//ch2 is to save the right column in the file
      f=fopen(filename,"r");//reopen the file
      i=0;
      while(!feof(f))
      {
        fscanf(f,"%s %s\n",&ch1[i],&ch2[i]);//scan the file line by line and save the name in two array
        i++;
      }
      fclose(f);//close thr file
      
      people_list=malloc(sizeof(struct people_card)*i);//declare a array[] which has i elements
      
      int lines;
      int people_num=1;//in order to anaylze the data,people_list[] from 1 to n,so people_num starts at 1
    
      for (lines=0;lines<i;lines++)//establish a list people_list[] which includes the name of vertexes and the ID
      {
          if (lines==0)//wihle at the first line,just save the two vertexes in the people_list[]
          {
             strcpy(people_list[people_num].name,ch1[lines]);//use the people_num to be the label
             people_list[people_num].ID=people_num;
             strcpy(people_list[people_num+1].name,ch2[lines]);
             people_list[people_num+1].ID=people_num+1;
             people_num=people_num+2;//after these two steps,the number of people increase 2
          }
          else//while it is not the first line in the file
          {
              int mark;//mark to be the label that scan all the existed elements in the people_list[] 
              for (mark=1;mark<people_num;mark++)//mark from 1 to current people_num 
                  if (strcmp(people_list[mark].name,ch1[lines])==0)//this is to use current ch1[mark] compare the whole people_list[]
                     break; 
              if (mark==people_num)//if the ch1[mark] is an new element,take it into the people_list[]
              {
                  strcpy(people_list[people_num].name,ch1[lines]);
                  people_list[people_num].ID=people_num;
                  people_num++;
                  }
              for (mark=1;mark<people_num;mark++)//this is to use current ch2[mark] compare the whole people_list[]
                  if (strcmp(people_list[mark].name,ch2[lines])==0)
                     break;
              if (mark==people_num)//if the ch2[mark] is an new element,take it into the people_list[]
              {
                  strcpy(people_list[people_num].name,ch2[lines]);
                  people_list[people_num].ID=people_num;
                  people_num++;
                  } 
          }
      }
      
      int j;
      for (j=1;j<people_num;j++)//create the  Adjacency list for every vertex
      {
          int k;
          people_link newptr,current;//the "current" is to save the current point,newptr is to store the new info
          
          people_list[j].next_people=NULL;//set the first node's next address points to the NULL 
          current=&people_list[j];//transfer the address to the current
          
          for (k=0;k<i;k++)//i still represents the totaly lines of the file
          {
              if (strcmp(people_list[j].name,ch1[k])==0)//compare with the ch1[k],if the node in this position,take ch2[k] as its children
              {    
                  newptr=malloc(sizeof(struct people_card));
                  strcpy(newptr->name,ch2[k]);
                  
                  int n=1;
                  while(strcmp(ch2[k],people_list[n].name)!=0)//search ch2[k]'s name in people_list[],and copy the ID to the newptr->ID
                  {
                      n++;
                  }
                  newptr->ID=people_list[n].ID;
                  newptr->next_people=NULL;
                  current->next_people=newptr;
                  current=newptr;
              }
              else if (strcmp(people_list[j].name,ch2[k])==0)//compare with the ch2[k],if the node in this position,take ch1[k] as its children
              {    
                  newptr=malloc(sizeof(struct people_card));
                  strcpy(newptr->name,ch1[k]);
                  
                  int n=1;
                  while(strcmp(ch1[k],people_list[n].name)!=0)//search ch1[k]'s name in people_list[],and copy the ID to the newptr->ID
                  {
                      n++;
                  }
                  newptr->ID=people_list[n].ID;
                  newptr->next_people=NULL;
                  current->next_people=newptr;
                  current=newptr;
              }
          }//after this loop,one of the Adjacency list is finished          
      }//after this loop,all the Adjacency list is finished
      people_link temp;//set a temp variable to output each vertex's connected vertexes
      people_num=people_num-1;//for me to easy analyze
      for (j=1;j<=people_num;j++)//output each vertex's connected vertexes
      {
          temp=people_list[j].next_people;
          printf("the people who connect with %s are:\n",people_list[j].name);
          while (temp!=NULL)
          {
                printf("%d\t%s\n",temp->ID,temp->name);
                temp=temp->next_people;
          }
      }
      
      note_score=malloc(sizeof(float)*(people_num+1));//note_score[] to save the score of each vertex,it will be updated
      
      for (i=1;i<=people_num;i++)//firstly reset as 0 
          note_score[i]=0.0;
      
      i=1;
      while(i<=people_num)////i represents the current vertex,it will go over all the vertex 
      {
          int number=1;//number is to remember how many vertexes have been saved in the queue,start at 1
          int parents=1;//parents is the current previous nodes
          int children=0;//children is the new coming nodes
           
          line head,present,new_ptr;//"head" is the head of the queue,"present" is the current indicator
          people_link temp2;////temp2 is to get the info from the  Adjacency list 
          
          temp2=people_list[i].next_people;//gets the first node's info
          present=malloc(sizeof(struct queue)); //the queue is established by "present" 
          present->ID = temp2->ID;
          temp2=temp2->next_people;
          present->previous_ways=1;//set the previous_ways as 1
          
          present->previous_notes=malloc(sizeof(int*)*people_num);//create a matrix to store the number of paths and the passing nodes
          int j;
          for (j=0;j<people_num;j++)//it is a two dimension array
              present->previous_notes[j]=(int*)malloc(sizeof(int)*people_num);
 
          present->previous_notes[1][0]=0;//using previous_notes[i][0] to store the length of the path, initial length is 0
          present->next_note=NULL;
          head=present;//head store the first node in the queue
          
          while (temp2!=NULL)//get all the nodes in the queue,because all the nodes connected to the start node must be in the queue
          {
                new_ptr=malloc(sizeof(struct queue));
                if (new_ptr==NULL)
                   break;
                new_ptr->ID=temp2->ID;
                //new_ptr->level=1;
                new_ptr->next_note=NULL;
                new_ptr->previous_ways=1;
                
                new_ptr->previous_notes=malloc(sizeof(int*)*people_num);//it is a two dimension array to store the paths and the passing nodes
                for (j=0;j<people_num;j++)
                    new_ptr->previous_notes[j]=(int*)malloc(sizeof(int)*people_num);
                
                new_ptr->previous_notes[1][0]=0;//initial length is 0
                present->next_note=new_ptr;
                present=new_ptr;
                temp2=temp2->next_people;
                number++;//number increases 1,because one of the vertex is collected to the queue
                parents++;//parents is to store the number of the parents nodes 
                new_ptr=NULL;
          }// 

          if (number<people_num-1)//if number is biger than people_num-1,that means all the rest of vertexes are collected to the queue,then stop the calculation
          {
              line fake_head;//fake_head is the point that will be visited,after the visiting,fake_head will be moved to the next node in the queue 
              fake_head=head;
              function(&head,&fake_head,&present,parents,children,people_num,i,parents);//the function is to figure out the betweenness
          }
          i++;
      }
      for (j=1;j<=people_num;j++)
      {
          people_list[j].score=note_score[j];
          printf("The score of the ID.%d\t%s is:\t%f\n",people_list[j].ID,people_list[j].name,people_list[j].score);
      }
      
      //later use Bubble Sort from big to small
      float temp_score;
      int temp_id;
      char temp_name[10];
      int k;
      for (j=1;j<=people_num;j++)//Bubble Sort method
      {
          for (k=1;k<people_num;k++) 
              if(people_list[k].score<people_list[k+1].score)
              {
                  temp_score=people_list[k].score;
                  temp_id=people_list[k].ID;
                  strcpy(temp_name,people_list[k].name);
                  people_list[k].score=people_list[k+1].score;
                  people_list[k].ID=people_list[k+1].ID;
                  strcpy(people_list[k].name,people_list[k+1].name);
                  people_list[k+1].score=temp_score;
                  people_list[k+1].ID=temp_id;
                  strcpy(people_list[k+1].name,temp_name);
              }
      }
      
      int flag;//flag is to mark how many vertex need to output
      int count=1;
      j=2;
      while(j<=people_num)//this loop is to output the top 3 and their ties
      {
          if (people_list[j].score==people_list[j-1].score)//if the second number euqals to the first number,add more
          {
              while (people_list[j].score==people_list[j-1].score)//if the later number doesn't equal to the previous number,stop.
              {
                    flag=j;
                    count++;
                    j++;
              }
              if (count>=TOP_NUM)//if already over TOP_NUM,stop
                    break;
          }
          else if (count<TOP_NUM)//if count less than TOP_NUM,continue
          {
               flag=j;
               count++;
               j++;
          }
          else if (count>=TOP_NUM)//if already over TOP_NUM,stop
               break;
      }
      printf("the top%d are these notes:\n",TOP_NUM);
      int rank=1;//"rank" is to show the ranking of the current vertex
      int previous_rank=1;
      for (j=1;j<=flag;j++)
      {
          if (j==1)
             printf("The score of the NO.%d is:ID.%d\t%s\tis:%f \n",rank,people_list[j].ID,people_list[j].name,people_list[j].score);
          else if (people_list[j].score!=people_list[j-1].score)//if the later score doesn't equal to the previous score,it will get a lower ranking
          {  
             rank=rank+previous_rank;
             previous_rank=1;
             printf("The score of the NO.%d is:ID.%d\t%s\tis:%f \n",rank,people_list[j].ID,people_list[j].name,people_list[j].score);   
          }
          else if (people_list[j].score==people_list[j-1].score)//if the later score equals to the previous score,it sitll gets the same ranking
          {  
             previous_rank++;
             printf("The score of the NO.%d is:ID.%d\t%s\tis:%f \n",rank,people_list[j].ID,people_list[j].name,people_list[j].score);   
          }
      }
      system("pause");
}

void function(line *head,line *fake_head,line *present,int parents,int children,int people_num,int i,int visited_num)
{
      while (parents>0)//if parents is over,continue another loop
      {
          int j;
          for (j=1;j<=people_num;j++)////this loop is to find the fake_head matchs to which node in the Adjacency list 
              if ((*fake_head)->ID == people_list[j].ID)
                  break;
          people_link temp3;////after find the fake_head's position in the Adjacency list,temp3 points to the next_people     
          temp3=people_list[j].next_people;        
          while (temp3!=NULL)//the current Adjacency list will not be NULL
          {
                        line scan;//using "scan" to visit all the nodes in the queue 
                        scan=(*head);//scan equals to the original head
                        int count=1;//count is to check whether it is a new node or a repeat node.
                                               
                        while(scan!=NULL)//check whether the temp3 is existed in the queue,if scan==NULL means temp3 can be a new element in queue 
                        {
                            if(temp3->ID==scan->ID)
                                break;
                            scan=scan->next_note; 
                            count++;//count can be a flag,later will be used
                        }
                        if (scan==NULL && temp3->ID!=people_list[i].ID)//if temp3 is a new element,take the temp3 in the queue
                        {
                            line Newptr;
                            Newptr=malloc(sizeof(struct queue));
                            if (Newptr==NULL)
                               break;
                            Newptr->ID=temp3->ID;
                            Newptr->previous_ways=(*fake_head)->previous_ways;//if it is a new node,inhert its father's number of paths 
                            Newptr->next_note=NULL;
                            
                            Newptr->previous_notes=malloc(sizeof(int*)*(people_num-1));//create a matrix
                            for (j=0;j<people_num;j++)
                                Newptr->previous_notes[j]=(int*)malloc(sizeof(int)*(people_num-1));
                            
                            for (j=1;j<=(*fake_head)->previous_ways;j++)//copy the father's paths to the new node
                            {
                                int length=(*fake_head)->previous_notes[j][0];
                                int n;
                                Newptr->previous_notes[j][0]=length+1;//new length is one more than previous length
                                
                                for (n=1;n<=length;n++)
                                    Newptr->previous_notes[j][n]=(*fake_head)->previous_notes[j][n];
                                Newptr->previous_notes[j][length+1]=(*fake_head)->ID;//add the father as the last node in the path
                            }   
                            (*present)->next_note=Newptr;
                            (*present)=Newptr;
                            children++;//gets a new children,later the parents will be equaled as children.
                            Newptr=NULL;
                        }
                        if (scan!=NULL && count>visited_num && temp3->ID!=people_list[i].ID)//if the node is a repeated node,count bigger than visited_num means the new node is a repeated node
                        {
                            int temp_ways=scan->previous_ways;
                            int k;
                            scan->previous_ways=scan->previous_ways+(*fake_head)->previous_ways;//the new path will be current paths plus father's paths
                            for (j=1,k=temp_ways+1;j<=(*fake_head)->previous_ways;j++,k++)
                            {
                                int length=(*fake_head)->previous_notes[j][0];
                                int n;
                                scan->previous_notes[k][0]=length+1;
                                for (n=1;n<=length;n++)
                                    scan->previous_notes[k][n]=(*fake_head)->previous_notes[j][n];
                                scan->previous_notes[k][length+1]=(*fake_head)->ID;
                            }
                        }
                        temp3=temp3->next_people;
          }//after this loop,means we visited all the nodes in the temp3 list  
          (*fake_head)=(*fake_head)->next_note;//move to the next node in the queue     
          parents--;//the number of parents minus 1
    }
    
    if (children>0)//if children more than 0,means the process is working,and we need to calculate the score.Oterwise,finish the calculation
    {
        visited_num=visited_num+children;//now the new visited_num will increase children times
        parents=children;//the children change to the parents
        
        line temp_head;
        temp_head=(*fake_head);//temp_head right now points to the first children 
        int j;
        while (temp_head!=NULL)//this loop is to figure out how many times for each node appears in the shortest path 
        {
            int ways;
            float present_score;
            ways=temp_head->previous_ways;//gets the number of path
            present_score=(float)1/ways;//share the importance,so we need to divid paths
            int k;
            for (k=1;k<=ways;k++)//calculate each path 
            {
                int length=temp_head->previous_notes[k][0];//get the length of each path
                int n;
                int label;
                for (n=1;n<=length;n++)//visit all the vertexes in the current path
                {
                    label=temp_head->previous_notes[k][n];//label is to save the ID of each vertex which appears in the path
                    note_score[label]=note_score[label]+present_score;//note_score[label] means NO.label has the score xxx
                }
            }
            temp_head=temp_head->next_note;
        } 
        children=0;//reset children as 0
        return function(head,fake_head,present,parents,children,people_num,i,visited_num);//use the recursion function to continue calculate the rest of the vertexes
    }
}
