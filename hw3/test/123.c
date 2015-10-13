#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define max_ID 999
/*I will set the customer ID as the index in the off_set array.Because generally speaking,
  the user ID will increase continuity,and the gaps will not be too many.So that it's a effective way to store and check.
  */
void predict(int *,int *,int ,int,int);
void find_the_label(int *,int ,int *);

int array_size=0;
int user_number=0;
int superset_number=0;
int subset_number=0;
int disjoint_number=0;
int predicted_movie_number=0;
float RMSE;

main()
{
     FILE *f1;
     f1=fopen("nf-rating.txt","r");
     if (f1==NULL)//if can not open the file,stop the program
     {
         printf("OMG,the file is not existed!\n");
         system("pause");
         return 0;
     }
     int off_set[max_ID+1]={0};
     char ch;
    
     while(!feof(f1))
     {    
         ch=fgetc(f1);
         if (ch=='\n')
            array_size++;
         }
     rewind(f1);//set the file pointer to the beginning position
     array_size=array_size*2+1;//define how many size for the original data array
     int original_data[array_size];
    
     int i,j;
     int cust_id;
     int temp_id;
     i=1;
     fscanf(f1,"%d %d %d",&cust_id,&original_data[i],&original_data[i+1]);
    
     off_set[cust_id]=1;
     temp_id=cust_id;
     i=i+2;
     while (!feof(f1))
     {
          fscanf(f1,"%d %d %d",&cust_id,&original_data[i],&original_data[i+1]);
          if (temp_id!=cust_id)
          {     
               off_set[cust_id]=i;               
               temp_id=cust_id;
          }
          i=i+2;
     }
     fclose(f1);
     /*for testing the data
     for (j=1;j<array_size;j=j+2)
     {
          printf("%d %d\n",original_data[j],original_data[j+1]);
          }
     printf("%d\n",j);
    */
     for (j=0;j<=max_ID;j++)
        if (off_set[j]!=0)
           user_number++;
     
     //printf("%d---\n",user_number);
     
     FILE *f2;
     int quiz_size=0;
     f2=fopen("nf-quiz.txt","r");
     if (f2==NULL)//if can not open the file,stop the program
     {
         printf("OMG,the file is not existed!\n");
         system("pause");
         return 0;
     }
     while(!feof(f2))
     {    
         ch=fgetc(f2);
         if (ch=='\n')
            quiz_size++;
         }
     rewind(f2);
     quiz_size=quiz_size*3+1;
     int quiz_data[quiz_size];
     i=1;
     while(!feof(f2))
     {
         fscanf(f2,"%d %d %d",&quiz_data[i],&quiz_data[i+1],&quiz_data[i+2]);
         i=i+3;
         }
     fclose(f2);
     /*
     for (j=1;j<quiz_size;j=j+3)
     {
          printf("%d %d %d\n",quiz_data[j],quiz_data[j+1],quiz_data[j+2]);
          }
     */
     i=1;
     int current_cust;
     int current_movie;
     while (i<quiz_size)
     {
          current_cust=quiz_data[i];
          current_movie=quiz_data[i+1];
          FILE *file_predict;
          file_predict=fopen("prediction_file.txt","a");
          fprintf(file_predict,"%03d %05d %d ",current_cust,current_movie,quiz_data[i+2]);
          fclose(file_predict);
          
          predict(original_data,off_set,current_cust,current_movie,quiz_data[i+2]);
          
          i=i+3; 
     }
     RMSE = RMSE/predicted_movie_number;
     RMSE = sqrt(RMSE);
     printf("the number of customers with supersets:%d\n",superset_number);
     printf("the number of customers with subset but not superset:%d\n",subset_number);
     printf("number of customers with neither supersets nor subsets:%d\n",disjoint_number);
     printf("the RMSE is:%.4f\n",RMSE);
     
     system("pause");
}

void predict(int *original_data,int *off_set,int current_cust,int current_movie,int real_rating)
{
     int label_start;
     int label_stop;
     label_start=off_set[current_cust];
     
     find_the_label(off_set,current_cust,&label_stop);
     
     int i=0;
     int *potential_set;//to store the ID who has watched the predicted movie
     potential_set=malloc(sizeof(int)*user_number);
     int k=1;
     
     while (i<=max_ID)//
     {
           if (off_set[i]!=0 && i!=current_cust)//
           {
                 int section_start;
                 int section_stop;
                 
                 section_start=off_set[i];
                 find_the_label(off_set,i,&section_stop);
                 int j;
                 j=section_start;
                 
                 while (j<=section_stop)
                 {
                       if (original_data[j]==current_movie)
                       {
                              potential_set[k]=i;//i is the customer id,and put the i in the array
                              k++;
                              break;
                       }
                       j=j+2;
                 }
           }
           i++;
     }
     int superset_array[user_number];
     int subset_array[user_number];
     int disjoint_array[user_number];
     
     int n=1;
     if (n<k)
     {
         int superset=0;
         int subset=0;
         int disjoint=0;
         predicted_movie_number++;
         
         while (n<k)//check all the potential id, and figure out which one is superset or subset or disjoint
         {
               int compare_id;
               compare_id=potential_set[n];
               
               int section_start;
               int section_stop;
               section_start=off_set[compare_id];
               find_the_label(off_set,compare_id,&section_stop);
               
               int flag=4;//flag can be 1,2,3 represents superset,subset,and disjoint_set
               
               int m;
               m=label_start;
               while (m<=label_stop)
               {
                   int j;
                   j=section_start;
                   while (j<=section_stop)
                   {
                         if (original_data[m]==original_data[j] && flag==4)
                         {
                              flag=1;
                              break;
                              }
                         else if (original_data[m]==original_data[j] && flag==1)
                         {
                              flag=1;
                              break;
                              }
                         else if (original_data[m]==original_data[j] && flag!=1)
                         {
                              flag=2;
                              break;
                              }
                         j=j+2;
                   }
                   if (j>section_stop && flag>=3)
                         flag=3;
                   else if (j>section_stop && flag==1)
                         flag=2;
                   else if (j>section_stop && flag==2)
                         flag=2;
                   m=m+2;
               }
               
               if (flag==1)
               {
                   
                   superset++;
                   superset_array[superset]=compare_id;
                   }
               else if (flag==2)
               {
                   
                   subset++;
                   subset_array[subset]=compare_id;
                   }
               else if (flag==3)
               {
                   
                   disjoint++;
                   disjoint_array[disjoint]=compare_id;
                   }    
               n++;
         }
         if (superset>0)//the customer who has superset
         {
               FILE *file_super;
               file_super=fopen("superset_file.txt","a");
               superset_number++;
               
               fprintf(file_super,"for customer %d,he has these superset\n",current_cust);
               /*
               int j;
               for (j=1;j<=superset;j++)
                   fprintf(file_test,"%d---",superset_array[j]);
               fprintf(file_test,"\n");
               */
               float *similarity_array;
               int *rating_array;
               float total_similarity=0.0;
               similarity_array=malloc(sizeof(float)*(superset+1));
               rating_array=malloc(sizeof(int)*(superset+1));
               
               int a;
               for (a=1;a<=superset;a++)
               {
                   int compare_start;
                   int compare_stop;
                   int compare_id;
                   
                   compare_id=superset_array[a];
                   compare_start=off_set[compare_id];
                   find_the_label(off_set,compare_id,&compare_stop);
                   
                   int common_movie_number;
                   common_movie_number=(label_stop-label_start+1)/2;
                   float max_distance;
                   max_distance=4*sqrt(common_movie_number)+0.0001;//the 0.0001 is to prevent max_distance-d=0
                   float distance=0.0;
                   int m;
                   m=label_start;
                   while (m<label_stop)
                   {
                         int n;
                         n=compare_start;
                         while (n<compare_stop)
                         {
                               if (original_data[m]==original_data[n])
                               {
                                       float temp;
                                       temp=original_data[m+1]-original_data[n+1];
                                       temp=temp*temp;
                                       distance=distance+temp;
                                       break;
                               }
                               n=n+2;
                         }
                         m=m+2;
                   }
                   float similarity;
                   similarity=max_distance-sqrt(distance);
                   fprintf(file_super,"user %d,the similarity is %.4f\n",compare_id,similarity);
                   
                   similarity_array[a]=similarity;
                   total_similarity=total_similarity+similarity;
                   
                   int n;
                   n=compare_start;
                   while (n<compare_stop)
                   {
                         if (original_data[n]==current_movie)
                         {
                               rating_array[a]=original_data[n+1];
                               break;
                         }
                         n=n+2;
                   }
               }
               int n;
               float fake_rating=0.0;
               for (n=1;n<=superset;n++)
                   fake_rating=fake_rating + rating_array[n]*similarity_array[n]/total_similarity;
               int predicted_rating;
               predicted_rating=(int)(fake_rating+0.5);
               
               RMSE = RMSE + (real_rating-predicted_rating)*(real_rating-predicted_rating);
               
               FILE *f_p;
               f_p=fopen("prediction_file.txt","a");
               fprintf(f_p,"%d\n",predicted_rating);
               fclose(f_p);
               
         }
         else if (superset==0 && subset>0)//the customer who has subset
         {
               
               FILE *file_sub;
               file_sub=fopen("subset_file.txt","a");
               subset_number++;
               fprintf(file_sub,"for customer %d,he has these subset\n",current_cust);
               /*
               fprintf(file_test,"for customer %d,he has these subset\n",current_cust);
               int j;
               for (j=1;j<=subset;j++)
                   fprintf(file_test,"%d---",subset_array[j]);
               fprintf(file_test,"\n");
               */
               float *distance_array;
               distance_array=malloc(sizeof(float)*(subset+1));
               int *common_movie_array;
               common_movie_array=malloc(sizeof(float)*(subset+1));
               float *similarity_array;
               similarity_array=malloc(sizeof(float)*(subset+1));
               int *rating_array;
               rating_array=malloc(sizeof(int)*(subset+1));
               float total_similarity=0.0;
               int total_commom_movie=0;
               
               int a;
               for (a=1;a<=subset;a++)
               {
                   int compare_start;
                   int compare_stop;
                   int compare_id;
                   
                   compare_id=subset_array[a];
                   compare_start=off_set[compare_id];
                   find_the_label(off_set,compare_id,&compare_stop);
                   
                   int common_movie=0;
                   float distance=0.0;
                   int m;
                   m=label_start;
                   while (m<label_stop)
                   {
                         int n;
                         n=compare_start;
                         while (n<compare_stop)
                         {
                               if (original_data[m]==original_data[n])
                               {
                                     common_movie++;
                                     float temp;
                                     temp=original_data[m+1]-original_data[n+1];
                                     temp=temp*temp;
                                     distance=distance+temp;
                                     break;
                               }
                               n=n+2;
                         }
                         m=m+2;
                   }
                   distance=sqrt(distance/common_movie);
                   total_commom_movie=total_commom_movie+common_movie;
                   
                   distance_array[a]=distance;
                   common_movie_array[a]=common_movie;
                   
                   int n;
                   n=compare_start;
                   while (n<compare_stop)
                   {
                         if (original_data[n]==current_movie)
                         {
                               rating_array[a]=original_data[n+1];
                               break;
                         }
                         n=n+2;
                   }
               }
               int sub_cust_id;
               for (a=1;a<=subset;a++)
               {
                   sub_cust_id=subset_array[a];
                   similarity_array[a]=(4+0.0001-distance_array[a])*common_movie_array[a]/total_commom_movie;
                   fprintf(file_sub,"user %d,the similarity is %.4f\n",sub_cust_id,similarity_array[a]);
                   total_similarity=total_similarity+similarity_array[a];
               }
               
               int n;
               float fake_rating=0.0;
               for (n=1;n<=subset;n++)
                   fake_rating=fake_rating + rating_array[n]*similarity_array[n]/total_similarity;
               int predicted_rating;
               predicted_rating=(int)(fake_rating+0.5);
               
               RMSE = RMSE + (real_rating-predicted_rating)*(real_rating-predicted_rating);
               
               FILE *f_p;
               f_p=fopen("prediction_file.txt","a");
               fprintf(f_p,"%d\n",predicted_rating);
               fclose(f_p);
         }
         else //the customer whose id is disjoint
         {
               FILE *file_disjoint;
               file_disjoint=fopen("disjoint_file.txt","a");
               fprintf(file_disjoint,"for customer %d,he has these disjoint set:\n",current_cust);
               disjoint_number++;
               int *rating_array;
               rating_array=malloc(sizeof(int)*(disjoint+1));
               int total_movie_num;
               total_movie_num=(label_stop-label_start+1)/2;
               int *cust_rating;
               cust_rating=malloc(sizeof(int)*(total_movie_num+1));
               
               int sum_movie_rating=0;
               int sum_cust_rating=0;
               
               int a;
               for (a=1;a<=disjoint;a++)
               {
                   int compare_start;
                   int compare_stop;
                   int compare_id;
                   compare_id=disjoint_array[a];
                   compare_start=off_set[compare_id];
                   find_the_label(off_set,compare_id,&compare_stop);
                   
                   fprintf(file_disjoint,"user %d.\n",compare_id);
                   int n;
                   n=compare_start;
                   while (n<compare_stop)
                   {
                         if (original_data[n]==current_movie)
                         {
                               rating_array[a]=original_data[n+1];
                               sum_movie_rating=sum_movie_rating+rating_array[a];
                               break;
                         }
                         n=n+2;
                   }
               }
               int j;
               int m=1;
               j=label_start+1;
               while (j<=label_stop)
               {
                     cust_rating[m]=original_data[j];
                     sum_cust_rating=sum_cust_rating+cust_rating[m];
                     m++;
                     j=j+2;
                     }
               float stedv_movie,stedv_customer;
               float average_rate_movie;
               float average_rate_cust;
               average_rate_movie=(float)sum_movie_rating/disjoint;
               average_rate_cust=(float)sum_cust_rating/total_movie_num;
               
               float temp=0.0;
               for (j=1;j<=disjoint;j++)
                     temp=temp+(rating_array[j]-average_rate_movie)*(rating_array[j]-average_rate_movie);
               temp=temp/disjoint;
               stedv_movie=sqrt(temp)+0.0001;
               
               temp=0.0;
               for (j=1;j<=total_movie_num;j++)
                     temp=temp+(cust_rating[j]-average_rate_cust)*(cust_rating[j]-average_rate_cust);
               temp=temp/total_movie_num;
               stedv_customer=sqrt(temp)+0.0001;
               
               float fake_rating;
               fake_rating=(average_rate_movie*stedv_customer + average_rate_cust*stedv_movie)/(stedv_customer+stedv_movie);
               int predicted_rating;
               predicted_rating=(int)(fake_rating+0.5);
               
               RMSE = RMSE + (real_rating-predicted_rating)*(real_rating-predicted_rating); 
               /*
               fprintf(file_test,"for customer %d,he has these disjoint\n",current_cust);
               int j;
               for (j=1;j<=disjoint;j++)
                   fprintf(file_test,"%d---",disjoint_array[j]);
               fprintf(file_test,"\n");
               */
               FILE *f_p;
               f_p=fopen("prediction_file.txt","a");
               fprintf(f_p,"%d\n",predicted_rating);
               fclose(f_p);
         }
     }
     else//in this case,because no one had watched the movie which is going to be predicted,so we can not predict the rating for the customer
     {
         FILE *file_empty;
         file_empty=fopen("empty_file.txt","a");
         fprintf(file_empty,"for customer %03d,no one wathced his predicted movie %05d\n",current_cust,current_movie);
         //printf("for customer %03d,no one wathced the movie %05d\n",current_cust,current_movie);
         fclose(file_empty);
         
         FILE *f_p;
         f_p=fopen("prediction_file.txt","a");
         fprintf(f_p,"\n");
         fclose(f_p);
     }
     
     
     /*
     printf("%d has these choices:\n",current_cust);
     int n=1;
     while (n<k)
     {
           printf("%d--",potential_set[n]);
           n++;
           }
     printf("********\n");
     */
     //printf("%d-----%d\n",label_start,label_stop);
}

void find_the_label(int *off_set,int cust_id,int *label_2)
{
     int k=0;
     k=cust_id+1;
     while (off_set[k]==0)
     {
           k++;
     }
     if (k>max_ID)
           *label_2=array_size-1;
     else
           *label_2=off_set[k]-1;
}

