#include <stdio.h>
#define N 6

int main(){

    int arr[N]={1, -2, 3, -4, 1, 4};
    int temp;
    for(int i = 0; i < N; i++){
        if((i % 2 == 0) && (arr[i] < 0)){
            for(int j = i+1; j < N+1; j++){
                if(arr[j]>=0){
                    temp = arr[j];
                    arr[j] = arr[i];
                    arr[i] = temp;
                    break;
                }
            }
        }else if((i % 2 != 0) && (arr[i] >= 0)){
            for(int j = i+1; j < N; j++){
                if(arr[j] < 0){
                    temp = arr[j];
                    arr[j] = arr[i];
                    arr[i] = temp;
                    break;
                }
            }
        }
    }
    for(int i=0; i<N;i++){
        printf("%d ",arr[i]);  
    }

    return 0;
}