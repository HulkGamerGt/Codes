#include <stdio.h>

void valorab(int a);

int main()
{
    int num=0;
    printf("numero:");
    scanf("%d", &num);
    valorab(num);
    return 0;
}

void valorab(int a)
{   
    int b=0;
    if(a<0){
        b = (a*-1);
        printf("el valor absoluto es: %d\n", b);
    }else{
        printf("el valor absoluto es: %d\n", a);
    }
}