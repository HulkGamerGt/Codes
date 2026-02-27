/* Identificación del autor
Nombre: Diego Solis Rojas
Fecha: 18/08/2025
Tema:El siguiente codigo ordena de forma ascendente, mostrandolo en pantalla. 
    Despues imprime un mensaje y ordena el nuevo texto ingresado, dejandolo de forma ascendente
*/

#include <stdio.h>
#include <string.h>

/* Prototipos de funciones */
void ordenar(char *texto);
void ingresarnuevotexto(char *textonuevo);

int main(){

    char texto[] = "FZJYQKOMWUXVCPRSTBHLADGNIE";
    char textonuevo[31];
    ordenar(texto);
    printf("Ingrese un texto de maximo 30 caracteres: ");
    ingresarnuevotexto(textonuevo);
    return 0;
}

/* Funcion que ordena un texto de forma ascendente */
void ordenar(char *texto){

    int i=0,j=0;
    int cant = strlen(texto);
    char temp;

    for(i = 0; i < cant; i++){ /* Ordenar texto */
        for(j=0 ; j<i ; j++){
            if(texto[i] < texto[j]){
                temp = texto[i];
                texto[i] = texto[j];
                texto[j] = temp;
            }
        }
    }

    for(i = 0; i < cant; i++){ /* Imprimir texto ordenado */
        printf("%c", texto[i]);
    }
    printf("\n");
}

/* Funcion que permite ingresar un nuevo texto y ordenarlo de manera ascendente */
void ingresarnuevotexto(char *textonuevo){

    int i=0,j=0,k=0;
    char temp;
    char c = getchar();

    while (c != '\n' && k < 30) { /* Ingresar nuevo texto */
        textonuevo[k] = c;
        k++;
        c = getchar(); 
    }
    textonuevo[k] = '\0';


    for(i = 0; i < strlen(textonuevo); i++){ /* Ordenar texto */
        for(j=0 ; j<i ; j++){
            if(textonuevo[i] < textonuevo[j]){
                temp = textonuevo[i];
                textonuevo[i] = textonuevo[j];
                textonuevo[j] = temp;
            }
        }
    }
    for(i = 0; i < strlen(textonuevo); i++){ /* Imprimir texto ordenado */
        printf("%c", textonuevo[i]);
    }
    printf("\n");

}