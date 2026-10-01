#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string letras;
    int let_a, let_b;
    cin >> letras;

    int size = letras.size();

    for(int i =0 ; i < size; i++){
        if(letras[i] == 'A'){
            let_a++;
        }else if(letras[i] == 'B'){
            let_b++;
        }

    }
    if(let_a == 2 || let_b ==2){
        cout << "yes";
    }else{cout<<"No";}
}