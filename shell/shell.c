#include<stdio.h>

int main()
{
   char intput[100];

   while(1)
   {
    printf("$:");
    fgets(intput, sizeof(intput), stdin);
    printf("%s\n", intput);
   }
   return 0;
}
