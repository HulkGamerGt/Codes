#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll cant, temp;
    string ubi;

    map< string, set<ll> > ubicaciones;
    
    cin >> cant;
    for(int i = 0; i < cant ; i++){
        cin >> ubi >> temp;
        ubicaciones[ubi].insert(temp);
    }

    for (auto& [region, ids] : ubicaciones) {
        cout << "Región: " << region << "\n";
        cout << "- Total servidores únicos: " << ids.size() << "\n";
        cout << "- Menor ID: " << *ids.begin() << "\n\n";
    }
}