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

struct result{//this is to store different solution
       int case_id[20];
       int attnory_id[20];
       int already_done;//how many cases have stored in the partial solution
       int total_lenth;//this is the total days for a partial solution
};
struct result *result_array;

struct attnory_store{//this is for output to the file,each attnory has couple of assigned cases
       int case_num;
       int case_id[10];
};

int result_number=1;//to store how many posiable ways(partial order) 
int fit_cases=0;//fit_cases indicate how many cases have been assigned to the attnorys
int stop_sign=0;//when stop_sign=1,means find the complete schedule,then stop the program
int tree_nodes=0;//how many attempted cases has been assigned,even through some of them will not be scheduled in the final result

void Schedule_Plan(bool *,struct avaiable_schedule *,int );//plan the schedule,using the back track method
void check_avaiable_attnory(bool *,int *,struct avaiable_schedule *);//for current level,finding how many suitable attnorys for each case
void find_min_attnory_for_eachcase(int *,int *,bool *,int *,int *);//find the minimal number,min_ties
void find_min_attnory_for_eachcase_copy(int *,int *,bool *,int *,int *);
void after_match_the_case(bool *,int *,int *,int *,int *);//after assign an attnory to the case,what is the rest part of this attnory,and where to add in

main()
{
      int begin,end;
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
            
            current=attnory_list[i].next_time;//attnory_list[] is to store all the attnorys' time
            while (current!=NULL)
            {
                  int position;
                  int j,a,b;
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
      
      result_array=malloc(sizeof(struct result)*100);
      for (i=0;i<=99;i++)
      {
          result_array[i].already_done=0;
          result_array[i].total_lenth=0;
      }
      
      
      bool present_case[16];
      for (i=1;i<=case_num;i++)//present_case[] is the cases index which can be used in present level
          present_case[i]=1;
      
      Schedule_Plan(present_case,schedule_array,case_num);//present_case is the cases which can be used right now,schedule_array[] is the current suitable array
      
      int cases_for_attnory[attnory_num+1];
      int days_for_attnory[attnory_num+1];
      for (i=1;i<=attnory_num;i++)
      {
          cases_for_attnory[i]=0;
          days_for_attnory[i]=0;
      }
      
      if (stop_sign==1)
          printf("there is a solution!\n");
      else if (stop_sign==0)
          printf("there is no solution,but has partial schedule!\n");
      
      for (i=1;i<=result_number;i++)
      {
          int j;
          for (j=1;j<=result_array[i].already_done;j++)
          {
              int case_label;
              int days;
              case_label=result_array[i].case_id[j];
              days=events_list[case_label].Duration;
              result_array[i].total_lenth = result_array[i].total_lenth + days;
          }
      }
      
      int index,max;
      index=1;
      max=result_array[1].total_lenth;
      for (i=1;i<=result_number;i++)
      {
          if (max<=result_array[i].total_lenth)
          {
                index=i;//find the longest solution
                max=result_array[i].total_lenth;
          }
      }
      
      printf("the max length is %d\n",max);
      int un_schedule_case[case_num];
      int number_unschedule=0;
      
      for (i=1;i<=case_num;i++)
      {
          int j;
          int flag=0;
          for (j=1;j<=result_array[index].already_done;j++)
              if (result_array[index].case_id[j] == i)
              {
                 printf("case id:%d --- attnory id:%d\n",result_array[index].case_id[j],result_array[index].attnory_id[j]);
                 flag=1;
              }
          if (flag==0)
          {
              number_unschedule++;
              un_schedule_case[number_unschedule]=i;
          }
      }
      
      if (stop_sign==0)
      {
          printf("these cases are not scheduled:\n");
          for (i=1;i<=number_unschedule;i++)
              printf("%s ",events_list[un_schedule_case[i]].event);
          printf("\n");
      }
      
      //*********//the rest part is output the file//********//
          struct attnory_store attnory_case_list[attnory_num+1];
          for (i=1;i<=attnory_num;i++)
              attnory_case_list[i].case_num=0;
          
          for (i=1;i<=attnory_num;i++)
          {
              
              int j;
              for (j=1;j<=result_array[index].already_done;j++)
              {
                  if (result_array[index].attnory_id[j] == i)
                  {
                        int a;
                        attnory_case_list[i].case_num++;
                        a = attnory_case_list[i].case_num;
                        attnory_case_list[i].case_id[a]=result_array[index].case_id[j];
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
          f_write=fopen("partial_Schedule_file.txt","w");
          
          
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
      
      end=clock();
      float time;
      time=(float)(end-begin)/CLOCKS_PER_SEC;
      //printf("there are %d ways\n",result_number);
      printf("the number of tree nodes is:%d\nthe time is:%.3f seconds,%d ms\n",tree_nodes,time,end-begin);
      system("pause");
}

void Schedule_Plan(bool *present_case,struct avaiable_schedule *schedule_array,int current_case_num)
{
      if (current_case_num==0 || stop_sign==1)
          return;
      
      int i;
      
      int case_attnory_num[case_num+1];//case_attnory_num[] is to store how many attnorys are avaiable for each case
      
      for (i=1;i<=case_num;i++)
          if (present_case[i]==1)
              case_attnory_num[i]=0;
      check_avaiable_attnory(present_case,case_attnory_num,schedule_array);//after this function we will have the "case_attnory_num[]" array
      
      
      int min;
      int min_lawyer_case[case_num];//min_lawyer_case[] is to store which cases have the min attnorys.
      int min_ties=0;//"min_ties" is to store the number of the cases which have the min attnorys
      find_min_attnory_for_eachcase(&min,case_attnory_num,present_case,min_lawyer_case,&min_ties);//after this function,we get the min_lawyer_case[]
      
      
      int current_avaliable_num=0;
      for (i=1;i<=case_num;i++)
          if (present_case[i]==1)
               current_avaliable_num++;
      
      
      if (min==0 && min_ties==current_avaliable_num)//if the min is 0,and min_ties equals to the left cases,then we stop
      {
           return;
      }
      
      else if (min==0 && min_ties!=current_avaliable_num)//find the minimal case which has over 0 attnory,because we will find a partial,not the complete schedule
      {
           min_ties=0;//reset the min_ties
           find_min_attnory_for_eachcase_copy(&min,case_attnory_num,present_case,min_lawyer_case,&min_ties);
      }
      
      int longest_duration;//find the longest duration case,and assign attnory to it
      int temp_index;
      for (i=1;i<=min_ties;i++) 
      {
          if (i==1)
          {
              int a;
              a=min_lawyer_case[i];//find the min_attnory case,then compare who has a longer duration
              longest_duration=events_list[a].Duration;
              temp_index=a;
          }
          else
          {
              int a;
              a=min_lawyer_case[i];
              if (events_list[a].Duration>=longest_duration)
              {
                    longest_duration=events_list[a].Duration;
                    temp_index=a;//finally the "temp_index" is the choosen case id
              }
          }
      }
      
      present_case[temp_index]=0;//set the choosen case's bool value as 0,because this case has been selected,and will not be used in the next level
      
      int position=events_list[temp_index].case_position;//"temp_index" is the selected case id,and the "position" is the checking position
      
      tree_nodes++;//once we choose a case,then which means we can move the case to the tree structure.
      fit_cases++;//means we can get one more case,
      
      int inner_label;//this is to store how many cases have been assigned to the current solution
      result_array[result_number].already_done++;
      inner_label=result_array[result_number].already_done;
      result_array[result_number].case_id[inner_label] = temp_index;//assgin a case to the "result_array[]"
      
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
      
      if (selected_num==0)
      {
           fit_cases--;
           return;
      }
      
      for (i=1;i<=selected_num;i++)//this loop is the branch ordering,important thing is to get which index in "selected_position[]" should be earlier than other
      {
          if (stop_sign==1)
               break;
          
          int choose_position;
          choose_position=selected_position[i];//"b" gets the position in "schedule_array[]"
          
          struct avaiable_schedule copy_schedule_array[16];//using the copy list translate to the next level
          int j;
          for (j=1;j<=15;j++)
          {
               copy_schedule_array[j].present_num = schedule_array[j].present_num;
               int m;
               for (m=1;m<=copy_schedule_array[j].present_num;m++)
                    copy_schedule_array[j].attnory_id[m] = schedule_array[j].attnory_id[m];
               
               for (m=0;m<=5;m++)
               {
                    copy_schedule_array[j].position_bit[m] = schedule_array[j].position_bit[m];
               }
          }
          
          int choosing_id,label;
          label = copy_schedule_array[choose_position].present_num;
          choosing_id = copy_schedule_array[choose_position].attnory_id[label];//this is the selected attnory
          copy_schedule_array[choose_position].present_num--;//have taken one out of this position
          
          bool temp_bitset[6];
          for (j=1;j<=5;j++)//assgin the bitset to a "temp_bitset",because using the temp_bitset is easy to calculate and do some operation
                temp_bitset[j] = copy_schedule_array[choose_position].position_bit[j];
          
          for (j=0;j<=5;j++)//if the have the same value,assgin the value as 0
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
                copy_schedule_array[position_1].attnory_id[label_1]=choosing_id;
                
                copy_schedule_array[position_2].present_num++;
                label_2=copy_schedule_array[position_2].present_num;
                copy_schedule_array[position_2].attnory_id[label_2]=choosing_id;
          }
          else if (start_1!=0 && start_2==0)
          {
                unique_1=start_1*10+duration_1;
                position_1=get_position(unique_1);
                int label_1;
                copy_schedule_array[position_1].present_num++;
                label_1=copy_schedule_array[position_1].present_num;
                copy_schedule_array[position_1].attnory_id[label_1]=choosing_id;     
          }
          
          bool copy_present_case[case_num+1];//copy the case index,using the copy one translate to the next level
          for (j=1;j<=case_num;j++)
                copy_present_case[j] = present_case[j];
          
          if (fit_cases == case_num)
                stop_sign=1;
          
          result_array[result_number].attnory_id[inner_label]=choosing_id;
          Schedule_Plan(copy_present_case,copy_schedule_array,current_case_num-1);
          
          if (i<selected_num && stop_sign==0)
          {
                result_number++;
                for (j=1;j<=fit_cases;j++)
                {
                      result_array[result_number].attnory_id[j] = result_array[result_number-1].attnory_id[j];
                      result_array[result_number].case_id[j] = result_array[result_number-1].case_id[j];
                      result_array[result_number].already_done = fit_cases;
                }
          }
          
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

void find_min_attnory_for_eachcase_copy(int *min,int *case_attnory_num,bool *present_case,int *min_lawyer_case,int *min_ties)
{
      int i;
      int flag=0;
      for (i=1;i<=case_num;i++)
          if (present_case[i]==1)
          {
             if (flag==0)
             {
                  if (case_attnory_num[i]!=0)
                  {
                     (*min) = case_attnory_num[i];
                     flag=1;
                  }
             }
             else if (flag==1)
             {
                  if (case_attnory_num[i]<(*min) && case_attnory_num[i]!=0)
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
