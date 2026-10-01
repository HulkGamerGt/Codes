#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n;
    ll digito=0;
    ll num[3];
    cin >> n;

    for(ll i = 0; i < 3; i++){
        num[i] = n % 10;
        if(num[i] == 1) digito++;
        n /= 10;
    }
    cout << digito;
}