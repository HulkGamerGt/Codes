#include <bits/stdc++.h>
using namespace std;

int main(){
    int option;
    int n,n1;
    cout << "Bienvenido a una calculadora, necesitare 2 numeros cuando te lo pida";

    do{
        cout << "Ingrese un numero";
        cin >> n;
        cout << '/n'<< "Ingrese el 2do numero";
        cin >> n1;
        cout <<'/n' << "Ingrese la operacion hay que realizar: ";
        menu;
        cin >> option;
        switch(option){

            case 1:

            case 2:

            case 3:

            case 4:

            default:
        }

    }while(option != n);

    return 0;
}

void menu(){
    cout << "1.Logaritmo,  2.Raiz,  3.Potencia, 4.";
    cout << '/n' << "Ingrese una opcion :";
}