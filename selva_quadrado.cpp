#pragma GCC optimize("O3,unroll-loops,Ofast")
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first
#define se second
#define int long long
#define sz(v) (int)(v.size())
const int maxm=1e5+10;
const int inf=2e9 + 1000;
const int cte=1e9;
int x[maxm], y[maxm];
unordered_map<int,vector<int>>mp;
unordered_map<int,vector<pii>>ord1, ord2;
unordered_map<int,int>mp_id;

int pai[maxm], tam[maxm];
int find(int a){
    if(a==pai[a]) return a;
    return pai[a]=find(pai[a]);
}
void merge(int a, int b){
    a=find(a); b=find(b);
    if(tam[a]>tam[b]) swap(a,b);
    pai[a]=b; tam[b]+=tam[a];
}
signed main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; cin >> n >> m;
    for(int i=1;i<=m;i++) cin >> x[i] >> y[i];
    auto check=[&](int at){
        if(at==0) return true;

        int d=at;

        mp.clear(); mp_id.clear(); ord1.clear(); ord2.clear();

        auto go=[&](int a, int b, int t){
            if(mp_id[b]==0) return;

            int ret=inf;
            vector<pii>ord_a, ord_b;

            if(t==2||t==4){
                swap(a,b);
                if(t==2) t=1;
                if(t==4) t=3;
            }

            if(t==1||t==3){
                if(t==1){
                    ord_a=ord2[a]; ord_b=ord2[b];
                }else{
                    ord_a=ord1[a]; ord_b=ord1[b];
                }
                int best=inf;
                int id=0;
                for(pii p : ord_a){
                    while(id<sz(ord_b)&&ord_b[id].fi<=p.fi){
                        best=min(best,-ord_b[id].fi-ord_b[id].se);
                        id++;
                    }
                    ret=min(ret,best+p.fi+p.se);
                }

                best=inf, id=0;
                reverse(ord_a.begin(),ord_a.end()); reverse(ord_b.begin(),ord_b.end());
                for(pii p : ord_a){
                    while(id<sz(ord_b)&&ord_b[id].fi>=p.fi){
                        best=min(best,ord_b[id].fi-ord_b[id].se);
                        id++;
                    }
                    ret=min(ret,best-p.fi+p.se);
                }
            }

            if(ret<=2*at+1) merge(mp_id[a],mp_id[b]);
        };

        vector<int>cmp;
        for(int i=1;i<=m;i++){
            int auxx=(x[i]/d), auxy=(y[i]/d);
            int aux=auxx*cte+auxy;
            cmp.push_back(aux);
            mp[aux].push_back(i);
            ord1[aux].push_back({x[i],y[i]});
            ord2[aux].push_back({y[i],x[i]});
        }
        sort(cmp.begin(),cmp.end());
        cmp.erase(unique(cmp.begin(),cmp.end()),cmp.end());
        int qtd=sz(cmp);
        for(int i=1;i<=qtd+4;i++) pai[i]=i, tam[i]=1;
        for(int i=0;i<qtd;i++) mp_id[cmp[i]]=i+1, sort(ord1[cmp[i]].begin(),ord1[cmp[i]].end()), sort(ord2[cmp[i]].begin(),ord2[cmp[i]].end());
        for(int i=1;i<=m;i++){
            int auxx=(x[i]/d), auxy=(y[i]/d);
            int aux=auxx*cte+auxy;
            if(y[i]<=at) merge(mp_id[aux],qtd+1); 
            if(x[i]<=at) merge(mp_id[aux],qtd+2);
            if(n-1-y[i]<=at) merge(mp_id[aux],qtd+3);
            if(n-1-x[i]<=at) merge(mp_id[aux],qtd+4);
        }

        for(int i=0;i<qtd;i++){
            for(int s=1;s<=3;s++){
                for(int dx=-s;dx<=s;dx++){
                    int dy=s-abs(dx);
                    int t=-1;
                    if(dx<0) t=1;
                    else if(dx>0) t=2;
                    else if(dy<0) t=3;
                    else t=4;
                    go(cmp[i],cmp[i]+cte*dx+dy,t);
                }
            }
        }

        if(find(qtd+1)==find(qtd+2)||find(qtd+1)==find(qtd+3)||find(qtd+2)==find(qtd+4)||find(qtd+3)==find(qtd+4)) return false;
        return true;
    };
    int l=0, r=2*n;
    while(l<r){
        int mid=(l+r+1ll)/2ll;
        if(check(mid-1)) l=mid;
        else r=mid-1;
    }
    cout << l << '\n';
    return 0;
}
