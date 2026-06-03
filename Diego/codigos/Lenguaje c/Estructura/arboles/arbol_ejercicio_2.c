#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *leftChild;
    struct node *rightChild;
}node;

// Raíz del árbol, inicialmente vacía
node *root = NULL;

/* 
   Inserta un nodo en el árbol:
   Si el valor es MENOR que el padre, va a la IZQUIERDA.
   Si el valor es MAYOR (o igual) que el padre, va a la DERECHA.
*/
void insert(int data){
    
    node *tempNode = (node*) malloc(sizeof(node));
    node *current;
    node *parent;
    
    tempNode->data = data;
    tempNode->leftChild = NULL;
    tempNode->rightChild = NULL;
    
    // Si el árbol está vacío, el primer nodo es la raíz
    if(root == NULL){
        root = tempNode;
    }else{
        current = root;
        parent = NULL;
        while(1){
            parent = current;
            // Buscar la posición correcta
            if(data < parent->data){
                current = current->leftChild;
                if(current == NULL){
                    parent->leftChild = tempNode;
                    return;
                }
            }else{
                current = current->rightChild;
                if(current == NULL){
                    parent->rightChild = tempNode; 
                    return;
                }
            }
        }
    }
}

// Recorrido Preorden: Raíz -> Izquierda -> Derecha
void pre_order_traversal(node* root){
    if(root != NULL){
        printf("%d ", root->data);
        pre_order_traversal(root->leftChild);
        pre_order_traversal(root->rightChild);
    }
}

int main() {
    // 1. Definir el arreglo con los datos solicitados
    int array[7] = { 50, 30, 70, 20, 40, 60, 80 };
    int i;

    // 2. Insertar cada elemento del arreglo en el árbol
    for(i = 0; i < 7; i++) {
        insert(array[i]);
    }

    // 3. Mostrar el resultado del recorrido en Preorden
    printf("Preorder traversal: ");
    pre_order_traversal(root);
    printf("\n");

    return 0;
}