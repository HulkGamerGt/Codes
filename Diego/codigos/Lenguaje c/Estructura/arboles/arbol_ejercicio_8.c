#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    node *leftChild;
    node *rightChild;
}node;

node *root = NULL;

void insert(int data) {
    node *tempNode = (node*) malloc(sizeof(node));
    node *current, *parent;
    tempNode->data = data;
    tempNode->leftChild = NULL;
    tempNode->rightChild = NULL;
    if(root == NULL) root = tempNode;
    else {
        current = root;
        while(1) {
            parent = current;
            if(data < parent->data) {
                current = current->leftChild;
                if(current == NULL) {
                    parent->leftChild = tempNode;
                    return;
                }
            } else {
                current = current->rightChild;
                if(current == NULL) {
                    parent->rightChild = tempNode;
                    return;
                }
            }
        }
    }
}

int find_min() {
    node *current = root;
    if(current == NULL) {
        printf("El arbol esta vacio");
        return -1;
    }
    while(current->leftChild != NULL)
        current = current->leftChild;
    return current->data;
}

int main() {
    int array[7] = {27, 14, 35, 10, 19, 31, 42};
    for(int i = 0; i < 7; i++) insert(array[i]);

    printf("Valor menor: %d\n", find_min());
    return 0;
}