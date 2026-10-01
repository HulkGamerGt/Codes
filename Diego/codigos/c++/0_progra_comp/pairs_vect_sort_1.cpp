#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll cant;
    ll max_personas, max_tiempo, personas_act;
    cin >> cant;
    vector< pair <ll,ll> > eventos;

    for(ll i = 0 ; i < cant ;i++){
        ll llegada, salida;
        cin >> llegada >> salida;
        eventos.push_back({llegada, 1});
        eventos.push_back({salida, -1});
    }
    for(ll i = 0; i < eventos.size() ; i++){
        personas_act = eventos[i].first;
        
    }
    
}    