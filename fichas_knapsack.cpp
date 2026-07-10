#include<bits/stdc++.h>
using namespace std;
const int maxx=210;
const int inf=1e9+7;
int dp[maxx];
void pre(){
    vector<int>fichas={1,2,5,10};
    for(int i=1;i<maxx;i++) dp[i]=inf;
    for(int i=0;i<maxx;i++)
        for(int x : fichas) if(x+i<maxx) dp[i+x]=min(dp[i+x],dp[i]+1);
    // a complexidade da knapsack fica O(fichas*X)
}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    pre(); // precalcula a knapsack
    int x; cin >> x;
    cout << dp[x] << '\n';
}
