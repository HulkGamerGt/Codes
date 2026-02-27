#include <stdio.h>
#include <string.h>

// Prototipos funciones dadas:
void lee_original(char *, int *);
void inicializa_alfabeto(char *);
void codificar(char *, char *, char *, int);
void graba_mensaje(char *, int);
void primera_etapa(char *, char *, char *, int);
void segunda_etapa(char *, char *, char *, int);

//Funcion principal:
int main()
{
    char original[100];    
    char alfabeto[100];    
    char codificado[100]; 
    int N;                 

    lee_original(original, &N);
    inicializa_alfabeto(alfabeto);
    codificar(original, codificado, alfabeto, N);
    graba_mensaje(codificado, N);
    return 0;
}

//Lee el mensaje y el valor N dentro del archivo texto original:
void lee_original(char *mensajeOriginal, int *N_clave)
{
    FILE *archivo = fopen("original.txt", "r");
    if (!archivo)
    {
        puts("Error: No se pudo abrir el archivo original.txt");
        *mensajeOriginal = '\0';
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

            // Elimina salto de línea en caso que haya:
            char *nl = strchr(msg, '\n');
            if (nl) *nl = '\0';
            strcpy(mensajeOriginal, msg);
        }
        else
        {
            puts("Error: Formato incorrecto en original.txt. Se esperaba N#MENSAJE");
            *mensajeOriginal = '\0';
            *N_clave = 0;
        }
    }
    else
    {
        puts("Error: Archivo original.txt vacio o no se pudo leer.");
        *mensajeOriginal = '\0';
        *N_clave = 0;
    }
    fclose(archivo);
}

// Inicia el alfabeto ingles usado para codificar y decodificar:
void inicializa_alfabeto(char *alfabeto)
{
    const char *abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789!,.:;?-+*/";
    int i = 0;
    while (abc[i])
    {
        alfabeto[i] = abc[i];
        i++;
    }
    alfabeto[i] = '\0';
}

// Busca un carácter en el alfabeto y devuelve su posición (-1 si no está):
int obtener_indice(char caracter, char *alfabeto)
{
    char *ptr = strchr(alfabeto, caracter);
    if (ptr)
        return (int)(ptr - alfabeto);
    return -1;
}

// suma N posiciones a cada carácter del mensaje:
void primera_etapa(char *mensajeOriginal, char *resultadoPrimeraEtapa, char *alfabeto, int N)
{
    int i = 0; 
    int alf_len = strlen(alfabeto);

    while (mensajeOriginal[i])
    {
        int idx = obtener_indice(mensajeOriginal[i], alfabeto);
        resultadoPrimeraEtapa[i] = (idx != -1) ? alfabeto[(idx + N) % alf_len] : mensajeOriginal[i];
        i++;
    }
    resultadoPrimeraEtapa[i] = '\0';
}

// Resta N posiciones (en este caso son 6) a caracteres en posiciones múltiplos de 4:
void segunda_etapa(char *resultadoPrimeraEtapa, char *resultadoSegundaEtapa, char *alfabeto, int N)
{
    int i = 0;
    int alf_len = strlen(alfabeto);
    
    while (resultadoPrimeraEtapa[i])
    {
        if (i % 4 == 0)
        {
            int idx = obtener_indice(resultadoPrimeraEtapa[i], alfabeto);
            if (idx != -1)
            {
                int nueva_pos = idx - N;
                while (nueva_pos < 0) nueva_pos += alf_len;
                resultadoSegundaEtapa[i] = alfabeto[nueva_pos % alf_len];
            }
            else
            {
                resultadoSegundaEtapa[i] = resultadoPrimeraEtapa[i];
            }
        }
        else
        {
            resultadoSegundaEtapa[i] = resultadoPrimeraEtapa[i];
        }
        i++;
    }
    resultadoSegundaEtapa[i] = '\0';
}

// Función que coordina las dos etapas de codificación: 
void codificar(char *original, char *codificado, char *alfabeto, int N)
{
    char temp[100];
    memset(temp, 0, sizeof(temp));
    memset(codificado, 0, 100);
    primera_etapa(original, temp, alfabeto, N);
    segunda_etapa(temp, codificado, alfabeto, N);
}

// Guarda el mensaje codificado en un archivo txt:
void graba_mensaje(char *mensajeCodificado, int N)
{
    // Intenta abrir el archivo en modo escritura:
    FILE *archivo = fopen("codificado.txt", "w");
    if (!archivo)
    {
        puts("Error: No se pudo crear/abrir el archivo codificado.txt");
        return;
    }
    fprintf(archivo, "%d#%s\n", N, mensajeCodificado);
    fclose(archivo);
}
