#include<bits/stdc++.h>
#define ll long long
#define sz(v) (int)(v.size())
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
const ll INF=1e18;
const int maxm=1e5+10;

int rep[maxm];
int find(int a){
    if(a==rep[a]) return a;
    return rep[a]=find(rep[a]);
}
void merge(int a, int b){
    a=find(a); b=find(b);
    rep[a]=b;
}

class FenwickTree{
protected:
    vector<pair<ll,int>>bit;
public:
    FenwickTree(int n){ bit.resize(n+10,{INF,-1}); }
    void add(int x, pair<ll,int> val){
        x++;
        for(int i=x;i<sz(bit);i+=(i&-i)) bit[i]=min(bit[i],val);
    }
    pair<ll,int> query(int x){
        x++;
        pair<ll,int> ret={INF,-1};
        for(int i=x;i>0;i-=(i&-i)) ret=min(ret,bit[i]);
        return ret;
    }
};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ll n, m; cin >> n >> m;
    vector<pair<ll,pii>>arestas;
    ll ans=INF;
    vector<ll>xx(m), yy(m);
    for(int i=0;i<m;i++){
        cin >> xx[i] >> yy[i];
        ans=min(ans,xx[i]+yy[i]+1);
        ans=min(ans,2*(n-1)-xx[i]-yy[i]+1);
    }

    // manhattan mst
    vector<ll>x=xx, y=yy, id;
    for(int r=0;r<4;r++){ // faco line sweep 4 vezes para achar o mais perto nos oitavos (acha dois por vez)
        id.clear();
        for(int i=0;i<m;i++) id.push_back(i);
        auto cmp=[&](int a, int b){
            if(x[a]-y[a]!=x[b]-y[b]) return x[a]-y[a]<x[b]-y[b];
            return y[a]<y[b];
        };  
        sort(id.begin(),id.end(),cmp); // ordenando na diagonal (x-y=k)
        vector<ll>ord_y=y;
        sort(ord_y.begin(),ord_y.end());
        ord_y.erase(unique(ord_y.begin(),ord_y.end()),ord_y.end());
        FenwickTree bit(m+1);

        for(int j=m-1;j>=0;j--){
            int i=id[j];
            int pos=lower_bound(ord_y.begin(),ord_y.end(),y[i])-ord_y.begin();
            pos=(m-1)-pos;
            pair<ll,int>res=bit.query(pos);
            if(res.se!=-1) arestas.push_back({res.fi-x[i]-y[i],{i,res.se}});
            bit.add(pos,{x[i]+y[i],i});
        }

        if((r%2)==0) for(int i=0;i<m;i++) swap(x[i],y[i]);
        else for(int i=0;i<m;i++) x[i]=-x[i];
    }
    for(pair<ll,pii>&p : arestas) p.fi=(p.fi/2)+1;
    for(int i=0;i<m;i++){
        arestas.push_back({min(xx[i],n-1-yy[i])+1,{i,m}});
        arestas.push_back({min(yy[i],n-1-xx[i])+1,{i,m+1}});
    }
    for(int i=0;i<=m+1;i++) rep[i]=i;
    sort(arestas.begin(),arestas.end());
    for(auto[cost,p] : arestas){
        if(cost>=ans) break;
        merge(p.fi,p.se);
        if(find(m)==find(m+1)){ans=cost; break;}
    }
    cout << ans-1 << '\n';
}
