struct atribute{
       char word[60];
       char type;
       char email_id[10];
       struct atribute *next_word;
};
typedef struct atribute *word_link;

struct selected_atribute{
       char atribute[60];
};
struct selected_atribute *all_unique_atribute;//store all the unique words.
int unique_lenth;//the lenth of the all_unique_atribute[] array,means how many unique words in both files

struct bool_array{
       bool *array;
       // the "array" is a bool array,the lenth of this array is same as the total number of the all unique words,
       //1 and 0 represent whether the current email has this particular word or not.
       char correct_type;
};

void fliter_punct(char *str)
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

read_file(FILE *f,int *email,int *different_words,struct atribute **example_list,struct selected_atribute **unique_list)
{
      char string_abstract[100];//after some process when we get a string
      char string_temp[100];//get the the string char from the file
      char string_class[10];//string_class is to define whether it's a good email or bad email
      char string_original[100];//copy the string_temp;
      int total_word=0;
      while(!feof(f))//this loop is to get the number of the emails(examples)
      {
            strcpy(string_temp,"\0");
            strcpy(string_class,"\0");
            
            fscanf(f,"%s",string_temp);
            sscanf(string_temp,"%[^0-9]",string_class);
            if (strcmp(string_class,"--H")==0)
                 (*email)++;
            else if (strcmp(string_class,"--S")==0)
                 (*email)++;
      }
      rewind(f);
      
      (*example_list)=malloc(sizeof(struct atribute)*((*email)+1));//
      int number=1;
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
                  fliter_punct(string_original);
                  strcpy((*example_list)[number].email_id , string_original);//get the email id
                  (*example_list)[number].type='H';//get the email type,spam or ham
                  (*example_list)[number].next_word=NULL;
                  current_ptr=&(*example_list)[number];
                  
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
                  fliter_punct(string_original);
                  strcpy((*example_list)[number].email_id , string_original);//get the email id
                  (*example_list)[number].type='S';//get the email type,spam or ham
                  (*example_list)[number].next_word=NULL;
                  current_ptr=&(*example_list)[number];
                  
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
      
      (*unique_list)=malloc(sizeof(struct selected_atribute)*total_word);//this is the unique words in the current file
      int i;
      for (i=1;i<=(*email);i++)//loop from each email in the file
      {
            current_ptr=&(*example_list)[i];
            current_ptr=current_ptr->next_word;
            while(current_ptr!=NULL)
            {
                  int j=1;
                  int flag=1;
                  while ((*unique_list)[j].atribute[0]!='\0')
                  {
                        if(strcmp((*unique_list)[j].atribute,current_ptr->word)==0)
                        {
                              flag=0;
                              break;
                        }
                        j++;
                  }
                  if (flag==1)
                  {
                        strcpy((*unique_list)[j].atribute,current_ptr->word);
                        (*different_words)++;//get how many unique words in the current file
                  }
                  current_ptr=current_ptr->next_word;
            }
      }
}
