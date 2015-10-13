struct atribute{
       char word[60];
       char type;
       char email_id[10];
       struct atribute *next_word;
}*email_list,*quiz_list;
typedef struct atribute *word_link;

struct selected_atribute{
       char atribute[60];
}*different_atribute;

struct words_Y_N{
       int *index_have;//store the examples which have the current attribute
       int *index_without;//store the examples which don't have the current attribute
       int number_haveword;//the number of the examples which have the current attribute
       int without_word;//the number of the examples which don't  have the current attribute
       float info_gain;//the information gain for choosing the current attribute
};

int email=0;
int different_words=0;//this records the total words in the array,while all the words are different from each other

void fliter_punct(char *str)//this function is to filter the punctuation
{
     int i=0;
     while(str[i]!='\0')
     {
          if(ispunct(str[i]))
          {
              int j=i;
              while(str[j]!='\0')
              {
                  str[j]=str[j+1];
                  j++;
              }
          }
          else
              i++;
     }
}

read_emails(FILE *f)//this function is to read the examples file
{
      char string_abstract[100];//after some process when we get a string
      char string_temp[100];//get the the string char from the file
      char string_class[10];//string_class is to define whether it's a good email or bad email
      char string_original[100];//copy the string_temp;
      int total_word=0;
      while(!feof(f))//this loop is to get the number of the emails(or examples)
      {
            strcpy(string_temp,"\0");
            strcpy(string_class,"\0");
            
            fscanf(f,"%s",string_temp);
            sscanf(string_temp,"%[^0-9]",string_class);
            if (strcmp(string_class,"--H")==0)
                 email++;
            else if (strcmp(string_class,"--S")==0)
                 email++;
      }
      rewind(f);
      
      email_list=malloc(sizeof(struct atribute)*(email+1));//email_list[] is a structure array which store all the words in each email
      int number=1;//"number" is to represent the new index of the email_list[]
      word_link newptr,current_ptr;
      
      while (!feof(f))
      {
            strcpy(string_class,"\0");
            strcpy(string_temp,"\0");
            
            fscanf(f,"%s",string_temp);
            strcpy(string_original,string_temp);//copy string_temp to string_original,because after "sscanf" operations,the value of string_temp will be changed
            
            sscanf(string_temp,"%[^0-9]",string_class);
            if (strcmp(string_class,"--H")==0)
            {
                  email_list[number].type='H';
                  email_list[number].next_word=NULL;
                  current_ptr=&email_list[number];
                  
                  strcpy(string_temp,"\0");
                  fscanf(f,"%s",string_temp);//get the word from the file
                  fliter_punct(string_temp);//rid off the puncation
                  
                  if (string_temp[0]!='\0')
                  {
                       newptr=malloc(sizeof(struct atribute));
                       strcpy(string_abstract,strlwr(string_temp));//lowcase
                       strcpy(newptr->word,string_abstract);
                       newptr->next_word=NULL;
                       current_ptr->next_word=newptr;
                       current_ptr=newptr;
                       total_word++;
                  }
                  number++;
            }
            else if (strcmp(string_class,"--S")==0)
            {
                  email_list[number].type='S';
                  email_list[number].next_word=NULL;
                  current_ptr=&email_list[number];
                  
                  strcpy(string_temp,"\0");
                  fscanf(f,"%s",string_temp);//get the word from the file
                  
                  fliter_punct(string_temp);//rid off the puncation
                  if (string_temp[0]!='\0')
                  {
                       newptr=malloc(sizeof(struct atribute));
                       strcpy(string_abstract,strlwr(string_temp));//lowcase
                       
                       strcpy(newptr->word,string_abstract);
                       newptr->next_word=NULL;
                       current_ptr->next_word=newptr;
                       current_ptr=newptr;
                       total_word++;
                  }
                  number++;
            }
            else
            {
                  fliter_punct(string_original);//rid off the puncation,the string_original is the string_temp,they are same
                  if (string_original[0]!='\0')
                  {
                       strcpy(string_abstract,strlwr(string_original));//lowcase
                       
                       newptr=malloc(sizeof(struct atribute));
                       strcpy(newptr->word,string_abstract);
                       newptr->next_word=NULL;
                       current_ptr->next_word=newptr;
                       current_ptr=newptr;
                       total_word++;
                  }
            }
      }
      
      different_atribute=malloc(sizeof(struct selected_atribute)*total_word);//the different_atribute[] is to sellect the unique words in the file
      int i;
      for (i=1;i<=email;i++)
      {
            current_ptr=&email_list[i];
            current_ptr=current_ptr->next_word;
            while(current_ptr!=NULL)
            {
                  int j=1;
                  int flag=1;
                  while (different_atribute[j].atribute[0]!='\0')
                  {
                        if(strcmp(different_atribute[j].atribute,current_ptr->word)==0)
                        {
                              flag=0;
                              break;
                        }
                        j++;
                  }
                  if (flag==1)
                  {
                        strcpy(different_atribute[j].atribute,current_ptr->word);
                        different_words++;
                  }
                  current_ptr=current_ptr->next_word;
            }
      }
}

read_quiz(FILE *f,int *emails)//this function is to read the file which is going to be predicted,either quiz-file or email-file
{
      char string_abstract[100];//after some process when we get a string
      char string_temp[100];//get the the string char from the file
      char string_class[10];//string_class is to define whether it's a good email or bad email
      char string_original[100];//copy the string_temp;
      
      while(!feof(f))//this loop is to get the number of the emails(examples)
      {
            strcpy(string_temp,"\0");
            strcpy(string_class,"\0");
            
            fscanf(f,"%s",string_temp);
            sscanf(string_temp,"%[^0-9]",string_class);
            if (strcmp(string_class,"--H")==0)
                 (*emails)++;
            else if (strcmp(string_class,"--S")==0)
                 (*emails)++;
      }
      rewind(f);
      
      quiz_list=malloc(sizeof(struct atribute)*((*emails)+1));//quiz_list[] is a structure array which store all the words in each email
      int number=1;//"number" is to represent the new index of the quiz_list[]
      word_link newptr,current_ptr;
      
      while (!feof(f))
      {
            strcpy(string_class,"\0");
            strcpy(string_temp,"\0");
            
            fscanf(f,"%s",string_temp);
            strcpy(string_original,string_temp);//copy string_temp to string_original,because after "sscanf" operations,the value of string_temp will be changed
            
            sscanf(string_temp,"%[^0-9]",string_class);
            if (strcmp(string_class,"--H")==0)
            {
                  //quiz_list[number].type='H';
                  fliter_punct(string_original);
                  strcpy(quiz_list[number].email_id,string_original);
                  //printf("%s\n",quiz_list[number].email_id);
                  quiz_list[number].next_word=NULL;
                  current_ptr=&quiz_list[number];
                  
                  strcpy(string_temp,"\0");
                  fscanf(f,"%s",string_temp);//get the word from the file
                  fliter_punct(string_temp);//rid off the puncation
                  
                  if (string_temp[0]!='\0')
                  {
                       newptr=malloc(sizeof(struct atribute));
                       strcpy(string_abstract,strlwr(string_temp));//lowcase
                       strcpy(newptr->word,string_abstract);
                       newptr->next_word=NULL;
                       current_ptr->next_word=newptr;
                       current_ptr=newptr;
                  }
                  number++;
            }
            else if (strcmp(string_class,"--S")==0)
            {
                  fliter_punct(string_original);
                  strcpy(quiz_list[number].email_id,string_original);
                  quiz_list[number].next_word=NULL;
                  current_ptr=&quiz_list[number];
                  
                  strcpy(string_temp,"\0");
                  fscanf(f,"%s",string_temp);//get the word from the file
                  
                  fliter_punct(string_temp);//rid off the puncation
                  if (string_temp[0]!='\0')
                  {
                       newptr=malloc(sizeof(struct atribute));
                       strcpy(string_abstract,strlwr(string_temp));//lowcase
                       
                       strcpy(newptr->word,string_abstract);
                       newptr->next_word=NULL;
                       current_ptr->next_word=newptr;
                       current_ptr=newptr;
                  }
                  number++;
            }
            else
            {
                  fliter_punct(string_original);//rid off the puncation,the string_original is the string_temp,they are same
                  if (string_original[0]!='\0')
                  {
                       strcpy(string_abstract,strlwr(string_original));//lowcase
                       
                       newptr=malloc(sizeof(struct atribute));
                       strcpy(newptr->word,string_abstract);
                       newptr->next_word=NULL;
                       current_ptr->next_word=newptr;
                       current_ptr=newptr;
                  }
            }
      }
}
