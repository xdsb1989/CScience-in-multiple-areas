#include <stdio.h>
#include<stdlib.h>
struct queue{
       double b;
       char ID;
       int bb;
       struct queue *next_note;
       int a;
       //char c;
       char aa;
}people_list[0];
typedef struct queue  * line,Link;
int main()
{
    int a=0;
    printf("%d\n",sizeof(char));
    printf("%d\n",sizeof(int));
    printf("%d\n",sizeof(float));
    printf("%d\n",sizeof(double));
    printf("%d\n",sizeof(long));
    printf("%d\n",sizeof(struct queue));
    printf("%d\n",sizeof(line));
    printf("%d\n",sizeof(people_list));
    printf("%d\n",sizeof(Link));
    while(a<10)
    {
        int b;
        b++;
        a++;
        }
    b;
    printf("%d   %d",a,b);
    system("pause");
} 
