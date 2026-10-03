#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll cant;
    cin >> cant;
    vector< pair <ll,ll> > eventos;

    for(ll i = 0 ; i < cant ;i++){
        ll llegada, salida;
        cin >> llegada >> salida;
        eventos.push_back({llegada, 1});
        eventos.push_back({salida, -1});
    }
    
    sort(eventos.begin(), eventos.end());

    ll personas_actuales = 0;
    ll max_personas = 0;
    ll tiempo_del_pico = 0;

    for(ll i = 0; i < eventos.size() ; i++){
        personas_actuales += eventos[i].second;

        if(personas_actuales > max_personas){
            max_personas = personas_actuales;
            tiempo_del_pico = eventos[i].first;
        }
    }
    
    cout << tiempo_del_pico << " " << max_personas << "\n";
    
    return 0;
}