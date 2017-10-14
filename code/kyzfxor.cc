#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1e5 + 10;
vector<pair<int, ll> > g[MAXN];
vector<ll> a;
int vis[MAXN];
ll dis[MAXN];
ll b[60];
int n, m;
void dfs(int u, ll d) {
    vis[u] = 1;
    dis[u] = d;
    for(int i = 0; i < g[u].size(); i++) {
        int v = g[u][i].first;
        if(vis[v]) a.push_back(d^g[u][i].second^dis[v]);
        else dfs(v, dis[u]^g[u][i].second);
    }
}
int main() {
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int u, v;
        ll w;
        scanf("%d%d%lld", &u, &v, &w);
        g[u].push_back(make_pair(v, w));
        g[v].push_back(make_pair(u, w));
    }
    dfs(1, 0);
    for(int i = 0; i < a.size(); i++) {
        for(int j = 40; j >= 0; j--) {
            if(a[i] & (1LL << j)) {
                if(!b[j]) {b[j] = a[i]; break;}
                else a[i]^=b[j];
            }
        }
    }
    ll ans = dis[n];
    for(int i = 40; i >= 0; i--) ans = min(ans, ans^b[i]);
    cout << ans << endl;
}
