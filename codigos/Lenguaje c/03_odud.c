#include <stdio.h>
#include <string.h>

// Prototipos funciones dadas:
void inicializa_alfabeto_deco(char *, int *);
void lee_codificado(char *, int *);
void decodificar(char *, char *, char *, int , int );
void primera_etapa_deco(char *, char *, char *, int, int );
void segunda_etapa_deco(char *, char *, char *, int, int );
void graba_mensaje_deco(char *, int);



int main()
{
    char codificado[100];
    char decodificado[100];
    char alfabeto[100];
    int alfabeto_size;
    int N;

    inicializa_alfabeto_deco(alfabeto, &alfabeto_size);
    lee_codificado(codificado, &N);
    decodificar(codificado, decodificado, alfabeto, alfabeto_size, N);
    graba_mensaje_deco(decodificado, N);
    return 0;
}

// Inicializa el alfabeto para decodificar
void inicializa_alfabeto_deco(char *alfabeto, int *alfabeto_size)
{
    const char *abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789!,.:;?-+*/";
    int i = 0;
    while (abc[i])
    {
        alfabeto[i] = abc[i];
        i++;
    }
    alfabeto[i] = '\0';
    *alfabeto_size = i;
}

// Lee el mensaje y la clave desde el archivo codificado
void lee_codificado(char *mensajeCodificado, int *N_clave)
{
    FILE *archivo = fopen("codificado.txt", "r");
    if (!archivo)
    {
        puts("Error: No se pudo abrir el archivo codificado.txt");
        *mensajeCodificado = '\0';
        *N_clave = 0;
        return;
    }

    char linea[200];// el buffer para leer la línea del archivo
    if (fgets(linea, sizeof(linea), archivo))
    {
        int n = 0;
        char *msg = strchr(linea, '#');
        if (msg)
        {
            *msg = '\0';
            sscanf(linea, "%d", &n);
            *N_clave = n;
            msg++;
            char *nl = strchr(msg, '\n');
            if (nl) *nl = '\0';
            strcpy(mensajeCodificado, msg);
        }
        else
        {
            puts("Error: Formato incorrecto en codificado.txt. Se esperaba N#MENSAJE_CODIFICADO");
            *mensajeCodificado = '\0';
            *N_clave = 0;
        }
    }
    else
    {
        puts("Error: Archivo codificado.txt vacio o no se pudo leer.");
        *mensajeCodificado = '\0';
        *N_clave = 0;
    }
    fclose(archivo);
}

// Devuelve el índice de un carácter en el alfabeto, o -1 si no está
int obtener_indice_deco(char caracter, char *alfabeto, int alfabeto_size)
{
    for (int i = 0; i < alfabeto_size; i++)
    {
        if (alfabeto[i] == caracter) return i;
    }
    return -1;
}

// Inversa de la segunda_etapa del codificador: suma N a los múltiplos de 4
void primera_etapa_deco(char *mensajeCodificado, char *resultadoPrimeraEtapaDeco, char *alfabeto, int alfabeto_size, int N) {
    int i = 0;
    while (mensajeCodificado[i])
    {
        if (i % 4 == 0)
        {
            int nueva_pos;
            if ((nueva_pos = obtener_indice_deco(mensajeCodificado[i], alfabeto, alfabeto_size)) != -1)
            {
                nueva_pos += N;
                while (nueva_pos >= alfabeto_size) nueva_pos -= alfabeto_size;
                resultadoPrimeraEtapaDeco[i] = alfabeto[nueva_pos];
            }
            else
            {
                resultadoPrimeraEtapaDeco[i] = mensajeCodificado[i];
            }
        }
        else
        {
            resultadoPrimeraEtapaDeco[i] = mensajeCodificado[i];
        }
        i++;
    }
    resultadoPrimeraEtapaDeco[i] = '\0';
}

// Inversa de la primera etapa del codificador: resta N a todos los caracteres
void segunda_etapa_deco(char *resultadoPrimeraEtapaDeco, char *resultadoSegundaEtapaDeco, char *alfabeto, int alfabeto_size, int N)
{
    int i = 0;
    while (resultadoPrimeraEtapaDeco[i])
    {
        int nueva_pos;
        if ((nueva_pos = obtener_indice_deco(resultadoPrimeraEtapaDeco[i], alfabeto, alfabeto_size)) != -1)
        {
            nueva_pos -= N;
            while (nueva_pos < 0) nueva_pos += alfabeto_size;
            resultadoSegundaEtapaDeco[i] = alfabeto[nueva_pos % alfabeto_size];
        }
        else
        {
            resultadoSegundaEtapaDeco[i] = resultadoPrimeraEtapaDeco[i];
        }
        i++;
    }
    resultadoSegundaEtapaDeco[i] = '\0';
}

// Realiza la decodificación en dos etapas
void decodificar(char *codificado, char *decodificado, char *alfabeto, int alfabeto_size, int N)
{
    char temp[100];
    memset(temp, 0, sizeof(temp));
    memset(decodificado, 0, 100);
    primera_etapa_deco(codificado, temp, alfabeto, alfabeto_size, N);
    segunda_etapa_deco(temp, decodificado, alfabeto, alfabeto_size, N);
}

// Graba el mensaje decodificado y la clave N en decodificado.txt
void graba_mensaje_deco(char *mensajeDecodificado, int N_clave)
{
    FILE *archivo = fopen("decodificado.txt", "w");
    if (!archivo)
    {
        puts("Error: No se pudo crear/abrir el archivo decodificado.txt");
        return;
    }
    fprintf(archivo, "%d#%s\n", N_clave, mensajeDecodificado);
    fclose(archivo);

}