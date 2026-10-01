#include <iostream>
#include <vector>

void procesarTemperaturas(std::vector<double>& temps) {
    // 1. Agregar la nueva temperatura
    temps.push_back(25.5); 

    // 2. Mostrar la primera y la última temperatura
    std::cout << "Primera temperatura: " << temps.front() << " °C\n"; 
    std::cout << "Última temperatura: " << temps.back() << " °C\n"; 

    // 3. Mostrar el tamaño total
    std::cout << "Total de lecturas: " << temps.size() << "\n"; 
}

int main() {
    std::vector<double> lecturas = {18.2, 20.1, 22.4};
    procesarTemperaturas(lecturas);
    return 0;
}