#include<stdio.h>
#include<string.h>
main()
{
FILE *fp;
char c;
//String str[]={0};
fp=fopen("toy-friends.txt","r");
while((c=fgetc(fp))!=EOF)
{
    
    printf("%c",c);
}
fclose(fp);
system("pause");
}
