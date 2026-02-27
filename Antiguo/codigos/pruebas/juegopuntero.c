#include <stdio.h>

int main(){

    int c=0;
    printf("1. %d\n", c);
    int a=5;
    printf("2.1 %d\n", c);
    printf("2.2 %d\n", a);
    int *b;
    printf("3.1 %d\n", c);
    printf("3.2 %d\n", a);
    printf("3.3 %d\n", *b);
    b=&a;
    printf("4.1 %d\n", c);
    printf("4.2 %d\n", a);
    printf("4.3 %d\n", *b);
    printf("4.4 %d\n", b);
    c = *b;
    printf("5.1 %d\n", c);
    printf("5.2 %d\n", a);
    printf("5.3 %d\n", *b);
    printf("5.4 %d\n", b);

    *b=6;
    printf("6.1 %d\n", a);
    printf("6.2 %d\n", *b);
    printf("6.3 %d\n", b);
    printf("6.4 %d\n", c);
    printf("6.5 %d\n", *b);
}