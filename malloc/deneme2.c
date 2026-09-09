#include <stdio.h>
#include <unistd.h>

int main()
{
   struct Blok {
    int boyut;
    int bos_mu;
   };
   struct Blok deneme;
   deneme.boyut = 50;
   deneme.bos_mu = 1;

   printf("%d", deneme.boyut);
   printf("%d", deneme.bos_mu);
   return 0;
}
