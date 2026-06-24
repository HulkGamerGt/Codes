#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100   // Tamaño máximo para la cola del BFS

// ------------------------------------------------------------
// 1. Estructura de la lista de adyacencia
// ------------------------------------------------------------
struct AdjNode {
    int dest;
    struct AdjNode* next;
};

struct Graph {
    int numVertices;
    struct AdjNode** adjList;   // array de listas enlazadas
    bool* visitado;             // para marcar visitados en recorridos
};

// ------------------------------------------------------------
// 2. Funciones básicas del grafo
// ------------------------------------------------------------
struct AdjNode* crearNodo(int dest) {
    struct AdjNode* nuevo = (struct AdjNode*)malloc(sizeof(struct AdjNode));
    nuevo->dest = dest;
    nuevo->next = NULL;
    return nuevo;
}

struct Graph* crearGrafo(int vertices) {
    struct Graph* grafo = (struct Graph*)malloc(sizeof(struct Graph));
    grafo->numVertices = vertices;
    grafo->adjList = (struct AdjNode**)malloc(vertices * sizeof(struct AdjNode*));
    grafo->visitado = (bool*)malloc(vertices * sizeof(bool));

    for (int i = 0; i < vertices; i++) {
        grafo->adjList[i] = NULL;
        grafo->visitado[i] = false;
    }
    return grafo;
}

// Añadir arista (no dirigida)
void addArista(struct Graph* grafo, int src, int dest) {
    // src -> dest
    struct AdjNode* nuevo = crearNodo(dest);
    nuevo->next = grafo->adjList[src];
    grafo->adjList[src] = nuevo;

    // dest -> src (por ser no dirigido)
    nuevo = crearNodo(src);
    nuevo->next = grafo->adjList[dest];
    grafo->adjList[dest] = nuevo;
}

void imprimirGrafo(struct Graph* grafo) {
    for (int v = 0; v < grafo->numVertices; v++) {
        printf("Vértice %d:", v);
        struct AdjNode* temp = grafo->adjList[v];
        while (temp) {
            printf(" -> %d", temp->dest);
            temp = temp->next;
        }
        printf("\n");
    }
}

void liberarGrafo(struct Graph* grafo) {
    for (int i = 0; i < grafo->numVertices; i++) {
        struct AdjNode* temp = grafo->adjList[i];
        while (temp) {
            struct AdjNode* aux = temp;
            temp = temp->next;
            free(aux);
        }
    }
    free(grafo->adjList);
    free(grafo->visitado);
    free(grafo);
}

// ------------------------------------------------------------
// 3. BFS (recorrido en anchura) - usando cola estática
// ------------------------------------------------------------
void BFS(struct Graph* grafo, int inicio) {
    // Reiniciar visitados
    for (int i = 0; i < grafo->numVertices; i++)
        grafo->visitado[i] = false;

    int cola[MAX];
    int frente = 0, final = 0;

    grafo->visitado[inicio] = true;
    cola[final++] = inicio;

    printf("BFS desde %d: ", inicio);
    while (frente < final) {
        int actual = cola[frente++];
        printf("%d ", actual);

        struct AdjNode* temp = grafo->adjList[actual];
        while (temp) {
            int vecino = temp->dest;
            if (!grafo->visitado[vecino]) {
                grafo->visitado[vecino] = true;
                cola[final++] = vecino;
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

// ------------------------------------------------------------
// 4. DFS (recorrido en profundidad) - recursivo
// ------------------------------------------------------------
void DFSUtil(struct Graph* grafo, int v) {
    grafo->visitado[v] = true;
    printf("%d ", v);

    struct AdjNode* temp = grafo->adjList[v];
    while (temp) {
        int vecino = temp->dest;
        if (!grafo->visitado[vecino])
            DFSUtil(grafo, vecino);
        temp = temp->next;
    }
}

void DFS(struct Graph* grafo, int inicio) {
    // Reiniciar visitados
    for (int i = 0; i < grafo->numVertices; i++)
        grafo->visitado[i] = false;

    printf("DFS desde %d: ", inicio);
    DFSUtil(grafo, inicio);
    printf("\n");
}

// ------------------------------------------------------------
// 5. Función principal (ejemplo completo)
// ------------------------------------------------------------
int main() {
    // Crear un grafo con 6 vértices (0 al 5)
    struct Graph* grafo = crearGrafo(6);

    // Añadir aristas (no dirigidas)
    addArista(grafo, 0, 1);
    addArista(grafo, 0, 2);
    addArista(grafo, 1, 3);
    addArista(grafo, 1, 4);
    addArista(grafo, 2, 4);
    addArista(grafo, 3, 4);
    addArista(grafo, 3, 5);

    printf("=== LISTA DE ADYACENCIA ===\n");
    imprimirGrafo(grafo);
    printf("\n");

    // Recorridos
    BFS(grafo, 0);
    DFS(grafo, 0);

    // Liberar memoria
    liberarGrafo(grafo);

    return 0;
}