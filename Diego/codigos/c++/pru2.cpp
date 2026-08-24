#include <bits/stdc++.h>

using namespace std;

int main() {
    // 1. Desactivamos la sincronización para velocidad extrema
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 2. LEER DIRECTO DEL ARCHIVO (Sin usar comandos de consola)
    // Esto busca "datos.txt" en la misma carpeta y lo mete al 'cin' automáticamente
    if (freopen("datos.txt", "r", stdin) == NULL) {
        // Si el archivo no existe o no se puede abrir, el programa se cierra de forma segura
        return 0; 
    }
    
    // 3. GUARDAR DIRECTO EN UN ARCHIVO DE SALIDA
    // Todo lo que imprimas con 'cout' se guardará en "ordenados.txt" automáticamente
    freopen("ordenados.txt", "w", stdout);

    int n;
    // Leemos la cantidad de números (La primera línea de tu archivo)
    if (!(cin >> n)) return 0; 

    // Reservamos memoria para los 30 millones de datos (~120 MB en RAM)
    vector<int> numeros(n);
    for (int i = 0; i < n; i++) {
        cin >> numeros[i];
    }

    // Ordenamos eficientemente en tiempo O(N log N)
    sort(numeros.begin(), numeros.end());

    // Imprimimos de golpe usando '\n'
    for (int i = 0; i < n; i++) {
        cout << numeros[i] << '\n';
    }

    return 0;
}
