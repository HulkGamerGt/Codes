#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll d_regis, consultas;
    if(cin>> d_regis >>consultas){
        vector<ll> cons(consultas);
        vector<ll> gasto(d_regis);
        for (ll i = 1; i <= d_regis; i++)
        {
            ll temporal;
            cin >>temporal;
            gasto[i-1] = temporal;
        }
        for (ll i = 0; i < consultas; i++)
        {
            ll temp1,temp2;
            cin>>temp1;
            cin>>temp2;
            temp1--;
            temp2--;
            
            for (ll d= temp1; d <= temp2; d++) cons[i]+=gasto[d];
        }
        for (ll i = 0; i <= consultas; i++) cout<<cons[i]<< (i==consultas ? "" : "\n");
    }
    return 0;
}