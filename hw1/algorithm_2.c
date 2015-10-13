/*Algorithm2 is called degree of separation,using this algorithm can find out 
  the shortest length from one vertex to the rest of the vertexes.If a graph
  has n vertexes,so we can find n-1 pairs.And calculate the average length for
  each vertex.*/

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
       int level;//the score depends on the level
       struct queue *next_note;//*next_note points to the next vertex in the queue
};
typedef struct queue  * line;

main()
{
      FILE *f;
      char filename[50]={0};
      printf("input the name of the file:");
      scanf("%s",filename);//the file's name can be absolute path,include the .txt example: D:\\file1\\file2\\test.txt
      f=fopen(filename,"rb");//only read method to visit the file
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
      
      i=1;
      while(i<=people_num)//i represents the current vertex,it will go over all the vertex,this loop is to get the degree of separation
      {
          int number=1;//number is to remember how many vertexes have been saved in the queue,start at 1
          line head,present,new_ptr;//"head" is the head of the queue,"present" is the current indicator
          people_link temp2;//temp2 is to get the info from the  Adjacency list
          
          temp2=people_list[i].next_people;//gets the first node's info
          present=malloc(sizeof(struct queue)); //the queue is established by "present" 
          
          present->ID = temp2->ID;//copy all the info to "present"
          present->level=1;//the first time,level obviously be 1
          temp2=temp2->next_people;
          present->next_note=NULL;
          head=present;//head store the first node in the queue
          
          while (temp2!=NULL)//get all the nodes in the queue,because all the nodes connected to the start node must be in the queue
          {
                new_ptr=malloc(sizeof(struct queue));
                if (new_ptr==NULL)
                   break;
                new_ptr->ID=temp2->ID;
                new_ptr->level=1;//as the first level,it must be 1
                new_ptr->next_note=NULL;
                present->next_note=new_ptr;
                present=new_ptr;
                temp2=temp2->next_people;
                number++;//number increases 1,because one of the vertex is collected to the queue
                new_ptr=NULL;
          }

          people_list[i].score=number;//so far,score of the people_list[i] is the number of the first group of nodes
          if (number<people_num-1)//if number is biger than people_num-1,that means all the rest of vertexes are collected to the queue,then stop the calculation
          {
              line fake_head;//fake_head is the point that will be visited,after the visiting,fake_head will be moved to the next node in the queue
              fake_head=head;//firstly,fake_head euqals to head
              while (number<people_num-1)//also check if the number bigger than people_num-1
              {
                  int j;
                  for (j=1;j<=people_num;j++)//this loop is to find the fake_head matchs to which node in the Adjacency list 
                      if (fake_head->ID == people_list[j].ID)
                         break;
                  people_link temp3;//
                  temp3=people_list[j].next_people;//after find the fake_head's position in the Adjacency list,temp3 points to the next_people      
                  while (temp3!=NULL&&number<people_num-1)//the current Adjacency list will not be NULL and still remeber the number!
                  {
                        line scan;//using "scan" to visit all the nodes in the queue
                        scan=head;//                       
                        while(scan!=NULL)//check whether the temp3 is existed in the queue,if scan==NULL means temp3 can be a new element in queue 
                        {
                            if(temp3->ID==scan->ID)
                                break;
                            scan=scan->next_note;    
                        }
                        if (scan==NULL && temp3->ID!=people_list[i].ID)//if temp3 is a new element,take the temp3 in the queue
                        {
                            line Newptr;
                            Newptr=malloc(sizeof(struct queue));
                            if (Newptr==NULL)
                               break;
                            Newptr->ID=temp3->ID;
                            Newptr->level=fake_head->level+1;//check the fake_head's level,and plus 1 to be the new level for the new element 
                            Newptr->next_note=NULL;
                            present->next_note=Newptr;
                            present=Newptr;
                            people_list[i].score=people_list[i].score+present->level;//once there is an new element into the queue,update the score of the start vertex
                            number++;//number increase 1
                            Newptr=NULL;
                        }
                        temp3=temp3->next_people;
                  }//after this loop,means we visited all the nodes in the temp3 list 
                  fake_head=fake_head->next_note;//move to the next node in the queue                  
              }//if the number is equal to people_num-1,means we get all the nodes in queue,then stop                      
          }
          i++;
          present=NULL;           
      }//after this loop,means we get all the vertexes's degree of separation
      int k;
      for (k=1;k<=people_num;k++)//output the score
      {
          people_list[k].score=(double)people_list[k].score/(people_num-1);//divid n-1 pairs,beacuse each vertex has n-1 paths to rest of the nodes
          printf("The score of the ID.%d\t%s is:\t%f \n",people_list[k].ID,people_list[k].name,people_list[k].score);
      }
      //later use Bubble Sort from small to big
      float temp_score;
      int temp_id;
      char temp_name[10];
      for (j=1;j<=people_num;j++)//Bubble Sort method
      {
          for (k=1;k<people_num;k++) 
              if(people_list[k].score>people_list[k+1].score)
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
      int rank=1;//"rank" is to show the ranking of the current vertex
      int previous_rank=1;
      printf("the top%d are these notes:\n",TOP_NUM);
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
