struct events{
       char event[5];
       char start[5];
       int Duration;
       int unique_num;
       char judge_name[10];
       int case_position;
       bool case_bit[6];
}*events_list;

struct attnory{
       char name_attnory[10];
       char startday[5];
       int duration;
       int unique_num;
       int aviable_position;
       bool *attnory_bit;
       int *store_array;
       struct attnory *next_time;
};
struct attnory *attnory_list;
typedef struct attnory *Link_avaiable_time;

int attnory_num=0,case_num;

readfile(FILE *f)
{
      char ch;
      int judge_num=0;
      while (!feof(f))
      {
            
            ch=fgetc(f);
            if (ch=='\n')
                judge_num++;
            else if (ch=='*')
                break;
      }
      while (!feof(f))
      {
            ch=fgetc(f);
            if (ch=='\n')
                attnory_num++;
      }
      attnory_num--;
      rewind(f);
      
      events_list = malloc(sizeof(struct events)*(judge_num*3+1));
      char temp[10];
      char temp1[10];
      int i=1,j=1,m=1;
      int flag=1;
      while (!feof(f))
      {
            if (flag==1)
            {
                 int n,k;
                 fscanf(f,"%s",temp);
                 if (strcmp(temp , "*****")==0)
                     break;
                 
                 n=strlen(temp);
                 for (k=0;k<n-1;k++)
                     temp1[k]=temp[k];
                 temp1[k]='\0';
                 flag=0;
                 ch=fgetc(f);
            }
            else if (flag==0)
            {
                 if (ch!='\n')
                 {
                     fscanf(f,"%s %s %d",events_list[j].event,events_list[j].start,&events_list[j].Duration);
                     strcpy(events_list[j].judge_name,temp1);
                     int unique;
                     unique=get_unique(events_list[j].start,events_list[j].Duration);
                     events_list[j].unique_num=unique;
                     events_list[j].case_position=get_position(unique);
                     int a,b;
                     a=unique/10;
                     b=unique%10;
                     int l;
                     for (l=0;l<=5;l++)
                         events_list[j].case_bit[l]=0;
                     for (l=a;l<a+b;l++)
                         events_list[j].case_bit[l]=1;
                     j++;
                     ch=fgetc(f);
                 }
                 else if (ch=='\n')
                 {
                     flag=1;
                 }
            }
      }
      case_num=j-1;
      
      attnory_list=malloc(sizeof(struct attnory)*(attnory_num+1));
      i=1;
      Link_avaiable_time current;
      while (!feof(f))
      {
            
            if (flag==1)
            {
                 int n,k;
                 fscanf(f,"%s",temp);
                 n=strlen(temp);
                 for (k=0;k<n-1;k++)
                     temp1[k]=temp[k];
                 temp1[k]='\0';
                 strcpy(attnory_list[i].name_attnory , temp1);
                 
                 flag=0;
                 ch=fgetc(f);
                 
                 attnory_list[i].store_array=malloc(sizeof(int)*6);
                 attnory_list[i].attnory_bit=malloc(sizeof(bool)*6);
                 int x;
                 for (x=0;x<=5;x++)
                 {
                     attnory_list[i].attnory_bit[x]=0;
                     attnory_list[i].store_array[x]=0;
                 }
                 
                 current=&attnory_list[i];
                 current->next_time=NULL;
            }
            else if (flag==0)
            {
                 if (ch!='\n')
                 {
                     Link_avaiable_time newptr;
                     newptr=malloc(sizeof(struct attnory));
                     fscanf(f,"%s %d",newptr->startday,&newptr->duration);
                     newptr->next_time=NULL;
                     int unique;
                     unique=get_unique(newptr->startday,newptr->duration);
                     newptr->unique_num=unique;
                     newptr->aviable_position=get_position(unique);
                     current->next_time=newptr;
                     current=newptr;
                     //printf("%d ---position %d unique %d\n",i,current->aviable_position,current->unique_num);
                     ch=fgetc(f);
                 }
                 else if (ch=='\n')
                 {
                     flag=1;
                     i++;
                 }
            }
      }
      attnory_num=i-1;    
}

int get_unique(char *start,int duration)
{
      int a;
      int unique;
      if (strcmp(start,"Mon")==0)
           a=1;
      else if (strcmp(start,"Tue")==0)
           a=2;
      else if (strcmp(start,"Wed")==0)
           a=3;
      else if (strcmp(start,"Thu")==0)
           a=4;
      else if (strcmp(start,"Fri")==0)
           a=5;
      unique=a*10+duration;
      return unique;
}

int get_position(int unique)
{
      int i=1;
      int position[]={0,11,12,13,14,15,21,22,23,24,31,32,33,41,42,51};
      while (unique!=position[i])
           i++;
      return i;
}

int get_number(int index)
{
      int position[]={0,11,12,13,14,15,21,22,23,24,31,32,33,41,42,51};
      return position[index];
}
