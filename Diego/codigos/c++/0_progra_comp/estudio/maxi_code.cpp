#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll cantidad;
    

    if(cin >> cantidad){
        
        vector<ll> ganador_rondas(cantidad);
        
        for (ll i = 0; i < cantidad; i++){
        
            vector<ll> g_l;
            vector<ll> g_r;

            bool progreso = true;
            
            ll l_montanas, r_montanas;
            cin >> l_montanas >> r_montanas;

            for (ll i = 0; i < l_montanas; i++){
                ll tam_l;
                cin >> tam_l;
                g_l.push_back(tam_l);
            }
            
            for(ll i = 0; i < r_montanas; i++){
                ll tam_r; 
                cin >> tam_r; 
                g_r.push_back(tam_r);
            }

            ll turno=1, ganador = 0, l = 0, r = 0;

            while(progreso){
                if(turno == 1){
                    if(r == r_montanas-1){
                        
                        g_r[r]--;
                        if(g_r.back()== 0){
                            ganador = 1;
                            progreso = false;
                        }
                        
                    }else{
                        g_r[r]--;
                        ll temp=r++;
                        if(g_r[temp]>g_r[r]){
                            r++;
                        }
                    }
                    turno=2;
                    
                }else if(turno == 2){
                    
                    if(l == l_montanas--){

                        g_l[l]--;
                        if(g_l.back()== 0){
                            ganador = 2;
                            progreso = false;
                        }
                        
                    }else{
                        g_l[l]--;
                        ll temp=l++;
                        if(g_l[temp]>g_l[l]){
                            l++;
                        }
                    }
                    turno=1;
                }
            }
            ganador_rondas[i] = ganador;
        }
        for (ll i = 0; i < cantidad; i++) cout << ganador_rondas[i]<<"\n"; 
    }

    return 0;
}