#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>
#include"KNN_readfile.c"

void set_unique_bool_array(struct atribute **,int ,struct bool_array **);
void compare_function(struct bool_array *,struct bool_array *,int ,int ,char *);
int K;

main()
{
      int type;
      printf("this is KNN algorithm\nchoose sa-file press 1\nchoose toy-file press 2\ninput:");
      scanf("%d",&type);
      FILE *f_email, *f_quiz;
      if (type==1)
      {
            f_email=fopen("sa-email.txt","r");
            f_quiz=fopen("sa-quiz.txt","r");
            K=3;
            }
      else if (type==2)
      {
            f_email=fopen("toy-email.txt","r");
            f_quiz=fopen("toy-quiz.txt","r");
            K=1;
            }
      
      int email_number=0, quiz_number=0;//number of emails in example file,and number of emails in quiz file
      int email_unique_words=0;
      int quiz_unique_words=0;
      struct atribute *email_list, *quiz_list;//structure array list[] to store all the words in each email
      struct selected_atribute *email_unique_atribute, *quiz_unique_atribute;
      
      read_file(f_email,&email_number,&email_unique_words,&email_list,&email_unique_atribute);//call the read-file function
      fclose(f_email);
      
      read_file(f_quiz,&quiz_number,&quiz_unique_words,&quiz_list,&quiz_unique_atribute);//call the read-file function
      fclose(f_quiz);
      
      all_unique_atribute=malloc(sizeof(struct selected_atribute)*(email_unique_words+quiz_unique_words+1));
      //create a new array to store all unique words in two file
      int i;
      for (i=1;i<=email_unique_words;i++)
            strcpy(all_unique_atribute[i].atribute , email_unique_atribute[i].atribute);
      unique_lenth=email_unique_words;
      for (i=1;i<=quiz_unique_words;i++)
      {//store the two files' unique words together,in the all_unique_atribute[] array. And use the index to imply them
            int j;
            for (j=1;j<=unique_lenth;j++)
                if (strcmp(quiz_unique_atribute[i].atribute , all_unique_atribute[j].atribute)==0)
                     break;
            if (j>unique_lenth)
            {
                unique_lenth++;
                strcpy(all_unique_atribute[j].atribute , quiz_unique_atribute[i].atribute);
            }
      }
      
      struct bool_array *email_bool_list;
      email_bool_list = malloc(sizeof(struct bool_array)*(email_number+1));
      for (i=1;i<=email_number;i++)
      {
            email_bool_list[i].correct_type = email_list[i].type;//email_id is to store the type of the email
            email_bool_list[i].array = malloc(sizeof(bool)*(unique_lenth+1));
            int j;
            for (j=1;j<=unique_lenth;j++)//set all the bool value as 0
                  email_bool_list[i].array[j]=0;
      }
      //input the email_list[],number of emails and the email_bool_list[],and get the output is the useful email_bool_list
      set_unique_bool_array(&email_list,email_number,&email_bool_list);
      
      
      struct bool_array *quiz_bool_list;
      quiz_bool_list = malloc(sizeof(struct bool_array)*(quiz_number+1));
      for (i=1;i<=quiz_number;i++)
      {
            quiz_bool_list[i].correct_type = quiz_list[i].type;//email_id is to store the type of the email
            quiz_bool_list[i].array = malloc(sizeof(bool)*(unique_lenth+1));
            int j;
            for (j=1;j<=unique_lenth;j++)//set all the bool value as 0
                  quiz_bool_list[i].array[j]=0;
      }
      //input the quiz_list[],number of emails and the quiz_bool_list[],and get the output is the useful quiz_bool_list
      set_unique_bool_array(&quiz_list,quiz_number,&quiz_bool_list);
      
      
      char result_email[email_number+1];
      char result_quiz[quiz_number+1];
      //using the KNN algorithm to get the type,predict the quiz-file
      compare_function(email_bool_list,quiz_bool_list,email_number,quiz_number,result_quiz);
      //using the KNN algorithm to get the type,predict the email-file
      compare_function(email_bool_list,email_bool_list,email_number,email_number,result_email);
          
      FILE *email_file, *quiz_file;    
      quiz_file=fopen("KNN_quiz_predict_file.txt","w");
      
      int correct=0;//calculate the number of correct answer
      float accuracy;
      for (i=1;i<=quiz_number;i++)
      {
          if (quiz_bool_list[i].correct_type == result_quiz[i])
               correct++;
          fprintf(quiz_file,"the email id is:%s.the predicted result is:%c\n",quiz_list[i].email_id,result_quiz[i]);
      }
      accuracy=(float)correct/quiz_number;
      printf("the accuracy on the quiz file is:%.2f\n",accuracy);
      
      email_file=fopen("KNN_email_predict_file.txt","w");
      correct=0;
      for (i=1;i<=email_number;i++)
      {
          if (email_bool_list[i].correct_type == result_email[i])
               correct++;
          fprintf(email_file,"the email id is:%s.the predicted result is:%c\n",email_list[i].email_id,result_email[i]);
      }
      accuracy=(float)correct/email_number;
      printf("the accuracy on the email file is:%.2f\n",accuracy);
      
      system("pause");
}

void set_unique_bool_array(struct atribute **email_list,int email_number,struct bool_array **email_bool_list)
{
      int i;
      for (i=1;i<=email_number;i++)//this loop is to go over all the email in the (*email_list)
      {
            word_link current;
            
            current=(*email_list)[i].next_word;
            while (current!=NULL)
            {
                  int j;
                  for (j=1;j<=unique_lenth;j++)
                        if (strcmp(all_unique_atribute[j].atribute , current->word)==0)//if we find the word in the email
                        {
                              if ((*email_bool_list)[i].array[j]==0)//if this word hasn't been recorded then sign it as 1
                                    (*email_bool_list)[i].array[j]=1;
                                    //use "j" which is the index of the all_unique_atribute[] to be the current email word's ID,because they have the same lenth
                              break;
                        }
                  current=current->next_word;
            }
      }
}

void compare_function(struct bool_array *email_bool_list,struct bool_array *quiz_bool_list,int email_number,int quiz_number,char *result_quiz)
{
      int i;
      int j;
      for (i=1;i<=quiz_number;i++)
      {
            int score_list[email_number+1];
            for (j=1;j<=email_number;j++)
                  score_list[j]=0;//set the score for each email is 0
            for (j=1;j<=email_number;j++)
            {
                  int n;
                  for (n=1;n<=unique_lenth;n++)
                        if (email_bool_list[j].array[n]!=quiz_bool_list[i].array[n])//while if the value of each word is not equal,then the score increase
                              score_list[j]++;
            }
            int index[K+1];
            for (j=1;j<=K;j++)//this loop is to sellect the top K nearest 
            {
                  int temp,flag=1;
                  int n;
                  temp=score_list[1];
                  for (n=1;n<=email_number;n++)
                  {
                        if (score_list[n]<=temp)
                        {
                            temp=score_list[n];
                            flag=n;
                        }
                  }
                  score_list[flag]=unique_lenth+1;//after choose it,set the score as a max number
                  index[j]=flag;//index[] store the K Nearest label
            }
            
            int positive=0;
            int negative=0;
            for (j=1;j<=K;j++)//calculate the number of Ham and Spam
            {
                  int label=index[j];
                  if (email_bool_list[label].correct_type == 'H')
                        positive++;
                  else if (email_bool_list[label].correct_type == 'S')
                        negative++;
            }
            if (positive >= negative)//while if Ham large and equal to Spam, sign "H" to the predicted email
                  result_quiz[i]='H';
            else if (positive < negative)//while if Ham smaller than Spam, sign "S" to the predicted email
                  result_quiz[i]='S';
      }
}
