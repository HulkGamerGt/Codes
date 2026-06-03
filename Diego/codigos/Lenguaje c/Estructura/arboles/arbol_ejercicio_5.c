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

void pre_order_traversal(node* root) {
    if(root != NULL) {
        printf("%d ", root->data);
        pre_order_traversal(root->leftChild);
        pre_order_traversal(root->rightChild);
    }
}

void in_order_traversal(node* root) {
    if(root != NULL) {
        in_order_traversal(root->leftChild);
        printf("%d ", root->data);
        in_order_traversal(root->rightChild);
    }
}

void post_order_traversal(node* root) {
    if(root != NULL) {
        post_order_traversal(root->leftChild);
        post_order_traversal(root->rightChild);
        printf("%d ", root->data);
    }
}

int main() {
    int array[7] = {27, 14, 35, 10, 19, 31, 42};
    for(int i = 0; i < 7; i++) insert(array[i]);

    printf("Preorder traversal: ");
    pre_order_traversal(root);
    printf("\nInorder traversal: ");
    in_order_traversal(root);
    printf("\nPostorder traversal: ");
    post_order_traversal(root);
    printf("\n");
    return 0;
}