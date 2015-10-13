#include<stdio.h>
#include<math.h>
struct list{
       int a;
       int b;
       struct list *next;
};
struct list *link;
void display(int *);

main()
{
      float a=0.03333,b=3.32;
      float c=1.00001,d=1.0;
      float temp;
      float mile;
      int feet;
      int zhen;
      float xiao;
      
      temp=a*10;
      zhen=temp/1;
      printf("%d\n",zhen);
      xiao=temp-zhen;
      printf("%f\n",xiao);
      mile=(float)zhen/10;
      feet=5280*xiao/10;
      
      if (mile==0)
      printf("%d foot\n",feet);
      else if (feet==0)
      printf("%.1f miles\n",mile);
      else if (mile>0 && feet>0)
      printf("%.1f miles %d foot\n",mile,feet);
      //int b=123;
      a=((a-b)/(c-d));
      printf("%f\n",a);
      /*printf("%f\n",c);
      printf("input the string:");
      gets(ch);
      printf("input the num:");
      scanf("%d",&b);
      printf("string:%s\t%d\n",ch,b);
      */
      int i;
      i=0;
      display(&i);
      printf("%d",i);
      system("pause");
      }

void display(int *i)
{
     if (i==0 || *i==4)
        *i=*i*10;
     else if (*i==3 || *i==5)
        *i=*i*11;  
     else
         *i=*i+8;
}
            
            
            
