#include <stdio.h>
#define N 5
int main(){
    int arr[N] = {1,3,1,3,3};
    int a[N][2];
    int swap, c = 0, z = 0;
    int b = 0;
    for(int i = 0; i < N-1; i++){
        for(int j = i+1; j < N; j++){
            if(arr[i] == arr[j]){
                c++;
                swap = arr[i+c];
                arr[i+c] = arr[j];
                arr[j] = swap;
                
                
            }
        }
        if(c>0){
            a[b][0] = arr[i];
            a[b][1] = c;
            b++;
        }
        i = i + c;
        c = 0;
    }
    for(int i = 0; i < b; i++){
        printf("numero:%d repetido:%d  \n",a[i][0],a[i][1]);
        
    }
    return 0;
}