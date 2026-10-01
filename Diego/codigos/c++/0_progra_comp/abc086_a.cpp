#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n,m;
    cin >> n >> m;
    if((n*m) % 2 == 0){
        cout << "Even";
    }else{
        cout << "Odd";
    }
}