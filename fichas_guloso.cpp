#include<bits/stdc++.h>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int x; cin >> x;
    int resp=0;
    // pegando a maior qtd de fichas, depois vendo o que sobra
    resp+=x/10; /*qtd de 10*/x%=10; /*vendo o que sobra*/
    resp+=x/5; x%=5;
    resp+=x/2; x%=2; 
    resp+=x;
    cout << resp << '\n';
}
