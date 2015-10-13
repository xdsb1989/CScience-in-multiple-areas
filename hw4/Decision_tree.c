#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"read_file.c"
#include"predict_type.c"
#include<time.h>
void Build_Tree(struct decision_tree **,int *,int ,int *,int ,char *,char *);
int start,end;

main()
{
      
      
      int type;
      printf("This is Decision_tree algorithm.\nchoose sa-file press 1\nchoose toy-file press 2\ninput:");
      scanf("%d",&type);
      FILE *f, *f_target_1, *f_target_2;
      
      if (type==1)
      {
            f=fopen("sa-email.txt","r");
            f_target_1=fopen("sa-email.txt","r");
            f_target_2=fopen("sa-quiz.txt","r");
            }
      else if (type==2)
      {
            f=fopen("toy-email.txt","r");
            f_target_1=fopen("toy-email.txt","r");
            f_target_2=fopen("toy-quiz.txt","r");
            }
      start=clock();
      read_emails(f);//read the example file
      fclose(f);
      
      tree_link root;
      int example_index[email+1];//the examples stores a group of emails which can be used in current level.
      int atributes_index[different_words+1];//the atributes stores a group of different words,and it will update and transfer to the next level
      int i;
      for (i=1;i<=email;i++)
            example_index[i]=i;//"i" is the index of the email_list array,once a email_list[i] is used, then the value of examples[i] will be 0;
      for (i=1;i<=different_words;i++)//save all the index of the unique attributes in atributes_index[]
            atributes_index[i]=i;
      
      FILE *print_tree;
      print_tree=fopen("readable_tree.txt","w");//open a file to print readable tree;
      fprintf(print_tree,"1 means have the previous level's word,0 means don't have.\n");
      fclose(print_tree);
      char str1[]="|-";//the beginning string
      Build_Tree(&root,example_index,email,atributes_index,different_words,str1,"");//while we build the tree,we also  print the tree
      
      
      int target_emails=0, target_quiz=0;//we have two target file,one is the example itself, the other is the quiz file
      
      read_quiz(f_target_1,&target_emails);//read the email file, and store the number of emails target_emails.
      fclose(f_target_1);
      FILE *f_predict;
      f_predict=fopen("email_predict.txt","w");//print the result
      int correct_result=0;
      float email_accuracy;
      for (i=1;i<=target_emails;i++)
      {
            word_link current;
            current=&quiz_list[i];
            predict(root,current);//using the tree and the quiz_list[] value to predict the result,the quiz_list[] store the origina file words
            fprintf(f_predict,"the email id is:%s.Predict is:%c\n",quiz_list[i].email_id,quiz_list[i].type);
            if (quiz_list[i].email_id[0]==quiz_list[i].type)
                  correct_result++;//count the correct result
      }
      fclose(f_predict);
      email_accuracy=(float)correct_result/target_emails;
      printf("the accuracy on the email file is:%.2f\n",email_accuracy);
      
      
      read_quiz(f_target_2,&target_quiz);//read the quiz file, and store the number of emails target_quiz.
      fclose(f_target_2);
      f_predict=fopen("quiz_predict.txt","w");
      correct_result=0;
      for (i=1;i<=target_quiz;i++)
      {
            word_link current;
            current=&quiz_list[i];
            predict(root,current);//using the tree and the quiz_list[] value to predict the result,the quiz_list[] store the origina file words
            fprintf(f_predict,"the email id is:%s.Predict is:%c\n",quiz_list[i].email_id,quiz_list[i].type);
            if (quiz_list[i].email_id[0]==quiz_list[i].type)
                  correct_result++;//count the correct result
      }
      fclose(f_predict);
      email_accuracy=(float)correct_result/target_quiz;
      printf("the accuracy on the quiz file is:%.2f\n",email_accuracy);
      
      end=clock();
      float time;
      time=(float)(end-start)/CLOCKS_PER_SEC;
      printf("the time is:%.3f\nstart is:%d\nend is:%d\n",time,start,end);
      system("pause");
}

void Build_Tree(struct decision_tree **root,int *example_index,int emails,int *atributes_index,int current_words,char *str1,char *tail)
{//example[] and atributes[] update level by level
       int i;
       int positive=0,negative=0;//"positive" and "negative" store the number of Ham and Spam in the current group of examples
       
       for (i=1;i<=emails;i++)//this loop is to calculate how many spams and hams in current group
       {
             if (example_index[i]!=0)
             {
                   int label;
                   label=example_index[i];
                   if (email_list[label].type=='H')
                        positive++;
                   else if (email_list[label].type=='S')
                        negative++;
             }
       }
       FILE *print_tree;
       print_tree=fopen("readable_tree.txt","a");
       //the first way to stop building a tree.
       if (positive==0)//while if either positive or negative is 0,then we stop the Build_Tree,and assigin a value "S" or "H" to the levef
       {
             (*root)=malloc(sizeof(struct decision_tree));
             (*root)->type='S';
             fprintf(print_tree,"%s%c%s\n",str1,(*root)->type,tail);
             return;
       }
       else if (negative==0)//
       {
             (*root)=malloc(sizeof(struct decision_tree));
             (*root)->type='H';
             fprintf(print_tree,"%s%c%s\n",str1,(*root)->type,tail);
             return;
       }
       //the second way to stop building a tree.
       if (current_words==0)//means no more atributes,then return the majority as the value
       {
             if (positive >= negative)
             {
                   (*root)=malloc(sizeof(struct decision_tree));
                   (*root)->type='H';
                   fprintf(print_tree,"%s%c%s\n",str1,(*root)->type,tail);
                   return;
             }
             else if (positive < negative)
             {
                   (*root)=malloc(sizeof(struct decision_tree));
                   (*root)->type='S';
                   fprintf(print_tree,"%s%c%s\n",str1,(*root)->type,tail);
                   return;
             }
       }
       //if the first way and second way don't match,then continue to build a tree.
       
       float P_pos,P_neg,Info_before;//probablity of the good emails and bad emails
       P_pos=(float)positive/(positive+negative);
       P_neg=1-P_pos;
       Info_before=-P_pos*(log(P_pos)/log(2))-P_neg*(log(P_neg)/log(2));//Info_before
       
       struct words_Y_N *word_list;//the word_list[] is a strcuture array,it stores two arrays and the information gain
       word_list=malloc(sizeof(struct words_Y_N)*(current_words+1));//this struct array is to save all the infomation of all the current different words
       
       for (i=1;i<=current_words;i++)//current_words will be reduced level by level
       {
             int label;
             label=atributes_index[i];//"label" is the index of different_atributes[],there are different atributes.
             
             word_link word_ptr;
             
             word_list[i].number_haveword=0;
             word_list[i].without_word=0;
             word_list[i].index_have=malloc(sizeof(int)*(emails+1));
             word_list[i].index_without=malloc(sizeof(int)*(emails+1));
             
             int j;
             for (j=1;j<=emails;j++)//emails will be reduced level by level
             {//after this loop,we can get the number of the emails of having the current word and not having the current word.
              //and also store the index of these emails in index_have[] and index_without[]
                   int label_2;
                   label_2=example_index[j];//label_2 is to store the index of the email,while we can use the label_2 to visit email_list[].
                   
                   word_ptr=&email_list[label_2];
                   word_ptr=word_ptr->next_word;
                   int flag=0;
                   while (word_ptr!=NULL)
                   {
                         if (strcmp(word_ptr->word,different_atribute[label].atribute)==0)
                         {
                               flag=1;
                               break;
                               }
                         word_ptr=word_ptr->next_word;
                   }
                   int temp;
                   if (flag==1)//if flag is 1,means for the current attribute,the present email have this attribute
                   {
                         word_list[i].number_haveword++;
                         temp=word_list[i].number_haveword;
                         word_list[i].index_have[temp]=label_2;
                   }
                   else if (flag==0)//if flag is 0,means for the current attribute,the present email doesn't have this attribute
                   {
                         word_list[i].without_word++;
                         temp=word_list[i].without_word;
                         word_list[i].index_without[temp]=label_2;
                   }
             }
             
             int have_word,without_word;
             have_word=word_list[i].number_haveword;
             without_word=word_list[i].without_word;
             
             if (have_word==0 || without_word==0)
             {//if either the number of emails have the present attribute is 0,or the number of emails don't have the present attribute is 0, set the present attribute info_gain as -2
                    word_list[i].info_gain=-2;
                    continue;//and jump to the bottom of the loop
             }
             
             float info_Y, info_N, info_after;
             //info_Y means the info gain in the group which has the attribute,and info_Y means the info gain in the group which hasn't the attribute
             int Y_good_email=0;//number of ham in the group which has the attribute
             int Y_bad_email=0;//number of spam in the group which has the attribute
             int N_good_email=0;//number of ham in the group which hasn't the attribute
             int N_bad_email=0;//number of spam in the group which hasn't the attribute
             
             for (j=1;j<=have_word;j++)
             {
                   int index;
                   index=word_list[i].index_have[j];
                   if (email_list[index].type == 'H')
                         Y_good_email++;
                   else if (email_list[index].type == 'S')
                         Y_bad_email++;
             }
             
             float P_Y_pos,P_N_neg;
             if (Y_good_email==0 || Y_bad_email==0)//if either the number of spam or the number of ham is 0,set the information gian as 0;
             {
                   info_Y=0;
             }
             else
             {
                   P_Y_pos=(float)Y_good_email/(Y_good_email+Y_bad_email);
                   P_N_neg=1-P_Y_pos;
                   info_Y=-P_Y_pos*(log(P_Y_pos)/log(2))-P_N_neg*(log(P_N_neg)/log(2));
             }
             
             for (j=1;j<=without_word;j++)
             {
                   int index;
                   index=word_list[i].index_without[j];
                   if (email_list[index].type == 'H')
                         N_good_email++;
                   else if (email_list[index].type == 'S')
                         N_bad_email++;
             }
             if (N_good_email==0 || N_bad_email==0)//if either the number of spam or the number of ham is 0,set the information gian as 0;
             {
                   info_N=0;
             }
             else 
             {
                  P_Y_pos=(float)N_good_email/(N_good_email+N_bad_email);
                  P_N_neg=1-P_Y_pos;
                  info_N=-P_Y_pos*(log(P_Y_pos)/log(2))-P_N_neg*(log(P_N_neg)/log(2));
             }
             
             info_after = info_Y * have_word/(have_word+without_word) + info_N * without_word/(have_word+without_word);//calculate the after information gain
             word_list[i].info_gain = Info_before - info_after;
       }
       
       float temp=0.0;
       int mark;
       int flag=0;
       for (i=1;i<=current_words;i++)
       {
             if (word_list[i].info_gain>=temp)
             {
                   flag=1;
                   temp=word_list[i].info_gain;
                   mark=i;//find out the attribute which has the max information gain. "info_gain"
             }
       }
          
       if (flag==0)//means all the words have the info_gain which is less than 0,it is a speciall case and the tree will return the mode.
       {
             if (positive >= negative)
             {
                   (*root)=malloc(sizeof(struct decision_tree));
                   (*root)->type='H';
                   return;
             }
             else if (positive < negative)
             {
                   (*root)=malloc(sizeof(struct decision_tree));
                   (*root)->type='S';
                   return;
             }
       }
       
       int index;
       index=atributes_index[mark];//find out the index of the unique attributes array
       
       (*root)=malloc(sizeof(struct decision_tree));
       strcpy((*root)->atribute,different_atribute[index].atribute);//asign a word to the root(or node) by using the "index"
       
       
       fprintf(print_tree,"%s%s%s\n",str1,(*root)->atribute,tail);//print the tree in the tree file
       strcat(str1,"---");
       int lenth=strlen(str1);
       char str2[lenth];
       strcpy(str2,str1);//copy the new str1 to str2,then transfer str1 to the right side,and then transfer str2 to the left side
       
       for (i=mark;i<=current_words-1;i++)//update the atributes_index[],take off the index of the word which has been used.
             atributes_index[i]=atributes_index[i+1];
       current_words=current_words-1;//update the "current_words", in the next level,the number of the words will be reduced 1.
       
       int number_have_word, number_without_word;
       
       number_have_word=word_list[mark].number_haveword;
       number_without_word=word_list[mark].without_word;
       
       int emails_have_word[number_have_word+1];//the array which store the examples' index which has the present attribute
       int emails_without_word[number_without_word+1];//the array which store the examples' index which hasn't the present attribute
       
       for (i=1;i<=number_have_word;i++)
             emails_have_word[i]=word_list[mark].index_have[i];
       for (i=1;i<=number_without_word;i++)
             emails_without_word[i]=word_list[mark].index_without[i];
       
       char tail_have[5]="(1)";
       char tail_without[5]="(0)";
       Build_Tree(&((*root)->have_atribute),emails_have_word,number_have_word,atributes_index,current_words,str1,tail_have);//first jump to the branch which has the word
       Build_Tree(&((*root)->without_atribute),emails_without_word,number_without_word,atributes_index,current_words,str2,tail_without);//then jump to the branch which hasn't the word
       
}
