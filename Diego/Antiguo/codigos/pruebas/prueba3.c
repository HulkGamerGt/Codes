
/*CLASES*/

#include <stdio.h>

int main() {
    int tabla[8]={2,3,4,5,6,7,8,9};
    int num;
    int i=0;
    int o=0;
    printf("Elige que tabla quieres ver(del 2 al 9): ");
    scanf("%d", &num);
    for (i=0; i < 8; i++) {
        o = num * tabla[i];

        printf("%d x %d = %d\n", num, tabla[i], o);
    }
}
