
#include <stdio.h>

void limpiar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}   

int main() {

    char n;
    char vocales[5]={97,'e','i','o','u'};
    char letras[20];
    int j=0;
    int c=0;
    int k=0;


    for(j=0; j < 20; j++)
    {
        printf("Dime una letra: ");
        scanf("%c",&n);
        limpiar_buffer();
        letras[j] = n;
    }
    for (j=0; j < 20; j++)
    {
        for(k=0; k < 5; k++)
        {
            if(vocales[k] == letras[j] )
            {
                c++;
            }

        }
    }

    printf("\n");
    printf("las vocales ingresadas fueron %d",c);

    return 0;
}