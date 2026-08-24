#include <bits/stdc++.h>

using namespace std;
int main(){
    cout<< "ingrese 1 para usar el analizador de palabras, 2 para usar el constructor de frases, 3 para el editor y 0 para salir: ";
    int option;
    cin>>option;
    switch(option){
        case 1: {
            cout<< "ingrese una palabra: ";
            string cadena;
            cin>>cadena;
            cadena.empty() ? cout << "ADVERTENCIA, LA CADENA ESTA VACIA"<<endl : cout<< "la palabra tiene un tamano de: " << cadena.length() << endl;; 
            cout<<"el primer caracter de tu palabra es: " <<cadena.at(0)<< endl <<"y el ultimo caracter es: "<< cadena.at(cadena.length() - 1)<<endl;
            cadena.clear();
            if(!cadena.length()) cout<< "la cadena se vacio exitosamente"; 
            else cout<< "la cadena no se vacio exitosamente";
            break;
        }
        case 2:{
            string frase_c = NULL;
            string frase = NULL;
            bool opt = true;
            while(opt){
                cout<<"ingrese frase: ";
                getline(cin >> ws, frase);
                frase_c.append(frase);
                frase.clear();
                cout<< "su palabra es " <<frase_c<< endl;
                cout<< "quiere agregar otra palabra a su frase? ingrese 1 para si y 0 para no: ";
                cin>>opt;
                if (opt == false) cout<< "su frase final es: " <<frase_c<<endl<<" gracias por usar el programa"<< endl;
            }
            break;
        }
        case 3:{
            string frase = "";
            string temp = "";
            cout<< "ingrese la frase que desea editar: ";
            getline(cin >> ws, temp);
            frase.append(temp);
            temp.clear();
            int opt;
            bool x = true;
            while(x){
                cout<<"ingrese 1 para insertar texto en una posicion especifica"<<endl;
                cout<<"ingrese 2 para buscar una palabra en el texto y borrarla"<<endl;
                cout<<"ingrese 3 para ver el caracter en posicion especifica del texto"<<endl;
                cout<<"ingrese 4 para borrar el texto completo"<<endl;
                cout<<"ingrese 5 para ver el estado actual del texto"<<endl;
                cout<<"ingrese 0 para salir del programa"<<endl;
                cout<<"opcion: ";
                cin>> opt;
                switch(opt){
                    case 1:{
                        cout<< "ingrese la frase a añadir en el texto: "<< endl;
                        getline(cin>>ws, temp);
                        cout<< "ingrese posicion a agregarla(de 0 hasta "<< frase.length() << "):" <<endl ;
                        int pos;
                        cin>> pos;
                        if(pos <= frase.length() -1 || pos > 0){
                            frase.insert(pos, temp);
                            cout<< "LISTO" << endl;
                        } else cout << "la posicion no es valida" << endl << "========================="<<endl;
                        temp.clear();
                        break;
                    }
                    case 2:{
                        cout<< "ingrese palabra a buscar en el texto para borrarla: ";
                        getline(cin>>ws, temp);
                        int pos = frase.find(temp);
                        int pos_t = pos;
                        if(pos == -1) cout << "la palabra no existe en el texto" << endl << "========================="<<endl;
                        else{
                            int z = 1;
                            do{
                                if(frase.at(pos_t) == ' ' || frase.at(pos_t) == '.' || frase.at(pos_t) == ',' || frase.at(pos_t) == ';' || frase.at(pos_t) == ':' || frase.at(pos_t) == '?' || frase.at(pos_t) == '!' || frase.at(pos_t) == '\0'){
                                    z = 0;
                                }else{ 
                                    pos_t++;
                                }
                            } while(z == 1 && pos_t < frase.length());
                            if (pos_t == frase.length()) pos_t--;
                            frase.erase(pos, pos_t);
                            cout<< "LISTO, la palabra fue borrada del texto" << endl << "========================="<<endl;
                        }
                        break;
                    }
                    case 3:{
                        int temp = 0;
                        cout<<"ingrese la posicion del texto en la que quiere analizar el caracter (de 0 hasta "<< frase.length() -1 << ")" << endl;
                        cin >> temp;
                        if (temp < 0 || temp > frase.length() -1 ) cout<<"ERROR, POSICION NO ESTÁ DENTRO DE LOS CARACTERES"<< endl << "========================="<<endl;
                        else{
                            cout<<"el caracter en esa posicion es:"<<frase.at(temp)<<endl<<"========================="<<endl;
                        }
                        break;
                    }
                    case 4:{
                        frase.clear();
                        cout<<"TEXTO LIMPIO"<<endl<<"========================="<<endl;
                        break;
                    }
                    case 5:{
                        cout<< "el estado actual del texto es: "<< frase<< endl <<"========================="<<endl;
                        break;
                    }
                    case 0:{
                        x=false;
                        cout<<"GRACIAS POR USAR EL PROGRAMA"<<endl;
                        break;
                    }
                    default:{
                        cout<<"ERROR, la opcion escogida no es valida, ingrese valores desde 0 hasta 5"<<endl<<"========================="<<endl;
                        break;
                    }
                }
            }
        }
        case 0: {
            cout<< "gracias por usar el programa"<< endl;
            break;
        }
        default: {
            cout<< "opcion invalida, por favor ingrese una opcion valida"<< endl << "=========================" ;
            break;
        }
    }
         
return 0;
}