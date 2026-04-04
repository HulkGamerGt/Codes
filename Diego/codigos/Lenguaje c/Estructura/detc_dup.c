#include <stdio.h>
#define N 10

int main(){
    int arr[N]={1,9,2,3,42,2,14,25,2,95};
    int nums[N]={0};
    int num[N];

    for(int i = 0; i < N ; i++){
        for(int j = 0; j< N; j++){
            if(arr[i] == arr[j]){
                nums[i] += 1;
            }
        }
    }

    for(int i=0 ; i < N ; i++) num[i] = arr[i];

    for(int i =0; i< N; i++){
        for(int j=0 ; j<N; j++){
            if(num[i] == arr[j]){
                num[i] = 0;
            }
        }
    }

    for(int i=0; i< N ; i++){
        if(nums[i] != 1){
            
            printf("%d ", nums[i]);
        }
    }

    return 0;
}