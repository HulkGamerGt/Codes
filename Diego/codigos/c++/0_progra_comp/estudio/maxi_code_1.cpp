#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
    ll n, m;
    cin >> n >> m;
    
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    
    vector<ll> b(m);
    for (ll i = 0; i < m; i++) cin >> b[i];
    
    // Total de golpes que puede soportar la cordillera de cada uno
    ll vida_bea = a[0] + n - 1;
    ll vida_ver = b[0] + m - 1;
    
    // CORRECCIÓN: Como Bea ataca primero, si las vidas son iguales, 
    // Bea destruye la última opción de Ver antes de que Ver pueda responder.
    if (vida_bea >= vida_ver) {
        cout << 1 << "\n";
    } else {
        cout << 2 << "\n";
    }
}

int main() {
    // Optimización de flujo de entrada/salida para Codeforces
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}





/*

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
    ll n, m;
    cin >> n >> m;
    
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    
    vector<ll> b(m);
    for (ll i = 0; i < m; i++) cin >> b[i];
    
    ll pos_a = 0, pos_b = 0;
    int turno = 1; // 1 = Turno de Bea, 2 = Turno de Ver
    
    while (true) {
        // Si un gigante está en el suelo (0) y no hay más montañas enfrente, pierde.
        if (a[pos_a] == 0 && pos_a == n - 1) {
            cout << 2 << "\n";
            return;
        }
        if (b[pos_b] == 0 && pos_b == m - 1) {
            cout << 1 << "\n";
            return;
        }
        
        // Simulación matemática del combate en las posiciones actuales
        if (turno == 1) {
            // Bea ataca la montaña de Ver
            if (a[pos_a] >= b[pos_b]) {
                // Bea tiene suficiente o más vida que la montaña de Ver
                ll pasos = b[pos_b];
                a[pos_a] -= pasos;
                b[pos_b] = 0;
                // El juego avanza 'pasos * 2 - 1' turnos. 
                // Si 'pasos' es impar, el turno cambia a 2. Si es par, se mantiene en 1.
                turno = (pasos % 2 == 1) ? 2 : 1;
            } else {
                // Ver sobrevive a esta colina de Bea
                ll pasos = a[pos_a];
                b[pos_b] -= pasos;
                a[pos_a] = 0;
                turno = (pasos % 2 == 1) ? 2 : 1;
            }
        } else {
            // Ver ataca la montaña de Bea
            if (b[pos_b] >= a[pos_a]) {
                ll pasos = a[pos_a];
                b[pos_b] -= pasos;
                a[pos_a] = 0;
                turno = (pasos % 2 == 1) ? 1 : 2;
            } else {
                ll pasos = b[pos_b];
                a[pos_a] -= pasos;
                b[pos_b] = 0;
                turno = (pasos % 2 == 1) ? 1 : 2;
            }
        }
        
        // Movimiento de los gigantes según las reglas del problema:
        // "Si la montaña de enfrente es más alta que en la que está parado, salta"
        if (pos_a + 1 < n && a[pos_a + 1] > a[pos_a]) {
            pos_a++;
        }
        if (pos_b + 1 < m && b[pos_b + 1] > b[pos_b]) {
            pos_b++;
        }
    }
}

int main() {
    // Optimización de I/O para programación competitiva
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}

*/
/*#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll cantidad;

    if(cin >> cantidad){ 
        vector<int> ganador(cantidad);
        
        for (ll i = 0; i < cantidad; i++){
            ll l_montanas, r_montanas;
            cin >> l_montanas >> r_montanas;     
            
            vector<ll> g_l(l_montanas);
            vector<ll> g_r(r_montanas);
            
            // Leemos la lista izquierda
            for (ll j = 0; j < l_montanas; j++){
                cin >> g_l[j];
            }
                
            // Leemos la lista derecha
            for(ll j = 0; j < r_montanas; j++){
                cin >> g_r[j];
            }
            
            ll pos_l = 0, pos_r = 0;
            
            // El ciclo continúa mientras ambos ejércitos tengan montañas vivas
            while(pos_l < l_montanas && pos_r < r_montanas){
                
                if (g_l[pos_l] > g_r[pos_r]){
                    // La izquierda aplasta a la derecha
                    g_l[pos_l] -= g_r[pos_r];
                    pos_r++;
                } 
                else if(g_r[pos_r] > g_l[pos_l]){
                    // La derecha aplasta a la izquierda
                    g_r[pos_r] -= g_l[pos_l];
                    pos_l++;
                }
                else {
                    // Empate: ambas tienen la misma fuerza y se destruyen mutuamente
                    pos_l++;
                    pos_r++;
                }
            }
            
            // Si el puntero izquierdo llegó al final, el jugador 1 se quedó sin montañas.
            if (pos_l == l_montanas) {
                ganador[i] = 2; // Gana el jugador 2 (derecha)
            } else {
                ganador[i] = 1; // Gana el jugador 1 (izquierda)
            }
        }
        
        // Imprimimos los resultados de todas las rondas al final
        for(auto gan : ganador){
            cout << gan << "\n";
        }
    }
    return 0;
}*/