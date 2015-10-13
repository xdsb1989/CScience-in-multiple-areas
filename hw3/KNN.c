#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define max_ID 999
/*I will set the customer ID as the index in the off_set array.Because generally speaking,
  the user ID will increase continuity,and the gaps will not be too many.So that it's a effective way to store and check.
  */
void predict(int *,int *,int ,int,int);//the main function to calculate the predicted rating
void find_the_label(int *,int ,int *);//using off_set array and customer id,you can get the stop index number in the original_data array

int array_size=0;//the array_size is to store how much data are there in the rating-file
int user_number=0;//to store how many different user_id are there in the rating-file
int neighbor_number=0;//number of the neighbors a customer has
int disjoint_number=0;//number of the disjoint users a customer has
float RMSE;
int top_K;//top_K is to define the k nearest neighbors

main()
{
     int choice;
     printf("please input the choice.\n1 is for toy-file data\n2 is for nf-file data\nchoice=:");
     scanf("%d",&choice);
     
     char file_path_1[20];
     char file_path_2[20];
     if(choice==1)
     {
          strcpy(file_path_1,"toy-rating.txt");
          strcpy(file_path_2,"toy-quiz.txt");
          top_K=2;
     }
     else if(choice==2)
     {
          strcpy(file_path_1,"nf-rating.txt");
          strcpy(file_path_2,"nf-quiz.txt");
          top_K=5;
     }
     
     
     FILE *f1;
     f1=fopen(file_path_1,"r");
     if (f1==NULL)//if can not open the file,stop the program
     {
         printf("OMG,the file is not existed!\n");
         system("pause");
         return 0;
     }
     int off_set[max_ID+1]={0};//set the off_set
     char ch;
     while(!feof(f1))
     {    
         ch=fgetc(f1);
         if (ch=='\n')
            array_size++;
         }
     rewind(f1);//set the file pointer to the beginning position
     array_size=array_size*2+1;//define how many size for the original data array
     int original_data[array_size];//
    
     int i,j;
     int cust_id;//
     int temp_id;//temp_id is to check whether a new customer id is repeated in the previous time
     i=1;
     fscanf(f1,"%d %d %d",&cust_id,&original_data[i],&original_data[i+1]);
    
     off_set[cust_id]=1;
     temp_id=cust_id;
     i=i+2;
     while (!feof(f1))
     {
          fscanf(f1,"%d %d %d",&cust_id,&original_data[i],&original_data[i+1]);//store the rating file data
          if (temp_id!=cust_id)
          {
               off_set[cust_id]=i;//once we get a new id,just set the id as the index in the off_set array
               temp_id=cust_id;
          }
          i=i+2;
     }
     fclose(f1);
     for (j=0;j<=max_ID;j++)
        if (off_set[j]!=0)
           user_number++;//figure out how many different users are there in the rating file
     FILE *f2;
     int quiz_size=0;
     f2=fopen(file_path_2,"r");
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
            quiz_size++;//each line in the quiz file means another movie need to predict
         }
     rewind(f2);
     
     int predicted_movie_number;
     predicted_movie_number=quiz_size;//the number of the movies are going to be predicted equals to the lines the quiz file has
     quiz_size=quiz_size*3+1;//get the real size in the quiz_data array
     int quiz_data[quiz_size];
     i=1;
     while(!feof(f2))
     {
         fscanf(f2,"%d %d %d",&quiz_data[i],&quiz_data[i+1],&quiz_data[i+2]);//store the quiz file data
         i=i+3;
         }
     fclose(f2);
     
     i=1;
     int current_cust;// the current customer ID
     int current_movie;// the current movie ID
     
     FILE *file;
     file=fopen("prediction_file.txt","w");
     fclose(file);
     file=fopen("neighbor_file.txt","w");
     fclose(file);
     file=fopen("disjoint_file.txt","w");
     fclose(file);
     file=fopen("unwatch_file.txt","w");
     fclose(file);
     
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
     RMSE = RMSE/predicted_movie_number;//calculate the rating
     RMSE = sqrt(RMSE);//calculate the rating
     printf("the number of customers with neighbor:%d\n",neighbor_number);
     printf("number of customers with neither supersets nor subsets:%d\n",disjoint_number);
     printf("the RMSE is:%.4f\n",RMSE);
     
     system("pause");
}

void predict(int *original_data,int *off_set,int current_cust,int current_movie,int real_rating)
{
     int label_start;//find the start index for the current customer
     int label_stop;//find the ending index for the current customer
     label_start=off_set[current_cust];
     
     find_the_label(off_set,current_cust,&label_stop);
     
     int i=0;
     int *potential_set;//to store the ID who has watched the predicted movie
     potential_set=malloc(sizeof(int)*user_number);
     int k=1;
     
     while (i<=max_ID)//
     {
           if (off_set[i]!=0 && i!=current_cust)//if off_set[i]!=0,that means here is a start
           {
                 int section_start;
                 int section_stop;
                 
                 section_start=off_set[i];
                 find_the_label(off_set,i,&section_stop);//get the ending index for the comparing user
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
     int neighbor_array[user_number];//put the neighbor user id in the neighbor_array
     int disjoint_array[user_number];//put the disjoint user id in disjoint_array
     
     int n=1;
     if (n<k)
     {
         int neighbor=0;//how many users are neighbor
         int disjoint=0;//how many users are disjoint set
         
         while (n<k)//check all the potential id, and figure out which one is superset or subset or disjoint
         {
               int compare_id;
               compare_id=potential_set[n];
               
               int section_start;
               int section_stop;
               section_start=off_set[compare_id];
               find_the_label(off_set,compare_id,&section_stop);
               
               int flag=0;//flag can be 1 or 0,to detect the user style
               
               int m;
               m=label_start;
               int j;
               j=section_start;
               
               while (m<=label_stop)//this loop is to choose all the movies from current customer,the time complexity is O(n)
               {
                   while (j<=section_stop && original_data[m]>=original_data[j])//this loop is to choose all the movies from the comparing customer
                   {
                         if (original_data[m]==original_data[j])//once find a common movie,set it as a neighbor
                         {
                              flag=1;
                              break;
                              }
                         j=j+2;
                   }
                   if (flag==1)//find a common,break out the loop
                         break;
                   m=m+2;
               }
               
               if (flag==1)
               {
                   neighbor++;
                   neighbor_array[neighbor]=compare_id;
                   }
               else//if no common movie,set it as dijoint set
               {
                   disjoint++;
                   disjoint_array[disjoint]=compare_id;
                   }    
               n++;
         }
         if (neighbor>0)//the customer who has neighbors
         {
               int K;
               if (neighbor>top_K)//if the neighbor is over the number of top_K,then use top_K,otherwise use the number of neighbor
                    K=top_K;
               else 
                    K=neighbor;
               
               neighbor_number++;//increase the number of the customer who has a neighbor
               FILE *file_neighbor;
               file_neighbor=fopen("neighbor_file.txt","a");
               fprintf(file_neighbor,"for customer %03d,he has these top_%d neighbors\n",current_cust,K );
               
               float *distance_array;//store all the user's distance
               distance_array=malloc(sizeof(float)*(neighbor+1));
               int *common_movie_array;//store how many common movies for each pair
               common_movie_array=malloc(sizeof(float)*(neighbor+1));
               float *similarity_array;//similarity array is to store all the similarities
               similarity_array=malloc(sizeof(float)*(neighbor+1));
               int *rating_array;//rating array is to store the rating from different customer for the movie which is going to be predicted
               rating_array=malloc(sizeof(int)*(neighbor+1));
               float total_similarity=0.0;//summary all the similarities
               int total_commom_movie=0;//summary all the common movies
               
               int a;
               for (a=1;a<=neighbor;a++)//this loop is to choose each selected pair
               {
                   int compare_start;//the comparing customer's start index
                   int compare_stop;//the comparing customer's ending index
                   int compare_id;////the comparing customer's ID
                   
                   compare_id=neighbor_array[a];
                   compare_start=off_set[compare_id];
                   find_the_label(off_set,compare_id,&compare_stop);
                   
                   int common_movie=0;
                   float distance=0.0;
                   int m;
                   m=label_start;
                   int i;
                   i=compare_start;
                   while (m<label_stop)//this loop is to choose each movie in the current customer,the time complexity is O(n)
                   {
                         while (i<compare_stop && original_data[m]>=original_data[i])//this loop is to choose each movie in the comparing customer
                         {
                               if (original_data[m]==original_data[i])
                               {
                                     common_movie++;//increase the common movie
                                     float temp;
                                     temp=original_data[m+1]-original_data[i+1];//calculate the distance
                                     temp=temp*temp;
                                     distance=distance+temp;
                                     break;
                               }
                               i=i+2;
                         }
                         m=m+2;
                   }
                   distance=sqrt(distance/common_movie);
                   total_commom_movie=total_commom_movie+common_movie;
                   
                   distance_array[a]=distance;//store all the different distance in the distance_array[]
                   common_movie_array[a]=common_movie;//store all the different common movies in the common_movie_array[]
                   
                   int n;
                   n=compare_start;
                   while (n<compare_stop)
                   {
                         if (original_data[n]==current_movie)
                         {
                               rating_array[a]=original_data[n+1];//store all the rating in the array
                               break;
                         }
                         n=n+2;
                   }
               }
               int sub_cust_id;
               for (a=1;a<=neighbor;a++)
                   similarity_array[a]=(4+0.0001-distance_array[a])*common_movie_array[a]/total_commom_movie;//get all the similarity in the array
               
               int j,i;
               int top_rating_array[K+1];//choose top K neighbors
               float top_similarity_array[K+1];//choose top K neighbors
               int top_neighbor_id[K+1];//choose top K neighbors

               for (j=1;j<=K;j++)//this loop is to find out the top K nearest neighbors
               {
                   float temp_similarity=0.0;
                   int index;
                   for (i=1;i<=neighbor;i++)
                   {
                       if (similarity_array[i]>temp_similarity)
                       {
                            temp_similarity=similarity_array[i];
                            index=i;
                       }
                   }
                   top_similarity_array[j]=similarity_array[index];
                   total_similarity=total_similarity + top_similarity_array[j];
                   top_rating_array[j]=rating_array[index];
                   top_neighbor_id[j]=neighbor_array[index];
                   similarity_array[index]=0.0;//set the original similarity_array[index] as zero,because it has been calculated
               }
               
               int n;
               float fake_rating=0.0;
               for (n=1;n<=K;n++)
               {
                   fprintf(file_neighbor,"user %03d,the similarity is %.4f\n",top_neighbor_id[n],top_similarity_array[n]);
                   fake_rating=fake_rating + top_rating_array[n]*top_similarity_array[n]/total_similarity;
                   }
               
               int predicted_rating;
               predicted_rating=(int)(fake_rating+0.5);//change the float to int
               
               RMSE = RMSE + (real_rating-predicted_rating)*(real_rating-predicted_rating);//get the current summary of the RMSE
               
               FILE *f_p;
               f_p=fopen("prediction_file.txt","a");
               fprintf(f_p,"%d\n",predicted_rating);//output the predicted rating score in the prediction file
               fclose(f_p);
         }
         else //the customer whose id is disjoint
         {
               FILE *file_disjoint;
               file_disjoint=fopen("disjoint_file.txt","a");
               fprintf(file_disjoint,"for customer %d,he has these disjoint set:\n",current_cust);
               disjoint_number++;//the number of customer who has disjoint set increase one
               int *rating_array;//the rating array is to store the movie score which other one has watched
               rating_array=malloc(sizeof(int)*(disjoint+1));
               int total_movie_num;//the total number of the movie that the customer wathced
               total_movie_num=(label_stop-label_start+1)/2;//using the start index and the ending index to calculate the total movies
               int *cust_rating;//the cust_rating array is to store the customer's watched movies
               cust_rating=malloc(sizeof(int)*(total_movie_num+1));
               
               int sum_movie_rating=0;
               int sum_cust_rating=0;
               
               int a;
               for (a=1;a<=disjoint;a++)
               {
                   int compare_start;//the other user's ending index
                   int compare_stop;//the other user's start index
                   int compare_id;//for each pair,compare_id is to store the other comparing user's id
                   compare_id=disjoint_array[a];//get the disjoint customers' id
                   compare_start=off_set[compare_id];
                   find_the_label(off_set,compare_id,&compare_stop);
                   
                   fprintf(file_disjoint,"user %d.\n",compare_id);
                   int n;
                   n=compare_start;
                   while (n<compare_stop)
                   {
                         if (original_data[n]==current_movie)
                         {
                               rating_array[a]=original_data[n+1];//get the different rating for the current_movie
                               sum_movie_rating=sum_movie_rating+rating_array[a];//summary of the predicted movie score
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
                     cust_rating[m]=original_data[j];//get the current customer's rating
                     sum_cust_rating=sum_cust_rating+cust_rating[m];//sumary of the customer's rating
                     m++;
                     j=j+2;
                     }
               float stedv_movie,stedv_customer;//calculate the standard deviation of the movie score,the stancard deviation of the customer
               float average_rate_movie;
               float average_rate_cust;
               average_rate_movie=(float)sum_movie_rating/disjoint;//get the average socre
               average_rate_cust=(float)sum_cust_rating/total_movie_num;
               
               float temp=0.0;//to store the tempory value of the standard deviation
               for (j=1;j<=disjoint;j++)
                     temp=temp+(rating_array[j]-average_rate_movie)*(rating_array[j]-average_rate_movie);
               temp=temp/disjoint;
               stedv_movie=sqrt(temp)+0.0001;
               
               temp=0.0;
               for (j=1;j<=total_movie_num;j++)
                     temp=temp+(cust_rating[j]-average_rate_cust)*(cust_rating[j]-average_rate_cust);
               temp=temp/total_movie_num;
               stedv_customer=sqrt(temp)+0.0001;
               
               float fake_rating;//using the formula to figure out the rating.
               fake_rating=(average_rate_movie*stedv_customer + average_rate_cust*stedv_movie)/(stedv_customer+stedv_movie);
               int predicted_rating;
               predicted_rating=(int)(fake_rating+0.5);//change the rating into int style
               
               RMSE = RMSE + (real_rating-predicted_rating)*(real_rating-predicted_rating);//get the current summary of the RMSE

               FILE *f_p;
               f_p=fopen("prediction_file.txt","a");
               fprintf(f_p,"%d\n",predicted_rating);//output the predicted rating score in the prediction file
               fclose(f_p);
         }
     }
     else//in this case,because no one had watched the movie which is going to be predicted,
     {   //so that we just use the average socre of the movies that the customer has watched.  
         FILE *file_empty;
         file_empty=fopen("unwatch_file.txt","a");
         fprintf(file_empty,"for customer %03d,no one watched movie %05d,the predicted rating is:",current_cust,current_movie);
         
         int total_movie_num;
         total_movie_num=(label_stop-label_start+1)/2;//calculate how many movies that the customer has watched
         int total_score=0;
         int j;
         j=label_start+1;
         
         while (j<=label_stop)
         {
             total_score=total_score+original_data[j];//get the summary of all the movie rating
             j=j+2;
         }
         float average_rate_cust;
         average_rate_cust=(float)total_score/total_movie_num;//get the average score
         int predicted_rating;
         predicted_rating=(int)(average_rate_cust+0.5);//change the float number to the int number
         fprintf(file_empty,"%d\n",predicted_rating);//output the predicted rating to the unwatch file
         fclose(file_empty);
         
         RMSE = RMSE + (real_rating-predicted_rating)*(real_rating-predicted_rating);//get the current summary of the RMSE
         
         FILE *f_p;
         f_p=fopen("prediction_file.txt","a");
         fprintf(f_p,"%d\n",predicted_rating);//output the predicted rating in the prediction file
         fclose(f_p);
     }
}

void find_the_label(int *off_set,int cust_id,int *label_2)
{
     int k=0;
     k=cust_id+1;//in the off_set,if i is not the customer id,then off_set[i] will be 0.
     while (off_set[k]==0)//once the off_set[k] is not 0,that means we get the next customer id,the next customer id equals k
     {
           k++;
     }
     if (k>max_ID)
           *label_2=array_size-1;//if k>max_ID then the stop position would be the whole main array_size-1.
     else
           *label_2=off_set[k]-1;//if k<max_ID then the stop position would be the next customer start position-1
}
