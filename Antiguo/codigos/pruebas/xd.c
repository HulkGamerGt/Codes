#include<stdio.h>
int main(){ 
    int arr[10] = {23, 5, 98, 65, 3, 55, 73, 9, 21, 85}, *p; 
    p = arr; 
    printf("%d\n", arr[*(p + 7)]); 
    printf("%d\n", *arr + 3); 
    printf("%d\n", *p++); 
    printf("%d\n", *(arr + 1)); 
    printf("%d\n", (*p)++); 
    printf("%d\n", *p); 
    printf("%d\n", *p++); 
    printf("%d\n", *p); 
    return 0; 
}