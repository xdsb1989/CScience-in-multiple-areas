#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include <stdbool.h>
#include"read_file.c"
struct avaiable_schedule{//this is a positon index for finding whether the current case has enough attnorys
       int attnory_id[10];//which attnorys are there in this position
       int present_num;//the number of the attnorys
       bool position_bit[6];//the specialist in the current positon
};

struct search_index{//once get an unique number,this is to help find the correct position
       int index[20];
       int item_num;
}*index_list;//this list is to store the positon which is going to check

struct result{//the complete solution find the schedule
       int case_id;
       int attnory_id;
};
struct result *result_array;

struct attnory_store{//this is for output to the file,each attnory has couple of assigned cases
       int case_num;
       int case_id[10];
};

int fit_cases=0;//fit_cases indicate how many cases have been assigned to the attnorys
int stop_sign=0;//when stop_sign=1,means find the complete schedule,then stop the program
int tree_nodes=0;//how many attempted cases has been assigned,even through some of them will not be scheduled in the final result

void Schedule_Plan(bool *,struct avaiable_schedule *,int ,int *);//plan the schedule,using the back track method
void check_avaiable_attnory(bool *,int *,struct avaiable_schedule *);//for current level,finding how many suitable attnorys for each case
void find_min_attnory_for_eachcase(int *,int *,bool *,int *,int *);//find the minimal number,min_ties
void after_match_the_case(bool *,int *,int *,int *,int *);//after assign an attnory to the case,what is the rest part of this attnory,and where to add in

main()
{
      clock_t begin,end;
      char file_name[20]="toy-attorney";
      char input[5];
      printf("input the number between 1 -- 7:");
      scanf("%s",input);
      strcat(file_name,input);
      strcat(file_name,".txt");
      FILE *f;
      f=fopen(file_name,"r");
      
      begin=clock();
      readfile(f);
      fclose(f);
      struct avaiable_schedule  schedule_array[16];//this is the main list,which store the avaiable time for the attnorys
      
      int i;
      int workload[attnory_num+1];
      for (i=1;i<=attnory_num;i++)
            workload[i]=0;
      
      for (i=1;i<=15;i++)
            schedule_array[i].present_num=0;
      for (i=1;i<=15;i++)
      {
            int num;
            num=get_number(i);
            int a,b;
            a=num/10;
            b=num%10;
            int l;
            for (l=0;l<=5;l++)
                schedule_array[i].position_bit[l]=0;
            for (l=a;l<a+b;l++)
                schedule_array[i].position_bit[l]=1;
      }
      
      for (i=1;i<=attnory_num;i++)
      {
            Link_avaiable_time current;
            int position;
            current=attnory_list[i].next_time;//attnory_list[] is to store all the attnorys' time
            while (current!=NULL)
            {
                  int a,b;
                  int j;
                  a=(current->unique_num)/10;
                  b=(current->unique_num)%10;
                  for (j=a;j<a+b;j++)
                      attnory_list[i].attnory_bit[j]=1;
                  
                  position=current->aviable_position;
                  schedule_array[position].present_num++;
                  j=schedule_array[position].present_num;
                  schedule_array[position].attnory_id[j]=i;
                  current=current->next_time;
            }
      }
      int search_table[5][5]={{1,2,3,4,5},{0,6,7,8,9},{0,0,10,11,12},{0,0,0,13,14},{0,0,0,0,15}};
      index_list=malloc(sizeof(struct search_index)*16);
      
      int j;
      for (i=1;i<=15;i++)//index_list[] is to store which position we need to jump to
          index_list[i].item_num=0;
      for (i=0;i<5;i++)//this loop is to store which start-duration I need to check
          for (j=0;j<5;j++)
          {
              if (search_table[i][j]!=0)
              {
                  int label;
                  int n,m,l;
                  label=search_table[i][j];//label is the index for index_list[]
                  for (n=i;n>=0;n--)
                      for (m=j;m<5;m++)
                      {
                          index_list[label].item_num++;//item_num for index_list[label] will be increase 1.
                          l=index_list[label].item_num;
                          index_list[label].index[l]=search_table[n][m];
                      }
              }
          }
      
      result_array=malloc(sizeof(struct result)*(case_num+1));
      
      
      bool present_case[16];
      for (i=1;i<=case_num;i++)//present_case[] is the cases index which can be used in present level
          present_case[i]=1;
      Schedule_Plan(present_case,schedule_array,case_num,workload);//present_case is the cases which can be used right now,schedule_array[] is the current suitable array
      
      int cases_for_attnory[attnory_num+1];
      int days_for_attnory[attnory_num+1];
      for (i=1;i<=attnory_num;i++)
      {
          cases_for_attnory[i]=0;
          days_for_attnory[i]=0;
      }
          
      if (stop_sign==1)
      {    
          printf("there is a solution!\n");
          for (i=1;i<=case_num;i++)
          {
              int j;
              for (j=1;j<=case_num;j++)
                  if (i==result_array[j].case_id)
                       printf("case id:%d --- attnory id:%d\n",result_array[j].case_id,result_array[j].attnory_id);
              
              int cass_id,attnory_id,days;
              cass_id=result_array[i].case_id;
              attnory_id=result_array[i].attnory_id;
              
              cases_for_attnory[attnory_id]++;
              days=events_list[cass_id].Duration;
              days_for_attnory[attnory_id] = days_for_attnory[attnory_id] + days;
          }
          int attnory_without_case=0;
          int min_case , max_cases , min_days , max_days;
          int sum_cases=0 , sum_days=0;
          float average_cases , average_days;
          float sum_Std_cases=0 , sum_Std_days=0;
          float SD_case , SD_days;
          
          min_case=cases_for_attnory[1];
          max_cases=cases_for_attnory[1];
          min_days=days_for_attnory[1];
          max_days=days_for_attnory[1];
          
          for (i=1;i<=attnory_num;i++)
          {
              //printf("id:%d --- cases:%d --- days:%d\n",i,cases_for_attnory[i],days_for_attnory[i]);
              if (cases_for_attnory[i]==0)
                   attnory_without_case++;
              if (cases_for_attnory[i]<min_case)
                   min_case=cases_for_attnory[i];
              if (cases_for_attnory[i]>max_cases)
                   max_cases=cases_for_attnory[i];
              if (days_for_attnory[i]<min_days)
                   min_days=days_for_attnory[i];
              if (days_for_attnory[i]>max_days)
                   max_days=days_for_attnory[i];
              sum_cases = sum_cases + cases_for_attnory[i];
              sum_days = sum_days + days_for_attnory[i];
          }
          average_cases=(float)sum_cases/attnory_num;
          average_days=(float)sum_days/attnory_num;
          
          
          for (i=1;i<=attnory_num;i++)
          {
              sum_Std_cases = (cases_for_attnory[i]-average_cases)*(cases_for_attnory[i]-average_cases) + sum_Std_cases;
              sum_Std_days  = (days_for_attnory[i]-average_days)*(days_for_attnory[i]-average_days) + sum_Std_days;
          }
          SD_case=sqrt(sum_Std_cases/attnory_num);
          SD_days=sqrt(sum_Std_days/attnory_num);
          
          printf("Number of attorneys without any cases:%d\n",attnory_without_case);
          printf("Std, min, and max number of scheduled cases for an attorney:\n");
          printf("Std:%f min:%d max:%d\n",SD_case,min_case,max_cases);
          printf("Std, min, and max number of scheduled days for an attorney:\n");
          printf("Std:%f min:%d max:%d\n",SD_days,min_days,max_days);
          
          //*********//the rest part is output the file//********//
          struct attnory_store attnory_case_list[attnory_num+1];
          for (i=1;i<=attnory_num;i++)
              attnory_case_list[i].case_num=0;
          
          for (i=1;i<=attnory_num;i++)
          {
              int j;
              for (j=1;j<=case_num;j++)
              {
                  if (result_array[j].attnory_id == i)
                  {
                        int a;
                        attnory_case_list[i].case_num++;
                        a = attnory_case_list[i].case_num;
                        attnory_case_list[i].case_id[a]=result_array[j].case_id;
                  }
              }
          }
          
          for (i=1;i<=attnory_num;i++)
          {
              attnory_list[i].store_array[5]=0;
              int j;
              for (j=1;j<=attnory_case_list[i].case_num;j++)
              {
                  int case_id,m;
                  case_id=attnory_case_list[i].case_id[j];
                  for (m=1;m<=5;m++)
                  {
                       if (events_list[case_id].case_bit[m]==1)
                            attnory_list[i].store_array[m]=case_id;
                  }
              }
          }
          
          FILE *f_write;
          f_write=fopen("workload_Schedule_file.txt","w");
          
          
          for (i=1;i<=attnory_num;i++)
          {
              int j;
              fprintf(f_write,"%-10s",attnory_list[i].name_attnory);
              for (j=1;j<=5;j++)
              {
                  if (attnory_list[i].store_array[j]!=0)
                  {
                       int caseid;
                       char temp_str[15];
                       caseid=attnory_list[i].store_array[j];
                       strcpy(temp_str , events_list[caseid].event);
                       strcat(temp_str,":");
                       strcat(temp_str , events_list[caseid].judge_name);
                       
                       fprintf(f_write,"%-12s",temp_str);
                  }
                  else if (attnory_list[i].store_array[j]==0)
                  {
                       if (attnory_list[i].attnory_bit[j]==1)
                            fprintf(f_write,"  Y         ");
                       else if (attnory_list[i].attnory_bit[j]==0)
                            fprintf(f_write,"  N         ");
                  }
              }
              fprintf(f_write,"\n");
          }
      }
      else if (stop_sign==0)
          printf("there is no solution!\n");
      
      end=clock();
      float time;
      time=(float)(end-begin)/CLOCKS_PER_SEC;
      printf("the number of tree nodes is:%d\nthe time is:%.3f seconds,%d ms\n",tree_nodes,time,end-begin);
      system("pause");
}

void Schedule_Plan(bool *present_case,struct avaiable_schedule *schedule_array,int current_case_num,int *workload)
{
      if (current_case_num==0 || stop_sign==1)
          return;
      
      int case_attnory_num[case_num+1];//case_attnory_num[] is to store how many attnorys are avaiable for each case
      int i;
      for (i=1;i<=case_num;i++)
          if (present_case[i]==1)
              case_attnory_num[i]=0;
      check_avaiable_attnory(present_case,case_attnory_num,schedule_array);//after this function we will have the "case_attnory_num[]" array
      
      for (i=1;i<=case_num;i++)
          if (present_case[i]==1)
               ;//printf("%d --- %d\n",i,case_attnory_num[i]);
      
      int min;
      int min_lawyer_case[case_num];//min_lawyer_case[] is to store which cases have the min attnorys.
      int min_ties=0;//"min_ties" is to store the number of the cases which have the min attnorys
      find_min_attnory_for_eachcase(&min,case_attnory_num,present_case,min_lawyer_case,&min_ties);//after this function,we get the min_lawyer_case[]
      
      if (min==0)
      {
           //printf("can not get the schedule,some of the case have no avaiable attnory!\n");
           return;
      }
      int longest_duration;
      int temp_index;
      for (i=1;i<=min_ties;i++) 
      {
          if (i==1)
          {
              int a;
              a=min_lawyer_case[i];
              longest_duration=events_list[a].Duration;
              temp_index=a;
          }
          else
          {
              int a;
              a=min_lawyer_case[i];//find the min_attnory case,then compare who has a longer duration
              if (events_list[a].Duration>=longest_duration)
              {
                    longest_duration=events_list[a].Duration;
                    temp_index=a;//finally the "temp_index" is the choosen case id
              }
          }
      }
      present_case[temp_index]=0;//set the choosen case's bool value as 0,because this case has been selected,and will not be used in the next level
      //printf("case id:%d --- duration:%d\n",temp_index,longest_duration);
      int position=events_list[temp_index].case_position;//"temp_index" is the selected case id,and the "position" is the checking position
      
      tree_nodes++;//once we choose a case,which means we can move the case to the tree structure.
      fit_cases++;//means we can get one more case,
      result_array[fit_cases].case_id = temp_index;//assgin a case to the "result_array[]"
      
      bool case_bitset[6];
      for (i=0;i<=5;i++)//use "case_bitset" to represent the current case's start day and duration
           case_bitset[i] = events_list[temp_index].case_bit[i];
      
      int selected_position[index_list[position].item_num+1];
      int selected_num=0;
      
      for (i=1;i<=index_list[position].item_num;i++)//this loop is to choose which position has the attnory that is avaiable for the current case
      {
            int label;
            label=index_list[position].index[i];
            if (schedule_array[label].present_num>0)
            {
                 selected_num++;
                 selected_position[selected_num]=label;
            }
      }
      
      //the following five arrays are the basic data to order the branches"attnorys".
      bool avaiable_array[selected_num+1];//this array is to store which position can be used,means after assgin this position to the case,no case will be 0 avaiable attnory
      int min_array[selected_num+1];//store the min avaiable attnory in each selected position
      int min_ties_array[selected_num+1];//store the min_ties in each selected position
      int summary_array[selected_num+1];//store the summary_avaiable attnorys in each selected position
      int section_array[selected_num+1];//store how many sections has been made after choosing the selected position
      
      for (i=1;i<=selected_num;i++)
           avaiable_array[i]=1;
      
      for (i=1;i<=selected_num;i++)//this loop is to indicate which position you need to check
      {
           int label;
           label=selected_position[i];//each "label" will go to the "schedule_array[label]" to find the bit set
           schedule_array[label].present_num--;//means for the list in this position,we take off one of them
           int j;
           bool temp_bitset[6];
           for (j=0;j<=5;j++)//assgin the bitset to a "temp_bitset",because using the temp_bitset is easy to calculate and do some operation
                temp_bitset[j] = schedule_array[label].position_bit[j];
           
           for (j=1;j<=5;j++)//if the have the same value,assgin the value as 0
                if (temp_bitset[j]==case_bitset[j])
                     temp_bitset[j]=0;
           
           int start_1=0,start_2=0,duration_1=0,duration_2=0;
           int unique_1,unique_2;
           int position_1,position_2;
           
           after_match_the_case(temp_bitset,&start_1,&start_2,&duration_1,&duration_2);//after this fuction,we will get at most two start day
           
           if (start_1!=0 && start_2!=0)
           {
                section_array[i]=2;//store the sections after the operation
                unique_1=start_1*10+duration_1;
                unique_2=start_2*10+duration_2;
                position_1=get_position(unique_1);
                position_2=get_position(unique_2);
                
                schedule_array[position_1].present_num++;
                schedule_array[position_2].present_num++;
           }
           else if (start_1!=0 && start_2==0)
           {
                section_array[i]=1;//store the sections after the operation
                unique_1=start_1*10+duration_1;
                position_1=get_position(unique_1);
                schedule_array[position_1].present_num++;
           }
           else if (start_1==0 && start_2==0)
                section_array[i]=1;//store the sections after the operation
           
           int temp_case_attnory_num[case_num+1];//temp array to store how many avaiable attnorys are suitable for each case
           for (j=1;j<=case_num;j++)
                if (present_case[j]==1)
                    temp_case_attnory_num[j]=0;
           check_avaiable_attnory(present_case,temp_case_attnory_num,schedule_array);
           //after this function,we get a new array "temp_case_attnory_num[]" which shows how many attnorys are avaiable for each case
           
           //refresh the orginal "schedule_array[]",add something and minus something
           schedule_array[label].present_num++;
           if (start_1!=0 && start_2!=0)
           {
                schedule_array[position_1].present_num--;
                schedule_array[position_2].present_num--;
           }
           else if (start_1!=0 && start_2==0)
                schedule_array[position_1].present_num--;
           
           for (j=1;j<=case_num;j++)
               if (present_case[j]==1)
                    ;//printf("%d --- %d\n",j,temp_case_attnory_num[j]);
           
           int smallest=10,smallest_ties=0,sum=0;
           int temp_array[case_num];
           find_min_attnory_for_eachcase(&smallest,temp_case_attnory_num,present_case,temp_array,&smallest_ties);
           
           if (smallest==0)//if the min number is 0,then we will not choose any attnory from this position,set the "avaiable_array[i]" as 0.
                avaiable_array[i]=0;
           
           min_array[i]=smallest;
           min_ties_array[i]=smallest_ties;
           
           for (j=1;j<=case_num;j++)
               if (present_case[j]==1)
                    sum = temp_case_attnory_num[j] + sum;
           summary_array[i]=sum;
           //printf("min:%d\nmin_ties:%d\nsum:%d\nsection:%d\n",smallest,smallest_ties,sum,section_array[i]);
      }//get all the candidates for the current case.
      
      i=1;
      while (i<=selected_num)
      {
           if (avaiable_array[i]==0)
           {
               int j;
               for (j=i;j<selected_num;j++)
               {
                   avaiable_array[j]=avaiable_array[j+1];
                   selected_position[j]=selected_position[j+1];
                   min_array[j]=min_array[j+1];
                   min_ties_array[j]=min_ties_array[j+1];
                   summary_array[j]=summary_array[j+1];
                   section_array[j]=section_array[j+1];
               }
               selected_num--;
               
           }
           else if (avaiable_array[i]==0 && i==selected_num)
               selected_num--;
           else
               i++;
      }//after this loop,we update the "selected_position[]" and get the new positions which are useful
        
      if (selected_num==0)
      {
           fit_cases--;
           //printf("there is no avaiable attnory that can make the all of the rest cases have attnory\n");
           return;
      }
      
      int unique_array[selected_num+1];
      int candidates[attnory_num+1];//this is the candidates' ID
      int score_candid[attnory_num+1];//this is the score of those candidates
      int candid_num=0;//the number of candidates
      
      for (i=1;i<=selected_num;i++)//in this loop we will get a score_candid[],which can order the candidates
      {
            unique_array[i] = 100000*min_array[i] + 10000*(10-min_ties_array[i]) + 100*summary_array[i] + selected_position[i];
            
            int label;
            int j,n;
            label=selected_position[i];
            for (j=candid_num+1,n=1;n<=schedule_array[label].present_num;n++,j++)
            {
                  candidates[j]=schedule_array[label].attnory_id[n];
                  int worktime;
                  int id;
                  id=schedule_array[label].attnory_id[n];
                  worktime=workload[id];
                  score_candid[j]=(5-worktime)*1000000 + unique_array[i];
                  score_candid[j]=score_candid[j]*10 + j;
                  //printf("position:%d----%d\n",selected_position[i],score_candid[j]);
            }     
            candid_num=schedule_array[label].present_num + candid_num;
      }
      
      for (i=1;i<=candid_num;i++)
      {
          int j;
          for (j=1;j<candid_num;j++)
          {
              int temp;
              if (score_candid[j]<=score_candid[j+1])
              {
                    temp=score_candid[j];
                    score_candid[j]=score_candid[j+1];
                    score_candid[j+1]=temp;
              }
          }
      }
      
      for (i=1;i<=candid_num;i++)//this loop is the branch ordering,important thing is to get which index in "selected_position[]" should be earlier than other
      {
          if (stop_sign==1)
               break;
          
          int attnory_id;
          int index,search_position;
          int temp_score;
          
          index=score_candid[i]%10;
          attnory_id=candidates[index];//get the attnory id
          
          temp_score=score_candid[i]/10;
          search_position=temp_score%100;//get position,which to find the attnory id
          
          int j;
          int copy_workload[attnory_num+1];
          for (j=1;j<=attnory_num;j++)
               copy_workload[j]=workload[j];
          copy_workload[attnory_id]=copy_workload[attnory_id] + events_list[temp_index].Duration;
          
          struct avaiable_schedule copy_schedule_array[16];//using the copy list translate to the next level
          
          for (j=1;j<=15;j++)
          {
               copy_schedule_array[j].present_num = schedule_array[j].present_num;
               int m;
               for (m=1;m<=copy_schedule_array[j].present_num;m++)
                    copy_schedule_array[j].attnory_id[m] = schedule_array[j].attnory_id[m];
               
               for (m=0;m<=5;m++)
                    copy_schedule_array[j].position_bit[m] = schedule_array[j].position_bit[m];
          }
          
          for (j=1;j<=copy_schedule_array[search_position].present_num;j++)//find which attnory is going to be kicked off
                if (copy_schedule_array[search_position].attnory_id[j] == attnory_id)
                    break;
          while (j<copy_schedule_array[search_position].present_num)
          {
                copy_schedule_array[search_position].attnory_id[j]=copy_schedule_array[search_position].attnory_id[j+1];
                j++;
          }
          copy_schedule_array[search_position].present_num--;//have taken one out of this position
          
          
          
          bool temp_bitset[6];
          for (j=0;j<=5;j++)//assgin the bitset to a "temp_bitset",because using the temp_bitset is easy to calculate and do some operation
                temp_bitset[j] = copy_schedule_array[search_position].position_bit[j];
           
          for (j=1;j<=5;j++)//if the have the same value,assgin the value as 0
                if (temp_bitset[j]==case_bitset[j])
                     temp_bitset[j]=0;
           
          int start_1=0,start_2=0,duration_1=0,duration_2=0;
          int unique_1,unique_2;
          int position_1,position_2;
          after_match_the_case(temp_bitset,&start_1,&start_2,&duration_1,&duration_2);
          if (start_1!=0 && start_2!=0)//this operation is to update the copy_schedule_array
          {
                unique_1=start_1*10+duration_1;
                unique_2=start_2*10+duration_2;
                position_1=get_position(unique_1);
                position_2=get_position(unique_2);
                int label_1,label_2;
                copy_schedule_array[position_1].present_num++;
                label_1=copy_schedule_array[position_1].present_num;
                copy_schedule_array[position_1].attnory_id[label_1]=attnory_id;
                
                copy_schedule_array[position_2].present_num++;
                label_2=copy_schedule_array[position_2].present_num;
                copy_schedule_array[position_2].attnory_id[label_2]=attnory_id;
          }
          else if (start_1!=0 && start_2==0)
          {
                unique_1=start_1*10+duration_1;
                position_1=get_position(unique_1);
                int label_1;
                copy_schedule_array[position_1].present_num++;
                label_1=copy_schedule_array[position_1].present_num;
                copy_schedule_array[position_1].attnory_id[label_1]=attnory_id;     
          }
          
          bool copy_present_case[case_num+1];//copy the case index,using the copy one translate to the next level
          for (j=1;j<=case_num;j++)
                copy_present_case[j] = present_case[j];
          
          if (fit_cases == case_num)
                stop_sign=1;
          result_array[fit_cases].attnory_id=attnory_id;
          Schedule_Plan(copy_present_case,copy_schedule_array,current_case_num-1,copy_workload);
      }
      fit_cases--;
}

void check_avaiable_attnory(bool *present_case,int *case_attnory_num,struct avaiable_schedule *schedule_array)
{
      int i;
      for (i=1;i<=case_num;i++)
      {
          if (present_case[i]==1)
          {
                int position,num_positions;
                position=events_list[i].case_position;
                num_positions=index_list[position].item_num;//num_positions get what are the positions that you need to check 
                int j;
                for (j=1;j<=num_positions;j++)
                {
                    int label;
                    label=index_list[position].index[j];
                    case_attnory_num[i] = schedule_array[label].present_num + case_attnory_num[i];
                    //case_attnory_num[i] is the current attnory number for the case,schedule_array[label].present_num is that how many attnorys
                    //are avaiable in this position.
                }
          }
      }
}

void find_min_attnory_for_eachcase(int *min,int *case_attnory_num,bool *present_case,int *min_lawyer_case,int *min_ties)
{
      int i;
      int flag=0;
      for (i=1;i<=case_num;i++)
          if (present_case[i]==1)
          {
             if (flag==0)
             {
                  (*min) = case_attnory_num[i];
                  flag=1;
             }
             else if (flag==1)
             {
                  if (case_attnory_num[i]<(*min))
                      (*min)=case_attnory_num[i];
             }
                
          }
      for (i=1;i<=case_num;i++)
          if (present_case[i]==1 && case_attnory_num[i]==(*min))
          {
               (*min_ties)++;
               min_lawyer_case[(*min_ties)]=i;
          }
}

void after_match_the_case(bool *set,int *start_1,int *start_2,int *duration_1,int *duration_2)
{
      int i=1;
      while (i<=5)
      {
          if (set[i]==1 && (*start_1)==0)
          {
               (*start_1)=i;
               int j=i;
               while (set[j]==1)
               {
                     (*duration_1)++;
                     j++;
               }
               i=j+1;
          }
          else if (set[i]==1 && (*start_1)!=0)
          {
               (*start_2)=i;
               int j=i;
               while (set[j]==1)
               {
                     (*duration_2)++;
                     j++;
               }
               i=j+1;     
          }
          else
               i++;
      }
}
