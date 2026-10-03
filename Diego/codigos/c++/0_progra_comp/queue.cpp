#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll tam;
    cin >> tam;
    queue<ll>cola;
    vector<ll> colita;

    for(int i = 1; i <= tam ;i++){
        cola.push(i);
    }

    while(cola.size() > 1){
        colita.push_back(cola.front());
        cola.pop();
        cola.push(cola.front());
        cola.pop();
    }
    cout << "Descartadas:";
    for(int i = 0; i < colita.size() ; i++){
        cout<<" "<<colita.at(i);
    }
    cout << "\n"<<"Restante: " << cola.front();
}