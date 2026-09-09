#include <stdio.h>
#include <unistd.h>

struct Blok
{
    int boyut;
    int bos_mu;
    struct Blok *sonraki;
};

int main()
{

    struct Blok *ilk_blok = sbrk(sizeof(struct Blok) + 100);
    ilk_blok->boyut = 100;
    ilk_blok->bos_mu = 0;
    ilk_blok->sonraki = NULL;
    printf("%d\n", ilk_blok->boyut);
    printf("%d\n", ilk_blok->bos_mu);
    printf("%p\n", ilk_blok->sonraki);
    return 0;
}
