#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll cant, temp1;
    cin >> cant;
    vector< pair<ll, ll> >soldados(cant);


    for(ll i = 0 ; i < cant ;i++){
        cin >> temp1 >> soldados.at(i).second;
        soldados.at(i).first = temp1*-1;
    }
    
    sort(soldados.begin() , soldados.end());

    for(ll i = 0 ; i < cant ;i++){
        cout << (soldados[i].first * -1) << " " << soldados[i].second << "\n";
    }
}