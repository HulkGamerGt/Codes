#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<double> precios = {12.5, 45.0, 8.2, 19.9};

    // 1. Sustituir el primer precio por 5.0
    precios.front() = 5.0;

    // 2. Eliminar el último elemento (19.9)
    precios.pop_back(); 

    // 3. Sumar los precios restantes
    double sum_total = 0.0; 
    for (double precio : precios) {
        sum_total += precio;
    }

    cout << "El total es: " << sum_total << "\n";

    return 0;
}