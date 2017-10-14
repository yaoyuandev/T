//2-sat中不能走的决策往另一个决策连一条边
int dfs(int u) {
    if(vis[u^1]) return false;
    if(vis[u]) return true;
    s[cnt++] = u;
    vis[u] = 1;
    for(int i = 0; i < g[u].size(); i++) if(!dfs(g[u][i])) return false;
    return true;
}
bool flag = true;
//一定记得+=2
for(int i = 2; i <= 2 * n; i+= 2) {
    if(!vis[i] && !vis[i + 1]) {
        cnt = 0;
        if(!dfs(i)) {
            while(cnt) vis[s[--cnt]] = 0;
            if(!dfs(i + 1)) {flag = false; break;}
        }
    }
}
