#include <stdio.h>
#include <unistd.h>

int main() {
    void *baslangic = sbrk(0);
    printf("baslangic adresi: %p\n", baslangic);

    void *yeni_adres = sbrk(100);
    printf("sbrk(100) donen adres: %p\n", yeni_adres);

    void *son_durum = sbrk(0);
    printf("son durum: %p\n", son_durum);

    return 0;
}
